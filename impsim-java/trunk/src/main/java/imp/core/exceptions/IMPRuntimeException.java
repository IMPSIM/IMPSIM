/**
 * IMPRuntimeExceptoin.java
 * Sep 18, 2011
 */
package imp.core.exceptions;

/**
 * A class to extend from so that we don't have to catch NullPointerExceptions
 * 
 * @author zastrowm
 * @version 1.0
 */
public class IMPRuntimeException extends RuntimeException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6710392563753075911L;

	/**
	 * Create a new IMPRuntimeException
	 * 
	 * @param message the error message
	 */
	public IMPRuntimeException(String message) {
		super(message);
	}

	
	
}
