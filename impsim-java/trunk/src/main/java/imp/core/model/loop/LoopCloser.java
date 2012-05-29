package imp.core.model.loop;

import imp.core.Constants;
import imp.core.exceptions.LoopException;
import imp.core.model.elements.Joint;
import imp.core.model.elements.Joint.JVAR;
import imp.core.structures.PositionMatrix;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import Jama.Matrix;
import Jama.SingularValueDecomposition;

/**
 * This class is used to close all of the loops in a model. It uses a jacobian
 * matrix to solve for the joint changes using a QR decompositions for over
 * determined matrices, and a singular value decomposition otherwise.
 * 
 * @author workmanjz - created 10/04/2011
 * @version 1.0
 * 
 */
public class LoopCloser {
	//@formatter:off
	//all the loops to be closed
	private List<Loop> loops;
	//the 0Tn matrices, stored dynamically as we move around the loop
	private List<List<PositionMatrix>> tMatrices;
	//the solution we are trying to get in loop closure
	private List<PositionMatrix> solutions;
	//the original values for the jvars if loop closure cannot converge
	private List<Double> originalJointValues = new ArrayList<Double>();
	//the original body position matrices
	private List<PositionMatrix> originalBodyPositions = new ArrayList<PositionMatrix>();
	//the changes for each jvar in the current iteration of loop closure
	private List<Double> deltaPhiValues;
	//the jvars that changed
	private List<Integer> changedJVARs = new ArrayList<Integer>();
	//list of vars that have been changed already
	private List<Integer> dirtyVars = new ArrayList<Integer>();
	//list of joints that have already been changed
	private List<String> dirtyJoints = new ArrayList<String>();
	//Map of the column numbers for each joint name
	private Map<String, Integer> columnMap = new HashMap<String, Integer>();
	//the number of variables changed in this loop closure
	private int numOfVariables = 0;
	//the current precision for finding a solution
	private double loopClosurePrecision = 0.0001;
	
	/**
	 * Calculate the 0Tn matrices for the joints in each loop
	 * @param saveSolution true if this is the target solution
	 */
	private void calcTMatrices() {
		//for each loop in the model
		for(int n = 0; n < loops.size(); n++){ 
			List<Joint> currentLoop = loops.get(n).getLoop();
			List<PositionMatrix> currentTMatrixList = this.tMatrices.get(n);
			
			//set initial T matrix, this is the transformation 
			currentTMatrixList.set(0, currentLoop.get(0).getAxisBefore().getShapeMatrix().multiply(currentLoop.get(0).getPhiMatrix())); 
			
			//for each joint in the loop, calculate the T Matrix and update the Bodies postion matrix
			for (int i = 1; i < this.loops.get(n).getLoop().size(); i++) { 
				Joint currentJoint = currentLoop.get(i - 1);
				Joint nextJoint = currentLoop.get(i);
				
				//calculate that T matrix, this is T(n-1)* ShapeMatrix to move from this joint to the next * phiMatrix to move to the Axis after the joint
				currentTMatrixList
				.set(i,
						currentTMatrixList.get(i - 1).multiply(
								currentJoint.getAxisAfter().getShapeMatrix().inverse())
								.multiply(nextJoint.getAxisBefore().getShapeMatrix())
									.multiply(nextJoint.getPhiMatrix()));
				

				//Update the bodies position matrix, this is T(n-1)*the inverse shape matrix of the axis after the joint.  
				// It represents the movement of the body with respect to the global coordinate system
				currentJoint.getBodyAfter().setPositionMatrix(currentTMatrixList.get(i-1).multiply(currentJoint.getAxisAfter().getShapeMatrix().inverse()));
			}
		}
	}

