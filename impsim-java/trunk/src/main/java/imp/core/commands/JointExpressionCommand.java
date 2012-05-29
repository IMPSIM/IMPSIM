package imp.core.commands;

import imp.core.commands.expressions.FakeExpression;
import imp.core.exceptions.IMPException;
import imp.core.expressions.Expression;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * The Class JointExpresionCommand.
 * 
 * @author zastrowm
 */
public class JointExpressionCommand implements Command {

	private String jointName;
	private JVAR type;
	private FakeExpression expression;
	
	/**
	 * Instantiates a new joint expresion command.
	 *
	 * @param jointName the joint name
	 * @param type the type
	 * @param expression the expression
	 */
	public JointExpressionCommand(String jointName, JVAR type, FakeExpression expression) {
		super();
		this.jointName = jointName;
		this.type = type;
		this.expression = expression;
	}

	@Override
	public void execute(Model model) throws IMPException {
		Expression exp = expression.toExpression(model);
		model.expressions.add(exp);
		model.jointExpressionManager.add(jointName, type, exp);
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.jointName).append(this.type).append(this.expression).toHashCode();
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {

		// check if same object
		if (this == otherObject) {
			return true;
		}

		if (!(otherObject instanceof JointExpressionCommand)) {
			return false;
		} else {
			JointExpressionCommand otherCmd = (JointExpressionCommand) otherObject;
			// return whether EVERY attribute is the same
			return otherCmd.jointName.equals(this.jointName) && otherCmd.type.equals(this.type)
					&& otherCmd.expression.equals(this.expression);
		}

	}

}
