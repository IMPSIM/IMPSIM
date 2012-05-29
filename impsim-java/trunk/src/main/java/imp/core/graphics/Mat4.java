/* Mat4.java
 */
package imp.core.graphics;

/**
 * A very lightweight 4x4 matrix class that uses a primitive float array for easy interfacing with the JOGL wrapper.
 * 
 * @author klehmc
 * @version 2.0
 * @edit Justin Kreier - Removed default constructor to hide its visibility
 */
public class Mat4 {
	
	private float matrix[];
	/** Can write out your matrix either way we default to having it column oriented */
	public static final boolean rowOriented = false;
	/** The dimension of our 4x4 is 4! wow */
	private static final int DIM = 4;


	/**
	 * Diagonals are the same for row and col orientation so no special handling.
	 * 
	 * @param val Create a diagonal of this value.
	 */
	public Mat4(float val) {
		// @formatter:off
		// no worries about row col orientation due to diagonal only
		this.matrix = new float[] { 
			val,  0.0f, 0.0f, 0.0f,
			0.0f, val,  0.0f, 0.0f,
			0.0f, 0.0f, val,  0.0f,
			0.0f, 0.0f, 0.0f, val
		};
		// @formatter:on
	}

	/**
	 * Initialize the matrix to the passed in array.
	 * 
	 * @param m The values to be set
	 */
	public Mat4(float m[]) {
		this.matrix = new float[m.length];

		for (int i = 0; i < m.length; ++i) {
			this.matrix[i] = m[i];
		}
	}

	/**
	 * Create a copy
	 * 
	 * @param m The Mat4 to copy.
	 */
	public Mat4(Mat4 m) {
		this(m.raw());
	}

	/**
	 * Multiply one matrix by another.
	 * 
	 * @param m The matrix to get multiplied.
	 * @return The result of the multiplication.
	 */
	public Mat4 multiply(Mat4 m) {
		float result[] = new float[16];
		float a[] = this.raw();
		float b[] = m.raw();

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result[j * 4 + i] = 0.0f;

				for (int k = 0; k < 4; ++k) {
					result[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
				}
			}
		}

		return new Mat4(result);
	}

	/**
	 * Double secret recipe for doing matrix perspective math.
	 * 
	 * @param fov Field of view.
	 * @param aspect Aspect ratio.
	 * @param near Near ratio.
	 * @param far Far ratio.
	 */
	public void perspective(float fov, float aspect, float near, float far) {
		float range = (float) (Math.tan(Math.toRadians(fov / 2.0f)) * near);
		float left = -range * aspect;
		float right = range * aspect;
		float bottom = -range;
		float top = range;

		float zeze = (2.0f * near) / (right - left);
		float onon = (2.0f * near) / (top - bottom);
		float twtw = -(far + near) / (far - near);
		float twth = -1.0f;
		float thtw = -(2.0f * far * near) / (far - near);

		Mat4 pers;

		if (rowOriented) {
			// @formatter:off
			pers = new Mat4(new float[] {
				zeze, 0.0f, 0.0f, 0.0f,
				0.0f, onon, 0.0f, 0.0f,
				0.0f, 0.0f, twtw, thtw,
				0.0f, 0.0f, twth, 0.0f
			});
			// @formatter:on
		} else {
			// @formatter:off
			pers = new Mat4(new float[] {
				zeze, 0.0f, 0.0f, 0.0f,
				0.0f, onon, 0.0f, 0.0f,
				0.0f, 0.0f, twtw, twth,
				0.0f, 0.0f, thtw, 0.0f
			});
			// @formatter:on
		}

		this.matrix = this.multiply(pers).raw();
	}
	

	/**
	 * Get the primitive array representation of this matrix, it's how JOGL likes it.
	 * 
	 * @return An array of floats.
	 */
	public float[] raw() {
		return this.matrix;
	}

	/**
	 * A scaling matrix multiply modifying this matrix.
	 * 
	 * @param x Scale of x.
	 * @param y Scale of y.
	 * @param z Scale of z.
	 */
	public void scale(float x, float y, float z) {
		Mat4 scale = new Mat4(1.0f);

		scale.set(0, 0, x);
		scale.set(1, 1, y);
		scale.set(2, 2, z);

		this.matrix = this.multiply(scale).raw();
	}

	/**
	 * Scaling matrix multiply using vector values.
	 * 
	 * @param vec The vector of values to use.
	 */
	public void scale(Vec3 vec) {
		Mat4 scale = new Mat4(1.0f);

		scale.set(0, 0, vec.x);
		scale.set(1, 1, vec.y);
		scale.set(2, 2, vec.z);

		this.matrix = this.multiply(scale).raw();
	}

	/**
	 * Set a location on the matrix to a certain value.
	 * 
	 * @param col The column location.
	 * @param row The row location.
	 * @param val The value to be set.
	 */
	public void set(int col, int row, float val) {
		if (rowOriented) {
			this.matrix[row * DIM + col] = val;
		} else {
			this.matrix[col * DIM + row] = val;
		}
	}

	/**
	 * Set a row or column depending on your orientation to a vector4.
	 * 
	 * @param the major location (either row or col depending on rowOriented)
	 * @param vec The values to set
	 */
	public void set(int loc, Vec4 vec) {
		this.set(loc, 0, vec.x);
		this.set(loc, 1, vec.y);
		this.set(loc, 2, vec.z);
		this.set(loc, 3, vec.w);
	}

	/**
	 * Modify the current matrix with a translation matrix based on the values passed in.
	 * 
	 * @param x The x value.
	 * @param y The y value.
	 * @param z The z value.
	 */
	public void translate(float x, float y, float z) {
		Mat4 trans = new Mat4(1.0f);
		trans.set(3, new Vec4(x, y, z, 1.0f));

		this.matrix = this.multiply(trans).raw();
	}

	/**
	 * Modify the current matrix with a translation matrix based on the values passed in.
	 * 
	 * @param vec The values to modify with.
	 */
	public void translate(Vec3 vec) {
		Mat4 trans = new Mat4(1.0f);
		trans.set(3, new Vec4(vec, 1.0f));

		this.matrix = this.multiply(trans).raw();
	}

	/**
	 * Transpose the matrix.
	 * 
	 * @return A new matrix with transposed values.
	 */
	public Mat4 transpose() {
		float m[] = this.matrix;
		// @formatter:off
		// no worries about row col here since mirrored
		return new Mat4(new float[] {
				m[0], m[4], m[8],  m[12],
				m[1], m[5], m[9],  m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]
		});
		// @formatter:on
	}
}
