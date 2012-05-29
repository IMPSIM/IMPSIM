/**
 * Vector3.java
 * January 14, 2011
 * 
 */

package imp.core.structures;

import imp.core.Constants;
import imp.core.exceptions.NullParameterException;
import Jama.Matrix;

/**
 * Defines a vector of three double-precision floating-point values.
 * 
 * @author kemmannl
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class Vector3 {

	/**
	 * Returns a three-dimensional zero vector instance.
	 * 
	 * @return a new instance of a three-dimensional zero vector.
	 */
	public static Vector3 Zero() {
		return new Vector3(0, 0, 0);
	}

	/**
	 * The JAMA matrix that holds this Vector in the background.
	 */
	private Matrix matrix;

	/**
	 * Initialize a new three-dimensional vector with the specified values.
	 * 
	 * @param x the first-dimension value.
	 * @param y the second-dimension value.
	 * @param z the third-dimension value.
	 */
	public Vector3(double x, double y, double z) {
		this.matrix = new Matrix(1, 3);
		this.setX(x);
		this.setY(y);
		this.setZ(z);
	}

	/**
	 * Make a vector from a point.
	 * 
	 * @param p the point which holds x, y, & z coordinates.
	 */
	public Vector3(Point p) {
		if (p == null) {
			throw new NullParameterException("The Point this is based on cannot be null", 0);
		}
		this.matrix = new Matrix(1, 3);
		this.setX(p.getX());
		this.setY(p.getY());
		this.setZ(p.getZ());
	}

	/**
	 * Copy the specified vector into a new three-dimensional vector instance.
	 * 
	 * @param v the vector to copy.
	 */
	public Vector3(Vector3 v) {
		if (v == null) {
			throw new NullParameterException("The Vector3 this is based on cannot be null", 0);
		}
		this.matrix = new Matrix(1, 3);
		this.setX(v.getX());
		this.setY(v.getY());
		this.setZ(v.getZ());
	}

	/**
	 * Returns the cross product of two three-dimensional vectors.
	 * 
	 * <pre>
	 * a.crossProduct(b) = (a2b3 - a3b2, a3b1 - a1b3, a1b2 - a2b1)
	 * </pre>
	 * 
	 * @param v2 the second vector.
	 * @return the cross product of the two vectors.
	 */
	public Vector3 crossProduct(Vector3 v2) {
		return new Vector3(this.get(1) * v2.get(2) - this.get(2) * v2.get(1), // a2b3 - a3b2
				this.get(2) * v2.get(0) - this.get(0) * v2.get(2), // a3b1 - a1b3
				this.get(0) * v2.get(1) - this.get(1) * v2.get(0)); // a1b2 - a2b1
	}

	/**
	 * Returns the dot product of two three-dimensional vectors.
	 * 
	 * @param v2 the second vector.
	 * @return the dot product of the two vectors.
	 */
	public double dotProduct(Vector3 v2) {
		double vdot = 0.0;

		for (int j = 0; j < 3; j++) {
			vdot += this.get(j) * v2.get(j); // Multiply the corresponding
												// vector components together
												// and add it to the sum
		}

		return vdot;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object v) {
		if (v instanceof Vector3) {
			return this.equals((Vector3) v);
		} else {
			return false;
		}
	}

	/**
	 * Compares each value to see if the vectors are coincidental.
	 * 
	 * @param v the vector to compare this to.
	 * @return true if the vectors are the same, false otherwise.
	 */
	public boolean equals(Vector3 v) {
		return this.equalsEpsilon(v, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Compares each value to see if the vectors are coincidental.
	 * 
	 * @param v the vector to compare this to.
	 * @param epsilon the maximum difference allowed between floating point values.
	 * @return true if the vectors are the same, false otherwise.
	 */
	public boolean equalsEpsilon(Vector3 v, double epsilon) {
		if( v == null ) {
			return false;
		}
		
		return Constants.compareDoubleEpsilon(this.getX(), v.getX(), epsilon) && Constants.compareDoubleEpsilon(this.getY(), v.getY(), epsilon)
				&& Constants.compareDoubleEpsilon(this.getZ(), v.getZ(), epsilon);
	}

	/**
	 * Returns the value of the vector at the specified index.
	 * 
	 * @param index the (zero-based) index.
	 * @return the value of the vector at the specified index.
	 */
	public double get(int index) {
		return this.matrix.get(0, index);
	}

	/**
	 * Returns the first-dimension value of this vector.
	 * 
	 * @return the first-dimension value.
	 */
	public double getX() {
		return this.matrix.get(0, 0);
	}

	/**
	 * Returns the second-dimension value of this vector.
	 * 
	 * @return the second-dimension value.
	 */
	public double getY() {
		return this.matrix.get(0, 1);
	}

	/**
	 * Returns the third-dimension value of this vector.
	 * 
	 * @return the third-dimension value.
	 */
	public double getZ() {
		return this.matrix.get(0, 2);
	}

	/**
	 * Returns the magnitude of a three-dimensional vector.
	 * 
	 * <pre>
	 *   _________________
	 *  /(x^2)+(y^2)+(z^2)
	 * V
	 * </pre>
	 * 
	 * @return the magnitude of a three-dimensional vector.
	 */
	public double magnitude() {
		return Math.sqrt(this.get(0) * this.get(0) + this.get(1) * this.get(1) + this.get(2) * this.get(2));
	}

	/**
	 * Return the normalized vector of this vector. Multiples the matrix by (1/magnitude). Gives a zero vector if the
	 * magnitude is zero.
	 * 
	 * @return the normalized vector
	 */
	public Vector3 normalize() {
		double magnitude = this.magnitude();

		// return 0 vector for 0 magnitude
		if (Constants.compareDoubleEpsilon(magnitude, 0.0, Constants.ERROR_TOLERANCE)) {
			return new Vector3(0, 0, 0);

			// normalized vector = vector / magnitude
		} else {
			return this.scalarMultiply(1.0 / magnitude);
		}
	}

	/**
	 * Returns a new Vector3 instance with values equal to the values of this Vector3 times a scalar multiple.
	 * 
	 * @param scalar the scalar multiple to multiply the matrix with.
	 * @return a new Vector3 instance with the products of the scalar and the original vector entries.
	 */
	public Vector3 scalarMultiply(double scalar) {
		Vector3 multiple = new Vector3(this); // Copy the vector over
		for (int i = 0; i < 3; i++) {
			double curVal = multiple.get(i);
			multiple.set(i, curVal * scalar);
		}
		return multiple;
	}

	/**
	 * Sets the value of the vector at the specified index.
	 * 
	 * @param index the (zero-based) index.
	 * @param value the value to set.
	 */
	public void set(int index, double value) {
		this.matrix.set(0, index, value);
	}

	/**
	 * Sets the first-dimension value of this vector.
	 * 
	 * @param x the first-dimension value.
	 */
	public void setX(double x) {
		this.matrix.set(0, 0, x);
	}

	/**
	 * Sets the second-dimension value of this vector.
	 * 
	 * @param y the second-dimension value.
	 */
	public void setY(double y) {
		this.matrix.set(0, 1, y);
	}

	/**
	 * Sets the third-dimension value of this vector.
	 * 
	 * @param z the third-dimension value.
	 */
	public void setZ(double z) {
		this.matrix.set(0, 2, z);
	}

	/**
	 * Returns the difference between two three-dimensional vectors.
	 * 
	 * @param v2 the second vector.
	 * @return the difference between two three-dimensional vectors.
	 */
	public Vector3 subtract(Vector3 v2) {
		return new Vector3(this.get(0) - v2.get(0), this.get(1) - v2.get(1), this.get(2) - v2.get(2));
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "[" + this.getX() + "," + this.getY() + "," + this.getZ() + "]";
	}
}
