package imp.core.expressions;

import imp.core.exceptions.WrappedException;
import imp.core.exceptions.expressions.MethodReturnValue;

/**
 * Class to represent an expression. Should be extended for use.
 * 
 * @author zastrowm
 */
public abstract class Expression {

	public final ExpressionType type;
	public Object cachedValue;

	/**
	 * Constructor. Set the type of expression
	 * 
	 * @param tType the type of expression
	 */
	public Expression(ExpressionType tType) {
		this.type = tType;
	}

	/**
	 * Get the value of the expression as an object
	 * 
	 * @return the value of expression as an object
	 * @throws WrappedException
	 * @throws MethodReturnValue
	 */
	public abstract Object rawValue();

	/**
	 * Cache the value of this expression
	 * 
	 * @throws WrappedException
	 * @throws MethodReturnValue
	 */
	public void cacheValue() {
		this.cachedValue = rawValue();
	}

	/**
	 * Get the cached value of this expression
	 * 
	 * @return the value of this expression
	 */
	public Object value() {
		return this.cachedValue;
	}
}
