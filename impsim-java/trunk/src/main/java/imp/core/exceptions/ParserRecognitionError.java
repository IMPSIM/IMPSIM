package imp.core.exceptions;

import org.antlr.runtime.RecognitionException;

/**
 * Represents an exception with the parser.
 * 
 * @author zastrowm
 * @version 1.0
 */
public class ParserRecognitionError extends IMPException {

	// Generated serial UID.
	private static final long serialVersionUID = -3362492876526074491L;

	/**
	 * The array of token names the parser failed on.
	 */
	final public String[] tokenNames;

	/**
	 * The inner recognition exception.
	 */
	final public RecognitionException recognitionException;

	/**
	 * Instantiates a new parser recognition error.
	 * 
	 * @param tokenNames the token names
	 * @param e the e
	 */
	public ParserRecognitionError(String[] tokenNames, RecognitionException e) {
		super("ParserRecognitionError");

		this.tokenNames = tokenNames;
		this.recognitionException = e;
	}

}
