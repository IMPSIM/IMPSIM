package imp.core.exceptions;

import imp.core.expressions.Expression;
import imp.core.expressions.ExpressionType;

/**
 * Class to be thrown whenever someone tries to convert an expression value into something that it shouldn't be
 * 
 * @author zastrowm
 */
public class InvalidTypeCastException extends IMPException {

	// Generated Serial:
	private static final long serialVersionUID = 1915259567862732435L;

	/**
	 * The type attempted to cast to.
	 */
	public final ExpressionType actualType;

	/**
	 * The type attempted to be converted.
	 */
	public final ExpressionType tryType;

	/**
	 * The expression that caused this exception.
	 */
	public final Expression expression;

	/**
	 * Creates a new exception.
	 * 
	 * @param datatype the data type of the variable
	 * @param convertType the type that was attempted to convert to
	 * @param tExpression the expression causing the exception.
	 */
	public InvalidTypeCastException(ExpressionType datatype, ExpressionType convertType, Expression tExpression) {
		super("Invalid cast to " + convertType + ". Actual type:" + datatype);
		this.actualType = datatype;
		this.tryType = convertType;
		this.expression = tExpression;
	}

}
