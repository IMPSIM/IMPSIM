package imp.core.commands.joints;

import imp.core.commands.Command;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Revolute;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Represents the base for a joint command
 */
public abstract class BaseJointCommand implements Command {

	// The body before this joint.
	protected final String bodyNameBefore;

	// The body after this joint.
	protected final String bodyNameAfter;

	// The name of this joint.
	protected final String jointName;

	/**
	 * General definition for definition commands. It implements the command used to create a * joint to link together
	 * two bodies.
	 * 
	 * @param jointName The name of the joint.
	 * @param bodyNameAfter The body after the joint.
	 * @param bodyNameBefore The body before the joint.
	 * @throws NullParameterException Thrown if any parameters are null.
	 * @throws SelfLoopException Thrown if the command attempts to create a joint linking a body to itself.
	 */
	public BaseJointCommand(String jointName, String bodyNameBefore, String bodyNameAfter) throws SelfLoopException {
		NullParameterException.check(bodyNameBefore, "bodyNameBefore", 0);
		NullParameterException.check(bodyNameAfter, "bodyNameAfter", 1);
		NullParameterException.check(jointName, "jointName", 2);

		if (bodyNameBefore.equals(bodyNameAfter)) { // check if both body names are the same
			throw new SelfLoopException("A joint cannot link a body to itself (Two body names cannot be equal)");
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
	public void execute(Model model) throws IMPException {
		NullParameterException.check(model, "model", 0);

		// create revolute joint called name
		Joint j = new Revolute(this.jointName);
		// adds the joint to the model
		model.addJoint(j, this.bodyNameAfter, this.bodyNameBefore);

		model.getPrintStream().println("Created Joint " + this.jointName + " linking bodies " + this.bodyNameBefore + " and " + this.bodyNameAfter);

	}

	/**
	 * Throw an InvalidParameterException if the condition is true.
	 * 
	 * @param condition the condition
	 * @param param the index of the parameter (0 based) that is causing this issue.
	 * @param message The message describing the exception.
	 */
	protected static void checkParameter(boolean condition, int num, String message) {
		InvalidParameterException.throwIf(condition, num, message);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		return new HashCodeBuilder().append(jointName).append(bodyNameBefore).append(bodyNameAfter).toHashCode();
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
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof BaseJointCommand)) {
			return false;
		}
		BaseJointCommand other = (BaseJointCommand) obj;
		if (bodyNameAfter == null) {
			if (other.bodyNameAfter != null) {
				return false;
			}
		} else if (!bodyNameAfter.equals(other.bodyNameAfter)) {
			return false;
		}
		if (bodyNameBefore == null) {
			if (other.bodyNameBefore != null) {
				return false;
			}
		} else if (!bodyNameBefore.equals(other.bodyNameBefore)) {
			return false;
		}
		if (jointName == null) {
			if (other.jointName != null) {
				return false;
			}
		} else if (!jointName.equals(other.jointName)) {
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
		return jointName + " " + bodyNameBefore + " " + bodyNameAfter;
	}

}
