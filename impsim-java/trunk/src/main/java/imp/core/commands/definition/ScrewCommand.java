/**
 * ScrewCommand.java
 * March 19, 2011
 */

package imp.core.commands.definition;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Screw;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for implementing the command for creating a helical (screw) joint.
 * 
 * @author hellmerj
 * @edit dykstran Updated JavaDoc
 * @edit zastrowm extends DeclarationCommand
 * @version 1.02
 */
public class ScrewCommand extends DeclarationCommand {

	/**
	 * This is the ScrewCommand. It implements the command used to create a screw joint to link together two bodies.
	 * 
	 * @param bodyNameAfter The name of the body after the joint.
	 * @param bodyNameBefore The name of the body before the joint.
	 * @param jointName The name of the joint.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public ScrewCommand(String bodyNameBefore, String bodyNameAfter, String jointName) throws NullParameterException, SelfLoopException {
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

		if (!(otherObject instanceof ScrewCommand)) {
			return false;
		} else {
			ScrewCommand otherCmd = (ScrewCommand) otherObject;
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

		// create screw joint called name
		Joint j = new Screw(this.jointName);

		// adds the joint to the model
		model.addJoint(j, this.bodyNameAfter, this.bodyNameBefore);

		// display message for joint creation
		model.getPrintStream().println("Created Screw Joint named " + this.jointName + " linking bodies " + this.bodyNameBefore + " and " + this.bodyNameAfter);
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
		return "ScrewCommand [joint=" + this.jointName + ", bodyBefore=" + this.bodyNameBefore + ", bodyAfter=" + this.bodyNameAfter + "]";
	}
}
