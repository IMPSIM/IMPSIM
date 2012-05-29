/**
 * VariableManager.java
 * Sep 27, 2011
 */
package imp.core.model;

import imp.core.exceptions.parser.ModelVariableAlreadyExists;
import imp.core.exceptions.parser.ModelVariableDoesNotExist;
import imp.core.expressions.Expression;

import java.util.HashMap;
import java.util.Map;

/**
 * 
 * 
 * @author zastrowm
 * @version 1.0
 */
public class VariableManager {

	/**
	 * Map of containing variable expressions
	 */
	private Map<String, Expression> variables = new HashMap<String, Expression>();

	/**
	 * Add a new variable
	 * 
	 * @param name the name of the variable
	 * @param value the value of the variable
	 * @throws ModelVariableAlreadyExists if the variable already exists in the model
	 */
	public void add(String name, Expression value) throws ModelVariableAlreadyExists {
		if (has(name))
			throw new ModelVariableAlreadyExists(name);

		variables.put(name, value);
	}

	/**
	 * Test to see if the variable already exists in the manager
	 * 
	 * @param name the name of the variable
	 * @return true if the variable already exists
	 */
	public boolean has(String name) {
		return variables.containsKey(name);
	}

	/**
	 * Get the expression associated with a variable
	 * 
	 * @param name the name of the variable
	 * @return the expression which represents the value of the variable
	 * @throws ModelVariableDoesNotExist thrown if the model does not contain the named expression.
	 */
	public Expression get(String name) throws ModelVariableDoesNotExist {
		if (!has(name))
			throw new ModelVariableDoesNotExist(name);
		return variables.get(name);
	}

	/**
	 * Get all the variables contained in the manager
	 * 
	 * @return a mapping of variables names to variable values (as expressions)
	 */
	public Map<String, Expression> getAllVariables() {
		Map<String, Expression> all = new HashMap<String, Expression>(variables);
		return all;
	}

}
