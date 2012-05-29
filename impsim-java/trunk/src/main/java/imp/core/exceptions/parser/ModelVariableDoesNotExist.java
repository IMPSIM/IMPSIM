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
public class ModelVariableDoesNotExist extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 4231107151431073533L;

	/**
	 * The name of the variable that caused this exception.
	 */
	public final String variableName;

	/**
	 * @param name the name of the variable.
	 */
	public ModelVariableDoesNotExist(String name) {
		super("The variable " + name + " does not exist in this model");

		variableName = name;
	}

}
