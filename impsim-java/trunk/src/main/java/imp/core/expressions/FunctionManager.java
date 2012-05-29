/**
 * FunctionManager.java
 * Sep 18, 2011
 */
package imp.core.expressions;

import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.exceptions.expressions.FunctionAmbiguous;
import imp.core.exceptions.expressions.FunctionSignatureDoesNotExist;
import imp.core.exceptions.expressions.InvalidFunctionSignature;
import imp.core.expressions.attributes.Library;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * A class to manage all the functions in the imp language
 * 
 * @author zastrowm
 * @version 1.0
 */
public class FunctionManager {

	private HashMap<FunctionSignature, Function> functions = new HashMap<FunctionSignature, Function>();

	/**
	 * Create a new FunctionManager
	 */
	public FunctionManager() {

	}

	/**
	 * Add the functions that come with imp by default
	 * 
	 * @throws FunctionAlreadyExists
	 */
	public void addCoreFunctions() throws FunctionAlreadyExists {
		this.addFunctions(new imp.core.expressions.CoreFunctions());
	}

	/**
	 * Add a function to the manager
	 * 
	 * @param function the function to add
	 * @throws FunctionAlreadyExists
	 */
	public void addFunction(Function function) throws FunctionAlreadyExists {
		NullParameterException.check(function, "function", 0);

		if (hasSignature(function.signature))
			throw new FunctionAlreadyExists(function.signature);

		functions.put(function.signature, function);
	}

	/**
	 * Add a library to the function manager
	 * 
	 * @param library the library to add to the function manager
	 * @return the number of functions added to the manager
	 * @throws FunctionAlreadyExists
	 */
	public int addFunctions(FunctionLibrary library) throws FunctionAlreadyExists {
		return addFunctions(library, null);
	}

	/**
	 * Add a library to the function manager
	 * 
	 * @param library the library to add to the function manager
	 * @param namespace the name space to add the function in, overriding the library's Library attribute if it contains
	 *            one. Pass null to accept the library's Library attribute
	 * @return the number of functions added to the manager
	 * @throws FunctionAlreadyExists
	 */
	public int addFunctions(FunctionLibrary library, String namespace) throws FunctionAlreadyExists {
		NullParameterException.check(library, "library", 0);

		int totalCount = 0;

		Class<?> libraryClass = library.getClass();

		if (namespace == null) {
			Library libraryAnnotation = library.getClass().getAnnotation(imp.core.expressions.attributes.Library.class);
			namespace = libraryAnnotation != null ? libraryAnnotation.value() : "";
		}

		methodfor: for (Method method : libraryClass.getMethods()) {

			imp.core.expressions.attributes.Function funcAnno = method.getAnnotation(imp.core.expressions.attributes.Function.class);
			if (funcAnno == null)
				continue methodfor;

			try {
				MethodDelgate methodDelgate = new MethodDelgate(library, method);
				FunctionSignature sig = new FunctionSignature(namespace, funcAnno.value(), methodDelgate);
				addFunction(new Function(sig, methodDelgate));
				totalCount++;
			} catch (InvalidFunctionSignature e) {
				continue methodfor;
			} catch (FunctionAlreadyExists e) {
				throw e;
			}
		}

		return totalCount;
	}

	/**
	 * Check if the manager has a function with that signature
	 * 
	 * @param sig the function signature
	 * @return true if the manager has a function with that signature
	 */
	public boolean hasSignature(FunctionSignature sig) {
		// whether or not the namespace is valid
		boolean checkWithNamespace = !sig.namespace.isEmpty();

		// find all of the matches
		for (Map.Entry<FunctionSignature, Function> current : functions.entrySet()) {
			if (current.getKey().matches(sig, checkWithNamespace)) {
				return true;
			}
		}

		return false;
	}

	/**
	 * Retrieve the function with the designated or return null if it does not exist
	 * 
	 * @param sig the signature of the function
	 * @return the function signature if it exists, otherwise null
	 * @throws FunctionSignatureDoesNotExist
	 * @throws FunctionAmbiguous
	 */
	public Function getFunction(FunctionSignature sig) throws FunctionSignatureDoesNotExist, FunctionAmbiguous {

		// whether or not the namespace is valid
		boolean checkWithNamespace = !sig.namespace.isEmpty();

		List<Map.Entry<FunctionSignature, Function>> matches = new ArrayList<Map.Entry<FunctionSignature, Function>>();

		// find all of the matches
		for (Map.Entry<FunctionSignature, Function> current : functions.entrySet()) {
			if (current.getKey().matches(sig, checkWithNamespace)) {
				matches.add(current);
			}
		}

		// no function matches, throw
		if (matches.size() == 0) {
			throw new FunctionSignatureDoesNotExist(sig);
		} else if (matches.size() > 1) {
			throw new FunctionAmbiguous(sig, matches, checkWithNamespace); // too many matches, try with namespace
		} else {
			return matches.get(0).getValue(); // size 1
		}

	}

}
