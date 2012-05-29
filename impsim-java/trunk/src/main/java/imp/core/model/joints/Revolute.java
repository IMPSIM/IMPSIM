/**
 * February 11, 2011
 */
package imp.core.model.joints;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.elements.Joint;
import imp.core.observer.Observer;
import imp.core.structures.PositionMatrix;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for holding the data of a revolute joint.
 * 
 * @author edmissonj
 * @review zastrowm (1.0)
 * @edit dykstran Added q operator and getJVAR methods.
 * @edit dykstran Update JavaDoc
 * @version 1.11
 */
public class Revolute extends Joint {

	/**
	 * Creates a new revolute joint.
	 * 
	 * @param name The name of the joint.
	 * @throws NullParameterException Thrown if the name is null.
	 * @throws InvalidParameterException Thrown if the name is empty.
	 */
	public Revolute(String name) throws NullParameterException, InvalidParameterException {
		super(name);
		this.setJointVariable(JVAR.THETA, 0);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.observer.Subject#addObserver(imp.observer.Observer)
	 */
	@Override
	public void addObserver(Observer obv) {
		this.getJointVariable(JVAR.THETA).addObserver(obv);

	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {

		// check if same object
		if (this == otherObject) {
			return true;
		}

		// check if passed object is a Revolute
		if (!(otherObject instanceof Revolute)) {
			return false;
		} else {
			// cast object into revolute for comparison
			Revolute otherRvl = (Revolute) otherObject;
			// return whether EVERY attribute is the same
			return this.name.equals(otherRvl.name) && this.getJointVariablesMap().equals(otherRvl.getJointVariablesMap())
					&& this.getAxisAfter().equals(otherRvl.getAxisAfter()) && this.getAxisBefore().equals(otherRvl.getAxisBefore())
					&& this.loopIdentNumber == otherRvl.loopIdentNumber && this.orientation == otherRvl.orientation;
		}

	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getAccelerationMatrix()
	 */
	@Override
	public PositionMatrix getAccelerationMatrix() {
		// get the second derivative of the revolute phi matrix
		PositionMatrix retVal = this.getSecondDerivativeMatrix(JVAR.THETA, JVAR.THETA);
		// multiply second derivative by the acceleration value of the theta joint variable
		retVal.setJamaMatrix(retVal.getJamaMatrix().times(this.getJointVariable(JVAR.THETA).getAcceleration()));
		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getDerivativeMatrix(imp.model.elements.Joint.JVAR)
	 */
	@Override
	public PositionMatrix getDerivativeMatrix(JVAR variableType) {
		PositionMatrix retVal = new PositionMatrix();

		double cos = Math.cos(this.getJointVariable(JVAR.THETA).getMagnitude());
		double sin = Math.sin(this.getJointVariable(JVAR.THETA).getMagnitude());
		// sets the values to the derivatives of the phi matrix
		retVal.set(0, 0, -sin);
		retVal.set(0, 1, -cos);
		retVal.set(1, 1, -sin);
		retVal.set(1, 0, cos);
		retVal.set(2, 2, 0);
		retVal.set(3, 3, 0);
		/*
		 * <pre> = [ -sin(theta), cos(theta), 0, 0] [ -cos(theta), -sin(theta), 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0] </pre>
		 */
		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getJVARs()
	 */
	@Override
	public List<JVAR> getJVARs() {
		List<JVAR> jVarList = new ArrayList<JVAR>();

		/* A revolute joint may only rotate. */
		jVarList.add(JVAR.THETA);

		return jVarList;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getPhiMatrix()
	 */
	@Override
	public PositionMatrix getPhiMatrix() {
		PositionMatrix retVal = new PositionMatrix();
		double cos = Math.cos(this.getJointVariable(JVAR.THETA).getMagnitude());
		double sin = Math.sin(this.getJointVariable(JVAR.THETA).getMagnitude());
		retVal.set(0, 0, cos);
		retVal.set(0, 1, -sin);
		retVal.set(1, 1, cos);
		retVal.set(1, 0, sin);
		/*
		 * <pre> Q = [ cos(theta), -sin(theta), 0, 0] [ sin(theta), cos(theta), 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0] </pre>
		 */
		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getQOperator(imp.model.elements.Joint.JVAR)
	 */
	@Override
	public PositionMatrix getQOperator(JVAR jvar) {
		/**
		 * From the documentation:
		 * 
		 * <pre>
		 * Q =	[ 0,-1, 0, 0]
		 * 		[ 1, 0, 0, 0]
		 * 		[ 0, 0, 0, 0]
		 * 		[ 0, 0, 0, 0]
		 * 
		 * </pre>
		 */
		PositionMatrix qOperator = new PositionMatrix(new double[][] { { 0, -1, 0, 0 }, { 1, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } });
		return qOperator;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getSecondDerivativeMatrix(imp.model.elements.Joint.JVAR,
	 * imp.model.elements.Joint.JVAR)
	 */
	@Override
	public PositionMatrix getSecondDerivativeMatrix(JVAR thisType, JVAR previousType) {
		PositionMatrix retVal = new PositionMatrix();
		double cos = Math.cos(this.getJointVariable(JVAR.THETA).getMagnitude());
		double sin = Math.sin(this.getJointVariable(JVAR.THETA).getMagnitude());
		// sets the values to the second derivative of the phi matrix
		retVal.set(0, 0, -cos);
		retVal.set(0, 1, sin);
		retVal.set(1, 1, -cos);
		retVal.set(1, 0, -sin);

		retVal.set(2, 2, 0);
		retVal.set(3, 3, 0);

		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getVelocityMatrix()
	 */
	@Override
	public PositionMatrix getVelocityMatrix() {
		// get the derivative of the revolute joint's phi matrix
		PositionMatrix retVal = this.getDerivativeMatrix(JVAR.THETA);
		// multiply derivative matrix by the velocity value
		retVal.setJamaMatrix(retVal.getJamaMatrix().times(this.getJointVariable(JVAR.THETA).getVelocity()));
		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).append(this.getAxisAfter()).append(this.getAxisBefore()).append(this.getBodyBefore())
				.append(this.getBodyAfter()).append(this.getJointVariablesMap()).append(this.loopIdentNumber).append(this.orientation)
				.toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Revolute [name=" + this.name + ", body before=" + this.getBodyBefore() + ", body after=" + this.getBodyAfter() + "]";
	}
}
