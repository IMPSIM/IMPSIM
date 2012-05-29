/**
 * Joint.java
 * March 29, 2011
 */

package imp.core.model.elements;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Axis;
import imp.core.model.Element;
import imp.core.structures.JointVariable;
import imp.core.structures.PositionMatrix;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Represents a joint in a model.
 * 
 * @author biesew
 * @edit edmissonj moved the map to body to body
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public abstract class Joint extends Element {

	/**
	 * The types of joint variables a particular joint can have.
	 */
	@SuppressWarnings("javadoc")
	public enum JVAR {
		XDISPLACEMENT, YDISPLACEMENT, ZDISPLACEMENT, THETA, PHI, PSI;

		/**
		 * Create an enum from a string
		 * 
		 * @param str the str to convert, case insensitive
		 * @return the JVAR converted
		 */
		public static JVAR fromString(String str) {

			for (JVAR var : JVAR.values()) {
				if (str.equalsIgnoreCase(var.name())) {
					return var;
				}
			}

			return null;
		}
	}

	/**
	 * Store the values for the joint variables for this particular joint.
	 */
	private Map<JVAR, JointVariable> jointVariables;

	/**
	 * The axis of the body after this joint.
	 */
	private Axis axisAfter;

	/**
	 * The axis of the body before this joint.
	 */
	private Axis axisBefore;

	/**
	 * The loop identity number of this joint.
	 */
	public int loopIdentNumber;

	/**
	 * The orientation (in loops) of this joint.
	 */
	public int orientation = 1;

	/**
	 * Creates a new joint.
	 * 
	 * @param name The name attribute of the Joint to be created.
	 * @throws NullParameterException Thrown if the string is null.
	 * @throws InvalidParameterException Thrown if the name is empty.
	 */
	public Joint(String name) throws NullParameterException, InvalidParameterException {
		super(name);
		this.jointVariables = new HashMap<JVAR, JointVariable>();
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

		// check if passed object is a joint
		if (!(otherObject instanceof Joint)) {
			return false;
		} else {
			// cast object into joint for comparison
			Joint otherJnt = (Joint) otherObject;
			// return whether EVERY attribute is the same
			return this.name.equals(otherJnt.name) && this.jointVariables.equals(otherJnt.jointVariables) && this.axisAfter.equals(otherJnt.axisAfter)
					&& this.axisBefore.equals(otherJnt.axisBefore) && this.loopIdentNumber == otherJnt.loopIdentNumber
					&& this.orientation == otherJnt.orientation;
		}
	}

	/**
	 * This is the getAccelerationMatrix method. It is responsible for creating the joint's acceleration matrix by
	 * multiplying the joint's second derivative matrix by an acceleration value stored in the joint variable.
	 * 
	 * @return The acceleration matrix for the joint.
	 * @throws InvalidParameterException Invalid joint variable type passed to second derivative method
	 * @throws NullParameterException Null value passed for joint variable type to second derivative
	 */
	public abstract PositionMatrix getAccelerationMatrix() throws NullParameterException, InvalidParameterException;

	/**
	 * Get the axis after this joint.
	 * 
	 * @return The Axis after this joint.
	 */
	public final Axis getAxisAfter() {
		return this.axisAfter;
	}

	/**
	 * Get the axis before this joint.
	 * 
	 * @return The Axis before this joint.
	 */
	public final Axis getAxisBefore() {
		return this.axisBefore;
	}

	/**
	 * Get the body after this joint.
	 * 
	 * @return The Body after this joint.
	 */
	public final Body getBodyAfter() {
		return this.axisAfter.getBody();
	}

	/**
	 * Get the body before this joint.
	 * 
	 * @return The body before this joint
	 */
	public final Body getBodyBefore() {
		return this.axisBefore.getBody();
	}

	/**
	 * This is the getDerivativeMatrix method. It is responsible for creating the joint's derivative matrix by taking
	 * the derivative of each position in the phi matrix.
	 * 
	 * @param variableType The type of joint variable used in the joint.
	 * @return The derivative matrix for the joint.
	 * @throws NullParameterException The type of the joint variable was null.
	 * @throws InvalidParameterException The type of the joint variable does not match the joint.
	 */
	public abstract PositionMatrix getDerivativeMatrix(JVAR variableType) throws NullParameterException, InvalidParameterException;

	/**
	 * Get the specified joint variable.
	 * 
	 * @param variableType The joint variable to get.
	 * @return The joint variable.
	 */
	public JointVariable getJointVariable(JVAR variableType) {
		if (this.jointVariables.containsKey(variableType)) {
			return this.jointVariables.get(variableType);
		}

		return null;
	}

	/**
	 * Get the map of the values for the joint variabls of this particular joint.
	 * 
	 * @return The map of joint variables
	 */
	public Map<JVAR, JointVariable> getJointVariablesMap() {
		return this.jointVariables;
	}

	/**
	 * Returns a list of JVARs that are valid for this joint.
	 * 
	 * @return A list of applicable JVARs.
	 */
	public abstract List<JVAR> getJVARs();

	/**
	 * This is the getPhiMatrix method. It is responsible for creating the joint's phi matrix by taking a 4x4 identity
	 * matrix and setting the various positions to their proper values.
	 * 
	 * @return The phi matrix for the joint.
	 */
	public abstract PositionMatrix getPhiMatrix();

	/**
	 * Gets the 4x4 matrix representing the Q operator for the specified joint variable.
	 * 
	 * @param jvar The joint variable to get the Q operator for.
	 * @return The Q operator matrix.
	 */
	public abstract PositionMatrix getQOperator(JVAR jvar);

	/**
	 * This is the getSecondDerivativeMatrix method. It is responsible for creating the joint's second derivative matrix
	 * by taking the second derivative of each position in the phi matrix.
	 * 
	 * @param thisType The type of joint variable used for the joint.
	 * @param previousType the previous type of the derivative.
	 * @return The second derivative matrix for the joint.
	 * @throws NullParameterException The type of the joint variable was null.
	 * @throws InvalidParameterException The type of the joint variable does not match the joint.
	 */
	public abstract PositionMatrix getSecondDerivativeMatrix(JVAR thisType, JVAR previousType) throws NullParameterException, InvalidParameterException;

	/**
	 * This is the getVelcoityMatrix method. It is responsible for creating the joint's velocity matrix by multiplying
	 * the joint's derivative matrix by a velocity value stored in the joint variable.
	 * 
	 * @return The velocity matrix for the joint.
	 * @throws NullParameterException Null joint variable passed to derivative method call.
	 * @throws InvalidParameterException Invalid joint variable type passed to derivative method call.
	 */
	public abstract PositionMatrix getVelocityMatrix() throws NullParameterException, InvalidParameterException;

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.axisAfter).append(this.axisBefore).append(this.jointVariables).append(this.loopIdentNumber)
				.append(this.orientation).append(this.name).toHashCode();
	}

	/**
	 * Set the axis after this joint.
	 * 
	 * @param theAxis The axis to set as after.
	 */
	public final void setAxisAfter(Axis theAxis) {
		this.axisAfter = theAxis;
	}

	/**
	 * Set the axis before this joint.
	 * 
	 * @param theAxis The Axis to set as before.
	 */
	public final void setAxisBefore(Axis theAxis) {
		this.axisBefore = theAxis;
	}

	/**
	 * Set the magnitude of the specified joint variable.
	 * 
	 * @param variableType The joint variable to set.
	 * @param magnitude The magnitude to set for the joint variable.
	 */
	public void setJointVariable(JVAR variableType, double magnitude) {
		// Create the joint variable if it doesn't exist
		if (!this.jointVariables.containsKey(variableType)) {
			this.jointVariables.put(variableType, new JointVariable(magnitude));
			this.jointVariables.get(variableType).setType(variableType);
		} else {
			// Modify the magnitude if the joint variable is already in the map
			this.jointVariables.get(variableType).setMagnitude(magnitude);
		}

	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.Element#toString()
	 */
	@Override
	public String toString() {
		return "Joint: [name=" + this.name + ", body before=" + this.getBodyBefore() + ", body after=" + this.getBodyAfter() + "]";
	}
}
