/**
 * 
 */
package imp.core.commands;

import imp.core.exceptions.IMPException;
import imp.core.model.Model;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * A command which marks the begining of a new model
 * 
 * @author zastrowm
 */
public class ModelCommand implements Command {

	/** The model name. */
	public final String modelName;

	/**
	 * Instantiates a new model command.
	 * 
	 * @param modelName the name of the model to create
	 */
	public ModelCommand(String modelName) {
		this.modelName = modelName;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.core.commands.Command#execute(imp.core.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		// TODO implement

	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		return new HashCodeBuilder().append(this.modelName).toHashCode();
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
		if (!(obj instanceof ModelCommand)) {
			return false;
		}
		ModelCommand other = (ModelCommand) obj;
		if (modelName == null) {
			if (other.modelName != null) {
				return false;
			}
		} else if (!modelName.equals(other.modelName)) {
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
		return "ModelCommand [modelName=" + modelName + "]";
	}

}