	/**
	 * Calculate the Jacobian and Error matrices and come up with the deltaPhi values
	 * @param changedJVARs the jvars which are known
	 */
	private void calcDeltaPhiValues(List<Integer> changedJVARs){
		
		//Map each jvar to its deltaPhiMatrix
		Map<String, PositionMatrix> deltaPhiMatrices = new HashMap<String, PositionMatrix>();
		
		//calculate each delta phi matrix.  Which is T*Q*T-inverse.  Q here represents the Q operator which is defined for each joint.
		for(int n = 0; n < loops.size(); n++){
			List<Joint> currentLoop = loops.get(n).getLoop();
			
			//loop through each joint...
			for(int i = 0; i < currentLoop.size(); i++){
				Joint currentJoint = currentLoop.get(i);
				
				//and each JVAR
				for(JVAR j: currentJoint.getJVARs()){
					//The key for the map is the joint name + the jvar name + the loop number. Ex. J1THETA1
					deltaPhiMatrices.put(currentJoint.getName() + j.name() + n,this.tMatrices.get(n).get(i)
							.multiply(currentLoop.get(i).getQOperator(j)
									.multiply(tMatrices.get(n).get(i).inverse())));
				}
			}
		}
		//calculate the jacobian and error matrix to solve for the other deltaPhi values
		Matrix jacobianMatrix = new Matrix(6*loops.size(), columnMap.size());
		Matrix errorMatrix = new Matrix(6*loops.size(), 1);
		
		int errorColumn = 0;
		//number of deltaPhiMatrices we have checked
		int count = 0; 
		
		//for each loop in the model
		for(int n = 0; n< loops.size(); n++){
			List<Joint> currentLoop = loops.get(n).getLoop();
			
			//for each joint in the loop
			for(int i = 0; i < currentLoop.size(); i++){
				Joint currentJoint = currentLoop.get(i);
				
				//for each jvar in the joint
				for(JVAR j: currentJoint.getJVARs()){
					
					//create the key to get the column, the key is jointname+jvarName, ex. J1THETA
					String key = currentJoint.getName() + j.name();
					PositionMatrix m = deltaPhiMatrices.get(key + n);

					//if this is not a known jvar add its values to the Jacobian Matrix
					if(!changedJVARs.contains(count)){
						jacobianMatrix.set(0 + 6*n, columnMap.get(key), m.get(0, 3));
						jacobianMatrix.set(1 + 6*n, columnMap.get(key), m.get(1, 3));
						jacobianMatrix.set(2 + 6*n, columnMap.get(key), m.get(2, 3));
						jacobianMatrix.set(3 + 6*n, columnMap.get(key), m.get(0, 1));
						jacobianMatrix.set(4 + 6*n, columnMap.get(key), m.get(0, 2));
						jacobianMatrix.set(5 + 6*n, columnMap.get(key), m.get(1, 2));
					}
					//Otherwise add the values to the Error Matrix
					else{
						Matrix tempMatrix = new Matrix(6*loops.size(), 1);
						tempMatrix.set(0 + 6*n, 0, m.get(0, 3));
						tempMatrix.set(1 + 6*n, 0, m.get(1, 3));
						tempMatrix.set(2 + 6*n, 0, m.get(2, 3));
						tempMatrix.set(3 + 6*n, 0, m.get(0, 1));
						tempMatrix.set(4 + 6*n, 0, m.get(0, 2));
						tempMatrix.set(5 + 6*n, 0, m.get(1, 2));
						tempMatrix = tempMatrix.times(-deltaPhiValues.get(changedJVARs.get(errorColumn)));
						errorMatrix = errorMatrix.plus(tempMatrix);
						errorColumn++;
					}		
					count++;
				}
			}
		}
		
		/**solve the system of equations @seeLoopCloser.solve() */
		Matrix deltaPhiResults = solve(jacobianMatrix, errorMatrix); 
		
		//Add each value from the solution matrix to the deltaPhi list
		int jvarNumber = 0;
		
		//for each loop
		for(int n = 0; n< loops.size(); n++){
			List<Joint> currentLoop = loops.get(n).getLoop();
			
			//each joint
			for(int i = 0; i < currentLoop.size(); i++){
				Joint currentJoint = currentLoop.get(i);
				
				//each JVAR
				for(JVAR j: currentJoint.getJVARs()){
					String key = currentJoint.getName() + j.name();
					//if this was not one of the known values then update with the result, the result is in the same row as the column its values were added to
					if(!changedJVARs.contains(jvarNumber)){ 
						deltaPhiValues.set(jvarNumber, deltaPhiResults.get(columnMap.get(key), 0));
					}
					jvarNumber++;
				}
			}
		}
		
		
		
	}
	
	/**
	 * Helper method to solve a matrix with a QR decomp first and then a Singular Value Decomp if that fails
	 * @param jacobianMatrix
	 * @param errorMatrix
	 * @return solution matrix
	 */
	private Matrix solve(Matrix jacobianMatrix, Matrix errorMatrix) {
		Matrix results = null;
		
		//Try to solve using the QR decomposition
		try{
			results = jacobianMatrix.solve(errorMatrix);
		}catch(Exception e){
			//If that does not work then calculate the MoorePenroseInverse and multiple it times the error Matrix
			Matrix Ainv = computeMoorePenroseInverse(jacobianMatrix);
			results = Ainv.times(errorMatrix);
		}		
		return results;
	}
	
