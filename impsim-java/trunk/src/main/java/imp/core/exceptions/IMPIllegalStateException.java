package imp.core.exceptions;

/**
 * Exception class used to indicate that something is in an invalid state.
 * @author kuszewskij
 *
 */
public class IMPIllegalStateException extends IMPRuntimeException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6628206155178484674L;

	/**
	 * Constructor for this class. Thrown when a state is illegal.
	 * @param message
	 */
	public IMPIllegalStateException(String message) {
		super(message);
	}

}
