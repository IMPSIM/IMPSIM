package imp.core.graphics;

/**
 * This class represents a 3 dimensional vector
 * @author kreierj
 * @edit kuszewskij added raw() for passing to openGL easier
 * @version 1, 3/19/2012
 */
public class Vec3 {
	
	/**
	 * The x component of the vector
	 */
	public float x;
	
	/**
	 * The y component of the vector
	 */
	public float y;
	
	/**
	 * The z component of the vector
	 */
	public float z;

	/**
	 * Instantiates a new vector from the passed in float array
	 * @param v 3 value float array
	 */
	public Vec3(float v[]) {
		this.x = v[0];
		this.y = v[1];
		this.z = v[2];
	}

	/**
	 * Instantiates a new vector from the parameters
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 */
	public Vec3(float x, float y, float z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	/**
	 * Returns the raw value of this vector in the form of a float array.
	 * @return
	 */
	public float[] raw(){
		return new float[]{this.x,this.y,this.z};
	}

	/**
	 * Performs the cross product
	 * @param vec The vector to cross with
	 * @return Result of the cross product as a new vector
	 */
	public Vec3 cross(Vec3 vec) {
		// @formatter:off
		return new Vec3(
			this.y * vec.z - this.z * vec.y,
			this.z * vec.x - this.x * vec.z,
			this.x * vec.y - this.y * vec.x
		);
		// @formatter:on
	}
	
	/**
	 * This method will return the dot product of this vector multiplied and the given vector
	 * @param vec The vector to take the dot Product of
	 * @return The dot Product
	 */
	public double dotProduct(Vec3 vec){
		double dotProduct = (this.x*vec.x)+(this.y*vec.y)+(this.z*vec.z);
		return dotProduct;
	}

	/**
	 * Returns the length of the vector
	 * @return
	 */
	public float length() {
		return this.magnitude();
	}
	
	/**
	 * This method will convert the vector to a 4X4 matrix.
	 * @return
	 */
	public Mat4 toMatrix(){
		Mat4 ret = new Mat4(0);
		ret.set(0, 0, this.x);
		ret.set(1, 1, this.y);
		ret.set(2, 2, this.z);
		ret.set(3, 3, 1f);
		return ret;
	}

	/**
	 * Returns the magnitude of the vector
	 * @return
	 */
	public float magnitude() {
		// @formatter:off
		return (float) Math.sqrt(
			this.x * this.x +
			this.y * this.y +
			this.z * this.z
		);
		// @formatter:on
	}

	/**
	 * Subtracts a vector from this vector
	 * @param vec The vector to subtract from this vector
	 * @return New vector result
	 */
	public Vec3 minus(Vec3 vec) {
		// @formatter:off
		return new Vec3(
			this.x - vec.x,
			this.y - vec.y,
			this.z - vec.z
		);
		// @formatter:on
	}

	/**
	 * Multiplies the vector by a scalar value
	 * @param n The scalar
	 * @return New vector result
	 */
	public Vec3 multiply(float n) {
		return new Vec3(this.x * n, this.y * n, this.z * n);
	}

	/**
	 * Normalizes the vector such that the magnitude = 1.0f
	 * @return new normalized vector
	 */
	public Vec3 normalize() {
		float mag = this.magnitude();

		return new Vec3(this.x / mag, this.y / mag, this.z / mag);
	}
	
	/**
	 * Normalizes the vector in place such that the magnitude = 1.0f
	 * @return this
	 */
	public Vec3 normalizeLocal(){
		float mag = this.magnitude();
		x = x/mag;
		y = y/mag;
		z = z/mag;
		
		return this;
	}

	/**
	 * Adds a vector to this vector
	 * @param vec the vector to add
	 * @return new result vector
	 */
	public Vec3 plus(Vec3 vec) {
		// @formatter:off
		return new Vec3(
			this.x + vec.x,
			this.y + vec.y,
			this.z + vec.z
		);
		// @formatter:on
	}
}