	/**
	 * Helper method to calculate the MoorePenroseInverse to solve under constrained matrices
	 * @param x
	 * @return the inverse matrix
	 */
	private Matrix computeMoorePenroseInverse(Matrix x) {
		
		//rank too small
		if (x.rank() < 1)
			return null;
		//if more columns than rows, calculate using the transpose
		if (x.getColumnDimension() > x.getRowDimension())
			return computeMoorePenroseInverse(x.transpose()).transpose();
		
		//Create a new singular value decomposition
		SingularValueDecomposition svdX = new SingularValueDecomposition(x);
		double[] singularValues = svdX.getSingularValues();
		double tol = Math.max(x.getColumnDimension(), x.getRowDimension()) * singularValues[0];
		double[] singularValueReciprocals = new double[singularValues.length];
		
		//calculate the moore penrose inverse matrix
		for (int i = 0; i < singularValues.length; i++)
			singularValueReciprocals[i] = Math.abs(singularValues[i]) < tol ? 0 : (1.0 / singularValues[i]);
		double[][] u = svdX.getU().getArray();
		double[][] v = svdX.getV().getArray();
		int min = Math.min(x.getColumnDimension(), u[0].length);
		double[][] inverse = new double[x.getColumnDimension()][x.getRowDimension()];
		for (int i = 0; i < x.getColumnDimension(); i++)
			for (int j = 0; j < u.length; j++)
				for (int k = 0; k < min; k++)
					inverse[i][j] += v[i][k] * singularValueReciprocals[k] * u[j][k];
		return new Matrix(inverse);
	}
	/**
	 * Update the joint positions after closing the loop
	 * @param vars the loop variables used in closing this loop.
	 * @param loops the collection of loops for this model.
	 * @return the list of closed loops.
	 * @throws LoopException thrown if an exception is encountered during loop closure.
	 */
	public List<Loop> closeLoop(List<LoopVariable> vars, List<Loop> loops) throws LoopException {
		
		//clear all of the maps and lists
		this.loops = loops;
		numOfVariables = vars.size();
		originalJointValues.clear();
		changedJVARs.clear();
		dirtyVars.clear();
		columnMap.clear();
		
		//initialize the lists of deltaPhiValues and tMatrices
		this.tMatrices = new ArrayList<List<PositionMatrix>>(loops.size());
		this.solutions = new ArrayList<PositionMatrix>(loops.size());
		deltaPhiValues = new ArrayList<Double>();
		
		//for each loop in the model add a new list of T-Matrices
		for(int n = 0; n < loops.size(); n++){
			tMatrices.add(new ArrayList<PositionMatrix>());
			solutions.add(new PositionMatrix());
			
			//add one matrix for each joint
			for(int i = 0; i < loops.get(n).getLoop().size(); i++){
				tMatrices.get(n).add(new PositionMatrix());
			}
		}
		int jvarNumber = 0;
		int bodyNumber = 0;
		int column = 0;
		
		//calculate the initial t matrices
		calcTMatrices();
		
		//for each loop  in the model find which values are known and which need to be calculated
		for(int n = 0; n < loops.size(); n++){
			List<Joint> loop = loops.get(n).getLoop();
			
			//check each joint in the loop
			for(int i = 0; i < loop.size(); i++){ 
				Joint currentJoint = loop.get(i);
				
				//save the original body positions in case closure fails
				originalBodyPositions.add(currentJoint.getBodyAfter().getPositionMatrix());
				
				//check each jvar that the joint has
				for(JVAR j: currentJoint.getJVARs()){ 
					//store the original magnitude in case closure fails
					originalJointValues.add(currentJoint.getJointVariable(j).getMagnitude()); 
					deltaPhiValues.add(0.0);
					
					//check each known value to see if it matches the current joint
					for(int k = 0; k < numOfVariables; k++){
						//if this is the jvar we know changed, store that jvar
						if(currentJoint.getName().equals(vars.get(k).getJoint()) && j.equals(vars.get(k).getJvarType())){ 
							changedJVARs.add(jvarNumber);
							deltaPhiValues.set(jvarNumber, vars.get(k).getMagnitude());
							
							//only change the magnitude once(this is used in case a variable is in multiple loops)
							if(!dirtyVars.contains(k)){
								dirtyVars.add(k);
								currentJoint.setJointVariable(j, currentJoint.getJointVariable(j).getMagnitude() + vars.get(k).getMagnitude());
							}
						}
					}
					
					//if the variable is not changed, add it to the column map to be used when creating the jacobian matrix
					if(!changedJVARs.contains(jvarNumber)){
						if(!columnMap.containsKey(currentJoint.getName() + j.name())){
							columnMap.put(currentJoint.getName() + j.name(), column);
							column++;
						}
					}
					jvarNumber++;
				}
				bodyNumber++;
			}
		}
		
		calcDeltaPhiValues(changedJVARs);
		int count = 1;
		//loop until the precision is met or we reach the maximum number of iterations
		while(count <= Constants.LOOP_CLOSURE_ITERATIONS){
			//set the new magnitude for the joint variables
			jvarNumber = 0;
			
			//this is used to only change each joint once(for when a joint is in multiple loops)
			dirtyJoints.clear();
			
			//for each loop
			for(int n = 0; n < loops.size(); n++){
				List<Joint> loop = loops.get(n).getLoop();
				
				//check each joint in the loop
				for(int i = 0; i < loop.size(); i++){ 
					Joint currentJoint = loop.get(i);
					
					//check each JVAR in the joint
					for(JVAR j: currentJoint.getJVARs()){ 
						String key = currentJoint.getName() + j.name();
						
						//if the value was not already known and this joint has not been updated already then add the deltaPhi value to the magnitude
						if(!changedJVARs.contains(jvarNumber)){
							if(!dirtyJoints.contains(key)){
							currentJoint.setJointVariable(j, currentJoint.getJointVariable(j).getMagnitude() + this.deltaPhiValues.get(jvarNumber));
							dirtyJoints.add(key);			
							}
						}
						jvarNumber++;
					}
				}
			}
			
			//calculate the T Matrices to see if the solution has been met
			calcTMatrices();
			

			//check if we have reached the solution, if so break out of the loop
			if(checkPrecision()){
				break;
			}
			
			//calculate new delta phi values with the updated magnitudes
			calcDeltaPhiValues();
			count++;
		}
		
		//could not close loop
		if(!(count <= Constants.LOOP_CLOSURE_ITERATIONS)){
			//reset all joint variable values back to original
			jvarNumber = 0;
			bodyNumber = 0;
			
			//reset each loop
			for(int n = 0; n < loops.size(); n++){
				List<Joint> loop = loops.get(n).getLoop();
				//check each joint in the loop
				for(int i = 0; i < loop.size(); i++){ 
					Joint currentJoint = loop.get(i);
					
					//reset each body position
					currentJoint.getBodyAfter().setPositionMatrix(originalBodyPositions.get(bodyNumber));
					//reset each jvar magnitude
					for(JVAR j: currentJoint.getJVARs()){ 
						currentJoint.setJointVariable(j, originalJointValues.get(jvarNumber));
						jvarNumber++;
					}
					bodyNumber++;
				}
			}
			throw new LoopException("Error: Could not close loop within the set number of iterations");
		}
		return this.loops;
	}

