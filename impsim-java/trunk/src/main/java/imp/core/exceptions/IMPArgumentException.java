/**
 * IMPArgumentException.java
 * May 8, 2011
 */
package imp.core.exceptions;

/**
 * Represents an argument exception for the command line IMP.
 * 
 * @author dykstran
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class IMPArgumentException extends IMPException {

	/**
	 * Generated serial ID.
	 */
	private static final long serialVersionUID = -3974946755255719209L;

	/**
	 * Represents an argument exception for the command line IMP.
	 * 
	 * @param message The message detailing the reason this exception was thrown.
	 */
	public IMPArgumentException(String message) {
		super(message);
	}

}
