/**
 * FunctionSingnatureDoesNotExists.java
 * Sep 18, 2011
 */
package imp.core.exceptions.expressions;

import imp.core.exceptions.IMPException;
import imp.core.expressions.FunctionSignature;

/**
 * Exception for the case when a a function does not exist in a FunctionManager
 * 
 * @author zastrowm
 * @version 1.0
 */
public class FunctionSignatureDoesNotExist extends IMPException {

	/**
	 * The signature of the function that caused the error.
	 */
	public final FunctionSignature signature;

	// Generated serial UID.
	private static final long serialVersionUID = 2091400649936200299L;

	/**
	 * Represents an error when a function signature does not exist.
	 * 
	 * @param sig the function signature.
	 */
	public FunctionSignatureDoesNotExist(FunctionSignature sig) {
		super("A function with the signature (" + sig + ") does not exist");
		signature = sig;
	}

}
