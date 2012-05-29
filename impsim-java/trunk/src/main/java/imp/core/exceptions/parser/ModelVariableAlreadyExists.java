/**
 * ModelVariableDoesNotExist.java
 * Sep 27, 2011
 */
package imp.core.exceptions.parser;

import imp.core.exceptions.IMPException;

/**
 * 
 * 
 * @author zastrowm
 * @version 1.0
 */
public class ModelVariableAlreadyExists extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 2938161792585374437L;

	/**
	 * The name of the variable that caused this exception.
	 */
	public final String variableName;

	/**
	 * @param name the name of the variable.
	 */
	public ModelVariableAlreadyExists(String name) {
		super("The variable " + name + " already exists in this model");

		variableName = name;
	}

}
