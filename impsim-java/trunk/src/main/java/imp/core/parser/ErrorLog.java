/**
 * ErrorLog.java
 * May 12, 2011
 */
package imp.core.parser;

import imp.core.exceptions.IMPException;
import imp.core.parser.ErrorLog.ErrorContainer;

import java.util.Iterator;
import java.util.LinkedList;

import org.antlr.runtime.Token;
import org.antlr.runtime.tree.Tree;

/**
 * Class to maintain a list of exceptions/errors and their locations in the source code.
 * 
 * @author zastrowm
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class ErrorLog implements Iterable<ErrorContainer> {

	/**
	 * Class to hold exceptions and their start/end locations.
	 * 
	 * @author zastrowm
	 * @review edmissonj
	 */
	public static class ErrorContainer {

		// The exception of this error.
		final IMPException exception;

		// Index of the starting character.
		final int characterStart;

		// Index of the ending character.
		final int characterEnd;

		// Starting line number.
		final int lineStart;

		// Ending line number.
		final int lineEnd;

		// Whether the end is valid
		final boolean doesEnd;

		/**
		 * Construct a new ExceptionContainer.
		 * 
		 * @param tException The exception.
		 * @param lStart The line where the error starts.
		 * @param cStart The character in that line where the error starts.
		 * @param lEnd The line where the error ends.
		 * @param cEnd The character in that line where the error ends.
		 */
		public ErrorContainer(IMPException tException, int lStart, int cStart, int lEnd, int cEnd) {
			this.exception = tException;
			this.lineStart = lStart;
			this.lineEnd = lEnd;
			this.characterStart = cStart;
			this.characterEnd = cEnd;
			this.doesEnd = true;
		}

		/**
		 * Construct a new ExceptionContainer.
		 * 
		 * @param tException The exception.
		 * @param lStart The line where the error starts.
		 * @param cStart The character in that line where the error starts.
		 */
		public ErrorContainer(IMPException tException, int lStart, int cStart) {
			this.exception = tException;
			this.lineStart = lStart;
			this.lineEnd = -1;
			this.characterStart = cStart;
			this.characterEnd = -1;
			this.doesEnd = false;
		}

		/*
		 * (non-Javadoc)
		 * @see java.lang.Object#toString()
		 */
		@Override
		public String toString() {
			return "l:" + this.lineStart + " c:" + this.characterStart + " - l:" + this.lineEnd + " c:" + this.characterEnd + " :: "
					+ this.exception.toString();
		}

	}

	/**
	 * A list of errors for this log.
	 */
	public LinkedList<ErrorContainer> errors = new LinkedList<ErrorContainer>();

	/**
	 * Add a new exception to the list of exceptions found.
	 * 
	 * @param tException The exception to add.
	 * @param startLine The line where the error starts.
	 * @param startChar The character in that line where the error starts.
	 * @param endLine The line where the error ends.
	 * @param endChar The character in that line where the error ends.
	 */
	public void add(IMPException tException, int startLine, int startChar, int endLine, int endChar) {
		this.errors.add(new ErrorContainer(tException, startLine, startChar, endLine, endChar));
	}

	/**
	 * Add a new exception to the list of exceptions found.
	 * 
	 * @param tException The exception to add.
	 * @param start The start token.
	 * @param end The end token.
	 */
	public void add(IMPException tException, Tree start, Tree end) {
		this.add(tException, start.getLine(), start.getCharPositionInLine(), end.getLine(), end.getCharPositionInLine() + end.getText().length());
	}

	/**
	 * Add a new exception to the list of exceptions found.
	 * 
	 * @param tException The exception to add.
	 * @param start The start token.
	 * @param end The end token.
	 */
	public void add(IMPException tException, Token start, Token end) {
		this.add(tException, start.getLine(), start.getCharPositionInLine(), end.getLine(), end.getCharPositionInLine() + end.getText().length());
	}

	/**
	 * Add a new exception to the list of exceptions found.
	 * 
	 * @param tException The exception to add.
	 * @param start The start token.
	 */
	public void add(IMPException tException, Token start) {
		errors.add(new ErrorContainer(tException, start.getLine(), start.getCharPositionInLine()));
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Iterable#iterator()
	 */
	@Override
	public Iterator<ErrorContainer> iterator() {
		return this.errors.iterator();
	}

}
