/**
 * TestJoint.java
 */
package imp.core.model.elements;

import static imp.core.Constants.compareDoubles;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Axis;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Cylinder;
import imp.core.model.joints.Screw;
import imp.core.structures.Point;

import org.junit.Test;

/**
 * Unit tests for Joint class.
 * 
 * @author dykstran klehmc
 * @edit edmissonj - March 29, 2011. moved the test for map to body to test body
 * 
 */
@SuppressWarnings("javadoc")
public class TestJoint {

	/**
	 * Test method for {@link imp.core.model.elements.Joint#getJointVariable(imp.core.model.elements.Joint.JVAR)} and
	 * {@link imp.core.model.elements.Joint#setJointVariable(imp.core.model.elements.Joint.JVAR, double)}
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void getSetJointVariable() throws NullParameterException, InvalidParameterException {
		Joint joint = new Cylinder("CylJoint");
		double refMagSetFirst = 10.0;
		double refMagSetAgain = 20.0;

		// not set yet
		assertNull(joint.getJointVariable(JVAR.PHI));

		joint.setJointVariable(JVAR.PHI, refMagSetFirst);

		// set when previously not set
		assertTrue(compareDoubles(refMagSetFirst, joint.getJointVariable(JVAR.PHI).getMagnitude()));

		joint.setJointVariable(JVAR.PHI, refMagSetAgain);

		// set when had been set before
		assertTrue(compareDoubles(refMagSetAgain, joint.getJointVariable(JVAR.PHI).getMagnitude()));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#getBodyAfter()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetBodyAfter() throws NullParameterException, InvalidParameterException {
		Joint j = new Cylinder("CylinderJoint");
		Body bodyA = new Body("BodyA");
		Axis axis = new Axis(j, bodyA);

		j.setAxisAfter(axis);

		assertEquals(j.getBodyAfter(), bodyA);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#getBodyBefore()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetBodyBefore() throws NullParameterException, InvalidParameterException {
		Joint j = new Cylinder("CylinderJoint");
		Body bodyA = new Body("BodyA");
		Axis axis = new Axis(j, bodyA);

		j.setAxisBefore(axis);

		assertEquals(j.getBodyBefore(), bodyA);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#getAxisAfter()} and
	 * {@link imp.core.model.elements.Joint#setAxisAfter(imp.core.model.Axis)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSetAxisAfter() throws NullParameterException, InvalidParameterException {
		Joint j = new Cylinder("CylinderJoint");
		Body bodyA = new Body("BodyA");
		Axis axis = new Axis(j, bodyA);

		// axisAfter defaults to null
		assertNull(j.getAxisAfter());

		j.setAxisAfter(axis);

		assertEquals(j.getAxisAfter(), axis);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#getAxisBefore()} and
	 * {@link imp.core.model.elements.Joint#setAxisBefore(imp.core.model.Axis)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSetAxisBefore() throws NullParameterException, InvalidParameterException {
		Joint j = new Cylinder("CylinderJoint");
		Body bodyA = new Body("BodyA");
		Axis axis = new Axis(j, bodyA);

		// axisAfter defaults to null
		assertNull(j.getAxisBefore());

		j.setAxisBefore(axis);

		assertEquals(j.getAxisBefore(), axis);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Joint j = new Cylinder("CylinderJoint");

		Point p = new Point();

		// invalid object type
		assertFalse(j.equals(p));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Joint j = new Cylinder("CylinderJoint");
		Joint jCpy = new Cylinder("CylinderJoint");
		Body b1 = new Body("b1");
		Axis theAxis = new Axis(j, b1);
		j.setAxisAfter(theAxis);
		j.setAxisBefore(theAxis);
		jCpy.setAxisAfter(theAxis);
		jCpy.setAxisBefore(theAxis);
		// sunny day
		assertTrue(j.equals(jCpy));
		assertTrue(jCpy.equals(j));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Joint#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Joint j = new Cylinder("CylinderJoint");
		Joint jDff = new Screw("ScrewJoint");

		// non equal
		assertFalse(j.equals(jDff));
		assertFalse(jDff.equals(j));
	}
	
	/**
	 * Test method for {@link imp.core.model.elements.Joint#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {

		Joint j = new Cylinder("CylinderJoint");
		
		// should not equal null joint
		assertFalse( j.equals( null ));
	}
}