/**
 * IMPException.java
 * January 22, 2011
 */

package imp.core.exceptions;

/**
 * Represents a general IMP exception.
 * 
 * @author biesew
 */
public abstract class IMPException extends Exception {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = -4129669632000025677L;

	/**
	 * Represents a general IMP exception.
	 * 
	 * @param message The message describing the exception.
	 */
	public IMPException(String message) {
		super(message);
	}
}
