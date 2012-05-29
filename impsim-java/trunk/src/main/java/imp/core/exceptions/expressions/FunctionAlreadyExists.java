/**
 * FunctionAlreadyExists.java
 * Sep 18, 2011
 */
package imp.core.exceptions.expressions;

import imp.core.exceptions.IMPException;
import imp.core.expressions.FunctionSignature;

/**
 * Thrown when a duplicate function has been added
 * 
 * @author zastrowm
 * @version 1.0
 */
public class FunctionAlreadyExists extends IMPException {

	// Generated serial UID.
	private static final long serialVersionUID = -7094115818726689490L;

	/**
	 * The signature of this function.
	 */
	public final FunctionSignature signature;

	/**
	 * Constructor
	 * 
	 * @param sig the function signature
	 */
	public FunctionAlreadyExists(FunctionSignature sig) {
		super("A function with this signature has already been added (" + sig.toString() + ")");
		signature = sig;
	}
}
