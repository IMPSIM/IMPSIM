package imp.core.commands.joints;

import static imp.core.Constants.notNull;
import imp.core.commands.Command;
import imp.core.commands.JointEntry;
import imp.core.commands.data.DataCylinderCommand;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.structures.Point;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * The unified Cylinder Command. It represents a cylinder and it's data
 */
//@formatter:off
@JointEntry(
		name = "Cylinder",
		arg3 = "origin: the origin location of the joint",
		arg4 = "comandAxis: The point defining the axis about which the joint revolves and slides",
		arg5 = "halfPlane: The point defining the axis about which the joint revolves and slides"
		)
//@formatter:on
public class CylinderCommand implements Command {

	/** The data cylinder command that this command represents. */
	private final DataCylinderCommand dataCylinderCommand;

	/** The cylinder command that this command represents. */
	private final imp.core.commands.definition.CylinderCommand cylinderCommand;

	/**
	 * Instantiates a new cylinder command.
	 * 
	 * @param jointName The name of the new Cylinder.
	 * @param bodyNameBefore The name of the first body being joined.
	 * @param bodyNameAfter The name of the second body being joined.
	 * @param origin The origin of the joint.
	 * @param commonAxis The point defining the axis about which the joint revolves and slides.
	 * @param halfPlane The point defining the common half plane of the bodies being joined.
	 * @throws NullParameterException Thrown if a parameter is null.
	 * @throws InvalidParameterException Thrown if 2 parameters occupy the same point.
	 */
	public CylinderCommand(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point commonAxis, Point halfPlane)
			throws NullParameterException, SelfLoopException, InvalidParameterException {

		cylinderCommand = new imp.core.commands.definition.CylinderCommand(bodyNameBefore, bodyNameAfter, jointName);
		dataCylinderCommand = new DataCylinderCommand(origin, commonAxis, halfPlane, jointName);
	}

	/**
	 * Instantiates a new XSlide Command
	 * 
	 * @param jointName The name of the new Cylinder.
	 * @param bodyNameBefore The name of the first body being joined.
	 * @param bodyNameAfter The name of the second body being joined.
	 * @param origin The origin of the joint.
	 * @throws NullParameterException Thrown if a parameter is null.
	 * @throws InvalidParameterException Thrown if 2 parameters occupy the same point.
	 */
	public static PrismCommand createXSlide(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point commonAxis, Point bodyAxisFirst,
			Point bodyAxisSecond) throws NullParameterException, SelfLoopException, InvalidParameterException {
		//@formatter:off
		return new PrismCommand(
				jointName, 
				bodyNameBefore, 
				bodyNameAfter, 
				origin, 
				new Point(notNull(origin, 0).getX()+1, notNull(origin, 0).getY(), notNull(origin, 0).getZ()), 
				new Point(notNull(origin, 0).getX(), notNull(origin, 0).getY()-1, notNull(origin, 0).getZ()));
		//@formatter:on
	}

	/*
	 * (non-Javadoc)
	 * @see imp.core.commands.Command#execute(imp.core.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		this.cylinderCommand.execute(model);
		this.dataCylinderCommand.execute(model);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.cylinderCommand).append(this.dataCylinderCommand).toHashCode();
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
		if (!(obj instanceof CylinderCommand))
			return false;
		CylinderCommand other = (CylinderCommand) obj;
		if (cylinderCommand == null) {
			if (other.cylinderCommand != null)
				return false;
		} else if (!cylinderCommand.equals(other.cylinderCommand))
			return false;
		if (dataCylinderCommand == null) {
			if (other.dataCylinderCommand != null)
				return false;
		} else if (!dataCylinderCommand.equals(other.dataCylinderCommand))
			return false;
		return true;
	}

}
