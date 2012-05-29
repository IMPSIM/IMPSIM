/**
 * InvalidFunctionSignature.java
 * Sep 24, 2011
 */
package imp.core.exceptions.expressions;

import imp.core.exceptions.IMPException;

/**
 * Exception for when someone tries to create a Function with a method that uses an invalid type
 * 
 * @author zastrowm
 * @version 1.0
 */
public class InvalidFunctionSignature extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 57303821781489231L;

	/**
	 * Constructor for invalid parameter type
	 * 
	 * @param paramNumber the parameter number
	 * @param type the type of the function
	 */
	public InvalidFunctionSignature(int paramNumber, Class<?> type) {
		super("Parameter " + paramNumber + " is not a valid type for a Function.  Type was " + type.toString());
	}
	
	/**
	 * Constructor for invalid return type
	 * 
	 * @param type the type of the function
	 */
	public InvalidFunctionSignature(Class<?> type) {
		super("Return type is not a valid type for a Function.  Type was " + type.toString());
	}
	
	/**
	 * Constructor for not static/public
	 */
	public InvalidFunctionSignature() {
		super("Function must be public and static");
	}

}
