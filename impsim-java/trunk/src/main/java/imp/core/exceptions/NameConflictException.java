/**
 * NameConflictException.java
 * January 22, 2011
 */

package imp.core.exceptions;

/**
 * Represents an exception when an element is added to a model that already contains an element by that name.
 * 
 * @author biesew
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class NameConflictException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 7817548671321503746L;

	/**
	 * Represents an exception when an element is added to a model that already contains an element by that name.
	 * 
	 * @param elementName the name of the element causing this exception.
	 */
	public NameConflictException(String elementName) {
		super("An element named `" + elementName + "` is already present in this model.");
	}
}
