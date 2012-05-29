/**
 * TestMatrixMath.java
 */
package imp.core;

import static org.junit.Assert.assertEquals;

import org.apache.commons.math.linear.Array2DRowRealMatrix;
import org.apache.commons.math.linear.ArrayRealVector;
import org.apache.commons.math.linear.DecompositionSolver;
import org.apache.commons.math.linear.QRDecompositionImpl;
import org.apache.commons.math.linear.RealMatrix;
import org.apache.commons.math.linear.RealVector;
import org.apache.commons.math.linear.SingularValueDecompositionImpl;
import org.junit.Test;

/**
 * @author hellmerj
 * @version 1.0
 * 
 *          This test class was created to test multiple Java matrix math libraries to determine which were capable of
 *          solving rank deficient matrices. The libraries tested were JAMA, Apache, EJML, and Colt. After completion of
 *          testing, the only library with the necessary capabilities was the Apache Commons Math library. The other
 *          library tests were removed to eliminate errors from the imp test suite and additional Apache tests were
 *          created.
 * 
 */
public class TestMatrixMath {

	/**
	 * Testing Apache with underdetermined (rank deficient) matrix
	 */
	@Test
	public void TestUnderDeterminedApache() {
		// create rank deficient matrix of equations for unknowns
		RealMatrix a = new Array2DRowRealMatrix(new double[][] { { 1, 1, 1 }, { 1, 2, -1 } }, false);

		// get decomposition solver used to solve rank deficient matrices
		DecompositionSolver solver = new SingularValueDecompositionImpl(a).getSolver();

		// create matrix of solutions to equations
		RealMatrix b = new Array2DRowRealMatrix(new double[][] { { 3 }, { 4 } }, false);

		// solve for the unknown variables
		RealMatrix x = solver.solve(b);

		// create expected output vector
		RealVector exp = new ArrayRealVector(new double[] { 1.14286, 1.57143, 0.28571 }, false);

		// compare values
		assertEquals(x.getEntry(0, 0), exp.getEntry(0), 0.001);
		assertEquals(x.getEntry(1, 0), exp.getEntry(1), 0.001);
		assertEquals(x.getEntry(2, 0), exp.getEntry(2), 0.001);
	}

	/**
	 * Testing Apache with overdetermined matrix
	 */
	@Test
	public void TestOverDeterminedApache() {
		// create overdetermined matrix of equations
		RealMatrix a = new Array2DRowRealMatrix(new double[][] { { 1, 1 }, { 1, -1 }, { 1, -2 }, { 1, -3 } }, false);

		// get decomposition solver
		DecompositionSolver solver = new QRDecompositionImpl(a).getSolver();

		// create matrix of solutions to equations
		RealMatrix b = new Array2DRowRealMatrix(new double[][] { { 4 }, { 2 }, { 7 }, { 6 } }, false);

		// solve for the unknown variables
		RealMatrix x = solver.solve(b);

		// create expected output vector
		RealVector exp = new ArrayRealVector(new double[] { 3.85714, -0.71429 }, false);

		// compare values
		assertEquals(x.getEntry(0, 0), exp.getEntry(0), 0.001);
		assertEquals(x.getEntry(1, 0), exp.getEntry(1), 0.001);
	}

	/**
	 * Testing Apache for square matrix
	 */
	@Test
	public void TestSquareApache() {
		// create equation matrix (equal number of equations and unknowns)
		RealMatrix a = new Array2DRowRealMatrix(new double[][] { { 3, 1 }, { 2, 3 } }, false);

		// create matrix of solutions to equations
		RealMatrix b = new Array2DRowRealMatrix(new double[][] { { 8 }, { 10 } }, false);

		// solve for unknown variables (this is a deprecated method)
		@SuppressWarnings("deprecation")
		RealMatrix x = a.solve(b);

		// create expected output vector
		RealVector exp = new ArrayRealVector(new double[] { 2, 2 }, false);

		// compare values
		assertEquals(x.getEntry(0, 0), exp.getEntry(0), 0.001);
		assertEquals(x.getEntry(1, 0), exp.getEntry(1), 0.001);
	}

	/**
	 * Testing Apache for square matrix with the QRDecomposition
	 */
	@Test
	public void TestSquareApacheQR() {
		// create equation matrix (equal number of equations and unknowns)
		RealMatrix a = new Array2DRowRealMatrix(new double[][] { { 3, 1 }, { 2, 3 } }, false);

		// get decomposition solver
		DecompositionSolver solver = new QRDecompositionImpl(a).getSolver();

		// create matrix of solutions to equations
		RealMatrix b = new Array2DRowRealMatrix(new double[][] { { 8 }, { 10 } }, false);

		// solve for unknown variables
		RealMatrix x = solver.solve(b);

		// create expected output vector
		RealVector exp = new ArrayRealVector(new double[] { 2, 2 }, false);

		// compare values
		assertEquals(x.getEntry(0, 0), exp.getEntry(0), 0.001);
		assertEquals(x.getEntry(1, 0), exp.getEntry(1), 0.001);
	}

	/**
	 * Testing Apache for square matrix with SingularValueDecomposition
	 */
	@Test
	public void TestSquareApacheSVD() {
		// create equation matrix (equal number of equations and unknowns)
		RealMatrix a = new Array2DRowRealMatrix(new double[][] { { 3, 1 }, { 2, 3 } }, false);

		// get decomposition solver
		DecompositionSolver solver = new SingularValueDecompositionImpl(a).getSolver();

		// create matrix of solutions to equations
		RealMatrix b = new Array2DRowRealMatrix(new double[][] { { 8 }, { 10 } }, false);

		// solve for unknown variables
		RealMatrix x = solver.solve(b);

		// create expected output vector
		RealVector exp = new ArrayRealVector(new double[] { 2, 2 }, false);

		// compare values
		assertEquals(x.getEntry(0, 0), exp.getEntry(0), 0.001);
		assertEquals(x.getEntry(1, 0), exp.getEntry(1), 0.001);
	}

}
