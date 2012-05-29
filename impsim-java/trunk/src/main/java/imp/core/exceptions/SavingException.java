/**
 * SavingException.java
 * October 9, 2011
 */
package imp.core.exceptions;

/**
 * Represents an exception when the IMP model is being saved.
 * 
 * @author dykstran
 * @version 1.0
 */
public class SavingException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 3453396619545066656L;

	/**
	 * Represents an exception when the IMP model is being saved.
	 * 
	 * @param message the message describing the failure.
	 */
	public SavingException(String message) {
		super(message);
	}

}
