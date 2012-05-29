/**
 * InvalidDatatypeException.java
 * May 11, 2011
 */
package imp.core.exceptions;

/**
 * Represents when a Contains method would return true, but for the wrong type of element i.e. a body instead of a
 * joint.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class InvalidDatatypeException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 4225120733957534170L;

	/**
	 * Represents when a Contains method would return true, but for the wrong type of element i.e. a body instead of a
	 * joint.
	 * 
	 * @param message The message describing the exception.
	 */
	public InvalidDatatypeException(String message) {
		super(message);
	}

}
