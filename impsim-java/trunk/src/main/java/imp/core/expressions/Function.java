/**
 * Function.java
 * Sep 24, 2011
 */
package imp.core.expressions;

import imp.core.exceptions.expressions.InvalidFunctionSignature;

/**
 * A class to hold a delegate and function signature
 * 
 * @author zastrowm
 * @version 1.0
 */
public class Function {

	public final FunctionSignature signature;
	public final MethodDelgate method;

	/**
	 * Create a new function
	 * 
	 * @param sig the function signature
	 * @param meth the method associated with the function
	 */
	/* package */Function(FunctionSignature sig, MethodDelgate meth) {
		this.method = meth;
		this.signature = sig;
	}

	/**
	 * Create a new function
	 * 
	 * @param namespace the namespace the function belongs in
	 * @param name the name of the function
	 * @param meth the method associated with function
	 * @throws InvalidFunctionSignature
	 */
	public Function(String namespace, String name, MethodDelgate meth) throws InvalidFunctionSignature {
		this.method = meth;
		this.signature = new FunctionSignature(namespace, name, meth);
	}
}
