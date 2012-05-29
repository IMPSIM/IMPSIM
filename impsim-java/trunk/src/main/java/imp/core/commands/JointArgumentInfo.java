/**
 * 
 */
package imp.core.commands;

/**
 * Contains information about a joint's arguments
 * 
 * @author zastrowm
 */
public class JointArgumentInfo {

	/** The class. */
	public final Class<?> theClass;

	/** The name. */
	public final String name;

	/** The description. */
	public final String description;

	/** The argument number. */
	public final int argumentNumber;

	/**
	 * Instantiates a new argument.
	 * 
	 * @param theClass the the class of the type of the argument
	 * @param name the name of the argument
	 * @param description a plain-text description of the argument
	 * @param argumentNumber the argument number
	 */
	public JointArgumentInfo(Class<?> theClass, String name, String description, int argumentNumber) {
		this.theClass = theClass;
		this.name = name;
		this.description = description;
		this.argumentNumber = argumentNumber;
	}
}
