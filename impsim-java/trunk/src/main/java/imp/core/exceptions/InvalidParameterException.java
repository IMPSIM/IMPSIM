/**
 * InvalidParameterException.java
 * May 11, 2011
 */
package imp.core.exceptions;

/**
 * Represents when the Command is passed in a parameter that is bad.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class InvalidParameterException extends IMPRuntimeException {

	/**
	 * The index of the parameter causing the exception.
	 */
	private final int paramNum;

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 356266066432270666L;

	/**
	 * Represents when the Command is passed in a parameter that is bad.
	 * 
	 * @param message The message describing the exception.
	 * @param param the index of the parameter (0 based) that is causing this issue.
	 */
	public InvalidParameterException(String message, int param) {
		super(message);
		this.paramNum = param;
	}

	/**
	 * Returns the index of the parameter with the problem.
	 * 
	 * @return The index of the parameter with the problem.
	 */
	public int getParamNum() {
		return this.paramNum;
	}

	/**
	 * Throw an InvalidParameterException if the condition is true.
	 * 
	 * @param condition the condition
	 * @param param the index of the parameter (0 based) that is causing this issue.
	 * @param message The message describing the exception.
	 */
	public static void throwIf(boolean condition, int param, String message) {
		if (condition) {
			throw new InvalidParameterException(message, param);
		}
	}
}
