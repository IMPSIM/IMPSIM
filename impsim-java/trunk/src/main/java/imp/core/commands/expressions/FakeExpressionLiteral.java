/**
 * 
 */
package imp.core.commands.expressions;

import imp.core.exceptions.IMPException;
import imp.core.exceptions.NullParameterException;
import imp.core.expressions.Expression;
import imp.core.expressions.ExpressionLiteral;
import imp.core.expressions.ExpressionType;
import imp.core.model.Model;
import imp.core.structures.Point;

import java.util.Arrays;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * A fake expression literal while waiting to create the actual expression literal
 * 
 * @author zastrowm
 */
public class FakeExpressionLiteral implements FakeExpression {

	// The type of the expression that this holds
	private ExpressionType type;

	// The Expression's literal value
	private Object literalValue;

	/**
	 * Instantiates a new expression literal from a String
	 * 
	 * @param value the String value
	 */
	public FakeExpressionLiteral(String value) {
		NullParameterException.check(value, "value", 0);
		type = ExpressionType.string;
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a String[]
	 * 
	 * @param value the String[] value
	 */
	public FakeExpressionLiteral(String[] value) {
		NullParameterException.check(value, "value", 0);
		type = ExpressionType.listOfStrings;
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a double
	 * 
	 * @param value the double value
	 */
	public FakeExpressionLiteral(double value) {
		type = ExpressionType.number;
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a double[]
	 * 
	 * @param value the double[] value
	 */
	public FakeExpressionLiteral(double[] value) {
		NullParameterException.check(value, "value", 0);
		type = ExpressionType.listOfNumbers;
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a Point
	 * 
	 * @param value the Point value
	 */
	public FakeExpressionLiteral(Point value) {
		NullParameterException.check(value, "value", 0);
		type = ExpressionType.point;
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a Point[]
	 * 
	 * @param value the Point[] value
	 */
	public FakeExpressionLiteral(Point[] value) {
		NullParameterException.check(value, "value", 0);
		type = ExpressionType.listOfPoints;
		literalValue = value;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.expressions.FakeExpression#toExpression(imp.model.Model)
	 */
	@Override
	public Expression toExpression(Model model) throws IMPException {
		switch (type) {
		case number:
			return new ExpressionLiteral((Double) literalValue);
		case listOfNumbers:
			return new ExpressionLiteral((double[]) literalValue);
		case string:
			return new ExpressionLiteral((String) literalValue);
		case listOfStrings:
			return new ExpressionLiteral((String[]) literalValue);
		case point:
			return new ExpressionLiteral((Point) literalValue);
		case listOfPoints:
			return new ExpressionLiteral((Point[]) literalValue);
		default: // should never be able to get to
			return null;
		}
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.literalValue).append(this.type).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;

		if (obj == null || getClass() != obj.getClass()) {
			return false;
		}

		FakeExpressionLiteral other = (FakeExpressionLiteral) obj;

		if (other.type != this.type) {
			return false;
		} else {
			switch (type) {
			case listOfNumbers:
				return Arrays.equals((double[]) other.literalValue, (double[]) literalValue);
			case listOfAny:
			case listOfPoints:
			case listOfStrings:
				return Arrays.equals((Object[]) other.literalValue, (Object[]) literalValue);
			default:
				return other.literalValue.equals(literalValue);
			}
		}
	}

}
