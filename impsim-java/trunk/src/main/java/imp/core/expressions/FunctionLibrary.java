/**
 * 
 */
package imp.core.expressions;

import imp.core.model.Model;

/**
 * Contains the interface for a function library to be added to a function manager
 * 
 * @author zastrowm
 * 
 */
public interface FunctionLibrary {

	/**
	 * Initialize the library with the model. Can be an empty function
	 * 
	 * @param model the model TODO this should use the encapsulated model, not an actual model
	 */
	public void initialize(Model model);

}
