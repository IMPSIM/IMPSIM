/**
 * 
 */
package imp.core.expressions;

import imp.core.exceptions.expressions.InvocationException;
import imp.core.exceptions.expressions.MethodReturnValue;

import java.util.Arrays;

/**
 * A function which returns the value of a function which executes
 * 
 * @author zastrowm
 * @version 2.0
 * @edit 1 Justin Kreier - fixed a copy/paste error in the javadocs
 */
public class FunctionExpression extends Expression {

	public final Function function;
	public final Expression[] parameters;

	/**
	 * Create a new function object
	 * 
	 * @param function the actual function
	 * @param parameters the parameters to the function
	 */
	public FunctionExpression(Function function, Expression[] parameters) {
		super(function.signature.returnType);

		this.function = function;
		this.parameters = parameters;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.expressions.Expression#rawValue()
	 */
	@Override
	public Object rawValue() {
		Object[] parametersToPass = new Object[this.function.signature.parameterTypes.length];

		for (int i = 0; i < this.function.signature.parameterTypes.length; i++) {
			parametersToPass[i] = parameters[i].rawValue();
		}

		Object retvalue = null;
		try {
			// call the method:
			retvalue = this.function.method.invoke(parametersToPass);

		} catch (Exception e) {
			throw new InvocationException(e);
		}

		// check to see if it's non null if it's not allowed to be
		if (retvalue == null && this.function.signature.returnType != ExpressionType.none) {
			throw new MethodReturnValue("Null return value is not valid for this method", this);
		} else if (!isTypeCorrect(retvalue)) { // check to see that it's what we expected
			throw new MethodReturnValue("Function returned unexpected type.  Expected type associated with " + this.function.signature.returnType
					+ " but got type " + retvalue.getClass().toString(), this);
		}

		return retvalue;
	}

	/**
	 * Check to see if the return value is of the type that we expected
	 * 
	 * @param value the object to test
	 * @return true if the type is the expected type
	 */
	private boolean isTypeCorrect(Object value) {
		return this.function.signature.returnType.matchesJavaType(value);
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

		if (!(otherObject instanceof FunctionExpression)) {
			return false;
		} else {
			FunctionExpression other = (FunctionExpression) otherObject;
			// return whether EVERY attribute is the same
			return other.function.equals(this.function) && Arrays.equals(other.parameters, this.parameters);
		}
	}

}
