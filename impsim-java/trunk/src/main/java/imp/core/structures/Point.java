/**
 * Point.java
 * February 6, 2011
 */
package imp.core.structures;

import imp.core.Constants;
import imp.core.graphics.Vec3;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * This class represents a point in 3 dimensional space.
 * 
 * @author dykstran klehmc
 * @edit dykstran Added Validate method.
 * @edit dykstran Updated JavaDoc
 * @edit zastrowm merged LiteralPoint and Point, the distiction is no longer necessary
 * @version 1.21
 */
public class Point {

	/**
	 * This points X, Y, and Z coordinates.
	 */
	private double x, y, z;

	/**
	 * Initializes a point in 3 space with the coordinates (0,0,0).
	 * 
	 */
	public Point() {
		this.x = 0.0;
		this.y = 0.0;
		this.z = 0.0;
	}

	/**
	 * Initialize the 3 space point with the given coordinates.
	 * 
	 * @param x the x coordinate.
	 * @param y the y coordinate.
	 * @param z the z coordinate.
	 * 
	 */
	public Point(double x, double y, double z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object point) {
		if (point instanceof Point) {
			return this.equals((Point) point);
		} else {
			return false;
		}
	}

	/**
	 * Compares the point against another point constrained by the default error tolerance.
	 * 
	 * @param p the point to compare to.
	 * @return true if the points data compares within error false if not.
	 */
	public boolean equals(Point p) {
		return this.equalsEpsilon(p, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Compares the point against another point constrained by the given error tolerance.
	 * 
	 * @param p the point to compare to.
	 * @param epsilon the error tolerance to use during comparisons.
	 * @return true if the points data compares within error false if not.
	 */
	public boolean equalsEpsilon(Point p, double epsilon) {
		if (!(p instanceof Point)) {
			return false;
		}

		return Constants.compareDoubleEpsilon(this.getX(), p.getX(), epsilon) && Constants.compareDoubleEpsilon(this.getY(), p.getY(), epsilon)
				&& Constants.compareDoubleEpsilon(this.getZ(), p.getZ(), epsilon);
	}

	/**
	 * Get the angle between two points, with the current point as the origin.
	 * 
	 * @param p1 the first point.
	 * @param p2 the second point.
	 * @return the angle between the two points.
	 */
	public double getAngleBetween(Point p1, Point p2) {
		double a = this.getDistanceTo(p1);
		double b = this.getDistanceTo(p2);
		double c = p2.getDistanceTo(p1);

		return Math.acos((a * a + b * b - c * c) / (2 * a * b));
	}

	/**
	 * Get the distance to another point from the current point.
	 * 
	 * @param p the point to get the distance to.
	 * @return the distance between the points.
	 */
	public double getDistanceTo(Point p) {
		double x = p.getX() - this.getX();
		double y = p.getY() - this.getY();
		double z = p.getZ() - this.getZ();

		return Math.sqrt(x * x + y * y + z * z);
	}

	/**
	 * Get the x coordinate of this point.
	 * 
	 * @return the x coordinate.
	 */
	public double getX() {
		return this.x;
	}

	/**
	 * Get the y coordinate of this point.
	 * 
	 * @return the y coordinate.
	 */
	public double getY() {
		return this.y;
	}

	/**
	 * Get the z coordinate of this point.
	 * 
	 * @return the z coordinate.
	 */
	public double getZ() {
		return this.z;
	}

	/**
	 * Returns a unique value depending on the values of the coordinates.
	 * 
	 * @see <a
	 *      href="http://commons.apache.org/lang/api-2.5/org/apache/commons/lang/builder/HashCodeBuilder.html">HashCodeBuilder</a>
	 * 
	 * @return a hash code unique to the value of the LiteralPoint.
	 */
	@Override
	public int hashCode() {
		return new HashCodeBuilder().append(this.getX()).append(this.getY()).append(this.getZ()).toHashCode();
	}

	/**
	 * Subtract two points by subtracting each component of each point (x1 - x2, y1 - y2, z1 - z2).
	 * 
	 * @param rightSide the point to subtract from the current point.
	 * @return the result of the subtraction returned as a point.
	 */
	public Point minus(Point rightSide) {
		return new Point(this.x - rightSide.x, this.y - rightSide.y, this.z - rightSide.z);
	}

	/**
	 * Add two points by adding each component of each point (x1 + x2, y1 + y2, z1 + z2).
	 * 
	 * @param rightSide the point to add to the current point.
	 * @return the result of the addition returned as a point.
	 */
	public Point plus(Point rightSide) {
		return new Point(this.x + rightSide.x, this.y + rightSide.y, this.z + rightSide.z);
	}

	/**
	 * Set the x coordinate of this point.
	 * 
	 * @param x the value of the x coordinate.
	 */
	public void setX(double x) {
		this.x = x;
	}

	/**
	 * Set the y coordinate of this point.
	 * 
	 * @param y the value of the y coordinate.
	 */
	public void setY(double y) {
		this.y = y;
	}

	/**
	 * Set the z coordinate of this point.
	 * 
	 * @param z the value of the z coordinate.
	 */
	public void setZ(double z) {
		this.z = z;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return String.format("%f, %f, %f", this.x, this.y, this.z);
	}

	/**
	 * Convert the point to a vector 3
	 * 
	 * @return the vec3
	 */
	public Vec3 toVector3() {
		return new Vec3((float) this.x, (float) this.y, (float) this.z);
	}
}
