/**
 * IncorrectNumberOfPoints.java
 * May 11, 2011
 */
package imp.core.exceptions.parser;

import imp.core.exceptions.IMPException;

/**
 * Exception to be thrown when we don't have enough points in our data statement.
 * 
 * @author zastrowm
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class IncorrectNumberOfPoints extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = 8889659591857749141L;

	/**
	 * Exception to be thrown when we don't have enough points in our data statement.
	 * 
	 * @param expected How many points we expected.
	 * @param found How many points we actually got.
	 */
	public IncorrectNumberOfPoints(int expected, int found) {
		super((found > expected ? "Too many points in data statement." : "Not enough points in data statement.") + " Expected " + expected + " but found "
				+ found);
	}
}
