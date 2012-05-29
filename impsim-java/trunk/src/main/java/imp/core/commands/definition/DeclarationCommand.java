/**
 * DeclarationCommand.java
 */
package imp.core.commands.definition;

import imp.core.commands.Command;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;

/**
 * Superclass for all commands which create joints
 * 
 * @author zastrowm
 * 
 */
public abstract class DeclarationCommand implements Command {

	// The body before this joint.
	protected String bodyNameBefore;

	// The body after this joint.
	protected String bodyNameAfter;

	// The name of this joint.
	protected String jointName;

	/**
	 * General definition for definition commands. It implements the command used to create a * joint to link together
	 * two bodies.
	 * 
	 * @param bodyNameAfter The body after the joint.
	 * @param bodyNameBefore The body before the joint.
	 * @param jointName The name of the joint.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public DeclarationCommand(String bodyNameBefore, String bodyNameAfter, String jointName) throws NullParameterException, SelfLoopException {

		if (bodyNameBefore == null) { // check if first body name is null parameter
			throw new NullParameterException("The first body name cannot be null", 0);
		}

		if (bodyNameAfter == null) { // check if second body name is null parameter
			throw new NullParameterException("The second body name cannot be null", 1);
		}

		if (bodyNameBefore.equals(bodyNameAfter)) { // check if both body names are the same
			throw new SelfLoopException("A joint cannot link a body to itself (Two body names cannot be equal)");
		}

		if (jointName == null) { // check if joint name is a null parameter
			throw new NullParameterException("The joint name cannot be null", 2);
		}

		this.bodyNameBefore = bodyNameBefore;
		this.bodyNameAfter = bodyNameAfter;
		this.jointName = jointName;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public abstract void execute(Model model) throws IMPException;

}
