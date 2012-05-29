/**
 * MethodReturnValue.java
 * Sep 16, 2011
 */
package imp.core.exceptions.expressions;

import imp.core.exceptions.IMPRuntimeException;
import imp.core.expressions.FunctionExpression;

/**
 * An function expression's method returned the wrong value type
 * 
 * @author zastrowm
 * @version 1.0
 */
public class MethodReturnValue extends IMPRuntimeException {

	/**
	 * The function that was attempted to be executed
	 */
	public final FunctionExpression function;

	private static final long serialVersionUID = -2734105789970196405L;

	/**
	 * Constructor
	 * 
	 * @param message the message to output
	 * @param function the function that was executing
	 */
	public MethodReturnValue(String message, FunctionExpression function) {
		super(message);
		this.function = function;
	}

}
