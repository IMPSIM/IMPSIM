/**
 * WrappedExceptoin.java
 * Sep 16, 2011
 */
package imp.core.exceptions;

/**
 * An unknown exception caught by IMP
 * 
 * @author zastrowm
 * @version 1.0
 */
public class WrappedException extends IMPException {

	private static final long serialVersionUID = -1405963280127322246L;

	/** The exception that was caught **/
	public final Exception innerException;

	/**
	 * Constructor
	 * 
	 * @param exception the exception that we're wrapping
	 */
	public WrappedException(Exception exception) {
		super("Unknown caught exception");

		innerException = exception;
	}

	@Override
	public String toString() {
		return super.toString() + ":\n" + innerException.toString();
	}

}
