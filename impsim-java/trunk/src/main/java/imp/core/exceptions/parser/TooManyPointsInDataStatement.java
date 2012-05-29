/**
 * TooManyPointsInDataStatement.java
 * May 11, 2011
 */
package imp.core.exceptions.parser;

import org.antlr.runtime.tree.Tree;

/**
 * Exception to be thrown when we have too many points in our data statement.
 * 
 * @author zastrowm
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public class TooManyPointsInDataStatement extends ParserException {

	private static final long serialVersionUID = 8889659591857749141L;

	/**
	 * Exception to be thrown when we have too many points in our data statement.
	 * 
	 * @param token The token which contains the start and end index.
	 * @param expected How many points we expected.
	 * @param found How many points we actually got.
	 */
	public TooManyPointsInDataStatement(Tree token, int expected, int found) {
		super(token, "Too many points in data statement.  Expected " + expected + " but found " + found);
	}

	/**
	 * Exception to be thrown when we have too many points in our data statement.
	 * 
	 * @param tokenStart The token which contains the start index.
	 * @param tokenEnd The token which contains the end index.
	 * @param expected How many points we expected.
	 * @param found How many points we actually got.
	 */
	public TooManyPointsInDataStatement(Tree tokenStart, Tree tokenEnd, int expected, int found) {
		super(tokenStart, tokenEnd, "Too many points in data statement.  Expected " + expected + " but found " + found);
	}

}
