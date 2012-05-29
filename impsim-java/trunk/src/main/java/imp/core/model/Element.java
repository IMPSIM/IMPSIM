/**
 * Element.java
 * May 11, 2011
 */

package imp.core.model;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.observer.AbstractSubject;

/**
 * Represents an element (body, joint...) of a model.
 * 
 * @author biesew
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public abstract class Element extends AbstractSubject {

	/**
	 * The name of this element.
	 */
	protected String name;

	/**
	 * Creates a new element.
	 * 
	 * @param name The name attribute of the Element to be created.
	 * @throws NullParameterException Thrown if the string is null.
	 * @throws InvalidParameterException Thrown if the name is empty
	 */
	public Element(String name) throws NullParameterException, InvalidParameterException {
		if (name == null) {
			throw new NullParameterException("The name for this element cannot be null.", 0);
		}
		
		if ( name.equals("") ) {
			throw new InvalidParameterException("A name for the element cannot be empty.", 0);
		}
		
		this.name = name;
	}

	/**
	 * Gets the name of this element.
	 * 
	 * @return The name of this Element.
	 */
	public final String getName() {
		return this.name;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return this.name;
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {

		// check if same object
		if (this == otherObject) {
			return true;
		}

		// check if passed object is a Element
		if (!(otherObject instanceof Element)) {
			return false;
		} else {
			// cast object into cylinder for comparison
			Element otherElm = (Element) otherObject;
			// return whether EVERY attribute is the same
			return  this.name.equals(otherElm.name);
		}
	}
}
