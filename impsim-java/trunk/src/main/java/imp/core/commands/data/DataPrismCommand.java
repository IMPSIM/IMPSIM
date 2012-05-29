/**
 * DataPrismCommand.java
 * March 12, 2011
 */
package imp.core.commands.data;

import imp.core.commands.Command;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Model;
import imp.core.model.joints.Prism;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import java.io.PrintStream;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for assigning data to a prism joint.
 * 
 * @author dykstran
 * @edit zastrowm added .equals() method
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class DataPrismCommand implements Command {

	/**
	 * The local origin of the joint.
	 */
	Point origin;

	/**
	 * One of the points defining the axes before the joint.
	 */
	Point commonAxis;

	/**
	 * One of the points defining the axes after the joint.
	 */
	Point halfPlane;

	/**
	 * The name of this joint.
	 */
	String name;

	/**
	 * Associates data with a particular joint.
	 * 
	 * From the original documentation:
	 * 
	 * <pre>
	 * The initial locations of the two local coordinate systems attached 
	 * to the two links joined by a PRISM statement are coincident and 
	 * are both defined by a single DATA PRISM statement by specifying 
	 * the global coordinates of three points (see figure). The first 
	 * point defines the common origins of the two local coordinate 
	 * systems. The second point must be located on the common local 
	 * positive w,w axis. The third point must lie in the half-plane 
	 * defined by the common local w,w axis and the common local positive u,u axis.
	 * </pre>
	 * 
	 * @param origin The local origin.
	 * @param commonAxis A point defining the slide axis.
	 * @param halfPlane A point defining the half plane.
	 * @param jointName The name of the joint to add data to.
	 * @throws NullParameterException Thrown if any parameter is null.
	 * @throws InvalidParameterException Thrown if any parameters are not valid for a prism joint.
	 */
	public DataPrismCommand(Point origin, Point commonAxis, Point halfPlane, String jointName) throws NullParameterException, InvalidParameterException {

		// Parameter checking
		if (origin == null) {
			throw new NullParameterException("The point defining the origin can't be a null point", 0);
		}

		if (commonAxis == null) {
			throw new NullParameterException("The point defining one of the axes can't be a null point", 1);
		} else if (commonAxis.equals(origin)) {
			throw new InvalidParameterException("Points cannot be the same as the origin.", 1);
		}

		if (halfPlane == null) {
			throw new NullParameterException("The point defining one of the axes can't be a null point", 2);
		} else if (halfPlane.equals(origin)) {
			throw new InvalidParameterException("Points cannot be the same as the origin.", 2);
		}

		if (commonAxis.equals(halfPlane)) {
			throw new InvalidParameterException("The points defining the axes cannot be the same.", 2);
		}else if (origin.getAngleBetween(commonAxis, halfPlane) <= imp.core.Constants.MIN_ANGLE) {
			throw new InvalidParameterException("The angle between the point defining the half plane and the axis is not large enough", 3);
		}

		if (jointName == null || jointName.trim().equals("")) {
			throw new NullParameterException("The name of the joint can't be a null or empty value", 4);
		}

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

		if (!(otherObject instanceof DataPrismCommand)) {
			return false;
		} else {
			DataPrismCommand otherCmd = (DataPrismCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.name.equals(this.name) && otherCmd.origin.equals(this.origin) && otherCmd.commonAxis.equals(this.commonAxis)
					&& otherCmd.halfPlane.equals(this.halfPlane);
		}
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws JointNotFoundException, InvalidDatatypeException, MatrixIndexOutOfBoundsException, NullParameterException {
		
		// checks if the model being passed exists (not-null)
		NullParameterException.check( model, "model", 0 );

		// checks if the joint is missing from the model
		if (!model.contains(this.name, Prism.class)) {
			throw new JointNotFoundException("The joint '" + this.name + "' you are attempting to add data for doesn't exist.");
		}

		// Get the prism joint from the model
		Prism prism = (Prism) model.getJoint(this.name);

		// the Position matrix for the body before the joint and the body after the joint
		PositionMatrix pm = DataJointCommandHelper.calculateShapeMatrix(this.commonAxis, this.origin, this.halfPlane);

		// maps the shape matrices to their respective bodies
		PositionMatrix pmBefore = prism.getAxisBefore().getBody().mapToBody(pm);
		PositionMatrix pmAfter = prism.getAxisAfter().getBody().mapToBody(pm);

		// sets the shape matrices on the axes and the angle of the prism
		prism.getAxisBefore().setShapeMatrix(pmBefore);
		prism.getAxisAfter().setShapeMatrix(pmAfter);

		// Gets the print stream of the model to print out some info for the user
		PrintStream ps = model.getPrintStream();
		ps.println(prism.getName());

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
