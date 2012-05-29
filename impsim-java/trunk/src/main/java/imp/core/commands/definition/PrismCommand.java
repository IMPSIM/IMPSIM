/**
 * PrismCommand.java
 * March 12, 2011
 */
package imp.core.commands.definition;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Prism;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * 
 * @author dykstran
 * @edit dykstran Updated JavaDoc
 * @edit zastrowm extends DeclarationCommand
 * @version 1.02
 */
public class PrismCommand extends DeclarationCommand {

	/**
	 * Constructor for the prism command.
	 * 
	 * @param bodyNameBefore The name of the body before this joint.
	 * @param bodyNameAfter The name of the body after this joint.
	 * @param jointName The name of the joint to create.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public PrismCommand(String bodyNameBefore, String bodyNameAfter, String jointName) throws NullParameterException, SelfLoopException {
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

		if (!(otherObject instanceof PrismCommand)) {
			return false;
		} else {
			PrismCommand otherCmd = (PrismCommand) otherObject;
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
	public void execute(Model model) throws NameConflictException, SelfLoopException, NullParameterException, JointNotFoundException, InvalidParameterException {

		// Create a new joint
		Joint joint = new Prism(this.jointName);

		// Add the joint to the model
		model.addJoint(joint, this.bodyNameAfter, this.bodyNameBefore);

		// Inform the user
		model.getPrintStream().println("Created Prism Joint " + this.jointName + " linking bodies " + this.bodyNameBefore + " and " + this.bodyNameAfter);
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
		return "PrismCommand [joint=" + this.jointName + ", bodyBefore=" + this.bodyNameBefore + ", bodyAfter=" + this.bodyNameAfter + "]";
	}

}
