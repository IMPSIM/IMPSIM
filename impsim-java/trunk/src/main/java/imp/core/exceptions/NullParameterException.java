/**
 * NullParameterException.java
 * May 11, 2011
 */
package imp.core.exceptions;

/**
 * Represents an exception when the user attempts to pass a null value to a parameter.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @edit zastrowm extends IMPRuntimeException
 * @version 1.01
 * 
 */
public class NullParameterException extends IMPRuntimeException {

	/**
	 * The parameter number that caused the exception.
	 */
	private int paramNum;

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 7622072340152682633L;

	/**
	 * Represents an exception when the user attempts to pass a null value to a parameter.
	 * 
	 * @param message The message describing the exception.
	 * @param param the number of the parameter (0 based) that is causing the issue.
	 */
	public NullParameterException(String message, int param) {
		super(message);
		this.paramNum = param;
	}

	/**
	 * Returns the index of the parameter that caused the exception.
	 * 
	 * @return The index of the parameter with the problem.
	 */
	public int getParamNum() {
		return this.paramNum;
	}

	/**
	 * Check if a parameter is null, and if so throw an exception
	 * 
	 * @param parameter the parameter to check
	 * @param name the name of the parameter
	 * @param paramNumber the parameter number
	 */
	public static void check(Object parameter, String name, int paramNumber) {
		if (parameter == null) {
			String msg = String.format("Parameter %s (paramter #%d) cannot be null.", name, paramNumber);
			throw new NullParameterException(msg, paramNumber);
		}
	}
}
