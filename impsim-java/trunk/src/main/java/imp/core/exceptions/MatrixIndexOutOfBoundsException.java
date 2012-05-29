/**
 * MatrixIndexOutOfBoundsException.java
 * May 11, 2011
 */
package imp.core.exceptions;

/**
 * Represents an exception when the user attempts to manipulate a value from a matrix that does not exist or is denied
 * access to.
 * 
 * @author dykstran
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class MatrixIndexOutOfBoundsException extends IMPException {

	/**
	 * Auto generated serial version UID.
	 */
	private static final long serialVersionUID = 2396814054400580114L;

	/**
	 * The specified value of the matrix is out of bounds or denied access to.
	 * 
	 * @param message The message to describe why the index is inaccessible.
	 */
	public MatrixIndexOutOfBoundsException(String message) {
		super(message);
	}

}
