/**
 * CylinderCommand.java
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
import imp.core.model.joints.Cylinder;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * This is the RevoluteCommand. It implements the command used to create a revolute joint to link together two bodies.
 * 
 * @author edmissonj
 * @edit zastrowm (.equals())
 * @edit zastrowm extends DeclarationCommand
 * @version 1.02
 */
public class CylinderCommand extends DeclarationCommand {

	/**
	 * Method for taking the build information which is input and passing it to the execute method
	 * 
	 * 
	 * @param bodyNameBefore The name of the first body being joined.
	 * @param bodyNameAfter The name of the second body being joined.
	 * @param jointName The name of the new Cylinder.
	 * @throws NullParameterException Thrown if a null parameter is passed in.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public CylinderCommand(String bodyNameBefore, String bodyNameAfter, String jointName) throws NullParameterException, SelfLoopException {
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

		if (!(otherObject instanceof CylinderCommand)) {
			return false;
		} else {
			CylinderCommand otherCmd = (CylinderCommand) otherObject;
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
		// create cylinder joint named after the name input
		Joint c = new Cylinder(this.jointName);

		// adds the joint to the model
		model.addJoint(c, this.bodyNameAfter, this.bodyNameBefore);
		
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
		return "CylinderCommand [joint=" + this.jointName + ", bodyBefore=" + this.bodyNameBefore + ", bodyAfter=" + this.bodyNameAfter + "]";
	}
}
