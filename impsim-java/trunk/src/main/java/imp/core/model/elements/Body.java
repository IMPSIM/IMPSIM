/**
 * Body.java
 * January 22, 2011
 */

package imp.core.model.elements;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Axis;
import imp.core.model.Element;
import imp.core.observer.NotificationType;
import imp.core.structures.PositionMatrix;

import java.util.HashSet;
import java.util.Set;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Represents a rigid body in a model.
 * 
 * @author biesew
 * @edit edmissonj Added the shape Matrix, its getters and setters, and included it in the constructor
 * @edit dykstran Added exception throwing to constructor.
 * @edit edmissonj Moved the map to body to body
 * @edit edmissonj Implemented subject interface
 * @edit dykstran Updated JavaDoc
 * @edit zastrowm updated observer
 * @version 1.12
 */
public class Body extends Element {

	/** Set of axes of this body. */
	private Set<Axis> axes;

	/** Loop identity number. */
	public int loopIdentNumber;

	/**
	 * Matrix containing the position and rotation of the body with respect to the global origin.
	 */
	private PositionMatrix positionMatrix;

	/**
	 * Creates a new body.
	 * 
	 * @param name The name attribute of the Body to be created.
	 * @throws InvalidParameterException Thrown if the name is empty.
	 * @throws NullParameterException Thrown if the name is null.
	 */
	public Body(String name) throws NullParameterException, InvalidParameterException {
		super(name);
		this.axes = new HashSet<Axis>();
		this.setPositionMatrix(new PositionMatrix());
	}

	/**
	 * Adds the axis to the body.
	 * 
	 * @param theAxis The axis to add to this body.
	 * @return True if successfully added. False if the axis specified already existed in the body.
	 */
	public boolean addAxis(Axis theAxis) {
		return this.axes.add(theAxis);
	}

	/**
	 * Checks if the body contains the specified axis.
	 * 
	 * @param theAxis The axis to check.
	 * @return True if the axis is on the body, false otherwise.
	 */
	public boolean containsAxis(Axis theAxis) {
		return this.axes.contains(theAxis);
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

		// check if passed object is a body
		if (!(otherObject instanceof Body)) {
			return false;
		} else {
			// cast object into Body for comparison
			Body otherBody = (Body) otherObject;
			// return whether EVERY attribute is the same
			return this.name.equals(otherBody.name) && this.axes.equals(otherBody.axes) && this.loopIdentNumber == otherBody.loopIdentNumber
					&& this.positionMatrix.equals(otherBody.positionMatrix);
		}

	}

	/**
	 * Gets the position matrix of this body.
	 * 
	 * @return The positionMatrix of this body.
	 */
	public PositionMatrix getPositionMatrix() {
		return this.positionMatrix;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).append(this.axes).append(this.loopIdentNumber).append(this.positionMatrix).toHashCode();
	}

	/**
	 * Method for mapping a transformation matrix to a body instead of the global origin.
	 * 
	 * @param tm The transformation matrix to be re-mapped.
	 * @return The re-mapped transformation matrix.
	 */
	public PositionMatrix mapToBody(PositionMatrix tm) {
		// multiplies the inverse of the transformation matrix going from the global origin to
		// the body by the transformation matrix
		return this.getPositionMatrix().inverse().multiply(tm);
	}

	/**
	 * Removes the axis from the body.
	 * 
	 * @param theAxis The axis to remove from the body.
	 * @return True if successfully removed. False if the axis specified wasn't part of the body.
	 */
	public boolean removeAxis(Axis theAxis) {
		return this.axes.remove(theAxis);
	}

	/**
	 * Sets the position matrix of this body.
	 * 
	 * @param positionMatrix The new positionMatrix for this body.
	 */
	public void setPositionMatrix(PositionMatrix positionMatrix) {
		this.positionMatrix = positionMatrix;
	}

	/**
	 * Method for setting the position matrix and notifying the observers.
	 * 
	 * @param shapeMatrix The position matrix to set.
	 * @param notify Set to true to notify any subscribed observers.
	 */
	public void setPositionMatrixNotify(PositionMatrix shapeMatrix, boolean notify) {
		this.setPositionMatrix(shapeMatrix);
		if (notify) {
			this.notifyObservers(NotificationType.position);
		}
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Body [name=" + this.name + ", axes=" + this.axes + ", positionMatrix=" + this.positionMatrix + "]";
	}
}
