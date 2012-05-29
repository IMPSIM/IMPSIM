/**
 * BodyNotFoundException.java
 * May 11, 2011
 */
package imp.core.exceptions;

/**
 * Represents when a command is given to populate data on a nonexistent body.
 * 
 * @author edmissonj
 * 
 */
public class BodyNotFoundException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 4977420235698083079L;

	/**
	 * Represents when a command is given to populate data on a nonexistent body.
	 * 
	 * @param message The message describing the exception.
	 */
	public BodyNotFoundException(String message) {
		super(message);
	}

}
