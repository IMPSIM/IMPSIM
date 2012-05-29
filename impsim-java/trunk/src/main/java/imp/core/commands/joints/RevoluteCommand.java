package imp.core.commands.joints;

import imp.core.commands.JointEntry;
import imp.core.commands.data.DataJointCommandHelper;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Revolute;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class used to represent a Revolute Joint.
 */
@JointEntry(name = "Revolute", arg3 = "origin: TODO", arg4 = "commonAxis: TODO", arg5 = "bodyAxisFirst: TODO", arg6 = "bodyAxisSecond: TODO")
public class RevoluteCommand extends BaseJointCommand {

	/** The origin of the joint's axes.. */
	private final Point origin;

	/** The axis this joint rotates about. */
	private final Point commonAxis;

	/** The point along the x-axis of the first body. */
	private final Point bodyAxisFirst;

	/** The point along the x-axis of the second body. */
	private final Point bodyAxisSecond;

	/**
	 * Method for inputting data for the execute.
	 * 
	 * @param jointName The name of the revolute joint to add data to.
	 * @param bodyNameBefore The name of the first body attached by this joint.
	 * @param bodyNameAfter The name of the second body attached by this joint.
	 * @param origin The origin point of the joint.
	 * @param commonAxis The common axis between the two systems.
	 * @param bodyAxisFirst The point along the x axis of the first body.
	 * @param bodyAxisSecond The point along the x axis of the second body.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 * @throws InvalidParameterException Thrown if any parameters are invalid for a revolute joint.
	 */
	public RevoluteCommand(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point commonAxis, Point bodyAxisFirst,
			Point bodyAxisSecond) throws SelfLoopException {
		super(jointName, bodyNameBefore, bodyNameAfter);

		// null parameter checks
		NullParameterException.check(origin, "origin", 3);
		NullParameterException.check(commonAxis, "commonAxis", 4);
		NullParameterException.check(bodyAxisFirst, "bodyAxisFirst", 5);
		NullParameterException.check(bodyAxisSecond, "bodyAxisSecond", 6);

		// valid point checks
		checkParameter(commonAxis.equals(origin), 4, "The point defining the common axis can't be the same as the point defining the origin");
		checkParameter(bodyAxisFirst.equals(origin), 5, "The point defining the x axis of the first body can't be the same as the point defining the origin");
		checkParameter(bodyAxisSecond.equals(origin), 6, "The point defining the x axis of the first body can't be the same as the point defining the origin");

		// angle checks
		checkParameter(origin.getAngleBetween(bodyAxisFirst, commonAxis) <= imp.core.Constants.MIN_ANGLE, 5,
				"The angle between the point defining the first body and the axis is not large enough");
		checkParameter(origin.getAngleBetween(bodyAxisSecond, commonAxis) <= imp.core.Constants.MIN_ANGLE, 6,
				"The angle between the point defining the second body and the axis is not large enough");

		this.origin = origin;
		this.commonAxis = commonAxis;
		this.bodyAxisFirst = bodyAxisFirst;
		this.bodyAxisSecond = bodyAxisSecond;
	}

