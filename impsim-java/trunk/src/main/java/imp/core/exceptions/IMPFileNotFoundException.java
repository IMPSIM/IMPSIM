/**
 * September 25, 2011
 * IMPFileNotFoundException.java
 */
package imp.core.exceptions;

/**
 * Represents a file not found exception within the IMP framework.
 * 
 * @author dykstran
 * @version 1.0
 */
public class IMPFileNotFoundException extends IMPException {

	/**
	 * Generated serial ID.
	 */
	private static final long serialVersionUID = 8021603702016169835L;

	/**
	 * Represents an IMP file not being found when loading a model.
	 * 
	 * @param message The error message.
	 */
	public IMPFileNotFoundException(String message) {
		super(message);
	}

}
