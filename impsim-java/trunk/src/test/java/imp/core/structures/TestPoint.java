/**
 * TestPoint.java
 * February 24, 2011
 */
package imp.core.structures;

import imp.core.structures.Point;
import imp.core.structures.Vector3;
import junit.framework.TestCase;

import org.junit.Test;

/**
 * Unit tests for Point abstract class.
 * 
 * @author dykstran
 * 
 */
@SuppressWarnings("javadoc")
public class TestPoint extends TestCase {

	/**
	 * Test method for {@link imp.core.structures.Point#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObject() {

		// --------------Sunny-Day Case----------------
		// ------------Point equal to object-----------
		Point p = new Point(0, 1.5, .5);
		Object p2 = new Point(0, 1.5, .5);

		assertTrue(p.equals(p2));
		assertTrue(p2.equals(p));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObjectFalse() {
		// ------------Point not equal to object-------
		Point p = new Point(0, 1.5, .5);
		Object p2 = new Point(4, 1.6, .5);

		assertFalse(p.equals(p2));
		assertFalse(p2.equals(p));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObjectFalseObjectType() {
		// ------------Object is not a point-----------
		Point p = new Point(0, 1.5, .5);
		Object v = new Vector3(p);

		assertFalse(p.equals(v));
	}
	
	/**
	 * Test method for {@link imp.core.structures.Point#equals(java.lang.Object)}.
	 */
	@Test
	public void testEqualsObjectFalseNull() {
		Point p = new Point(0, 1.5, .5);
		Object o = null;
		
		assertFalse(p.equals( o ));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equals(imp.core.structures.Point)}.
	 */
	@Test
	public void testEqualsPoint() {

		// ------------------Sunny Day Case------------------
		// --------------Two points are equal----------------
		Point p = new Point(0, 1.5, .5);
		Point p2 = new Point(0, 1.5, .5);

		assertTrue(p.equals(p2));
		assertTrue(p2.equals(p));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equals(imp.core.structures.Point)}.
	 */
	@Test
	public void testEqualsPointFalse() {

		// --------------Two points are not equal------------
		Point p = new Point(0, 1.5, .5);
		Point p2 = new Point(4, 1.6, .5);

		assertFalse(p.equals(p2));
		assertFalse(p2.equals(p));
	}
	
