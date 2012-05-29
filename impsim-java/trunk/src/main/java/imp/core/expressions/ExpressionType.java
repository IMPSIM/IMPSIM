package imp.core.expressions;

import imp.core.structures.Point;

/**
 * The type of expression 
 * 
 * @author zastrowm
 */
public enum ExpressionType {
	invalid,	
	none,
	number,
	string,
	point,
	any,
	listOfNumbers,
	listOfStrings,
	listOfPoints,
	listOfAny;
	
	/**
	 * Convert a Java type to the corresponding ExpressionType
	 *
	 * @param theType the java type
	 * @return the ExpressionType which represents the data type
	 */
	public static ExpressionType convertType(Class<?> theType) {
		if (theType == double.class)		return ExpressionType.number;
		else if (theType == Point.class)	return ExpressionType.point;
		else if (theType == String.class)	return ExpressionType.string;
		else if (theType == double[].class)	return ExpressionType.listOfNumbers;
		else if (theType == Point[].class)	return ExpressionType.listOfPoints;
		else if (theType == String[].class)	return ExpressionType.listOfStrings;
		else if (theType == void.class)		return ExpressionType.none;
		else return ExpressionType.invalid;
	}

	/**
	 * Check to see if the enum type matches the java type.
	 *
	 * @param value the value to test against
	 * @return true, if successful, false otherwise
	 */
	public boolean matchesJavaType(Object value) {
		switch (this){
		case number:			return value instanceof Double;
		case string:			return value instanceof String;
		case point:				return value instanceof Point;
		case listOfNumbers:		return value instanceof double[];
		case listOfStrings:		return value instanceof String[];
		case listOfPoints:		return value instanceof Point[];
		default:				return false;
		}
	}

}
