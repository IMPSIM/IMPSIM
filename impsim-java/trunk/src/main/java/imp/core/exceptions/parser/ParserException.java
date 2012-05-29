/**
 * ParserException.java
 * May 11, 2011
 */

package imp.core.exceptions.parser;

import imp.core.exceptions.IMPException;

import org.antlr.runtime.tree.Tree;

/**
 * Implementation of a generic Parser Exception.
 * 
 * @author zastrowm
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 */
public abstract class ParserException extends IMPException {

	/**
	 * Generated serial version UID.
	 */
	private static final long serialVersionUID = -4247183914758178013L;

	/**
	 * The start character index where the error occurred in the document.
	 */
	int indexStart;

	/**
	 * The end character index where the error occurred in the document.
	 */
	int indexEnd;

	/**
	 * The message associated with the error.
	 */
	String message;

	/**
	 * Constructor for generic error.
	 * 
	 * @param tIndexStart The start character index where the error occurred in the document.
	 * @param tIndexEnd The end character index where the error occurred in the document.
	 * @param tMessage The message associated with the error.
	 */
	ParserException(int tIndexStart, int tIndexEnd, String tMessage) {
		super("Parsing Error (" + tIndexStart + "," + tIndexEnd + "): " + tMessage);
		this.indexStart = tIndexStart;
		this.indexEnd = tIndexEnd;
		this.message = tMessage;
	}

	/**
	 * Convenience constructor.
	 * 
	 * @param token The token containing the start index and end index.
	 * @param message The message associated with the error.
	 */
	ParserException(Tree token, String message) {
		this(token.getTokenStartIndex(), token.getTokenStopIndex(), message);
	}

	/**
	 * Convenience constructor.
	 * 
	 * @param tokenStart The token containing start index.
	 * @param tokenEnd The token containing the end index.
	 * @param message The message associated with the error.
	 */
	ParserException(Tree tokenStart, Tree tokenEnd, String message) {
		this(tokenStart.getTokenStartIndex(), tokenEnd.getTokenStopIndex(), message);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Throwable#toString()
	 */
	@Override
	public String toString() {
		return "Parsing Error (" + this.indexStart + "," + this.indexEnd + "): " + this.message;
	}

}
