/**
 * LoopException.java
 * April 5, 2011
 */

package imp.core.exceptions;

/**
 * Exceptions dealing with loop finding.
 * 
 * @author workmanjz
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class LoopException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = -1709970011490949998L;

	/**
	 * Represents an exception during loop finding.
	 * 
	 * @param message The message describing the exception.
	 */
	public LoopException(String message) {
		super(message);
	}
}
