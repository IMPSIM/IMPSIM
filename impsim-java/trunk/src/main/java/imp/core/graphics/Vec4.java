package imp.core.graphics;

/**
 * Light weight 4 dimensional vector.
 * 
 * @author klehmc
 * @version 1.0
 * 
 */
public class Vec4 {
	public float x;
	public float y;
	public float z;
	public float w;

	/**
	 * Creates a 4 dimensional vector using the given array values.
	 * 
	 * @param v The default values in x y z w order.
	 */
	public Vec4(float v[]) {
		this.x = v[0];
		this.y = v[1];
		this.z = v[2];
		this.w = v[3];
	}

	/**
	 * Creates a 4 dimensional vector using the given array values.
	 * 
	 * @param x The x value.
	 * @param y The y value.
	 * @param z The z value.
	 * @param w The w value.
	 */
	public Vec4(float x, float y, float z, float w) {
		this.x = x;
		this.y = y;
		this.z = z;
		this.w = w;
	}

	/**
	 * Creates a 4 dimensional vector using a 3 dimensional vector and an additional value.
	 * 
	 * @param vec The 3 dimensional vector for x y z.
	 * @param w The additional value.
	 */
	public Vec4(Vec3 vec, float w) {
		this.x = vec.x;
		this.y = vec.y;
		this.z = vec.z;
		this.w = w;
	}

	/**
	 * Gives the magnitude of the vector.
	 * 
	 * @return The magnitude of the vector.
	 */
	public float length() {
		return this.magnitude();
	}

	/**
	 * Gives the magnitude of the vector.
	 * 
	 * @return The magnitude of the vector.
	 */
	public float magnitude() {
		// @formatter:off
		return (float) Math.sqrt(
			this.x * this.x +
			this.y * this.y +
			this.z * this.z +
			this.w * this.w
		);
		// @formatter:on
	}

	/**
	 * Subtracts one vector from another. Returns a new vector for the result.
	 * 
	 * @param vec The vector that will be subtracted from the current one
	 * @return A new vector with the subtracted value.
	 */
	public Vec4 minus(Vec4 vec) {
		// @formatter:off
		return new Vec4(
			this.x - vec.x,
			this.y - vec.y,
			this.z - vec.z,
			this.w - vec.w
		);
		// @formatter:on
	}

	/**
	 * Scales a vector by the given value.
	 * 
	 * @param n The value to scale the vector by.
	 * @return A new vector with values resulting from scaling the original.
	 */
	public Vec4 multiply(float n) {
		return new Vec4(this.x * n, this.y * n, this.z * n, this.w * n);
	}

	/**
	 * Normalize a vectors value by dividing them by the vectors magnitude.
	 * 
	 * @return A new vector with normalized values.
	 */
	public Vec4 normalize() {
		float mag = this.magnitude();

		return new Vec4(this.x / mag, this.y / mag, this.z / mag, this.w / mag);
	}

	/**
	 * Add two vectors together.
	 * 
	 * @param vec The vector to be added.
	 * @return A new vector with with the addition result.
	 */
	public Vec4 plus(Vec4 vec) {
		// @formatter:off
		return new Vec4(
			this.x + vec.x,
			this.y + vec.y,
			this.z + vec.z,
			this.w + vec.w
		);
		// @formatter:on
	}
}