	/**
	 * Test method for {@link imp.core.structures.Point#equals(imp.core.structures.Point)}.
	 */
	@Test
	public void testEqualsPointFalseNull() {
		
		Point p = new Point(0, 1.5, .5);
		Point p2 = null;
		
		// should not equal null point
		assertFalse(p.equals(p2));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equalsEpsilon(Point)
	 */
	@Test
	public void testEqualsEpsilon() {

		// Sunny Day Case
		// X,Y,Z values of two points are equal
		Point p1 = new Point(1.5, 2.5, 3.5);
		Point p2 = new Point(1.5, 2.5, 3.5);
		double epsilon = 0.01;

		assertTrue(p1.equalsEpsilon(p2, epsilon));
		assertTrue(p2.equalsEpsilon(p1, epsilon));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equalsEpsilon(Point)
	 */
	@Test
	public void testEqualsEpsilonTolerance() {

		// X,Y,Z values different but equal to tolerance
		Point p1 = new Point(1.5, 2.5, 3.5);
		Point p2 = new Point(1.5011, 2.5001, 3.5051);
		double epsilon = 0.01;

		assertTrue(p1.equalsEpsilon(p2, epsilon));
		assertTrue(p2.equalsEpsilon(p1, epsilon));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#equalsEpsilon(Point)
	 */
	@Test
	public void testEqualsEpsilonFalseTolerance() {

		// X,Y,Z values not equal to tolerance
		Point p1 = new Point(1.5, 2.5, 3.5);
		Point p2 = new Point(1.5011, 2.5001, 3.5051);
		double epsilon = 0.001;

		assertFalse(p1.equalsEpsilon(p2, epsilon));
		assertFalse(p2.equalsEpsilon(p1, epsilon));
	}
	
	/**
	 * Test method for {@link imp.core.structures.Point#equalsEpsilon(Point)

	 */
	@Test
	public void testEqualsEpsilonFalseNull() {
		
		Point p1 = new Point(1.5, 2.5, 3.5);
		double epsilon = 0.001;
		
		assertFalse(p1.equalsEpsilon(null, epsilon));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#getX()}.
	 */
	@Test
	public void testGetX() {
		Point p = new Point(1.5, 9.3, 11.0);
		assertEquals(p.getX(), 1.5, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.Point#getY()}.
	 */
	@Test
	public void testGetY() {
		Point p = new Point(1.5, 9.3, 11.0);
		assertEquals(p.getY(), 9.3, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.Point#getZ()}.
	 */
	@Test
	public void testGetZ() {
		Point p = new Point(1.5, 9.3, 11.0);
		assertEquals(p.getZ(), 11.0, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.Point#Point()}.
	 */
	@Test
	public void testPoint() {
		Point p = new Point();

		assertEquals(p.getX(), 0.0, 0);
		assertEquals(p.getY(), 0.0, 0);
		assertEquals(p.getZ(), 0.0, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.Point#Point(double, double, double)}.
	 */
	@Test
	public void testPointDoubleDoubleDouble() {
		Point p = new Point(1.5, 9.3, 11.0);

		assertEquals(p.getX(), 1.5, 0);
		assertEquals(p.getY(), 9.3, 0);
		assertEquals(p.getZ(), 11.0, 0);
	}

	/**
	 * Test method for {@link imp.structures.point#getAngleBetween(Point, Point)}
	 */
	@Test
	public void testGetAngleBetween() {

		Point p1 = new Point();
		Point p2 = new Point(0.0, 2.0, 0.0);
		Point p3 = new Point(1.5, 0.0, 0.0);

		// p1.distanceTo(p2) = 2.0
		// p1.distanceTo(p3) = 1.5
		// p2.distanceTo(p3) = 2.5
		// Math.acos( (2*2)+(1.5*1.5)-(2.5*2.5) / (2*2*1.5) )
		// = Math.acos( 4 + 2.25 - 6.25 / 6 )
		// = Math.acos( 0 )

		assertEquals(p1.getAngleBetween(p2, p3), Math.acos(0), 0);
	}

	/**
	 * Test method for {@link imp.structures.point#getDistanceTo(Point)}
	 */
	@Test
	public void testGetDistanceTo() {

		Point p1 = new Point(5.0, 0.0, 0.0);
		Point p2 = new Point(5.0, 7.0, 0.0);

		assertEquals(p1.getDistanceTo(p2), 7.0, 0);

		Point p3 = new Point(7.0, 9.0, 2.0);
		assertEquals(p2.getDistanceTo(p3), Math.sqrt(12), 0);

	}

	/**
	 * Test method for {@link imp.structures.point#plus(Point)}
	 */
	@Test
	public void testPlus() {

		Point p1 = new Point(1.5, 2.5, 3.5);
		Point p2 = new Point(4.5, 5.5, 6.5);
		// point with X,Y,Z equal to p2 plus p1
		// Point( (4.5+1.5 = 6), (5.5+2.5 = 8), (6.5+3.5 = 10) )
		Point refPoint = new Point(6, 8, 10);

		assertTrue(p2.plus(p1).equals(refPoint));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#minus(Point)}.
	 */
	@Test
	public void testMinus() {

		Point p1 = new Point(1.5, 2.5, 3.5);
		Point p2 = new Point(4.5, 5.5, 6.5);
		// point with X,Y,Z equal to p2 minus p1
		// Point( (4.5-1.5 = 3), (5.5-2.5 = 3), (6.5-3.5 = 3) )
		Point refPoint = new Point(3, 3, 3);

		assertTrue(p2.minus(p1).equals(refPoint));
	}

	/**
	 * Test method for {@link imp.core.structures.Point#setX(double)}.
	 */
	@Test
	public void testSetX() {
		Point p = new Point();

		p.setX(5.5);

		// check that x value properly changes
		// and all other values remain 0.0
		assertEquals(p.getX(), 5.5, 0);
		assertEquals(p.getY(), 0.0, 0);
		assertEquals(p.getZ(), 0.0, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.Point#setY(double)}.
	 */
	@Test
	public void testSetY() {
		Point p = new Point();

		p.setY(5.5);

		// check that y value changes properly
		// and all other values remain 0.0
		assertEquals(p.getX(), 0.0, 0);
		assertEquals(p.getY(), 5.5, 0);
		assertEquals(p.getZ(), 0.0, 0);
	}

	/**
	 * Test method for {@link imp.core.structures.Point#setZ(double)}.
	 */
	@Test
	public void testSetZ() {
		Point p = new Point();

		p.setZ(5.5);

		// check that z value changes properly
		// and all other values remain 0.0
		assertEquals(p.getX(), 0.0, 0);
		assertEquals(p.getY(), 0.0, 0);
		assertEquals(p.getZ(), 5.5, 0);
	}

}
