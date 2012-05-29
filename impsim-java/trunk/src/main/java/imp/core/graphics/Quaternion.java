package imp.core.graphics;


/**
 * Quaternions extend a rotation in three dimensions to a rotation in four dimensions. This is to prevent gimbal lock and allow for smooth continuous rotation.
 * @author kreierj
 * @version 1, 3/16/12
 *
 */
public class Quaternion {

	/**
	 * The x component
	 */
	private float x;

	/**
	 * The y component
	 */
	private float y;

	/**
	 * The z component
	 */
	private float z;

	/**
	 * The w component
	 */
	private float w;

	/**
	 * Instantiates a new Quaternion with x,y,z,w values 0,0,0,1
	 */
	public Quaternion() {
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	/**
	 * Instantiates a new Quaternion with the given parameters
	 * @param x component
	 * @param y component
	 * @param z component
	 * @param w component
	 */
	public Quaternion(float x, float y, float z, float w){
		this.x = x;
		this.y = y;
		this.z = z;
		this.w = w;
	}

	/**
	 * Returns the x component
	 * @return
	 */
	public float getX(){
		return x;
	}

	/**
	 * Returns the y component
	 * @return
	 */
	public float getY(){
		return y;
	}

	/**
	 * Returns the z component
	 * @return
	 */
	public float getZ(){
		return z;
	}

	/**
	 * Returns the w component
	 * @return
	 */
	public float getW(){
		return w;
	}

	/**
	 * Sets the components of the Quaternion
	 * @param x component
	 * @param y component
	 * @param z component
	 * @param w component
	 * @return this to allow easy chaining of method calls
	 */
	public Quaternion set(float x, float y, float z, float w){
		this.x = x;
		this.y = y;
		this.z = z;
		this.w = w;
		return this;
	}

	/**
	 * Builds a Quaternion from the rotation angles (y,r,p). These are applied in the order roll, pitch, yaw 
	 * but are ordered in x,y,z for convenience
	 * @param yaw Rotation in radians around the y axis
	 * @param roll Rotation in radians around the z axis
	 * @param pitch Rotation in radians around the x axis
	 * @return A quaternion which represents the rotation
	 */
	public Quaternion fromAngles(float yaw, float roll, float pitch){
		//helper variables
		double angle;
		double sinRoll;
		double sinPitch;
		double sinYaw;
		double cosRoll;
		double cosPitch;
		double cosYaw;

		angle = pitch * 0.5;
		sinPitch = Math.sin(angle);
		cosPitch = Math.cos(angle);

		angle = roll * 0.5;
		sinRoll = Math.sin(roll);
		cosRoll = Math.cos(roll);

		angle = yaw * 0.5;
		sinYaw = Math.sin(angle);
		cosYaw = Math.cos(angle);

		//more helper variables
		double cosRollXcosPitch = cosRoll * cosPitch;
		double sinRollXsinPitch = sinRoll * sinPitch;
		double cosRollXsinPitch = cosRoll * sinPitch;
		double sinRollXcosPitch = sinRoll * cosPitch;

		//the formula for how this crazy math works
		w = (float) (cosRollXcosPitch * cosYaw - sinRollXsinPitch * sinYaw);
		x = (float) (cosRollXcosPitch * sinYaw + sinRollXsinPitch * cosYaw);
		y = (float) (sinRollXcosPitch * cosYaw + cosRollXsinPitch * sinYaw);
		z = (float) (cosRollXsinPitch * cosYaw - sinRollXcosPitch * sinYaw);

		normalize();
		return this;
	}

	/**
	 * Normalizes the current quaternion into a unit quaternion
	 */
	public void normalize(){
		float n = (float) (1.0/Math.sqrt(w * w + x*x + y*y + z*z));
		x *= n;
		y *= n;
		z *= n;
		w *= n;
	}

	/**
	 * Multiplies this quaternion by a vector. The result is a Vector rotated in space by the quaternion
	 * @param v The vector to multiply this by
	 * @return The result vector
	 */
	public Vec3 mult(Vec3 v){
		Vec3 output = new Vec3(0,0,0);



		//helper variables
		float vx = v.x;
		float vy = v.y;
		float vz = v.z;

		//then do some crazy math
		output.x = w*w*vx + 2*y*w*vz - 2*z*w*vy + x*x*vx + 2*y*x*vy + 2*z*x*vz - z*z*vx - y*y*vx;

		output.y = 2*x*y*vx + y*y*vy + 2*z*y*vz + 2*w*z*vx - z*z*vy + w*w*vy - 2*x*w*vz - x*x*vy;

		output.z = 2*x*z*vx + 2*y*z*vy + z*z*vz - 2*w*y*vx - y*y*vz + 2*w*x*vy - x*x*vz + w*w*vz;

		return output;
	}

}
