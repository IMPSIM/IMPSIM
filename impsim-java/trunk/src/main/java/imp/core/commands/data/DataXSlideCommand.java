/**
 * DataXSlideCommand.java
 * March 24, 2011
 */
package imp.core.commands.data;

import static imp.core.Constants.notNull;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.structures.Point;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for instantiating the data in an XSlide joint to be something other than the default values. The execute method
 * to be used is identical to the one in the Data Prism Command since the only difference is a question of axis, and
 * that is handled by the constructor.
 * 
 * @author dykstran
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class DataXSlideCommand extends DataPrismCommand {

	/**
	 * Method for collecting the data to be used in the execution of the command.
	 * 
	 * @param origin The location of the origin of the joint.
	 * @param jointName The name of the slide joint to add data to.
	 * @throws NullParameterException If an parameters are null.
	 * @throws InvalidParameterException Thrown if any of the parameters are values which would cause the pin to
	 *             malfunction.
	 */
	public DataXSlideCommand(Point origin, String jointName) throws NullParameterException, InvalidParameterException {
		super(origin, 
				new Point(notNull(origin, 0).getX()+1, notNull(origin, 0).getY(), notNull(origin, 0).getZ()), 
				new Point(
				notNull(origin, 0).getX(), notNull(origin, 0).getY()-1, notNull(origin, 0).getZ()), jointName);
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

		if (!(otherObject instanceof DataXSlideCommand)) {
			return false;
		} else {
			DataXSlideCommand otherCmd = (DataXSlideCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.name.equals(this.name) && otherCmd.origin.equals(this.origin) && otherCmd.commonAxis.equals(this.commonAxis)
					&& otherCmd.halfPlane.equals(this.halfPlane);
		}

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
		return "DataXSlideCommand [name=" + this.name + ", origin=" + this.origin + ", commonAxis=" + this.commonAxis + ", halfPlane=" + this.halfPlane + "]";
	}
}
