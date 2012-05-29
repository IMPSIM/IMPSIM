/**
 * JointNotFoundException.java
 * May 11, 2011
 */
package imp.core.exceptions;

/**
 * Represents when a command is given to populate data on a nonexistent joint.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class JointNotFoundException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 4507138314419664038L;

	/**
	 * Represents when a command is given to populate data on a nonexistent joint.
	 * 
	 * @param message The message describing the exception.
	 */
	public JointNotFoundException(String message) {
		super(message);
	}

}
