/**
 * DataScrewCommand.java
 * March 19, 2011
 */

package imp.core.commands.data;

import imp.core.Constants;
import imp.core.commands.Command;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Screw;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import java.io.PrintStream;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * This is the DataScrewCommand. It implements the command for entering data for the screw joint.
 * 
 * @author hellmerj
 * @edit zastrom (.equals() method)
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class DataScrewCommand implements Command {

	/**
	 * The angle relating the changes in angle and displacement as the bodies move with respect to each other.
	 */
	private double helicAngle;

	/**
	 * The origin of the joint.
	 */
	private Point origin;

	/**
	 * Point used to define the screw axis.
	 */
	private Point commonAxis;

	/**
	 * Point used to define common x axis.
	 */
	private Point halfPlane;

	/**
	 * The name of the joint the data is being added to.
	 */
	private String name;

	/**
	 * Constructor for the DataScrewCommand.
	 * 
	 * @param helical The helical angle of the screw.
	 * @param origin The point defining origin of the joint.
	 * @param commonAxis The point defining the screw axis.
	 * @param halfPlane The point defining the x axis.
	 * @param jointName The name of the joint data is being added to.
	 * @throws InvalidParameterException Thrown if any parameters are invalid for a screw joint.
	 * @throws NullParameterException Thrown if any parameters are null.
	 */
	public DataScrewCommand(double helical, Point origin, Point commonAxis, Point halfPlane, String jointName) throws InvalidParameterException,
			NullParameterException {

		if (helical == 0) { // check that the helical angle is valid
			throw new InvalidParameterException("The helical angle of the screw cannot be zero", 0);
		}

		if (origin == null) { // check that the given origin is not a null point
			throw new NullParameterException("The point defining the origin cannot be a null point", 1);
		}

		if (commonAxis == null) { // check that the first point is not a null point
			throw new NullParameterException("The point defining the initial horizontal axis position cannot be null", 2);
		} else if (commonAxis.equals(origin)) {
			throw new InvalidParameterException("Defining point cannot be at origin", 2);
		}

		if (halfPlane == null) { // check that the second point is not a null point
			throw new NullParameterException("The point defining the common axis cannot be null", 3);
		} else if (halfPlane.equals(origin)) {
			throw new InvalidParameterException("Defining point cannot be at origin", 3);
		} else if (halfPlane.equals(commonAxis)) {
			throw new InvalidParameterException("The two defining points cannot be equal", 3);
		}else if (origin.getAngleBetween(halfPlane, commonAxis) <= imp.core.Constants.MIN_ANGLE) {
			throw new InvalidParameterException("The angle between the point defining the half plane and the axis is not large enough", 3);
		}

		if (jointName == null) {
			throw new NullParameterException("The name of the joint cannot be null", 4);
		}

		this.helicAngle = helical;
		this.origin = origin;
		this.commonAxis = commonAxis;
		this.halfPlane = halfPlane;
		this.name = jointName;
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

		if (!(otherObject instanceof DataScrewCommand)) {
			return false;
		} else {
			DataScrewCommand otherCmd = (DataScrewCommand) otherObject;
			// return whether EVERY attribute is the same
			return Constants.compareDoubles(this.helicAngle, otherCmd.helicAngle) && otherCmd.name.equals(this.name)
					&& otherCmd.halfPlane.equals(this.halfPlane) && otherCmd.commonAxis.equals(this.commonAxis) && otherCmd.origin.equals(this.origin);
		}

	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws JointNotFoundException, InvalidDatatypeException, MatrixIndexOutOfBoundsException {
		
		// Checks if model being passed exists (not-null)
		NullParameterException.check( model, "model", 0 );

		// Check if joint is in the model
		if (!model.contains(this.name, Screw.class)) {
			throw new JointNotFoundException("The joint '" + this.name + "' you are attempting to add data for doesn't exist.");
		}

		// get joint from the model
		Screw scr = (Screw) model.getJoint(this.name);
		// set the helical angle of the screw
		scr.setHelicAngle(this.helicAngle);
		// set the joint variable containing sliding distance
		scr.setJointVariable(JVAR.ZDISPLACEMENT, 0);

		// position matrix for the screw
		PositionMatrix pm = DataJointCommandHelper.calculateShapeMatrix(this.commonAxis, this.origin, this.halfPlane);

		// map matrices to bodies
		PositionMatrix pmBefore = scr.getAxisBefore().getBody().mapToBody(pm);
		PositionMatrix pmAfter = scr.getAxisAfter().getBody().mapToBody(pm);

		// set matrices on axes
		scr.getAxisBefore().setShapeMatrix(pmBefore);
		scr.getAxisAfter().setShapeMatrix(pmAfter);

		// display information about the joint
		PrintStream ps = model.getPrintStream();
		ps.println(scr.getName() + " " + scr.getDisplacement());
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).append(this.helicAngle).append(this.origin).append(this.commonAxis).append(this.halfPlane).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "DataScrewCommand [name=" + this.name + ", helicAngle=" + this.helicAngle + ", origin=" + this.origin + ", commonAxis=" + this.commonAxis
				+ ", halfPlane=" + this.halfPlane + "]";
	}
}
