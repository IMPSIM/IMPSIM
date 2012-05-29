/**
 * Screw.java
 * March 19, 2011
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
 * Class for holding the data of a screw joint
 * 
 * @author hellmerj
 * @review zastrowm (1.1)
 * @edit dykstran Added q operator and getJVAR methods.
 * @edit dykstran Update JavaDoc
 * @version 1.21
 */
public class Screw extends Joint {

	/**
	 * The helical angle of the screw joint.
	 */
	private double helicAngle;

	/**
	 * Creates a new screw joint.
	 * 
	 * @param name The name of this joint.
	 * @throws NullParameterException Thrown if the name is null.
	 * @throws InvalidParameterException Thrown if the name is empty.
	 */
	public Screw(String name) throws NullParameterException, InvalidParameterException {
		super(name);
		this.setJointVariable(JVAR.ZDISPLACEMENT, 0);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.observer.Subject#addObserver(imp.observer.Observer)
	 */
	@Override
	public void addObserver(Observer obv) {
		super.addObserver(obv);
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

		// check if passed object is a Screw
		if (!(otherObject instanceof Screw)) {
			return false;
		} else {
			// cast object into screw for comparison
			Screw otherScr = (Screw) otherObject;
			// return whether EVERY attribute is the same
			return this.name.equals(otherScr.name) && this.helicAngle == otherScr.helicAngle
					&& this.getJointVariablesMap().equals(otherScr.getJointVariablesMap()) && this.getAxisAfter().equals(otherScr.getAxisAfter())
					&& this.getAxisBefore().equals(otherScr.getAxisBefore()) && this.loopIdentNumber == otherScr.loopIdentNumber
					&& this.orientation == otherScr.orientation;
		}
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getAccelerationMatrix()
	 */
	@Override
	public PositionMatrix getAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		// second derivative of the screw joint's phi matrix
		PositionMatrix secDeriv = this.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.ZDISPLACEMENT);
		PositionMatrix acc;

		// second derivative matrix multiplied by the acceleration value of the joint variable
		acc = new PositionMatrix(secDeriv.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getAcceleration()));

		return acc;
	}

	/**
	 * This is the getAngle method. It is responsible for pulling the angle from the phi matrix.
	 * 
	 * @return The angle between the bodies connected by the screw.
	 */
	public double getAngle() {
		System.out.println(this.getPhiMatrix().get(0, 0));
		double angle = Math.acos(this.getPhiMatrix().get(0, 0));

		return angle;
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
			throw new InvalidParameterException("Screw Joint Variable should be displacement", 0);
		}

		PositionMatrix deriv = new PositionMatrix();

		// the angle between the bodies
		// calculated as the body displacement divided by the helical(lead) angle
		double angle = this.getJointVariable(variableType).getMagnitude() / this.helicAngle;

		// derivative of sin and cos
		deriv.set(0, 0, -Math.sin(angle));
		deriv.set(0, 1, -Math.cos(angle));
		deriv.set(1, 0, Math.cos(angle));
		deriv.set(1, 1, -Math.sin(angle));
		// derivative of JVAR
		deriv.set(2, 3, 1);
		// derivative of 1s along diagonal
		deriv.set(2, 2, 0);
		deriv.set(3, 3, 0);

		return deriv;
	}

	/**
	 * This is the getDisplacement method. It is responsible for pulling the displacement from the phi matrix.
	 * 
	 * @return The displacement between the bodies connected by the screw.
	 */
	public double getDisplacement() {
		double displacement = this.getPhiMatrix().get(2, 3);

		return displacement;
	}

	/**
	 * This is the getHelicAngle method. It is responsible for returning the helical angle of the screw.
	 * 
	 * @return helicAngle The helical angle of this joint.
	 */
	public double getHelicAngle() {
		return this.helicAngle;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getJVARs()
	 */
	@Override
	public List<JVAR> getJVARs() {
		List<JVAR> jVarList = new ArrayList<JVAR>();

		// Only z displacement is valid for screw joints.
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

		// the angle between the bodies
		double angle = this.getJointVariable(JVAR.ZDISPLACEMENT).getMagnitude() / this.helicAngle;

		// set values of sin and cos of calculated displacement
		phi.set(0, 0, Math.cos(angle));
		phi.set(0, 1, -Math.sin(angle));
		phi.set(1, 0, Math.sin(angle));
		phi.set(1, 1, Math.cos(angle));
		// set value of joint variable position
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
		 * Defined in docs as:
		 * 
		 * <pre>
		 * Q =	[ 		0,-1/sigma, 0, 0]
		 * 		[ 1/sigma, 		 0, 0, 0]
		 * 		[		0, 		 0, 0, 1]
		 * 		[		0, 		 0, 0, 0]
		 * 
		 * </pre>
		 * 
		 * Sigma is the helical angle of the joint.
		 */
		double sigma = this.getHelicAngle();
		PositionMatrix qOper = new PositionMatrix(new double[][] { { 0, -1 / sigma, 0, 0 }, { 1 / sigma, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 0, 0 } });
		return qOper;
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
			throw new InvalidParameterException("Screw Joint Variable should be displacement", 0);
		}

		// initialize secDeriv to identity matrix
		PositionMatrix secDeriv = new PositionMatrix();

		// the angle between the bodies
		// calculated as the body displacement divided by the helical(lead) andgle
		double angle = this.getJointVariable(thisType).getMagnitude() / this.helicAngle;

		// second derivative of sin and cos
		secDeriv.set(0, 0, -Math.cos(angle));
		secDeriv.set(0, 1, Math.sin(angle));
		secDeriv.set(1, 0, -Math.sin(angle));
		secDeriv.set(1, 1, -Math.cos(angle));
		// second derivative of 1s along diagonal
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
		// derivative of the screw joint's phi matrix
		PositionMatrix deriv = this.getDerivativeMatrix(JVAR.ZDISPLACEMENT);
		PositionMatrix vel;

		// derivative matrix multiplied by velocity value
		vel = new PositionMatrix(deriv.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getVelocity()));

		return vel;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).append(this.helicAngle).append(this.getAxisAfter()).append(this.getAxisBefore())
				.append(this.getBodyBefore()).append(this.getBodyAfter()).append(this.getJointVariablesMap()).append(this.loopIdentNumber)
				.append(this.orientation).toHashCode();
	}

	/**
	 * This is the setHelicAngle method. It is responsible for setting the helical angle of the screw.
	 * 
	 * @param angle The helical angle in radians.
	 */
	public void setHelicAngle(double angle) {
		this.helicAngle = angle;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Screw [name=" + this.name + ", helic angle=" + this.helicAngle + ", body before=" + this.getBodyBefore() + ", body after="
				+ this.getBodyAfter() + "]";
	}
}
