/**
 * DataGearCommand.java
 * May 10, 2011
 */
package imp.core.commands.data;

import imp.core.commands.Command;
import imp.core.exceptions.IMPException;
import imp.core.model.Model;
import imp.core.structures.Point;

/**
 * Class for assigning data to a gear joint.
 * 
 * @author zastrowm made stub code so that it could be parsed
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class DataGearCommand implements Command {

	/**
	 * @param ratio
	 * @param distance
	 * @param p1
	 * @param p2
	 * @param p3
	 * @param jointName
	 */
	public DataGearCommand(double ratio, double distance, Point p1, Point p2, Point p3, String jointName) {
		// TODO Implement data gear command
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		// TODO implement gear execute
	}
}
