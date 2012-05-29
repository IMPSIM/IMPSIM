/**
 * Constants.java
 * May 10, 2011
 */
package imp.core;

import imp.core.exceptions.NullParameterException;

/**
 * Constants related or used in IMP.
 * 
 * @author dykstran
 * @version 1.02
 * @edit edmissonj added the min angle and distance fields
 * @edit dykstran Updated JavaDoc
 */
public class Constants {
	
	//#region Constant values.
	
	/**
	 * The error tolerance allowed for this model.
	 */
	public static final double ERROR_TOLERANCE = Math.pow(10, -15);
	
	/**
	 * Number of times to run loop closure before failure
	 */
	public static final int LOOP_CLOSURE_ITERATIONS = 30;
	
	/**
	 * Conversion factor to convert a radian measurement to a degree measurement.
	 */
	public static final double RADIAN_TO_DEGREE = 180 / (Math.PI);

	/**
	 * Minimum angle a joint is allowed to utilize.
	 */
	public static final double MIN_ANGLE = 10 / RADIAN_TO_DEGREE;

	/**
	 * Minimum distance of points when declaring the data for an element.
	 */
	public static final double MIN_DISTANCE = 1;

	//#endregion
	
	/**
	 * Compares two doubles considering the epsilon range of error.
	 * 
	 * @param d1 The first double to compare.
	 * @param d2 The second double to compare.
	 * @param epsilon The maximum difference allowed between the two values.
	 * @return True if the doubles are within the tolerance of each other false if not.
	 */
	public static boolean compareDoubleEpsilon(double d1, double d2, double epsilon) {
		return Math.abs(d1 - d2) < epsilon;
	}

	/**
	 * Compares two doubles considering the epsilon range of error.
	 * 
	 * @param d1 The first double to compare.
	 * @param d2 The second double to compare.
	 * @return True if the doubles are within the tolerance of each other false if not.
	 */
	public static boolean compareDoubles(double d1, double d2) {
		return compareDoubleEpsilon(d1, d2, ERROR_TOLERANCE);
	}

	/**
	 * Checks to make sure an object passed as a parameter isn't null. Throws an exception with the parameter number if
	 * the object is null.
	 * 
	 * @param obj The object to check for null.
	 * @param paramNum the parameter number that we are checking.
	 * @return The non-null object.
	 * @throws NullParameterException Thrown if the object is null.
	 */
	public static <T> T notNull(T obj, int paramNum) throws NullParameterException {
		if (obj == null) {
			throw new NullParameterException("Null parameter passed in.", paramNum);
		} else {
			return obj;
		}
	}
}
