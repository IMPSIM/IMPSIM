/**
 * Cylinder.java
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
 * Class for holding the data of a cylinder joint
 * 
 * @author edmissonj
 * @review zastrowm (1.0)
 * @edit dykstran Added q operator and getJVAR methods.
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class Cylinder extends Joint {

	/**
	 * Creates a new cylinder joint.
	 * 
	 * @param name The name of the joint.
	 * @throws NullParameterException Thrown if the name is null.
	 * @throws InvalidParameterException Thrown if the name is empty.
	 */
	public Cylinder(String name) throws NullParameterException, InvalidParameterException {
		super(name);
		this.setJointVariable(JVAR.THETA, 0);
		this.setJointVariable(JVAR.ZDISPLACEMENT, 0);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.observer.Subject#addObserver(imp.observer.Observer)
	 */
	@Override
	public void addObserver(Observer obv) {
		this.getJointVariable(JVAR.THETA).addObserver(obv);
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

		// check if passed object is a Cylinder
		if (!(otherObject instanceof Cylinder)) {
			return false;
		} else {
			// cast object into cylinder for comparison
			Cylinder otherCyl = (Cylinder) otherObject;
			// return whether EVERY attribute is the same
			return this.name.equals(otherCyl.name) && this.getJointVariablesMap().equals(otherCyl.getJointVariablesMap())
					&& this.getAxisAfter().equals(otherCyl.getAxisAfter()) && this.getAxisBefore().equals(otherCyl.getAxisBefore())
					&& this.loopIdentNumber == otherCyl.loopIdentNumber && this.orientation == otherCyl.orientation;
		}
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getAccelerationMatrix()
	 */
	@Override
	public PositionMatrix getAccelerationMatrix() {
		// second derivative matrix of the partial first derivative of theta with respect to theta
		PositionMatrix thetaTheta = this.getSecondDerivativeMatrix(JVAR.THETA, JVAR.THETA);
		// second derivative matrix of the partial first derivative of theta with respect to zDsip
		PositionMatrix thetaZDisp = this.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.THETA);
		// second derivative matrix of the partial first derivative of zDisp with respect to theta
		PositionMatrix zDispTheta = this.getSecondDerivativeMatrix(JVAR.THETA, JVAR.ZDISPLACEMENT);
		// second derivative matrix of the partial first derivative of zDisp with respect to zDisp
		PositionMatrix zDispZDisp = this.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.ZDISPLACEMENT);
		// return matrix to hold acceleration matrix
		PositionMatrix retVal = new PositionMatrix();

		// multiply each partial second derivative matrix by corresponding acceleration value
		thetaTheta.setJamaMatrix(thetaTheta.getJamaMatrix().times(this.getJointVariable(JVAR.THETA).getAcceleration()));
		thetaZDisp.setJamaMatrix(thetaZDisp.getJamaMatrix().times(this.getJointVariable(JVAR.THETA).getAcceleration()));
		zDispTheta.setJamaMatrix(zDispTheta.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getAcceleration()));
		zDispZDisp.setJamaMatrix(zDispZDisp.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getAcceleration()));

		// add all partial second derivative matrices together
		retVal.setJamaMatrix(thetaTheta.getJamaMatrix().plus(thetaZDisp.getJamaMatrix().plus(zDispTheta.getJamaMatrix().plus(zDispZDisp.getJamaMatrix()))));

		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getDerivativeMatrix(imp.model.elements.Joint.JVAR)
	 */
	@Override
	public PositionMatrix getDerivativeMatrix(JVAR variableType) {
		PositionMatrix retVal = new PositionMatrix();
		if (variableType.equals(JVAR.THETA)) {
			retVal.set(0, 0, -Math.sin(this.getJointVariable(variableType).getMagnitude()));
			retVal.set(0, 1, -Math.cos(this.getJointVariable(variableType).getMagnitude()));
			retVal.set(1, 1, -Math.sin(this.getJointVariable(variableType).getMagnitude()));
			retVal.set(1, 0, Math.cos(this.getJointVariable(variableType).getMagnitude()));
			retVal.set(2, 2, 0);
			retVal.set(3, 3, 0);
			/*
			 * <pre> Q = [ -sin(theta), -cos(theta), 0, 0] [ cos(theta), -sin(theta), 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0]
			 * </pre>
			 */
		} else if (variableType.equals(JVAR.ZDISPLACEMENT)) {
			// derivative of each 1 along diagonal = 0
			retVal.set(0, 0, 0);
			retVal.set(1, 1, 0);
			retVal.set(2, 2, 0);
			retVal.set(3, 3, 0);
			// derivative of joint variable = 1
			retVal.set(2, 3, 1);
			/*
			 * <pre> Q = [ 0, 0, 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 1] [ 0, 0, 0, 0] </pre>
			 */

		}
		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getJVARs()
	 */
	@Override
	public List<JVAR> getJVARs() {
		List<JVAR> jVarList = new ArrayList<JVAR>();

		/* A cylinder joint can slide and rotate */
		jVarList.add(JVAR.ZDISPLACEMENT);
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
		// sets the phi matrix

		double cos = Math.cos(this.getJointVariable(JVAR.THETA).getMagnitude());
		double sin = Math.sin(this.getJointVariable(JVAR.THETA).getMagnitude());

		retVal.set(0, 0, cos);
		retVal.set(0, 1, -sin);
		retVal.set(1, 1, cos);
		retVal.set(1, 0, sin);
		retVal.set(3, 2, this.getJointVariable(JVAR.ZDISPLACEMENT).getMagnitude());
		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getQOperator(imp.model.elements.Joint.JVAR)
	 */
	@Override
	public PositionMatrix getQOperator(JVAR jvar) {
		/**
		 * From the documentation for displacement:
		 * 
		 * <pre>
		 * Q =	[ 0,-1, 0, 0]
		 * 		[ 1, 0, 0, 0]
		 * 		[ 0, 0, 0, 0]
		 * 		[ 0, 0, 0, 0]
		 * 
		 * </pre>
		 */
		PositionMatrix diplacementqOperator = new PositionMatrix(new double[][] { { 0, -1, 0, 0 }, { 1, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } });

		/**
		 * From the documentation for rotation:
		 * 
		 * <pre>
		 * Q =	[ 0, 0, 0, 0]
		 * 		[ 0, 0, 0, 0]
		 * 		[ 0, 0, 0, 1]
		 * 		[ 0, 0, 0, 0]
		 * 
		 * </pre>
		 */
		PositionMatrix rotationqOperator = new PositionMatrix(new double[][] { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 0, 0 } });

		/* Return the displacement operator, otherwise return the rotation operator */
		if (jvar == JVAR.ZDISPLACEMENT) {
			return diplacementqOperator;
		} else {
			return rotationqOperator;
		}
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

		if (thisType.equals(JVAR.THETA) && previousType.equals(JVAR.THETA)) {// second derivative of theta with respect
			// to theta
			retVal.set(0, 0, -cos);
			retVal.set(0, 1, sin);
			retVal.set(1, 1, -cos);
			retVal.set(1, 0, -sin);

			retVal.set(2, 2, 0);
			retVal.set(3, 3, 0);
			// both derivatives are the same when switching from one variable to the other

			/*
			 * <pre> Q = [ -cos(theta), sin(theta), 0, 0] [ -sin(theta), -cos(theta), 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0]
			 * </pre>
			 */
		} else if ((thisType.equals(JVAR.THETA) && previousType.equals(JVAR.ZDISPLACEMENT))
				|| (thisType.equals(JVAR.ZDISPLACEMENT) && previousType.equals(JVAR.THETA))) {
			retVal.set(0, 0, 0);
			retVal.set(1, 1, 0);
			retVal.set(2, 2, 0);
			retVal.set(3, 3, 0);

			/*
			 * <pre> Q = [ 0, 0, 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0] </pre>
			 */
		} else if (thisType.equals(JVAR.ZDISPLACEMENT) && previousType.equals(JVAR.ZDISPLACEMENT)) {// second derivative
			// of zdist with
			// respect to zdist
			retVal.set(0, 0, 0);
			retVal.set(1, 1, 0);
			retVal.set(2, 2, 0);
			retVal.set(3, 3, 0);
			retVal.set(3, 2, 0);

			/*
			 * <pre> Q = [ 0, 0, 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0] [ 0, 0, 0, 0] </pre>
			 */
		}

		return retVal;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#getVelocityMatrix()
	 */
	@Override
	public PositionMatrix getVelocityMatrix() {
		// derivative of phi with respect to theta
		PositionMatrix theta = this.getDerivativeMatrix(JVAR.THETA);
		// derivative of phi with respect to zDisp
		PositionMatrix zDisp = this.getDerivativeMatrix(JVAR.ZDISPLACEMENT);
		// return value to hold velocity matrix
		PositionMatrix retVal = new PositionMatrix();

		// multiply each partial derivative matrix by the corresponding velocity value
		theta.setJamaMatrix(theta.getJamaMatrix().times(this.getJointVariable(JVAR.THETA).getVelocity()));
		zDisp.setJamaMatrix(zDisp.getJamaMatrix().times(this.getJointVariable(JVAR.ZDISPLACEMENT).getVelocity()));

		// add the partial velocity matrices together
		retVal.setJamaMatrix(theta.getJamaMatrix().plus(zDisp.getJamaMatrix()));

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
		return "Cylinder [name=" + this.name + ", body before=" + this.getBodyBefore() + ", body after=" + this.getBodyAfter() + "]";
	}

}
