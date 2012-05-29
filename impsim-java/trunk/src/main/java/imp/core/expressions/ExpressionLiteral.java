/*
 * 
 */
package imp.core.expressions;

import imp.core.structures.Point;

import java.util.Arrays;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * Represents an expression which is constant
 */
public class ExpressionLiteral extends Expression {

	// The Expression's literal value
	public final Object literalValue;

	/**
	 * Instantiates a new expression literal from a String
	 * 
	 * @param value the String value
	 */
	public ExpressionLiteral(String value) {
		super(ExpressionType.string);
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a String[]
	 * 
	 * @param value the String[] value
	 */
	public ExpressionLiteral(String[] value) {
		super(ExpressionType.listOfStrings);
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a double
	 * 
	 * @param value the double value
	 */
	public ExpressionLiteral(double value) {
		super(ExpressionType.number);
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a double[]
	 * 
	 * @param value the double[] value
	 */
	public ExpressionLiteral(double[] value) {
		super(ExpressionType.listOfNumbers);
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a Point
	 * 
	 * @param value the Point value
	 */
	public ExpressionLiteral(Point value) {
		super(ExpressionType.point);
		literalValue = value;
	}

	/**
	 * Instantiates a new expression literal from a Point[]
	 * 
	 * @param value the Point[] value
	 */
	public ExpressionLiteral(Point[] value) {
		super(ExpressionType.listOfPoints);
		literalValue = value;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.expressions.Expression#rawValue()
	 */
	@Override
	public Object rawValue() {
		return literalValue;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		return new HashCodeBuilder().append(this.literalValue).append(this.type).toHashCode();
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
		if (getClass() != obj.getClass()) {
			return false;
		}
		ExpressionLiteral other = (ExpressionLiteral) obj;
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