	/**
	 * Create a XPIN command
	 * 
	 * @param jointName The name of the revolute joint to add data to.
	 * @param bodyNameBefore The name of the first body attached by this joint.
	 * @param bodyNameAfter The name of the second body attached by this joint.
	 * @param origin The origin point of the joint.
	 * @param bodyAxisFirst A point along the x-axis of the first body.
	 * @param bodyAxisSecond A point along the x-axis of the second body.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 * @throws InvalidParameterException Thrown if any parameters are invalid for a revolute joint.
	 */
	@JointEntry(name = "XPin", arg3 = "origin: TODO", arg4 = "bodyAxisFirst: TODO", arg5 = "bodyAxisSecond: TODO")
	public static RevoluteCommand CreateXPin(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point bodyAxisFirst,
			Point bodyAxisSecond) throws NullParameterException, SelfLoopException, InvalidParameterException {

		NullParameterException.check(origin, "origin", 3);

		// checkParameter(bodyAxisFirst.equals(bodyAxisSecond), 6,
		// "The point definining the fist body can't be the same as the point defining the second body");

		Point commonAxis = new Point(origin.getX() + 1, origin.getY(), origin.getZ());

		return new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, bodyAxisFirst, bodyAxisSecond);
	}

	/**
	 * Create a YPIN command
	 * 
	 * @param jointName The name of the revolute joint to add data to.
	 * @param bodyNameBefore The name of the first body attached by this joint.
	 * @param bodyNameAfter The name of the second body attached by this joint.
	 * @param origin The origin point of the joint.
	 * @param bodyAxisFirst A point along the y-axis of the first body.
	 * @param bodyAxisSecond A point along the y-axis of the second body.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 * @throws InvalidParameterException Thrown if any parameters are invalid for a revolute joint.
	 */
	@JointEntry(name = "YPin", arg3 = "origin: TODO", arg4 = "bodyAxisFirst: TODO", arg5 = "bodyAxisSecond: TODO")
	public static RevoluteCommand CreateYPin(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point bodyAxisFirst,
			Point bodyAxisSecond) throws NullParameterException, SelfLoopException, InvalidParameterException {

		NullParameterException.check(origin, "origin", 3);
		// checkParameter(bodyAxisFirst.equals(bodyAxisSecond), 4,
		// "The point definining the fist body can't be the same as the point defining the second body");

		Point commonAxis = new Point(origin.getX(), origin.getY() + 1, origin.getZ());

		return new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, bodyAxisFirst, bodyAxisSecond);
	}

	/**
	 * Create a ZPIN command
	 * 
	 * @param jointName The name of the revolute joint to add data to.
	 * @param bodyNameBefore The name of the first body attached by this joint.
	 * @param bodyNameAfter The name of the second body attached by this joint.
	 * @param origin The origin point of the joint.
	 * @param bodyAxisFirst A point along the z-axis of the first body.
	 * @param bodyAxisSecond A point along the z-axis of the second body.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 * @throws InvalidParameterException Thrown if any parameters are invalid for a revolute joint.
	 */
	@JointEntry(name = "ZPin", arg3 = "origin: TODO", arg4 = "bodyAxisFirst: TODO", arg5 = "bodyAxisSecond: TODO")
	public static RevoluteCommand CreateZPin(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point bodyAxisFirst,
			Point bodyAxisSecond) throws NullParameterException, SelfLoopException, InvalidParameterException {

		NullParameterException.check(origin, "origin", 3);
		// checkParameter(bodyAxisFirst.equals(bodyAxisSecond), 4,
		// "The point definining the fist body can't be the same as the point defining the second body");

		Point commonAxis = new Point(origin.getX(), origin.getY(), origin.getZ() + 1);

		return new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, bodyAxisFirst, bodyAxisSecond);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.core.commands.Command#execute(imp.core.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		super.execute(model);

		// gets the revolute from the model
		Revolute r1 = (Revolute) model.getJoint(this.jointName);

		// the Position matrix for the body before the joint and the body after the joint
		PositionMatrix pmBefore = DataJointCommandHelper.calculateShapeMatrix(this.commonAxis, this.origin, this.bodyAxisFirst);
		PositionMatrix pmAfter = DataJointCommandHelper.calculateShapeMatrix(this.commonAxis, this.origin, this.bodyAxisSecond);

		pmBefore = r1.getAxisBefore().getBody().mapToBody(pmBefore);
		pmAfter = r1.getAxisAfter().getBody().mapToBody(pmAfter);

		PositionMatrix phi = pmBefore.inverse().multiply(pmAfter);

		// sets the shape matrices on the axis and the angle of the revolute
		r1.getAxisBefore().setShapeMatrix(pmBefore);
		r1.getAxisAfter().setShapeMatrix(pmAfter);
		r1.setJointVariable(JVAR.THETA, Math.atan2(phi.get(1, 0), phi.get(0, 0)));
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().appendSuper(super.hashCode()).append(this.origin).append(this.commonAxis).append(this.bodyAxisFirst)
				.append(this.bodyAxisSecond).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!super.equals(obj)) {
			return false;
		}
		if (!(obj instanceof RevoluteCommand)) {
			return false;
		}
		RevoluteCommand other = (RevoluteCommand) obj;
		if (bodyAxisFirst == null) {
			if (other.bodyAxisFirst != null) {
				return false;
			}
		} else if (!bodyAxisFirst.equals(other.bodyAxisFirst)) {
			return false;
		}
		if (bodyAxisSecond == null) {
			if (other.bodyAxisSecond != null) {
				return false;
			}
		} else if (!bodyAxisSecond.equals(other.bodyAxisSecond)) {
			return false;
		}
		if (commonAxis == null) {
			if (other.commonAxis != null) {
				return false;
			}
		} else if (!commonAxis.equals(other.commonAxis)) {
			return false;
		}
		if (origin == null) {
			if (other.origin != null) {
				return false;
			}
		} else if (!origin.equals(other.origin)) {
			return false;
		}
		return true;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "REVOLUTE " + super.toString() + " " + this.origin + " " + this.commonAxis + " " + this.bodyNameBefore + " " + this.bodyNameAfter;
	}
}
