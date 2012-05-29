/**
 * FakeExpression.java
 */
package imp.core.commands.expressions;

import imp.core.exceptions.IMPException;
import imp.core.expressions.Expression;
import imp.core.model.Model;

/**
 * Interface for Expression Commands
 * 
 * @author zastrowm
 * 
 */
public interface FakeExpression {

	/**
	 * Convert the FakeExpression to an actual expression (that can be evaluated)
	 * 
	 * @param model the model for which the expression is being created
	 * @return the expression
	 * @throws IMPException A general IMP exception has occurred.
	 */
	public Expression toExpression(Model model) throws IMPException;

}
