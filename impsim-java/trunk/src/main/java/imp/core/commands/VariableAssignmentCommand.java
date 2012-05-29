/**
 * VariableAssignmentCommand.java
 */
package imp.core.commands;

import imp.core.exceptions.IMPException;
import imp.core.expressions.Expression;
import imp.core.model.Model;

/**
 * Class to represent the
 * 
 * @author zastrowm
 */
public class VariableAssignmentCommand implements Command {

	// the variable name
	final String variableName;

	// the value/expression of the variable
	final imp.core.commands.expressions.FakeExpression value;

	/**
	 * Create a new property assignment command
	 * 
	 * @param tVariableName the variable name
	 * @param tValue the value of the property
	 */
	public VariableAssignmentCommand(String tVariableName, imp.core.commands.expressions.FakeExpression tValue) {
		this.variableName = tVariableName;
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
		model.variableManager.add(variableName, exp);
	}

}