	/**
	 * Used to calculate the jacobian matrix and find the new deltaPhi values
	 * This version of the method creates the error matrix by the difference between the solution and the calculated 0Tn matrix
	 */
	private void calcDeltaPhiValues() {
		
		Map<String, PositionMatrix> deltaPhiMatrices = new HashMap<String, PositionMatrix>();
		
		//calculate each delta phi matrix.  Which is T*Q*T-inverse
		for(int n = 0; n < loops.size(); n++){
			List<Joint> currentLoop = loops.get(n).getLoop();
			
			//each joint
			for(int i = 0; i < currentLoop.size(); i++){
				Joint currentJoint = currentLoop.get(i);
				
				//each jvar
				for(JVAR j: currentJoint.getJVARs()){
					deltaPhiMatrices.put(currentJoint.getName() + j.name() + n,this.tMatrices.get(n).get(i)
							.multiply(currentLoop.get(i).getQOperator(j)
									.multiply(tMatrices.get(n).get(i).inverse())));
				}
			}
		}
		
		//calculate the jacobian matrix to solve for the other deltaPhi values
		Matrix jacobianMatrix = new Matrix(6*loops.size(), columnMap.size());
		Matrix errorMatrix = new Matrix(6*loops.size(), 1);
		int count = 0;
		
		//for each loop set the jacobian matrix with the appropriate delta phi matrix values
		for(int n = 0; n< loops.size(); n++){
			List<Joint> currentLoop = loops.get(n).getLoop();
			
			//for each joint
			for(int i = 0; i < currentLoop.size(); i++){
				Joint currentJoint = currentLoop.get(i);
				
				//for each jvar
				for(JVAR j: currentJoint.getJVARs()){
					String key = currentJoint.getName() + j.name();
					PositionMatrix m = deltaPhiMatrices.get(key + n);

					if(!changedJVARs.contains(count)){
						jacobianMatrix.set(0 + 6*n, columnMap.get(key), m.get(0, 3));
						jacobianMatrix.set(1 + 6*n, columnMap.get(key), m.get(1, 3));
						jacobianMatrix.set(2 + 6*n, columnMap.get(key), m.get(2, 3));
						jacobianMatrix.set(3 + 6*n, columnMap.get(key), m.get(0, 1));
						jacobianMatrix.set(4 + 6*n, columnMap.get(key), m.get(0, 2));
						jacobianMatrix.set(5 + 6*n, columnMap.get(key), m.get(1, 2));
					}
					count++;
				}
			}
		}
		
		//set the error matrix with the new values(Solution-0Tn matrix)
		for(int n = 0; n < loops.size(); n++){
			PositionMatrix tMatrix = tMatrices.get(n).get(tMatrices.get(n).size()-1).multiply(loops.get(n).getLoop().get(loops.get(n).getLoop().size() - 1).getAxisAfter().getShapeMatrix().inverse());
			errorMatrix.set(0 + 6*n, 0, -tMatrix.get(0,3));
			errorMatrix.set(1 + 6*n, 0, -tMatrix.get(1,3));
			errorMatrix.set(2 + 6*n, 0, -tMatrix.get(2,3));
			errorMatrix.set(3 + 6*n, 0, -tMatrix.get(0,1));
			errorMatrix.set(4 + 6*n, 0, -tMatrix.get(0,2));
			errorMatrix.set(5 + 6*n, 0, -tMatrix.get(1,2));
		}
		Matrix deltaPhiResults = solve(jacobianMatrix, errorMatrix); //solve the system of equations

		int jvarNumber = 0;
		
		//for each joint in each loop update the deltaphi values
		for(int n = 0; n< loops.size(); n++){
			List<Joint> currentLoop = loops.get(n).getLoop();
			for(int i = 0; i < currentLoop.size(); i++){
				Joint currentJoint = currentLoop.get(i);
				for(JVAR j: currentJoint.getJVARs()){
					String key = currentJoint.getName() + j.name();
					
					//if this was not one of the known values then update with the result
					if(!changedJVARs.contains(jvarNumber)){ 
						deltaPhiValues.set(jvarNumber, deltaPhiResults.get(columnMap.get(key), 0));
					}
					jvarNumber++;
				}
			}
		}
		
	}

