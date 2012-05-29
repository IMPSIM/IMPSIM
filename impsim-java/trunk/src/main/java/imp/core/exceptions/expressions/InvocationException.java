/**
 * 
 */
package imp.core.exceptions.expressions;

import imp.core.exceptions.IMPRuntimeException;

/**
 * Exception that occurs while evaluating an expression
 * 
 * @author zastrowm
 */
public class InvocationException extends IMPRuntimeException {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 7889264679735531121L;

	/** The inner exception. */
	private final Exception innerException;

	/**
	 * Instantiates a new invocation exception.
	 * 
	 * @param exception the exception
	 */
	public InvocationException(Exception exception) {
		super("Exception caught while evaluating expression.");

		innerException = exception;
	}

	/**
	 * Gets the inner exception.
	 * 
	 * @return the innerException
	 */
	public Exception getInnerException() {
		return innerException;
	}

}
