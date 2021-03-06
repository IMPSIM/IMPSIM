/**
 * YSlideCommand.java
 * March 24, 2011
 */
package imp.core.commands.definition;

import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for implementing the command used to create an YSlide joint to link together two bodies. The execute method
 * would be the same as in the slide command which it extends.
 * 
 * @author dykstran
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class YSlideCommand extends PrismCommand {

	/**
	 * Method for collecting the data to be used in the execute method.
	 * 
	 * @param bodyNameBefore The name of the first body being linked.
	 * @param bodyNameAfter The name of the second body being linked.
	 * @param jointName The name of the YSlide.
	 * @throws NullParameterException This is thrown if any of the parameters are Null Values.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public YSlideCommand(String bodyNameBefore, String bodyNameAfter, String jointName) throws NullParameterException, SelfLoopException {
		super(bodyNameBefore, bodyNameAfter, jointName);
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

		if (!(otherObject instanceof YSlideCommand)) {
			return false;
		} else {
			YSlideCommand otherCmd = (YSlideCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.bodyNameBefore.equals(this.bodyNameBefore) && otherCmd.bodyNameAfter.equals(this.bodyNameAfter)
					&& otherCmd.jointName.equals(this.jointName);
		}

	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.jointName).append(this.bodyNameBefore).append(this.bodyNameAfter).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "YSlideCommand [joint=" + this.jointName + ", bodyBefore=" + this.bodyNameBefore + ", bodyAfter=" + this.bodyNameAfter + "]";
	}

}
