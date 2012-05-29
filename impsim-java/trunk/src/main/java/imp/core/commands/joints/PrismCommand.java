package imp.core.commands.joints;

import imp.core.commands.Command;
import imp.core.commands.JointEntry;
import imp.core.commands.data.DataPrismCommand;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.structures.Point;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Unified class to encapsulate a Prism for the model
 */
//@formatter:off
@JointEntry(
		name = "Prism",
		arg3 = "origin: the origin location of the joint",
		arg4 = "commonAxis: The point defining the axis about which the joint revolves and slides",
		arg5 = "halfPlane: The point defining the axis about which the joint revolves and slides"
		)
//@formatter:on
public class PrismCommand implements Command {

	/** The prism command. */
	imp.core.commands.definition.PrismCommand prismCommand;

	/** The data prism command. */
	imp.core.commands.data.DataPrismCommand dataPrismCommand;

	/**
	 * Instantiates a new prism command.
	 * 
	 * @param jointName The name of the joint to create.
	 * @param bodyNameBefore The name of the body before this joint.
	 * @param bodyNameAfter The name of the body after this joint.
	 * @param origin The local origin.
	 * @param commonAxis A point defining the slide axis.
	 * @param halfPlane A point defining the half plane.
	 * @throws SelfLoopException Thrown if any parameters are not valid for a prism joint
	 * @throws NullParameterException Thrown if any parameters are null
	 * @throws InvalidParameterException if the command attempts to create a joint linking a body to itself
	 */
	public PrismCommand(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point commonAxis, Point halfPlane)
			throws NullParameterException, SelfLoopException, InvalidParameterException {
		this.prismCommand = new imp.core.commands.definition.PrismCommand(bodyNameBefore, bodyNameAfter, jointName);
		this.dataPrismCommand = new DataPrismCommand(origin, commonAxis, halfPlane, jointName);
	}

	/**
	 * Instantiates a XSlide command.
	 * 
	 * @param jointName The name of the joint to create.
	 * @param bodyNameBefore The name of the body before this joint.
	 * @param bodyNameAfter The name of the body after this joint.
	 * @param origin The local origin.
	 * @throws SelfLoopException Thrown if any parameters are not valid for a prism joint
	 * @throws NullParameterException Thrown if any parameters are null
	 * @throws InvalidParameterException if the command attempts to create a joint linking a body to itself
	 */
	@JointEntry(name = "XSlide", arg3 = "origin: the origin location of the joint")
	public static PrismCommand CreateXSlide(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin) throws NullParameterException,
			SelfLoopException, InvalidParameterException {

		NullParameterException.check(origin, "origin", 3);

		Point commonAxis = new Point(origin.getX() + 1, origin.getY(), origin.getZ());
		Point halfPlane = new Point(origin.getX(), origin.getY() - 1, origin.getZ());

		return new PrismCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, halfPlane);
	}

	/**
	 * Instantiates a YSlide command.
	 * 
	 * @param jointName The name of the joint to create.
	 * @param bodyNameBefore The name of the body before this joint.
	 * @param bodyNameAfter The name of the body after this joint.
	 * @param origin The local origin.
	 * @throws SelfLoopException Thrown if any parameters are not valid for a prism joint
	 * @throws NullParameterException Thrown if any parameters are null
	 * @throws InvalidParameterException if the command attempts to create a joint linking a body to itself
	 */
	@JointEntry(name = "YSlide", arg3 = "origin: the origin location of the joint")
	public static PrismCommand CreateYSlide(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin) throws NullParameterException,
			SelfLoopException, InvalidParameterException {

		NullParameterException.check(origin, "origin", 3);

		Point commonAxis = new Point(origin.getX(), origin.getY() + 1, origin.getZ());
		Point halfPlane = new Point(origin.getX() + 1, origin.getY(), origin.getZ());

		return new PrismCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, halfPlane);
	}

	/**
	 * Instantiates a ZSlide command.
	 * 
	 * @param jointName The name of the joint to create.
	 * @param bodyNameBefore The name of the body before this joint.
	 * @param bodyNameAfter The name of the body after this joint.
	 * @param origin The local origin.
	 * @throws SelfLoopException Thrown if any parameters are not valid for a prism joint
	 * @throws NullParameterException Thrown if any parameters are null
	 * @throws InvalidParameterException if the command attempts to create a joint linking a body to itself
	 */
	@JointEntry(name = "ZSlide", arg3 = "origin: the origin location of the joint")
	public static PrismCommand CreateZSlide(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin) throws NullParameterException,
			SelfLoopException, InvalidParameterException {

		NullParameterException.check(origin, "origin", 3);

		Point commonAxis = new Point(origin.getX(), origin.getY(), origin.getZ() + 1);
		Point halfPlane = new Point(origin.getX() + 1, origin.getY(), origin.getZ());

		return new PrismCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, halfPlane);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.core.commands.Command#execute(imp.core.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		prismCommand.execute(model);
		dataPrismCommand.execute(model);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.prismCommand).append(this.dataPrismCommand).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(obj instanceof PrismCommand))
			return false;
		PrismCommand other = (PrismCommand) obj;
		if (dataPrismCommand == null) {
			if (other.dataPrismCommand != null)
				return false;
		} else if (!dataPrismCommand.equals(other.dataPrismCommand))
			return false;
		if (prismCommand == null) {
			if (other.prismCommand != null)
				return false;
		} else if (!prismCommand.equals(other.prismCommand))
			return false;
		return true;
	}

}
