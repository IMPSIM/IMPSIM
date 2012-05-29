/**
 * PropertyAssignmentCommand.java
 */
package imp.core.commands;

import imp.core.exceptions.IMPException;
import imp.core.expressions.Expression;
import imp.core.model.Model;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Class to represent the
 * 
 * @author zastrowm
 */
public class PropertyAssignmentCommand implements Command {

	final String variableName, propertyName;
	final imp.core.commands.expressions.FakeExpression value;

	/**
	 * Create a new property assignment command
	 * 
	 * @param tVariableName the variable name
	 * @param tPropertyName the property name
	 * @param tValue the value of the property
	 */
	public PropertyAssignmentCommand(String tVariableName, String tPropertyName, imp.core.commands.expressions.FakeExpression tValue) {
		this.variableName = tVariableName;
		this.propertyName = tPropertyName;
		this.value = tValue;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.Command#execute(imp.model.Model)
	 */
	@Override
	public void execute(Model model) throws IMPException {
		Expression exp = value.toExpression(model);
		model.expressions.add(exp);
		model.properties.add(variableName, propertyName, exp);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.variableName).append(this.propertyName).append(this.value).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof PropertyAssignmentCommand)) {
			return false;
		}
		PropertyAssignmentCommand other = (PropertyAssignmentCommand) obj;
		if (propertyName == null) {
			if (other.propertyName != null) {
				return false;
			}
		} else if (!propertyName.equals(other.propertyName)) {
			return false;
		}
		if (value == null) {
			if (other.value != null) {
				return false;
			}
		} else if (!value.equals(other.value)) {
			return false;
		}
		if (variableName == null) {
			if (other.variableName != null) {
				return false;
			}
		} else if (!variableName.equals(other.variableName)) {
			return false;
		}
		return true;
	}

}
