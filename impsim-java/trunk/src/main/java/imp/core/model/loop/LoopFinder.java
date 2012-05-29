/**
 * LoopFinder.java
 * May 11, 2011
 */
package imp.core.model.loop;

import imp.core.exceptions.BodyNotFoundException;
import imp.core.exceptions.LoopException;
import imp.core.model.Axis;
import imp.core.model.ElementMap;
import imp.core.model.Model;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

import Jama.Matrix;

/**
 * This class is used to find the kinematic loops.
 * 
 * @author workmanjz
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class LoopFinder {

	/**
	 * The model this loop finder will operate on.
	 */
	private Model model;

	/**
	 * Creates a new loop finder on the given model.
	 * 
	 * @param model The model to create a loop finder for.
	 */
	public LoopFinder(Model model) {
		this.model = model;
	}

	/**
	 * Check that each loop is consistent with the others.
	 * 
	 * @param loop Current loop matrix.
	 * @param nJoint The number of joints.
	 * @return A new loop matrix.
	 */
	private Matrix checkLoops(Matrix loop, int nJoint) {
		int nLoops = loop.getRowDimension();

		Matrix loopInteraction;
		boolean done = false;
		// keep loop checking until all inconsistencies are resolved
		while (!done) {
			// calculate the loop interaction matrix
			loopInteraction = loop.times(loop.transpose());

			// this will check each loop for consistency with the other loops.
			columnLoop: for (int i = 0; i < nLoops; i++) { // i is the current loop being checked
				for (int j = 0; j < i; j++) { // compare to each other loop: j
					if (this.getIntFromMatrix(loopInteraction, i, j) == 0) { // no interaction
						continue;
					} else if (this.getIntFromMatrix(loopInteraction, i, j) > 0) { // interact in same direction
						while (this.getIntFromMatrix(loopInteraction, i, j) >= 0) {
							j++;
							if (j == i) { // interacts with all loops correctly, check next loop
								if (i == nLoops - 1) {
									done = true;
								}
								continue columnLoop; // advance outer loop i- check the next loop
							}
						}
					} else if (this.getIntFromMatrix(loopInteraction, i, j) < 0) { // interact in opposite direction
						while (this.getIntFromMatrix(loopInteraction, i, j) <= 0) {
							j++;
							if (j == i) {
								for (int k = 0; k < nJoint; k++) { // interacts with all loops in opposite direction,
																	// flip direction
									loop.set(i, k, -loop.get(i, k));
								}
								break columnLoop; // break out of for loop and recalculate interaction matrix
							}
						}
					}

					// loop interacts with multiple loops in different directions
					// recombine to resolve inconsistent interaction
					double temp = 0;
					int loopNumber = 0;
					for (int x = 0; x < i; x++) {
						if (this.getIntFromMatrix(loopInteraction, i, j) < temp) {
							temp = loopInteraction.get(i, x);
							loopNumber = x;
						}
					}
					for (int x = 0; x < nJoint; x++) {
						double value = loop.get(i, x) + loop.get(loopNumber, x);
						loop.set(i, x, value);
					}
					break columnLoop; // recalculate interaction matrix and test again
				}
				if (i == nLoops - 1) {
					done = true;
				}
			}
		}

		// remove any loops contained within other loops
		for (int i = 0; i < nLoops; i++) { // loop being compared
			for (int j = 0; j < nLoops; j++) { // loop comparing to
				if (i != j) { // dont check a loop against itself
					boolean swap = true;
					for (int k = 0; k < nJoint; k++) {
						// check if the loop has any unique parts
						if (this.getIntFromMatrix(loop, j, k) != 0 && this.getIntFromMatrix(loop, j, k) != this.getIntFromMatrix(loop, i, k)) {
							swap = false;
							break;
						}
					}

					if (swap) { // loop is not unique so remove it
						for (int k = 0; k < nJoint; k++) {
							double value = loop.get(i, k) - loop.get(j, k);
							loop.set(i, k, value);
						}
					}
				}
			}
		}

		return loop;
	}

	/**
	 * Create loop objects for each of the loops.
	 * 
	 * @param loops The matrix with loops.
	 * @param nLoops The number of loops.
	 * @param nJoints The number of joints.
	 * @throws BodyNotFoundException Thrown if a body was not found in the model.
	 * @return A list of loops.
	 */
	private List<Loop> createLoops(Matrix loops, int nLoops, int nJoints) throws BodyNotFoundException {
		List<Loop> finalLoops = new LinkedList<Loop>();
		// iterate through each loop
		for (int i = 0; i < nLoops; i++) {
			List<Joint> joints = new LinkedList<Joint>();

			// check if each joint is in the loop
			for (int x = 0; x < nJoints; x++) {
				int orientation = this.getIntFromMatrix(loops, i, x);

				if (orientation > 0) { // if joint is going through loop in its defined direction
					joints.add(this.getJointFromNumber(x));
				} else if (orientation < 0) { // if joint is going through loop in opposite direction
					Joint joint = this.getJointFromNumber(x);
					// swap the axes
					Axis temp = joint.getAxisBefore();
					joint.setAxisBefore(joint.getAxisAfter());
					joint.setAxisAfter(temp);
					joint.orientation = -1;
					// change the orientation for all following loops since the axes have already been changed
					for (int j = i; j < nLoops; j++) {
						loops.set(j, x, -loops.get(j, x));
					}
					joints.add(joint);
				}
				// else do nothing since the joint is not in the loop
			}
			finalLoops.add(new Loop(joints, this.model.getGround()));
		}

		return finalLoops;
	}

	/**
	 * This method finds all kinematic loops for the current model.
	 * 
	 * @return A list of loop objects.
	 * @throws LoopException Thrown when a body or joint is not found in the loop.
	 * @throws BodyNotFoundException Thrown if a body is not found in the model.
	 */
	public List<Loop> findKinematicLoops() throws LoopException, BodyNotFoundException {
		int num = 0;
		ElementMap<Body> bodys = this.model.getBodyStructure();
		ElementMap<Joint> joints = this.model.getJointStructure();
		int nBodys = bodys.size();
		int nJoints = joints.size();
		int nLoops = Math.max(nJoints - nBodys + 1, 0);

		// check that bodies and joints exist
		if (nBodys == 0) {
			throw new LoopException("No bodies found in model.");
		}

		if (nJoints == 0) {
			throw new LoopException("No joints found in model.");
		}
		
		if(nLoops == 0){
			throw new LoopException("No Loops expected in the model.");
		}

		// assign each joint and body a number
		for (Body body : bodys) {
			body.loopIdentNumber = num;
			num++;
		}
		num = 0;
		for (Joint joint : joints) {
			joint.loopIdentNumber = num;
			num++;
		}

		/*
		 * create body/joint incidence matrix Row num = body number Col num = joint number -1 for body before joint 1
		 * for body after joint 0 otherwise
		 */
		Matrix incidenceMatrix = new Matrix(nBodys, nJoints);
		for (Joint joint : joints) {
			int j = joint.loopIdentNumber;
			for (int i = 0; i < nBodys; i++) {
				incidenceMatrix.set(i, j, 0);
			}
			incidenceMatrix.set(joint.getBodyBefore().loopIdentNumber, j, -1);
			incidenceMatrix.set(joint.getBodyAfter().loopIdentNumber, j, 1);
		}

		// calculate the loop and path matrices
		Matrix loop = this.findLoops(this.model.getGround().loopIdentNumber, incidenceMatrix, nBodys, nJoints, nLoops);

		loop = this.checkLoops(loop, nJoints);
		List<Loop> loops = this.createLoops(loop, nLoops, nJoints);
		// check that all joints are contained in loops
		for (Joint j : joints) {
			boolean found = false;
			for (Loop l : loops) {
				if (l.loop.contains(j)) {
					found = true;
				}
			}
			if (!found) {
				throw new LoopException("***Error: Not all joints contained in loops. ***");
			}
		}
		return loops;
	}

	/**
	 * Use breadth first search to find loop candidates.
	 * 
	 * @param groundNumber The reference number for ground node.
	 * @param incidenceMatrix The matrix that represents joint and body connections.
	 * @param nBodies Number of bodies.
	 * @param nJoints Number of joints.
	 * @param nLoops Number of loops.
	 * @return Loop matrix.
	 * @throws LoopException Thrown if an exception occurs when calculating loops.
	 */
	private Matrix findLoops(int groundNumber, Matrix incidenceMatrix, int nBodies, int nJoints, int nLoops) throws LoopException {
		Queue<Integer> queue = new LinkedList<Integer>();
		// create path and loop matrix
		Matrix loop = new Matrix(nLoops, nJoints);
		// create visited array to keep track of visited joints
		boolean[] visited = new boolean[nJoints];
		int[] prevBody = new int[nBodies];
		int[] level = new int[nBodies];
		int[] prevJoint = new int[nBodies];
		int loopNumber = -1;
		int bodiesRemaining = nBodies - 1;
		int currentLevel = 0;
		// initialize arrays for finding paths
		for (int i = 0; i < nBodies; i++) {
			level[i] = 0;
			prevBody[i] = -2;
			prevJoint[i] = -1;
		}
		// initialize the loop matrix to 0
		for (int j = 0; j < nJoints; j++) {
			visited[j] = false;
			for (int i = 0; i < nLoops; i++) {
				loop.set(i, j, 0);
			}
		}
		queue.add(groundNumber);
		prevBody[groundNumber] = -1;
		int currentBody = groundNumber;
		// keep searching until the queue is empty
		while (queue.size() != 0) {
			currentBody = queue.poll();
			currentLevel = level[currentBody] + 1;
			// look for edges incident to current vertex
			for (int j = 0; j < nJoints; j++) {
				if (this.getIntFromMatrix(incidenceMatrix, currentBody, j) != 0) { // check each joint incident to
																					// current joint
					// edge has not been visited yet
					if (visited[j] == false) {
						visited[j] = true;

						// find other vertex of this edge
						for (int i = 0; i < nBodies; i++) {
							if (this.getIntFromMatrix(incidenceMatrix, i, j) != 0 && i != currentBody) {
								// if not yet visited, add to queue
								if (prevBody[i] < -1) {
									queue.add(i);

									// set up tree, predecessor, level, and path
									prevBody[i] = currentBody;
									prevJoint[i] = j;
									level[i] = currentLevel;
									bodiesRemaining--;
									break;
								} else {
									// else vertex is already visited and we have a loop
									try {
										++loopNumber;
										loop.set(loopNumber, j, incidenceMatrix.get(currentBody, j));
										int leaf = i;
										int root = currentBody;

										// create the loop matrix for the current loop
										boolean done = false;
										while (!done) {
											// for level of root less than level of leaf, walk back from leaf to find
											// loop
											if (level[root] < level[leaf]) {
												int joint = prevJoint[leaf];
												loop.set(loopNumber, joint, incidenceMatrix.get(leaf, joint)); // set
																												// interaction
																												// based
																												// on
																												// leaf
																												// and
																												// prev
																												// Joint
												leaf = prevBody[leaf]; // leaf = prevBody
											} else if (level[root] == level[leaf]) {
												while (root != leaf) { // leaf and root on same level, walk back from
																		// each to find loop
													int joint = prevJoint[leaf];
													loop.set(loopNumber, joint, incidenceMatrix.get(leaf, joint));
													leaf = prevBody[leaf];
													joint = prevJoint[root];
													loop.set(loopNumber, joint, -incidenceMatrix.get(root, joint));
													root = prevBody[root];
												}
												done = true;
											} else { // for level[root] > level[leaf], walk back from root to find loop
												int joint = prevJoint[root];
												loop.set(loopNumber, joint, -incidenceMatrix.get(root, joint));
												root = prevBody[root];
											}
										}
									} catch (IndexOutOfBoundsException e) {
										throw new LoopException("*** Error: More than one independent assembly. ***");
									}
								}
							}

						}
					}
				}
			}
		}

		if (bodiesRemaining > 0) {
			throw new LoopException("*** Error: More than one independent assembly. ***");
		} else if (loopNumber + 1 != nLoops) {
			throw new LoopException("*** Error: Incorrect number of loops found. ***");
		}

		// return results
		return loop;

	}

	/**
	 * Used to return the integer value in the matrix for comparison. This is used since the matrix stores the values as
	 * doubles, and they are only ever 0, 1, or -1 and compared to integers in the algorithm.
	 * 
	 * @param mat The incident matrix.
	 * @param i The row index to get the value from.
	 * @param j The column index to get the value from.
	 * @return The value from the matrix at the indices.
	 */
	private int getIntFromMatrix(Matrix mat, int i, int j) {
		return (int) mat.get(i, j);
	}

	/**
	 * Get the joint object attached to the loop identity number.
	 * 
	 * @param i The loop ID number of the joint.
	 * @return The joint object.
	 */
	private Joint getJointFromNumber(int i) {
		Joint joint = null;
		for (Joint j : this.model.getJointStructure()) { // loop through the joints and compare the id number to find
															// the correct one
			if (j.loopIdentNumber == i) {
				joint = j;
				break;
			}
		}
		return joint;
	}
}
