/**
 * Variable.java
 * Sep 27, 2011
 */
package imp.core.commands.expressions;

import imp.core.exceptions.parser.ModelVariableDoesNotExist;
import imp.core.expressions.Expression;
import imp.core.model.Model;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Represents a variable as a temporary expression-like object
 * 
 * @author zastrowm
 * @version 1.0
 */
public class Variable implements FakeExpression{

	/**
	 * the name of the variable
	 */
	public final String name;
	
	/**
	 * Create a new variable
	 * 
	 * @param name the name of the variable
	 */
	public Variable(String name) {
		imp.core.exceptions.NullParameterException.check(name, "name", 0);
		
		this.name = name;
	}
	
	/* (non-Javadoc)
	 * @see imp.commands.expressions.FakeExpression#toExpression(imp.model.Model)
	 */
	@Override
	public Expression toExpression(Model model) throws ModelVariableDoesNotExist {
		return model.variableManager.get(name);
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.name).toHashCode();
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
		} else if (!(otherObject instanceof Variable)) {
			return false;
		} else {
			Variable other = (Variable) otherObject;
			// return whether EVERY attribute is the same
			return other.name.equals(this.name) ;
		}

	}


}
