/**
 * 
 */
package imp.core.commands.encapsulation;

import imp.core.expressions.Expression;
import imp.core.expressions.ExpressionType;
import imp.core.model.ModelPropertyManager;
import imp.core.structures.Point;

/**
 * A container that allows external querying of properties
 * 
 * @author zastrowm
 */
public class PropertyManager {

	/** The model internal property manager. */
	private final ModelPropertyManager internalManager;

	/**
	 * Instantiates a new property manager.
	 * 
	 * @param internalManager the internal manager that this manager should wrap
	 */
	public PropertyManager(ModelPropertyManager internalManager) {
		this.internalManager = internalManager;
	}

	/**
	 * Checks existence for a property on a variable
	 * 
	 * @param variableName the variable name that contains the property
	 * @param propertyName the property name to get
	 * @return true if the property exists
	 */
	public boolean hasProperty(String variableName, String propertyName) {
		return internalManager.has(variableName, propertyName);
	}

	/**
	 * Checks existence for a property on a variable.
	 * 
	 * @param variableName the variable name that contains the property
	 * @param propertyName the property name to get
	 * @param expectedType the expected type of the property
	 * @return true if the property exists and if it is the expected type
	 */
	public boolean hasProperty(String variableName, String propertyName, ExpressionType expectedType) {
		return hasProperty(variableName, propertyName) && internalManager.get(variableName, propertyName).type == expectedType;
	}

	/**
	 * Gets a property that is a string, or returns null if the point does not exist
	 * 
	 * @param variableName the variable name that contains the property
	 * @param propertyName the property name to get
	 * @return the string that represents the value of the property, or null if the property does not exist on the
	 *         variable
	 */
	public String getStringProperty(String variableName, String propertyName) {
		return getStringProperty(variableName, propertyName, null);
	}

	/**
	 * Gets a property that is a string, or returns defaultValue if the point does not exist
	 * 
	 * @param variableName the variable name that contains the property
	 * @param propertyName the property name to get
	 * @return the string that represents the value of the property, or defaultValue if the property does not exist on
	 *         the variable
	 */
	public String getStringProperty(String variableName, String propertyName, String defaultValue) {
		return (String) getPropertyValue(variableName, propertyName, defaultValue, ExpressionType.string);
	}

	/**
	 * Gets a property that is a point, or returns null if the point does not exist
	 * 
	 * @param variableName the variable name that contains the property
	 * @param propertyName the property name to get
	 * @return the point that represents the value of the property, or null if the property does not exist on the
	 *         variable
	 */
	public Point getPointProperty(String variableName, String propertyName) {
		return getPointProperty(variableName, propertyName, null);
	}

	/**
	 * Gets a property that is a point, or returns defaultValue if the point does not exist
	 * 
	 * @param variableName the variable name that contains the property
	 * @param propertyName the property name to get
	 * @return the point that represents the value of the property, or defaultValue if the property does not exist on
	 *         the variable
	 */
	public Point getPointProperty(String variableName, String propertyName, Point defaultValue) {
		return (Point) getPropertyValue(variableName, propertyName, defaultValue, ExpressionType.point);
	}

	/**
	 * Gets the property value or returns the default value if the property does not exist or if the property is not of
	 * the expected type.
	 * 
	 * @param variableName the variable name
	 * @param propertyName the property name
	 * @param defaultValue the default value to return if the property is not of the expected type
	 * @param type the type expected
	 * @return the property value of the property
	 */
	private Object getPropertyValue(String variableName, String propertyName, Object defaultValue, ExpressionType type) {
		if (internalManager.has(variableName, propertyName)) {
			Expression expression = internalManager.get(variableName, propertyName);

			// TODO - we should not be calling raw value directly
			if (expression.type == type) {
				return expression.rawValue();
			}
		}

		return defaultValue;

	}
}
