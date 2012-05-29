/**
 * PositionMatrix.java 
 * January 14, 2011
 * 
 */

package imp.core.structures;

import imp.core.Constants;
import imp.core.exceptions.NullParameterException;
import Jama.Matrix;

/**
 * Defines a specialized 4x4 matrix. The 4th row and column are known constants. Represents a position matrix of a body
 * or joint.
 * 
 * @author kemmannl dykstran klehmc
 * @edit dykstran Updated JavaDoc
 * @version 1.21
 */
public class PositionMatrix {

	/**
	 * The JAMA matrix used for internal storage.
	 */
	private Matrix matrix;

	/**
	 * Defines a 4x4 matrix filled with the identity values.
	 */
	public PositionMatrix() {
		/* Initializes to identity matrix */
		this.matrix = Matrix.identity(4, 4);
	}

	/**
	 * Defines a 4x4 matrix filled with the specified values. The last row of any matrix used in IMP is {0,0,0,1}. The
	 * last column will also be {0,0,0,1}.
	 * 
	 * @param values the values with which to populate the matrix.
	 */
	public PositionMatrix(double[][] values) {

		// check for null array of values
		NullParameterException.check(values, "values", 0);

		this.matrix = new Matrix(values);

	}

	/**
	 * Creates a 4x4 matrix from the Jama matrix passed in.
	 * 
	 * @param matrix the Jama matrix to create this position matrix from.
	 */
	public PositionMatrix(Jama.Matrix matrix) {

		// check for null Jama matrix
		NullParameterException.check(matrix, "matrix", 0);

		this.matrix = matrix;
	}

	/**
	 * Creates a new position matrix that is a copy of the matrix passed in.
	 * 
	 * @param posMtx the position matrix used to create this position matrix from.
	 */
	public PositionMatrix(PositionMatrix posMtx) {

		// check for null PositionMatrix
		NullParameterException.check(posMtx, "posMtx", 0);

		this.matrix = new Matrix(posMtx.getJamaMatrix().getArrayCopy());
	}

	/**
	 * Create a shallow copy of this matrix.
	 * 
	 * @return a copy of this matrix.
	 */
	public PositionMatrix copy() {
		return new PositionMatrix(this);
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o) {
		if (o instanceof PositionMatrix) {
			return this.equals((PositionMatrix) o);
		} else {
			return false;
		}
	}

