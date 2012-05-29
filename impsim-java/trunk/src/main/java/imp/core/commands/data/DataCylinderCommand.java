/**
 * DataCylinderCommand.java
 * March 24, 2011
 */
package imp.core.commands.data;

import imp.core.commands.Command;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Cylinder;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for assigning data to a cylinder joint.
 * 
 * @author edmissonj
 * @edit zastrowm added .equals()
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class DataCylinderCommand implements Command {

	/**
	 * The name of the joint
	 */
	String name;
	
	/**
	 * The location of the joint
	 */
	Point origin;
	
	/**
	 * The axis along which the joint moves
	 */
	Point commonAxis;
	
	/**
	 * The axis perpendicular to the commonAxis
	 */
	Point halfPlane;

	/**
	 * Method for inputting data for the cylinder.
	 * 
	 * @param origin The origin of the joint.
	 * @param commonAxis The point defining the axis about which the joint revolves and slides.
	 * @param halfPlane The point defining the common half plane of the bodies being joined.
	 * @param jointName The name of the joint.
	 * @throws NullParameterException Thrown if a parameter is null.
	 * @throws InvalidParameterException Thrown if 2 parameters occupy the same point.
	 */
	public DataCylinderCommand(Point origin, Point commonAxis, Point halfPlane, String jointName) throws NullParameterException, InvalidParameterException {
		// checks that none of the values are null and none of the points are coincidental
		if (origin == null) {
			throw new NullParameterException("The point defining the origin can't be a null value.", 0);
		}

		if (commonAxis == null) {
			throw new NullParameterException("The point defining the axis of movement and revolution can't be a null value.", 1);
		} else if (commonAxis.equals(origin)) {
			throw new InvalidParameterException("The point defining the axis of movement can't be coincidental with the point defining the origin", 1);
		}

		if (halfPlane == null) {
			throw new NullParameterException("The point defining the relative X axis for the two bodies can't be a null value.", 2);
		} else if (halfPlane.equals(origin)) {
			throw new InvalidParameterException("The point defining the relative X axis can't be coincidental with the point defining the origin", 2);
		} else if (halfPlane.equals(commonAxis)) {
			throw new InvalidParameterException("The point defining the relative X axis can't be coincidental with the point defining axis of movement", 2);
		} else if (origin.getAngleBetween(halfPlane, commonAxis) <= imp.core.Constants.MIN_ANGLE) {
			throw new InvalidParameterException("The angle between the point defining the first body and the axis is not large enough", 2);
		}

		if (jointName == null) {
			throw new NullParameterException("The name of the joint can't be a null value.", 3);
		}

		// sets the values
		this.name = jointName;
		this.origin = origin;
		this.commonAxis = commonAxis;
		this.halfPlane = halfPlane;
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

		if (!(otherObject instanceof DataCylinderCommand)) {
			return false;
		} else {
			DataCylinderCommand otherCmd = (DataCylinderCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.commonAxis.equals(this.commonAxis) && otherCmd.halfPlane.equals(this.halfPlane) && otherCmd.name.equals(this.name)
					&& otherCmd.origin.equals(this.origin);
		}

	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws JointNotFoundException, InvalidDatatypeException, MatrixIndexOutOfBoundsException {
		
		// checks if the model being passed in exists (not-null)
		NullParameterException.check( model, "model", 0 );
		
		// checks if the joint is missing from the model
		if (!model.contains(this.name, Cylinder.class)) {
			throw new JointNotFoundException("The joint '" + this.name + "' you are attempting to add data for doesn't exist.");
		}

		// gets the cylinder from the model
		Cylinder cyl = (Cylinder) model.getJoint(this.name);
		// sets the angle between the bodies connected by the cylinder
		cyl.setJointVariable(JVAR.THETA, 0);
		// sets the displacement between the bodies connected by the cylinder
		cyl.setJointVariable(JVAR.ZDISPLACEMENT, 0);

		// the position matrix of the cylinder relative to the global origin
		PositionMatrix pm = DataJointCommandHelper.calculateShapeMatrix(this.commonAxis, this.origin, this.halfPlane);

		// maps the shape matrices to their respective bodies
		PositionMatrix pmBefore = cyl.getAxisBefore().getBody().mapToBody(pm);
		PositionMatrix pmAfter = cyl.getAxisAfter().getBody().mapToBody(pm);

		// sets the shape matrices of the axes
		cyl.getAxisBefore().setShapeMatrix(pmBefore);
		cyl.getAxisAfter().setShapeMatrix(pmAfter);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).append(this.origin).append(this.commonAxis).append(this.halfPlane).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "DataCylinderCommand [name=" + this.name + ", origin=" + this.origin + ", commonAxis=" + this.commonAxis + ", halfPlane=" + this.halfPlane + "]";
	}
}
