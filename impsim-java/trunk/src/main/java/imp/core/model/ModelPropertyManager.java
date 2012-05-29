/**
 * ModelPropertyManager.java
 */
package imp.core.model;

import imp.core.expressions.Expression;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

/**
 * Class to hold various IMP variable PROPERTIES
 * 
 * @author zastrowm
 */
public class ModelPropertyManager {

	/**
	 * hold all the properties and values of a variable:
	 */
	Map<String, Map<String, Expression>> properties = new HashMap<String, Map<String, Expression>>();

	/**
	 * Make a new property manager
	 */
	public ModelPropertyManager() {

	}

	/**
	 * Add a property to a variable
	 * 
	 * @param variable the variable name
	 * @param property the property name
	 * @param value the value of the property
	 */
	public void add(String variable, String property, Expression value) {
		if (!properties.containsKey(variable)) {
			properties.put(variable, new HashMap<String, Expression>());
		}

		properties.get(variable).put(property, value);
	}

	/**
	 * Get a property value or return null
	 * 
	 * @param variableName the variable name
	 * @param propertyName the property name
	 * @return the property value or null if that property is not set for that variable
	 */
	public Expression get(String variableName, String propertyName) {
		return getOrDefault(variableName, propertyName, null);
	}

	/**
	 * Get a property value or return the default if that property doesn't exists
	 * 
	 * @param variableName the variable name
	 * @param propertyName the property name
	 * @param defaultValue the default value if that property is not set for that variable
	 * @return the property value or defaultValue if that property is not set for that variable
	 */
	public Expression getOrDefault(String variableName, String propertyName, Expression defaultValue) {
		if (!properties.containsKey(variableName) || !properties.get(variableName).containsKey(propertyName)) {
			return defaultValue;
		} else {
			return properties.get(variableName).get(propertyName);
		}
	}

	/**
	 * Check to see if a specific property exists for a specific variable
	 * 
	 * @param variableName the variable name
	 * @param propertyName the property name
	 * @return whether or not it exists
	 */
	public boolean has(String variableName, String propertyName) {
		return properties.containsKey(variableName) && properties.get(variableName).containsKey(propertyName);
	}

	/**
	 * Return all the properties that a specific variable has
	 * 
	 * @param variableName the name of the variable
	 * @return a set of all the property names that the variable has
	 */
	public Set<String> getPropertyLists(String variableName) {
		if (!properties.containsKey(variableName)) {
			return new TreeSet<String>(); // return an empty set
		} else {
			return properties.keySet();
		}
	}
}
