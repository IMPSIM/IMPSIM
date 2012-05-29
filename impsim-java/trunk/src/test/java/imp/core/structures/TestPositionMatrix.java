/**
 *	TestPositionMatrix.java
 *	Feb 15, 2011
 */
package imp.core.structures;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NullParameterException;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import Jama.Matrix;

/**
 * @author zastrowm
 * @edit klehmc April 7, 2011 Updated to JUnit 4 format.
 * @version 1.0
 * 
 */
@SuppressWarnings("javadoc")
public class TestPositionMatrix {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.structures.PositionMatrix#fill(imp.core.structures.Vector3, imp.core.structures.Vector3, imp.core.structures.Vector3, imp.core.structures.Vector3)}
	 * .
	 * 
	 * @throws MatrixIndexOutOfBoundsException
	 */
	@Test
	public void testFill() throws MatrixIndexOutOfBoundsException {
		PositionMatrix pm = new PositionMatrix();
		Vector3 cols[] = new Vector3[4];
		cols[0] = new Vector3(1, 2, 3);
		cols[1] = new Vector3(2, 3, 4);
		cols[2] = new Vector3(5, 6, 7);
		cols[3] = new Vector3(5, 6, 7);

		pm.fill(cols[0], cols[1], cols[2], cols[3]);
		// checks that the matrix is full of the proper columns
		for (int i = 0; i < cols.length; i++) {
			assertTrue(pm.getColumn(i).equals(cols[i]));
		}
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#get(int, int)}.
	 */
	@Test
	public void testGet() {
		double a = 1;
		double b = 2;
		double c = 3;
		PositionMatrix pm = new PositionMatrix(new double[][] { { a, b, c, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } });
		// checks that the matrix is full of the proper columns
		assertEquals(pm.get(0, 0), a, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(pm.get(0, 1), b, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(pm.get(0, 2), c, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#getColumn(int)}.
	 */
	@Test
	public void testGetColumn() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } });
		// checks that the proper column is returned
		assertEquals(new Vector3(1, 5, 9), pm.getColumn(0));
		assertEquals(new Vector3(2, 6, 10), pm.getColumn(1));
		assertEquals(new Vector3(3, 7, 11), pm.getColumn(2));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#getRow(int)}.
	 */
	@Test
	public void testGetRow() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } });
		// checks that the proper row is returned
		assertEquals(new Vector3(1, 2, 3), pm.getRow(0));
		assertEquals(new Vector3(5, 6, 7), pm.getRow(1));
		assertEquals(new Vector3(9, 10, 11), pm.getRow(2));
	}

	/**
	 * Test method for {@link imp.structures.PositionMatrix#inverse())
	 */
	@Test
	public void testInverse() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix ref = new PositionMatrix(new double[][] { { 0, 1, -1, 0 }, { 1, -1, 1, 0 }, { -1, 1, 0, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix inv = pm.inverse();
		// checks that inverting the matrix works properly
		assertTrue(inv.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#multiply(PositionMatrix)}.
	 */
	@Test
	public void testMultiplyPositionMatrix() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix inv = new PositionMatrix(new double[][] { { 0, 1, -1, 0 }, { 1, -1, 1, 0 }, { -1, 1, 0, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix ref = new PositionMatrix(new double[][] { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix res = pm.multiply(inv);
		// checks that the result of a matrix multipliation is correct
		assertTrue(res.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#multiply(Vector3)}.
	 */
	@Test
	public void testMultiplyVector3() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 1 } });

		Vector3 vec = new Vector3(1, 2, 3);

		Vector3 ref = new Vector3(3, 6, 5);

		Vector3 res = pm.multiply(vec);

		assertTrue(res.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix()}.
	 */
	@Test
	public void testPositionMatrix() {
		PositionMatrix pm = new PositionMatrix();
		Matrix m = pm.getJamaMatrix();
		int rowd = m.getRowDimension();
		int cold = m.getColumnDimension();

		assertEquals(rowd, 4);
		assertEquals(cold, 4);
		assertEquals(pm.get(3, 3), 1.0, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix(double[][])} and
	 * {@link imp.core.structures.PositionMatrix#equals(PositionMatrix)} and
	 * {@link imp.core.structures.PositionMatrix#equalsEpsilon(PositionMatrix, double)}.
	 */
	@Test
	public void testPositionMatrixArrayArrayDouble() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } });

		PositionMatrix ref = new PositionMatrix();
		ref.fill(new Vector3(1, 5, 9), new Vector3(2, 6, 10), new Vector3(3, 7, 11), new Vector3(4, 8, 12));
		ref.set(3, 0, 13);
		ref.set(3, 1, 14);
		ref.set(3, 2, 15);
		ref.set(3, 3, 16);

		/**
		 * <pre>
		 * [ 1, 2,  3,  4 ] 
		 * [ 5, 6,  7,  8 ] 
		 * [ 9, 10, 11, 12] 
		 * [13, 14, 15, 16]
		 * </pre>
		 */

		assertTrue(pm.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix(double[][])} and
	 * {@link imp.core.structures.PositionMatrix#equals(PositionMatrix)} and
	 * {@link imp.core.structures.PositionMatrix#equalsEpsilon(PositionMatrix, double)}.
	 */
	@Test
	public void testPositionMatrixArrayArrayDoubleNull() {
		double[][] ref = null;
		// tests that a null parameter throws an exception
		this.thrown.expect(NullParameterException.class);
		new PositionMatrix(ref);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix(Jama.Matrix)} and
	 * {@link imp.core.structures.PositionMatrix#getJamaMatrix()}.
	 */
	@Test
	public void testPositionMatrixJamaMatrix() {
		Jama.Matrix ref = new Jama.Matrix(new double[][] { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 } });

		PositionMatrix pm = new PositionMatrix(ref);

		assertEquals(pm.getJamaMatrix(), ref);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix(Jama.Matrix)} and
	 * {@link imp.core.structures.PositionMatrix#getJamaMatrix()}.
	 */
	@Test
	public void testPositionMatrixJamaMatrixNull() {
		Jama.Matrix ref = null;

		this.thrown.expect(NullParameterException.class);
		new PositionMatrix(ref);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix(PositionMatrix) }
	 */
	@Test
	public void testPositionMatrixPositionMatrix() {
		PositionMatrix ref = new PositionMatrix(new double[][] { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 } });

		PositionMatrix pm = new PositionMatrix(ref);

		assertTrue(pm.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#PositionMatrix(PositionMatrix) }
	 */
	@Test
	public void testPositionMatrixPositionMatrixNull() {
		PositionMatrix ref = null;

		this.thrown.expect(NullParameterException.class);
		new PositionMatrix(ref);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#set(int,int,double)}.
	 */
	@Test
	public void testSet() throws MatrixIndexOutOfBoundsException {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix ref = new PositionMatrix(new double[][] { { 5, 1, 0, 0 }, { 1, 10, 1, 0 }, { 0, 1, 15, 0 }, { 0, 0, 0, 1 } });

		pm.set(0, 0, 5);
		pm.set(1, 1, 10);
		pm.set(2, 2, 15);

		assertTrue(pm.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#setColumn(int, imp.core.structures.Vector3)}.
	 */
	@Test
	public void testSetColumn() throws MatrixIndexOutOfBoundsException {
		PositionMatrix pm = new PositionMatrix();
		Vector3 cols[] = new Vector3[4];
		cols[0] = new Vector3(1, 2, 3);
		cols[1] = new Vector3(2, 3, 4);
		cols[2] = new Vector3(5, 6, 7);
		cols[3] = new Vector3(5, 6, 7);

		for (int i = 0; i < cols.length; i++) {
			pm.setColumn(i, cols[i]);
			assertTrue(pm.getColumn(i).equals(cols[i]));
		}
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#trace()}.
	 */
	@Test
	public void testTrace() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 1 } });

		double ref = 4;

		assertEquals(pm.trace(), ref, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#transpose()}.
	 */
	@Test
	public void testTranspose() {
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix ref = new PositionMatrix(new double[][] { { 1, 4, 7, 0 }, { 2, 5, 8, 0 }, { 3, 6, 9, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix trans = pm.transpose();

		assertTrue(trans.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(Object)}.
	 */
	@Test
	public void testEqualsObject() {
		Object ob1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		Object ob2 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		assertTrue(ob1.equals(ob2));
		assertTrue(ob2.equals(ob1));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(Object)}.
	 */
	@Test
	public void testEqualsObjectFalse() {

		Object ob1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		Object ob2 = new PositionMatrix(new double[][] { { 0, 3, 2, 1 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		assertFalse(ob1.equals(ob2));
		assertFalse(ob2.equals(ob1));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(Object)}.
	 */
	@Test
	public void testEqualsObjectFalseObjectType() {

		Object ob1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		Object ob2 = new Point();

		assertFalse(ob1.equals(ob2));
	}
	
	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(Object)}.
	 */
	@Test
	public void testEqualsObjectFalseNull() {

		Object ob1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		
		// shoudl not eqaul null object
		assertFalse(ob1.equals( null ));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(PositionMatrix)}.
	 */
	@Test
	public void testEqualsPositionMatrix() {
		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		PositionMatrix pm2 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		assertTrue(pm1.equals(pm2));
		assertTrue(pm2.equals(pm1));
	}
	
	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(PositionMatrix)}.
	 */
	@Test
	public void testEqualsPositionMatrixFalse() {
		
		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		PositionMatrix pm2 = new PositionMatrix(new double[][] { { 0, 3, 2, 1 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		assertFalse(pm1.equals(pm2));
		assertFalse(pm2.equals(pm1));
	}
	
	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equals(PositionMatrix)}.
	 */
	@Test
	public void testEqualsPositionMatrixFalseNull() {
		
		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });
		PositionMatrix pm2 = null;
		
		// should not equal null matrix
		assertFalse(pm1.equals(pm2));
	}

	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equalsEpsilon(PositionMatrix, double)}.
	 */
	@Test
	public void testEqualsEpsilon() {
		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1.5, 2.5, 3.5, 0 }, { 4.5, 5.5, 6.5, 0 }, { 7.5, 8.5, 9.5, 0 }, { 0, 0, 0, 1.5 } });
		PositionMatrix pm2 = new PositionMatrix(new double[][] { { 1.5, 2.5, 3.5, 0 }, { 4.5, 5.5, 6.5, 0 }, { 7.5, 8.5, 9.5, 0 }, { 0, 0, 0, 1.5 } });
		double epsilon = 0.01;
		
		// checks for a deep equals
		assertTrue(pm1.equalsEpsilon(pm2, epsilon));
		assertTrue(pm2.equalsEpsilon(pm1, epsilon));
	}
	
	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equalsEpsilon(PositionMatrix, double)}.
	 */
	@Test
	public void testEqualsEpsilonTolerance() {
		
		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1.5, 2.5, 3.5, 0 }, { 4.5, 5.5, 6.5, 0 }, { 7.5, 8.5, 9.5, 0 }, { 0, 0, 0, 1.5 } });
		PositionMatrix pm2 = new PositionMatrix(new double[][] { { 1.501, 2.501, 3.501, 0 }, { 4.501, 5.501, 6.501, 0 }, { 7.501, 8.501, 9.501, 0 },
				{ 0, 0, 0, 1.501 } });
		double epsilon = 0.01;

		assertTrue(pm1.equalsEpsilon(pm2, epsilon));
		assertTrue(pm2.equalsEpsilon(pm1, epsilon));
	}
	
	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equalsEpsilon(PositionMatrix, double)}.
	 */
	@Test
	public void testEqualsEpsilonFalseTolerance() {

		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1.5, 2.5, 3.5, 0 }, { 4.5, 5.5, 6.5, 0 }, { 7.5, 8.5, 9.5, 0 }, { 0, 0, 0, 1.5 } });
		PositionMatrix pm2 = new PositionMatrix(new double[][] { { 1.501, 2.501, 3.501, 0 }, { 4.501, 5.501, 6.501, 0 }, { 7.501, 8.501, 9.501, 0 },
				{ 0, 0, 0, 1.501 } });
		double epsilon = 0.001;
		
		assertFalse(pm1.equalsEpsilon(pm2, epsilon));
		assertFalse(pm2.equalsEpsilon(pm1, epsilon));
	}
	
	/**
	 * Test method for {@link imp.core.structures.PositionMatrix#equalsEpsilon(PositionMatrix, double)}.
	 */
	@Test
	public void testEqualsEpsilonFalseNull() {
		PositionMatrix pm1 = new PositionMatrix(new double[][] { { 1.5, 2.5, 3.5, 0 }, { 4.5, 5.5, 6.5, 0 }, { 7.5, 8.5, 9.5, 0 }, { 0, 0, 0, 1.5 } });
		PositionMatrix pm2 = null;
		double epsilon = 0.01;
		
		assertFalse(pm1.equalsEpsilon(pm2, epsilon));
	}
}