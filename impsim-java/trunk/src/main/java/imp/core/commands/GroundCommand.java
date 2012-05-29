package imp.core.commands;

import imp.core.exceptions.IMPException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Model;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class for implementing setting a model's ground to a specific body
 * 
 * @author zastrowm
 */
public class GroundCommand implements Command {

	/**
	 * The name of the ground.
	 */
	private String name;

	/**
	 * Constructor for the ground command.
	 * 
	 * @param groundName The name of the body to be set to ground.
	 * @throws NullParameterException Thrown if the name is a null value.
	 */
	public GroundCommand(String groundName) throws NullParameterException {
		NullParameterException.check(groundName, "groundName", 0);

		this.name = groundName;
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

		if (!(otherObject instanceof GroundCommand)) {
			return false;
		} else {
			GroundCommand otherCmd = (GroundCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.name.equals(this.name);
		}
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		// sets the model's ground parameter to the body
		model.setGround(this.name);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "GroundCommand [name=" + this.name + "]";
	}

}
