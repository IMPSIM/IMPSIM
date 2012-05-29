/**
 * Axis.java
 * May 11, 2011
 */
package imp.core.model;

import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.structures.PositionMatrix;

/**
 * Represents an axis of a joint or body.
 * 
 * @author biesew
 * @edit edmissonj Added a method for getting absolute position.
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class Axis implements Comparable<Axis> {

	/**
	 * The Joint object to which this Axis is affixed.
	 */
	private Joint joint;

	/**
	 * The Body object to which this Axis is affixed.
	 */
	private Body body;

	/**
	 * The shapeMatrix object where this Axis are affixed.
	 */
	private PositionMatrix shapeMatrix;

	/**
	 * Creates a new axis.
	 * 
	 * @param theJoint The joint to which the axis is affixed.
	 * @param theBody The body to which the axis is affixed.
	 */
	public Axis(Joint theJoint, Body theBody) {
		this.joint = theJoint;
		this.body = theBody;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	 */
	@Override
	public int compareTo(Axis otherAxis) {
		return this.joint.getName().compareTo(otherAxis.joint.getName());
	}

	/**
	 * Method for getting the absolute position matrix.
	 * 
	 * @return The absolute position matrix.
	 */
	public PositionMatrix getAbsolutePosition() {
		return this.body.getPositionMatrix().multiply(this.shapeMatrix);
	}

	/**
	 * Gets the body this axis is affixed to.
	 * 
	 * @return The body.
	 */
	public Body getBody() {
		return this.body;
	}

	/**
	 * Gets the joint this axis is affixed to.
	 * 
	 * @return The joint.
	 */
	public Joint getJoint() {
		return this.joint;
	}

	/**
	 * Gets the shape matrix of this axis.
	 * 
	 * @return The shape matrix.
	 */
	public PositionMatrix getShapeMatrix() {
		return this.shapeMatrix;
	}

	/**
	 * Sets the shape matrix of this axis.
	 * 
	 * @param posM The matrix to use as the shape matrix.
	 */
	public void setShapeMatrix(PositionMatrix posM) {
		this.shapeMatrix = posM;
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

		// check if passed object is a Axis
		if (!(otherObject instanceof Axis)) {
			return false;
		} else {
			// cast object into cylinder for comparison
			Axis otherAxis = (Axis) otherObject;
			// return whether EVERY attribute is the same
			return  this.joint.equals(otherAxis.joint) && this.body.equals(otherAxis.body) && this.shapeMatrix.equals(otherAxis.shapeMatrix);
		}
	}
}