/**
 * Functions.java
 * Sep 18, 2011
 */
package imp.core.expressions;

import imp.core.expressions.attributes.Function;
import imp.core.expressions.attributes.Library;
import imp.core.model.Model;
import imp.core.structures.Point;

import java.util.Arrays;

/**
 * imp.core functions
 * 
 * Functions which are loaded automatically into imp
 * 
 * @author zastrowm
 * @version 1.0
 */
@Library("imp.core")
public class CoreFunctions implements FunctionLibrary {

	public CoreFunctions() {

	}

	@Override
	public void initialize(Model model) {
		// TODO Auto-generated method stub

	}

	//@formatter:off 
	
	@Function("+")	public static double plus(double leftSide) {return leftSide;}
	@Function("+")	public static Point plus(Point leftSide) { return leftSide; }
	@Function("-")	public static double minus(double leftSide) {return -leftSide;}
	@Function("-")	public static Point minus(Point leftSide) { return new Point().minus(leftSide); }
	
	@Function("+")	public static double plus(double leftSide, double rightSide) {return leftSide + rightSide;}
	@Function("+")	public static Point plus(Point leftSide, Point rightSide) {	return leftSide.plus(rightSide);}
	@Function("+")	public static Point plus(Point leftSide, double rightSide) {return leftSide.plus(new Point(rightSide, rightSide, rightSide));}
	
	@Function("-")	public static double minus(double leftSide, double rightSide) {return leftSide - rightSide;}
	@Function("-")	public static Point minus(Point leftSide, Point rightSide) {return leftSide.minus(rightSide);}
	@Function("-")	public static Point minus(Point leftSide, double rightSide) {return leftSide.minus(new Point(rightSide, rightSide, rightSide));}
	
	@Function("*")	public static double multiply(double leftSide, double rightSide) {return leftSide * rightSide;}	
	@Function("/")	public static double divide(double leftSide, double rightSide) {return leftSide / rightSide;}	
	@Function("^")	public static double power(double leftSide, double rightSide) {	return Math.pow(leftSide,rightSide);}
	
	@Function("Point")	public static Point point() { return new Point(); }
	@Function("Point")	public static Point point(double x, double y, double z) { return new Point(x,y,z); }
	
	@Function("&")		public static String concat(String leftSide, Object rightSide) {return leftSide + rightSide;}
	@Function("String")	public static String String(Object value) { return value.toString(); }
	
	@Function("Append")	public static String[] append(String[] leftSide, String[] rightSide){return concat(leftSide,rightSide);}
	@Function("Append")	public static Point[] append(Point[] leftSide, Point[] rightSide){return concat(leftSide,rightSide);}
	@Function("Append")	public static double[] append(double[] leftSide, double[] rightSide) {return concat(leftSide,rightSide);}
	
	//@formatter:on

	/**
	 * Join a string array
	 * 
	 * @param strings all the strings to join
	 * @param delimiter what to join them by
	 * @return All the strings joined by the delimiter
	 */
	@Function("Join")
	static String join(String[] strings, String delimiter) {
		StringBuilder builder = new StringBuilder();
		for (int i = 0; i < strings.length; i++) {
			builder.append(strings[i].toString());
			if (i == strings.length - 1)
				break;
			builder.append(delimiter);
		}
		return builder.toString();
	}

	/**
	 * Concat two arrays
	 * 
	 * @param <T> the type of array to concat
	 * @param first the first array
	 * @param second the second array
	 * @return the arrays concat'd
	 */
	public static <T> T[] concat(T[] first, T[] second) {
		T[] result = Arrays.copyOf(first, first.length + second.length);
		System.arraycopy(second, 0, result, first.length, second.length);
		return result;
	}

	/**
	 * concat implementation using double[] arrays
	 * 
	 * @see concat<T>
	 */
	public static double[] concat(double[] first, double[] second) {
		double[] result = Arrays.copyOf(first, first.length + second.length);
		System.arraycopy(second, 0, result, first.length, second.length);
		return result;
	}

}
