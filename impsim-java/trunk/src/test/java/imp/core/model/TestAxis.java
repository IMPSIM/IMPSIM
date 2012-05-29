/**
 * TestAxis.java
 * February 25, 2011
 */
package imp.core.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Axis;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Cylinder;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.junit.Test;

/**
 * Unit tests for the Axis class.
 * 
 * @author dykstran klehmc
 * @version 1.0
 * 
 */
@SuppressWarnings("javadoc")
public class TestAxis {

	// compareTo value
	private static final int PREVIOUS = -1;

	/**
	 * Test method for {@link imp.core.model.Axis#Axis(imp.core.model.elements.Joint, imp.core.model.elements.Body)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAxis() throws NullParameterException, InvalidParameterException {
		Body body = new Body("Body");
		Joint cyl = new Cylinder("Cylinder");

		Axis axis = new Axis(cyl, body);

		assertNotNull(axis);
	}

	/**
	 * Test method for {@link imp.core.model.Axis#compareTo(imp.core.model.Axis)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testCompareTo() throws NullParameterException, InvalidParameterException {
		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");
		Axis axisA = new Axis(cylA, bodyA);

		Body bodyB = new Body("BodyB");
		Joint cylB = new Cylinder("CylinderB");
		Axis axisB = new Axis(cylB, bodyB);

		// matches as CylinderA is previous to CylinderB
		assertEquals(PREVIOUS, axisA.compareTo(axisB));
	}

	/**
	 * Test method for {@link imp.core.model.Axis#getBody()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetBody() throws NullParameterException, InvalidParameterException {
		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");
		Axis axisA = new Axis(cylA, bodyA);

		assertEquals(bodyA, axisA.getBody());
	}

	/**
	 * Test method for {@link imp.core.model.Axis#getJoint()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetJoint() throws NullParameterException, InvalidParameterException {
		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");
		Axis axisA = new Axis(cylA, bodyA);

		assertEquals(cylA, axisA.getJoint());
	}

	/**
	 * Test method for {@link imp.core.model.Axis#getShapeMatrix()} and
	 * {@link imp.core.model.Axis#setShapeMatrix(imp.core.structures.PositionMatrix)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSetShapeMatrix() throws NullParameterException, InvalidParameterException {
		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");
		Axis axisA = new Axis(cylA, bodyA);

		// arbitrary matrix
		PositionMatrix pm = new PositionMatrix(new double[][] { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } });

		// shapeMatrix defaults to null
		assertNull(axisA.getShapeMatrix());

		axisA.setShapeMatrix(pm);

		assertEquals(pm, axisA.getShapeMatrix());
	}

	/**
	 * Test method for {@link imp.core.model.Axis#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");

		Axis a = new Axis(cylA, bodyA);
		a.setShapeMatrix(new PositionMatrix());

		Point p = new Point();

		// invalid object type
		assertFalse(a.equals(p));
	}

	/**
	 * Test method for {@link imp.core.model.Axis#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");

		Axis a = new Axis(cylA, bodyA);
		a.setShapeMatrix(new PositionMatrix());
		Axis aCpy = new Axis(cylA, bodyA);
		aCpy.setShapeMatrix(new PositionMatrix());

		// sunny day
		assertTrue(a.equals(aCpy));
		assertTrue(aCpy.equals(a));
	}

	/**
	 * Test method for {@link imp.core.model.Axis#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");
		Body bodyB = new Body("BodyB");
		Joint cylB = new Cylinder("CylinderB");

		Axis a = new Axis(cylA, bodyA);
		a.setShapeMatrix(new PositionMatrix());
		Axis aDff = new Axis(cylB, bodyB);

		// non equal
		assertFalse(a.equals(aDff));
		assertFalse(aDff.equals(a));
	}
	
	/**
	 * Test method for {@link imp.core.model.Axis#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {

		Body bodyA = new Body("BodyA");
		Joint cylA = new Cylinder("CylinderA");

		Axis a = new Axis(cylA, bodyA);
		a.setShapeMatrix(new PositionMatrix());
		
		// should not equal null axis
		assertFalse(a.equals( null ));
	}
}
