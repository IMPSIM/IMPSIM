/**
 * VariableManager.java
 * Sep 27, 2011
 */
package imp.core.model;

import imp.core.exceptions.WrappedException;
import imp.core.exceptions.expressions.MethodReturnValue;
import imp.core.exceptions.parser.ModelVariableAlreadyExists;
import imp.core.exceptions.parser.ModelVariableDoesNotExist;
import imp.core.expressions.Expression;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.loop.LoopVariable;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 
 * 
 * @author zastrowm
 * @version 1.0
 */
public class JointExpressionManager {

	class JointNameJvar {

		public JointNameJvar(String name, JVAR jvar) {
			this.name = name;
			this.jvar = jvar;
			this.oldValue = 0;
		}

		public String name;
		public JVAR jvar;
		/* package */double oldValue;

	}

	/** The variables and their associated expressions. */
	private Map<JointNameJvar, Expression> variables = new HashMap<JointNameJvar, Expression>();

	/**
	 * Add a new variable
	 * 
	 * @param name the name of the variable
	 * @param jvar the joint variable to add.
	 * @param value the value of the variable
	 * @throws ModelVariableAlreadyExists if the variable already exists in the model
	 */
	public void add(String name, JVAR jvar, Expression value) throws ModelVariableAlreadyExists {

		JointNameJvar entry = new JointNameJvar(name, jvar);

		if (has(entry))
			throw new ModelVariableAlreadyExists(name);

		variables.put(entry, value);
	}

	/**
	 * Test to see if the variable already exists in the manager
	 * 
	 * @param jvar the name of the variable
	 * @return true if the variable already exists
	 */
	public boolean has(JointNameJvar jvar) {
		return variables.containsKey(jvar);
	}

	/**
	 * Get the expression associated with a variable
	 * 
	 * @param jvar the name of the variable
	 * @return the expression which represents the value of the variable
	 * @throws ModelVariableDoesNotExist the joint variable does not exist in this model.
	 */
	public Expression get(JointNameJvar jvar) throws ModelVariableDoesNotExist {
		if (!has(jvar))
			throw new ModelVariableDoesNotExist(jvar.name);
		return variables.get(jvar);
	}

	/**
	 * To loop vars.
	 * 
	 * @return the list
	 * @throws WrappedException the wrapped exception
	 * @throws MethodReturnValue the method return value
	 */
	public List<LoopVariable> toLoopVars() throws WrappedException, MethodReturnValue {

		List<LoopVariable> loopVars = new ArrayList<LoopVariable>();

		for (Map.Entry<JointNameJvar, Expression> entry : variables.entrySet()) {

			JointNameJvar key = entry.getKey();
			Expression valueExpression = entry.getValue();
			double currentValue = (Double) valueExpression.value();

			double delta = currentValue - key.oldValue; // get the change from last time
			key.oldValue = currentValue; // save the old value
			LoopVariable var = new LoopVariable(entry.getKey().name, entry.getKey().jvar, delta);
			loopVars.add(var);
		}

		return loopVars;

	}

}
