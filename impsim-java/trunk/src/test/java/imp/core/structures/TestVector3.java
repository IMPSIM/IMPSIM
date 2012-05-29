/**
 *	TestVector3.java part of IMP
 *	Feb 15, 2011
 */
package imp.core.structures;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.NullParameterException;
import imp.core.structures.Point;
import imp.core.structures.Vector3;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * This unit test is used to verify the functionality of the Vector3 class in the imp.core package.
 * 
 * @author groszc klehmc
 * @version 1.1
 */
@SuppressWarnings("javadoc")
public class TestVector3 {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.structures.Vector3#crossProduct(Vector3)}.
	 */
	@Test
	public void testCrossProduct() {
		// a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// instantiate
		Vector3 v2 = new Vector3(0, 1, 2);
		// verify the cross product
		assertEquals(v1.crossProduct(v2).getX(), 1.0, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(v1.crossProduct(v2).getY(), -2.0, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(v1.crossProduct(v2).getZ(), 1.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#crossProduct(Vector3)}.
	 */
	@Test
	public void testCrossProductCase2() {
		// a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// instantiate
		Vector3 v2 = new Vector3(1, 2, 3);
		// verify the cross product
		assertEquals(v1.crossProduct(v2).getX(), 0.0, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(v1.crossProduct(v2).getY(), 0.0, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(v1.crossProduct(v2).getZ(), 0.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#crossProduct(Vector3)}.
	 */
	@Test
	public void testCrossProductCase3() {
		// a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// instantiate
		Vector3 v2 = new Vector3(2, 3, 4);
		// verify the cross product
		assertEquals(v1.crossProduct(v2).getX(), -1.0, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(v1.crossProduct(v2).getY(), 2.0, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(v1.crossProduct(v2).getZ(), -1.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#dotProduct(Vector3)}.
	 */
	@Test
	public void testDotProduct() {
		// a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// instantiate
		Vector3 v2 = new Vector3(0, 1, 2);
		// verify the dot product
		assertEquals(v1.dotProduct(v2), 8.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#dotProduct(Vector3)}.
	 */
	@Test
	public void testDotProductCase2() {
		// a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// instantiate
		Vector3 v2 = new Vector3(1, 2, 3);
		// verify the dot product
		assertEquals(v1.dotProduct(v2), 14.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#dotProduct(Vector3)}.
	 */
	@Test
	public void testDotProductCase3() {
		// a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// instantiate
		Vector3 v2 = new Vector3(2, 3, 4);
		// verify the dot product
		assertEquals(v1.dotProduct(v2), 20.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equalsEpsilon(Vector3, double)}.
	 */
	@Test
	public void testEqualsEpsilon() {
		Vector3 a = new Vector3(1.5, 2.5, 3.5);
		Vector3 b = new Vector3(1.5, 2.5, 3.5);
		double epsilon = 0.01;

		// sunny day => two vectors with equal values
		assertTrue(a.equalsEpsilon(b, epsilon));
		assertTrue(b.equalsEpsilon(a, epsilon));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equalsEpsilon(Vector3, double)}.
	 */
	@Test
	public void testEqualsEpsilonTolerance() {
		Vector3 a = new Vector3(1.5, 2.5, 3.5);
		Vector3 c = new Vector3(1.501, 2.501, 3.501);
		double epsilon = 0.01;

		// two vectors that are not equal but are equal to tolerance
		assertTrue(a.equalsEpsilon(c, epsilon));
		assertTrue(c.equalsEpsilon(a, epsilon));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equalsEpsilon(Vector3, double)}.
	 */
	@Test
	public void testEqualsEpsilonFalseTolerance() {
		Vector3 a = new Vector3(1.5, 2.5, 3.5);
		Vector3 c = new Vector3(1.501, 2.501, 3.501);
		double epsilon = 0.0001;

		// two vectors not equal at tolerance
		assertFalse(a.equalsEpsilon(c, epsilon));
		assertFalse(c.equalsEpsilon(a, epsilon));
	}
	
	/**
	 * Test method for {@link imp.core.structures.Vector3#equalsEpsilon(Vector3, double)}.
	 */
	@Test
	public void testEqualsEpsilonFalseNull() {
		Vector3 a = new Vector3(1.5, 2.5, 3.5);
		Vector3 b = null;
		double epsilon = 0.0001;
		
		// should not equal null vector
		assertFalse(a.equalsEpsilon(b, epsilon));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObject() {

		// Sunny day two equal vector3 objects
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 b = new Vector3(1, 2, 3);

		assertEquals(a, b);
		assertEquals(b, a);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObjectFalse() {

		// two unequal vector3 objects
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 b = new Vector3(1, 2, 3);
		Vector3 c = new Vector3(1, 2, 4);

		assertFalse(a.equals(c));
		assertFalse(c.equals(a));
		assertFalse(b.equals(c));
		assertFalse(c.equals(b));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObjectFalseObjectType() {
		Vector3 a = new Vector3(1, 2, 3);

		// object that is not vector3
		Object p = new Point();
		assertFalse(a.equals(p));
	}
	
	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObjectFalseNull() {

		// two unequal vector3 objects
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 b = null;
		
		// should not equal null object
		assertFalse(a.equals(b));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(Vector3)}.
	 */
	@Test
	public void testEqualsVector3() {
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 b = new Vector3(1, 2, 3);

		assertTrue(a.equals(b));
		assertTrue(b.equals(a));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(Vector3)}.
	 */
	@Test
	public void testEqualsVector3False() {
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 c = new Vector3(2, 3, 4);

		assertFalse(a.equals(c));
		assertFalse(c.equals(a));
	}
	
	/**
	 * Test method for {@link imp.core.structures.Vector3#equals(Vector3)}.
	 */
	@Test
	public void testEqualsVector3FalseNull() {
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 c = null;
		
		assertFalse(a.equals(c));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#get(int)}.
	 */
	@Test
	public void testGet() {
		// instantiate a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// verify the x argument
		assertEquals(v1.get(0), 1.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v1.get(1), 2.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v1.get(2), 3.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#magnitude()}.
	 */
	@Test
	public void testMagnitude() {
		// a vector3 to test
		Vector3 v1;

		// instantiate
		v1 = new Vector3(0, 1, 2);
		// verify the magnitude
		assertEquals(v1.magnitude(), Math.sqrt(5), imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#magnitude()}.
	 */
	@Test
	public void testMagnitudeCase2() {

		// instantiate
		Vector3 v1 = new Vector3(1, 2, 3);
		// verify the magnitude
		assertEquals(v1.magnitude(), Math.sqrt(14), imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#magnitude()}.
	 */
	@Test
	public void testMagnitudeCase3() {

		// instantiate
		Vector3 v1 = new Vector3(2, 3, 4);
		// verify the magnitude
		assertEquals(v1.magnitude(), Math.sqrt(29), imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#normalize()}.
	 */
	@Test
	public void testNormalize() {
		Vector3 v = new Vector3(1, 2, 3);
		Vector3 ref = new Vector3(1.0 / Math.sqrt(14), Math.sqrt(2.0 / 7.0), 3.0 / Math.sqrt(14));

		Vector3 res = v.normalize();

		assertTrue(res.equals(ref));
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#scalarMultiply(double)}.
	 */
	@Test
	public void testScalarMultiply() {
		// instantiate a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		Vector3 v2 = v1.scalarMultiply(3);

		// verify the x argument
		assertEquals(v2.getX(), 3.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v2.getY(), 6.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v2.getZ(), 9.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#set(int, double)}.
	 */
	@Test
	public void testSet() {
		// instantiate a vector3 to test
		Vector3 v1 = new Vector3(0, 0, 0);

		v1.set(0, 1);
		v1.set(1, 2);
		v1.set(2, 3);

		// verify the x argument
		assertEquals(v1.getX(), 1.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v1.getY(), 2.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v1.getZ(), 3.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#subtract(imp.core.structures.Vector3)}.
	 */
	@Test
	public void testSubtract() {
		Vector3 a = new Vector3(1, 2, 3);
		Vector3 b = new Vector3(1, 2, 3);
		Vector3 c = new Vector3(1, 2, 4);
		Vector3 d = new Vector3(0, 0, 0);
		Vector3 e = new Vector3(-1, -2, -3);
		Vector3 f = new Vector3(0, 0, 1);

		assertEquals(a.subtract(b), d);
		assertEquals(b.subtract(a), d);
		assertEquals(d.subtract(a), e);
		assertEquals(c.subtract(a), f);
		assertEquals(c.subtract(f), b);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#Vector3(double, double, double)} and
	 * {@link imp.core.structures.Vector3#getX()} and {@link imp.core.structures.Vector3#getY()} and
	 * {@link imp.core.structures.Vector3#getZ()}
	 */
	@Test
	public void testVector3DoubleDoubleDouble() {
		// instantiate a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);

		// verify the x argument
		assertEquals(v1.getX(), 1.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v1.getY(), 2.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v1.getZ(), 3.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#Vector3(Point)}
	 */
	@Test
	public void testVector3Point() {
		// instantiate a vector3 to test
		Point p = new Point(1, 2, 3);
		Vector3 v2 = new Vector3(p);

		// verify the x argument
		assertEquals(v2.getX(), 1.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v2.getY(), 2.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v2.getZ(), 3.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#Vector3(Point)}
	 */
	@Test
	public void testVector3PointNull() {
		Point p = null;

		this.thrown.expect(NullParameterException.class);
		new Vector3(p);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#Vector3(Vector3)}
	 */
	@Test
	public void testVector3Vector3() {
		// instantiate a vector3 to test
		Vector3 v1 = new Vector3(1, 2, 3);
		Vector3 v2 = new Vector3(v1);

		// verify the x argument
		assertEquals(v2.getX(), 1.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v2.getY(), 2.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v2.getZ(), 3.0, imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#Vector3(Vector3)}
	 */
	@Test
	public void testVector3Vector3Null() {
		Vector3 v1 = null;

		this.thrown.expect(NullParameterException.class);
		new Vector3(v1);
	}

	/**
	 * Test method for {@link imp.core.structures.Vector3#Zero()}.
	 */
	@Test
	public void testVector3Zero() {
		// instantiate a vector3 to test
		Vector3 v1 = Vector3.Zero();

		// verify the x argument
		assertEquals(v1.getX(), 0.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the y argument
		assertEquals(v1.getY(), 0.0, imp.core.Constants.ERROR_TOLERANCE);

		// verify the z argument
		assertEquals(v1.getZ(), 0.0, imp.core.Constants.ERROR_TOLERANCE);
	}
}