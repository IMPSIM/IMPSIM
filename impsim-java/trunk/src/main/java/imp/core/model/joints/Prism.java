/**
 * Prism.java
 * March 10, 2011
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
 * Represents a prism (sliding) joint.
 * 
 * @author dykstran
 * @author hellmerj implemented getPhiMatrix, getDerivativeMatrix, and getVelocityMatrix
 * @review zastrowm (1.2)
 * @edit dykstran Added q operator and getJVAR methods.
 * @edit dykstran Updated JavaDoc
 * 
 * @version 1.31
 */
public class Prism extends Joint {

	/**
	 * Instantiates a new instance of a prism joint.
	 * 
	 * @param name The name of this joint.
	 * @throws NullParameterException If the string is null.
	 * @throws InvalidParameterException Thrown if the name is empty.
	 */
	public Prism(String name) throws NullParameterException, InvalidParameterException {
		super(name);
		this.setJointVariable(JVAR.ZDISPLACEMENT, 0);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.observer.Subject#addObserver(imp.observer.Observer)
	 */
	@Override
	public void addObserver(Observer obv) {
		this.getJointVariable(JVAR.ZDISPLACEMENT).addObserver(obv);

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

		// check if passed object is a Prism
		if (!(otherObject instanceof Prism)) {
			return false;
		} else {
			// cast object into prism for comparison
			Prism otherPsm = (Prism) otherObject;
			// return whether EVERY attribute is the same
			return this.name.equals(otherPsm.name) && this.getJointVariablesMap().equals(otherPsm.getJointVariablesMap())
					&& this.getAxisAfter().equals(otherPsm.getAxisAfter()) && this.getAxisBefore().equals(otherPsm.getAxisBefore())
					&& this.loopIdentNumber == otherPsm.loopIdentNumber && this.orientation == otherPsm.orientation;
		}
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getAccelerationMatrix()
	 */
	@Override
	public PositionMatrix getAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		// second derivative of the prism joint's phi matrix
		PositionMatrix secDeriv = this.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.ZDISPLACEMENT);
		PositionMatrix acc;

		// multiply second derivative by the acceleration value of the joint variable
		acc = new PositionMatrix(secDeriv.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getAcceleration()));

		return acc;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getDerivativeMatrix(imp.model.elements.Joint.JVAR)
	 */
	@Override
	public PositionMatrix getDerivativeMatrix(JVAR variableType) throws NullParameterException, InvalidParameterException {

		// Null Checking
		if (variableType == null) {
			throw new NullParameterException("Joint Variable cannot be null", 0);
		}

		// Type Checking
		if (variableType != JVAR.ZDISPLACEMENT) {
			throw new InvalidParameterException("Prism Joint Variable should be displacement", 0);
		}

		PositionMatrix deriv = new PositionMatrix();

		// derivative of each 1 along diagonal = 0
		deriv.set(0, 0, 0);
		deriv.set(1, 1, 0);
		deriv.set(2, 2, 0);
		deriv.set(3, 3, 0);
		// derivative of joint variable = 1
		deriv.set(2, 3, 1);	// Prism joints' dof is along the local z-axis

		return deriv;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getJVARs()
	 */
	@Override
	public List<JVAR> getJVARs() {
		List<JVAR> jVarList = new ArrayList<JVAR>();

		/* A prism joint is only able to be displaced */
		jVarList.add(JVAR.ZDISPLACEMENT);

		return jVarList;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getPhiMatrix()
	 */
	@Override
	public PositionMatrix getPhiMatrix() {
		PositionMatrix phi = new PositionMatrix();

		// set the displacement along the local z-axis
		phi.set(2, 3, this.getJointVariable(JVAR.ZDISPLACEMENT).getMagnitude());

		return phi;
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
		 * Q =	[ 0, 0, 0, 0]
		 * 		[ 0, 0, 0, 0]
		 * 		[ 0, 0, 0, 1]
		 * 		[ 0, 0, 0, 0]
		 * 
		 * </pre>
		 */
		PositionMatrix qOperator = new PositionMatrix(new double[][] { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1}, { 0, 0, 0, 0 } });
		return qOperator;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getSecondDerivativeMatrix()
	 */
	@Override
	public PositionMatrix getSecondDerivativeMatrix(JVAR thisType, JVAR previousType) throws NullParameterException, InvalidParameterException {

		// previousType not needed for this joint

		// Null Checking
		if (thisType == null) {
			throw new NullParameterException("Joint Variable cannot be null", 0);
		}

		// Type Checking
		if (thisType != JVAR.ZDISPLACEMENT) {
			throw new InvalidParameterException("Prism Joint Variable should be displacement", 0);
		}

		// initialize secDeriv to identity matrix
		PositionMatrix secDeriv = new PositionMatrix();

		// change each 1 along diagonal to 0
		secDeriv.set(0, 0, 0);
		secDeriv.set(1, 1, 0);
		secDeriv.set(2, 2, 0);
		secDeriv.set(3, 3, 0);

		// all other positions set to and remain 0s from initialization

		return secDeriv;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getVelocityMatrix()
	 */
	@Override
	public PositionMatrix getVelocityMatrix() throws NullParameterException, InvalidParameterException {
		// the derivative of the prism joint's phi matrix
		PositionMatrix deriv = this.getDerivativeMatrix(JVAR.ZDISPLACEMENT);
		PositionMatrix vel;

		// derivative matrix multiplied by velocity value
		vel = new PositionMatrix(deriv.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getVelocity()));

		return vel;
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
		return "Prism [name=" + this.name + ", body before=" + this.getBodyBefore() + ", body after=" + this.getBodyAfter() + "]";
	}
}
