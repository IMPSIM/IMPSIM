/**
 * Command.java
 * May 10, 2011
 */
package imp.core.commands;

import imp.core.exceptions.IMPException;
import imp.core.model.Model;

/**
 * The interface that all IMP commands must use for the API.
 * 
 * @author dykstran
 * @version 1.0
 */
public interface Command {

	/**
	 * Executes the command (ie: Adds the joints to the model...)
	 * 
	 * @param model The model this command is executed on.
	 * @throws IMPException Thrown if problems arise during execution. The specific exception thrown will contain more
	 *             information about the nature of the exception.
	 */
	public void execute(Model model) throws IMPException;

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString();

}