	/**
	 * Check if each of the values in the 0Tn matrix is the same as the solution.
	 * @return true if precision is met
	 */
	private boolean checkPrecision(){
		boolean result = true;
		
		//for each loop check if the 0Tn matrix is equal to the solution
		for(int n = 0; n < loops.size(); n++){
			PositionMatrix m = this.tMatrices.get(n).get(tMatrices.get(n).size()-1).multiply(loops.get(n).getLoop().get(loops.get(n).getLoop().size() - 1).getAxisAfter().getShapeMatrix().inverse());
			if(Constants.compareDoubleEpsilon(m.get(0, 3),0, loopClosurePrecision) &&
					Constants.compareDoubleEpsilon(m.get(1, 3),0, loopClosurePrecision) &&
					Constants.compareDoubleEpsilon(m.get(2, 3),0, loopClosurePrecision) &&
					Constants.compareDoubleEpsilon(m.get(0, 1),0, loopClosurePrecision) &&
					Constants.compareDoubleEpsilon(m.get(0, 2),0, loopClosurePrecision) &&
					Constants.compareDoubleEpsilon(m.get(1, 2),0, loopClosurePrecision)){
				
				//this is used to make sure all loops are closed
				result = result && true;
			}
			else{
				result = result && false;
			}
		}
		return result;
	}
	//@formatter:on
}
