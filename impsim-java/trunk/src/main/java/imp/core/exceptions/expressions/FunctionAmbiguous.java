/**
 * 
 */
package imp.core.exceptions.expressions;

import imp.core.exceptions.IMPException;
import imp.core.expressions.Function;
import imp.core.expressions.FunctionSignature;

import java.util.List;
import java.util.Map.Entry;

/**
 * A function signature is ambiguous
 * 
 * @author zastrowm
 * @version 1.0
 */
public class FunctionAmbiguous extends IMPException {

	// Generated serial UID.
	private static final long serialVersionUID = 7893212800845526755L;

	/**
	 * List of matches.
	 */
	public final List<Entry<FunctionSignature, Function>> matches;

	/**
	 * The signature of this function.
	 */
	public final FunctionSignature signature;

	/**
	 * A function signature is ambiguous
	 * 
	 * @param sig the function signature
	 * @param matches all the matches of the function
	 * @param checkWithNamespace whether it was checked with namespace
	 */
	public FunctionAmbiguous(FunctionSignature sig, List<Entry<FunctionSignature, Function>> matches, boolean checkWithNamespace) {
		super("Function call (" + sig + ") is ambiguous." + (checkWithNamespace ? " Try using namespaced name." : ""));

		this.matches = matches;
		this.signature = sig;
	}

}
