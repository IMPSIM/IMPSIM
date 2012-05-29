/**
 * SelfLoopException.java
 * January 22, 2011
 */
package imp.core.exceptions;

/**
 * Represents an exception when two bodies form an enclosed loop.
 * 
 * @author biesew
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class SelfLoopException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = -1709970011490949998L;

	/**
	 * Represents an exception when two bodies form an enclosed loop.
	 * 
	 * @param message The message describing the exception.
	 */
	public SelfLoopException(String message) {
		super(message);
	}
}
