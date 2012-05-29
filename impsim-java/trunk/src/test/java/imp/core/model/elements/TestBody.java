/**
 * TestBody.java
 * February 24, 2011
 */
package imp.core.model.elements;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Axis;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Cylinder;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the Body class.
 * 
 * @author dykstran klehmc
 * @edit edmissonj - March 29, 2011. moved the test for map to body to test body
 * 
 */
@SuppressWarnings("javadoc")
public class TestBody {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.elements.Body#containsAxis(imp.core.model.Axis)}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void containsAxis() throws NullParameterException, InvalidParameterException {
		Body body = new Body("Body1");
		Joint cyl = new Cylinder("cyl");
		Axis axis = new Axis(cyl, body);

		assertFalse(body.containsAxis(axis));

		body.addAxis(axis);

		assertTrue(body.containsAxis(axis));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#addAxis(imp.core.model.Axis)} and
	 * {@link imp.core.model.elements.Body#removeAxis(imp.core.model.Axis)}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void testAddRemoveAxis() throws NullParameterException, InvalidParameterException {
		Joint cyl = new Cylinder("CylinderJoint");
		Body bodyA = new Body("BodyA");
		Body bodyB = new Body("BodyB");
		Axis axis = new Axis(cyl, bodyA);

		assertTrue(bodyB.addAxis(axis));
		assertTrue(bodyB.removeAxis(axis));
		assertFalse(bodyB.containsAxis(axis));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#Body(java.lang.String)}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void testBodyNull() throws NullParameterException, InvalidParameterException {
		// Null parameter check
		String name = null;

		this.thrown.expect(NullParameterException.class);
		new Body(name);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#Body(java.lang.String)}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void testBody() throws NullParameterException, InvalidParameterException {
		// Valid case
		Body bodyA = new Body("BodyA");

		assertNotNull(bodyA);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#mapToBody(imp.core.structures.PositionMatrix)}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void testMapToBody() throws NullParameterException, InvalidParameterException {
		// an arbitrary invertible matrix
		PositionMatrix shapeMatrix = new PositionMatrix(new double[][] { { 1, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 1 } });

		PositionMatrix transformationMatrix = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		// the result of taking of the inverse of shapeMatrix and then
		// multiplying it by the transformation matrix. Reference values
		// are from a TI89
		PositionMatrix ref = new PositionMatrix(new double[][] { { -3, -3, -3, 0 }, { 4, 5, 6, 0 }, { 3, 3, 3, 0 }, { 0, 0, 0, 1 } });

		Body body = new Body("Body");

		body.setPositionMatrix(shapeMatrix);

		assertEquals(ref, body.mapToBody(transformationMatrix));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#setPositionMatrix(imp.core.structures.PositionMatrix)} and
	 * {@link imp.core.model.elements.Body#getPositionMatrix()}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void testSetGetPositionMatrix() throws NullParameterException, InvalidParameterException {
		Body bodyA = new Body("BodyA");

		PositionMatrix def = new PositionMatrix();
		// arbitrary non-default values to use as a reference
		PositionMatrix ref = new PositionMatrix(new double[][] { { 1, 2, 3, 0 }, { 4, 5, 6, 0 }, { 7, 8, 9, 0 }, { 0, 0, 0, 1 } });

		assertEquals(bodyA.getPositionMatrix(), def);

		bodyA.setPositionMatrix(ref);

		assertEquals(bodyA.getPositionMatrix(), ref);
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#equals(Object)}.
	 * 
	 * @throws InvalidParameterException failure
	 * @throws NullParameterException failure
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Body b = new Body("Body");

		Point p = new Point();

		// invalid object type
		assertFalse(b.equals(p));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#equals(Object)}.
	 * 
	 * @throws InvalidParameterException failure
	 * @throws NullParameterException failure
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Body b = new Body("Body");
		Body bCpy = new Body("Body");

		// sunny day
		assertTrue(b.equals(bCpy));
		assertTrue(bCpy.equals(b));
	}

	/**
	 * Test method for {@link imp.core.model.elements.Body#equals(Object)}.
	 * 
	 * @throws InvalidParameterException failure
	 * @throws NullParameterException failure
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Body b = new Body("Body");
		Body bDff = new Body("DiffBody");

		// non equal
		assertFalse(b.equals(bDff));
		assertFalse(bDff.equals(b));
	}
	
	/**
	 * Test method for {@link imp.core.model.elements.Body#equals(Object)}.
	 * 
	 * @throws InvalidParameterException failure
	 * @throws NullParameterException failure
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {
		
		Body b = new Body("Body");
		
		// should not equal null body
		assertFalse( b.equals( null ));
	}
}