/**
 * BevelCommand.java
 * May 10, 2011
 */
package imp.core.commands.definition;

import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Commands for creating a bevel joint.
 * 
 * @author zastrowm
 * @version 1.1 Initial outline of method - execute() throws UnsupportedOperationException
 * 
 */
public class BevelCommand extends DeclarationCommand {

	/**
	 * This is the BevelCommand. It implements the command used to create a bevel joint to link together two bodies.
	 * 
	 * @param bodyNameAfter The name of the body after the joint.
	 * @param bodyNameBefore The name of the body before the joint.
	 * @param jointName The name of the joint.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public BevelCommand(String bodyNameBefore, String bodyNameAfter, String jointName) throws NullParameterException, SelfLoopException {
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

		if (!(otherObject instanceof BevelCommand)) {
			return false;
		} else {
			BevelCommand otherCmd = (BevelCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.bodyNameBefore.equals(this.bodyNameBefore) && otherCmd.bodyNameAfter.equals(this.bodyNameAfter)
					&& otherCmd.jointName.equals(this.jointName);
		}

	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.definition.DeclarationCommand#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws NameConflictException, SelfLoopException, NullParameterException, JointNotFoundException {
		throw new UnsupportedOperationException();
		// TODO: implement bevel command
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
		return "BevelCommand [joint=" + this.jointName + ", bodyBefore=" + this.bodyNameBefore + ", bodyAfter=" + this.bodyNameAfter + "]";
	}
}