	/**
	 * Compares two matrices for equality with the error tolerance constraint.
	 * 
	 * @param pm the PositionMatrix to compare to.
	 * @return true if the matrices' values match, false otherwise.
	 */
	public boolean equals(PositionMatrix pm) {
		return this.equalsEpsilon(pm, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Compares two matrices for equality with the specifed error tolerance constraint.
	 * 
	 * @param pm the PositionMatrix to compare to.
	 * @param epsilon the maximum allowed difference between values.
	 * @return true if the matrices' values match, false otherwise.
	 */
	public boolean equalsEpsilon(PositionMatrix pm, double epsilon) {
		
		if( pm == null ) {
			return false;
		}
		
		boolean foundMismatch = false;
		Matrix jm = pm.getJamaMatrix();
		Matrix tm = this.getJamaMatrix();
		int numRows = tm.getRowDimension();
		int numCols = tm.getColumnDimension();

		if ((jm.getColumnDimension() == numCols) && (jm.getRowDimension() == numRows)) {

			for (int r = 0; r < numRows && !foundMismatch; ++r) {
				for (int c = 0; c < numCols && !foundMismatch; ++c) {

					if (!Constants.compareDoubleEpsilon(this.get(r, c), pm.get(r, c), epsilon)) {
						foundMismatch = true;
					}
				}
			}
		}

		return !foundMismatch;
	}

	/**
	 * Set the first 3 rows of each column with vector values. The last row in a position matrix is a constant value in
	 * IMP and so cannot be set.
	 * 
	 * @param col1 the first column of the position matrix.
	 * @param col2 the second column of the position matrix.
	 * @param col3 the third column of the position matrix.
	 * @param col4 the fourth column of the position matrix.
	 */
	public void fill(Vector3 col1, Vector3 col2, Vector3 col3, Vector3 col4) {
		this.setColumn(0, col1);
		this.setColumn(1, col2);
		this.setColumn(2, col3);
		this.setColumn(3, col4);
	}

	/**
	 * Returns the value at the specified row and column.
	 * 
	 * @param row the row in the matrix (0-based).
	 * @param column the column in the matrix (0-based).
	 * @return the element at the specified row and column.
	 */
	public double get(int row, int column) {
		return this.matrix.get(row, column);
	}

	/**
	 * Returns the i-th column from the 4x3 sub-matrix. (The 4th row is known to be [0,0,0,1]).
	 * 
	 * @param column The column to retrieve (0 based).
	 * @return a Vector3 representation of the the column.
	 */
	public Vector3 getColumn(int column) {
		return new Vector3(this.get(0, column), this.get(1, column), this.get(2, column));
	}

	/**
	 * Gets the underlying Jama matrix for this position matrix.
	 * 
	 * @return the Jama matrix.
	 */
	public Matrix getJamaMatrix() {
		return this.matrix;
	}

	/**
	 * Returns the i-th row from the 4x3 sub-matrix. (The 4th row is known to be [0,0,0,1]).
	 * 
	 * @param row the row index to return (0-based).
	 * @return the i-th row from the 4x3 sub-matrix as a Vector3.
	 */
	public Vector3 getRow(int row) {
		return new Vector3(this.get(row, 0), this.get(row, 1), this.get(row, 2));
	}

	/**
	 * Returns a unique value depending on the values of the coordinates. IBM says we should implement this if we
	 * implement equals or we'll have weird bugs with HashMaps.
	 * 
	 * Use a real library for hashing so it actually works right.
	 * 
	 * @see <a
	 *      href="http://commons.apache.org/lang/api-2.5/org/apache/commons/lang/builder/HashCodeBuilder.html">HashCodeBuilder</a>
	 * 
	 * @return A hash code unique to the value of the PositionMatrix.
	 */
	// public int hashCode() {
	// FIXME: We should implement this since we override equals.
	// The biggest
	// issue is using this object as a HashMap key (it'll be fail if we don't
	// do this right).
	// I looked into this for an hour and it's quite tricky to do well. The
	// Apache hashcodebuilder library looks like the way to go.
	// }

	/**
	 * Returns the inverse of this matrix.
	 * 
	 * @return the inverse of this matrix.
	 */
	public PositionMatrix inverse() {
		// OPTIMIZE: matrix inverse, libmath/invxc.c invrt.c
		return new PositionMatrix(this.matrix.inverse());
	}

	/**
	 * Multiply this position matrix by another position matrix and return the resulting position matrix.
	 * 
	 * @param matrix the position matrix to multiply this one with.
	 * @return the product of the two position matrices.
	 */
	public PositionMatrix multiply(PositionMatrix matrix) {
		/* Use Jama to perform multiplication */
		Matrix result = this.matrix.times((matrix.getJamaMatrix()));
		return new PositionMatrix(result);
	}

	/**
	 * Multiplies this matrix by a 4-dimensional vector (last element implied to be 0).
	 * 
	 * @param vector the vector to multiply by.
	 * @return the product of this matrix and the vector (last element implied to be 0).
	 */
	public Vector3 multiply(Vector3 vector) {

		/* Create the 4x1 matrix to multiply this 4x4 matrix by */
		Matrix multiplier = new Matrix(4, 1);
		multiplier.set(0, 0, vector.getX());
		multiplier.set(1, 0, vector.getY());
		multiplier.set(2, 0, vector.getZ());
		multiplier.set(3, 0, 0);

		/* Multiply the matrices and convert the result to a Vector3 */
		Matrix resultMatrix = this.matrix.times(multiplier);
		Vector3 resultVector = new Vector3(resultMatrix.get(0, 0), resultMatrix.get(1, 0), resultMatrix.get(2, 0));

		return resultVector;
	}

	/**
	 * Set the element value at the specified row and column. Does not allow the user to set the values in the last row.
	 * 
	 * @param row the row in the matrix (0-based).
	 * @param column the column in the matrix (0-based).
	 * @param value the value to set in the matrix.
	 */
	public void set(int row, int column, double value) {

		this.matrix.set(row, column, value);
	}

	/**
	 * Set the column with the Vector3 data.
	 * 
	 * @param column the column data to set.
	 * @param data the Vector3 which holds the data.
	 */
	public void setColumn(int column, Vector3 data) {
		this.set(0, column, data.getX());
		this.set(1, column, data.getY());
		this.set(2, column, data.getZ());
	}

	/**
	 * Set this position matrix's underlying Jama matrix.
	 * 
	 * @param m the Jama matrix to set this position matrix to.
	 */
	public void setJamaMatrix(Matrix m) {
		this.matrix = m;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		StringBuffer out = new StringBuffer();

		int numRows = this.matrix.getRowDimension();
		int numCols = this.matrix.getColumnDimension();

		out.append("\n{");

		for (int r = 0; r < numRows; ++r) {
			if (r != 0) {
				out.append(',');
			}

			out.append("\n{ ");

			for (int c = 0; c < numCols; ++c) {
				if (c != 0) {
					out.append(", ");
				}

				out.append(this.matrix.get(r, c));
			}

			out.append('}');
		}

		out.append("\n}\n");

		return out.toString();
	}

	/**
	 * Converts this position matrix into an array.
	 * 
	 * @return an array of floating point numbers.
	 */
	public float[] toFloatArray() {
		float[] retArr = new float[16];

		// row walk
		for (int r = 0; r < 4; ++r) {
			// col walk
			for (int c = 0; c < 4; ++c) {
				int curIndex = r * 4 + c;
				retArr[curIndex] = (float) matrix.get(r, c);
			}
		}

		return retArr;
	}

	/**
	 * The trace is the sum of the main diagonal, from the upper left to the lower right.
	 * 
	 * @return the sum of the main diagonal.
	 */
	public double trace() {
		return this.matrix.trace();
	}

	/**
	 * Get the transpose of this matrix.
	 * 
	 * @return the transposed matrix.
	 */
	public PositionMatrix transpose() {
		return new PositionMatrix(this.matrix.transpose());
	}
}