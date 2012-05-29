/**
 * TestRevolute.java
 * February 20, 2011
 * @author hellmerj
 */

package imp.core.model.joints;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Axis;
import imp.core.model.ElementMap;
import imp.core.model.Model;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.model.elements.Joint.JVAR;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;

import java.util.Iterator;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * This is a test for the Revolute Creation Process. It uses both traditional testing as well as visual confirmation.
 * 
 * @author hellmerj
 * @version 1.0 - February 20, 2011
 * 
 */
@SuppressWarnings("javadoc")
public class TestRevolute {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#Revolute(String)};
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testRevolute() throws NullParameterException, InvalidParameterException {
		new Revolute("Revolute");
	}

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#Revolute(String)};
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testRevoluteNullParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new Revolute(null);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#Revolute(String)};
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testRevoluteInvalidParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new Revolute("");
	}

	/**
	 * Test addition of Revolute joint to model. Display structures for visual confirmation.
	 * 
	 * @throws JointNotFoundException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws NullParameterException
	 * @throws InvalidDatatypeException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddRevolute() throws JointNotFoundException, NullParameterException, NameConflictException, SelfLoopException, InvalidDatatypeException,
			InvalidParameterException {

		// Test adding first joint with first two bodies

		String testName = "Test";
		String testBodyBefore = "Body Before";
		String testBodyAfter = "Body After";

		// create model used for testing
		Model testModel = new Model();

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);

		// check that correct number of joints were added
		assertEquals(1, testModel.countJoints());
		// check that correct number of bodies were added
		assertEquals(2, testModel.countBodies());

		// make sure joint of correct name was added
		if (testModel.getJoint(testName) == null) {
			fail("Joint not added to model correctly");
		}

		// check that joint added was a Revolute
		assertTrue(testModel.contains(testName, Revolute.class));

		// Test adding second joint with two new bodies
		testName = "Test2";
		testBodyBefore = "Body Before 2";
		testBodyAfter = "Body After 2";

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);

		// check that correct number of joints are in model
		assertEquals(2, testModel.countJoints());
		// check that correct number of bodies are in model
		assertEquals(4, testModel.countBodies());

		// make sure joint of correct name was added
		if (testModel.getJoint(testName) == null) {
			fail("Joint not added to model correctly");
		}

		assertTrue(testModel.contains(testName, Revolute.class));

		// Test adding first joint again with two new Bodies

		testName = "Test";
		testBodyBefore = "Body Before 3";
		testBodyAfter = "Body After 3";

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);

		// check that correct number of joints are in model
		assertEquals(2, testModel.countJoints());
		// check that correct number of bodies are in model
		assertEquals(6, testModel.countBodies());

		// make sure joint of correct name was added
		if (testModel.getJoint(testName) == null) {
			fail("Joint not added to model correctly");
		}

		// check that joint added was a Revolute
		assertTrue(testModel.contains(testName, Revolute.class));

		// Test adding new joint with two existing Bodies

		testName = "Test3";
		testBodyBefore = "Body Before";
		testBodyAfter = "Body After 3";

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);

		// check that correct number of joints are in model
		assertEquals(3, testModel.countJoints());
		// check that correct number of bodies are in model
		assertEquals(6, testModel.countBodies());

		// make sure joint of correct name was added
		if (testModel.getJoint(testName) == null) {
			fail("Joint not added to model correctly");
		}

		// check that joint added was a Revolute
		assertTrue(testModel.contains(testName, Revolute.class));

		// Display current joints data structure (should contain 3 joints Test, Test2, Test3)

		// get map of all joints
		ElementMap<Joint> joints = testModel.getJointStructure();
		// get iterator for the joints structure
		Iterator<Joint> jointIterator = joints.iterator();

		System.out.println("\n\nJoints in the Model:");

		// iterate over joint structure
		while (jointIterator.hasNext()) {
			// Display
			System.out.println(jointIterator.next());
		}

		// Display current bodies data structure
		// should contain 6 bodies Body Before, Body Before 2, Body Before 3, Body After, Body After 2, Body After 3)

		// get map of all joints
		ElementMap<Body> bodies = testModel.getBodyStructure();
		// get iterator for the joints structure
		Iterator<Body> bodyIterator = bodies.iterator();

		System.out.println("\nBodies in the Model:");

		// iterate over joint structure
		while (bodyIterator.hasNext()) {
			// Display
			System.out.println(bodyIterator.next());
		}
	}

	/**
	 * Test axis linking joint and body after
	 * 
	 * @throws JointNotFoundException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAxisAfter() throws JointNotFoundException, NullParameterException, NameConflictException, SelfLoopException, InvalidParameterException {
		String testName = "Test";
		String testBodyBefore = "Body Before";
		String testBodyAfter = "Body After";

		// create a model to use for testing
		Model testModel = new Model();

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);
		// get joint linked by axis
		Joint testJoint = testModel.getJoint(testName);

		// get Body linked by axis
		Body afterBody = testModel.getBody(testBodyAfter);

		// make axis before linking body after to joint
		Axis afterAxis = new Axis(testJoint, afterBody);

		// set axis linking body to joint
		testJoint.setAxisBefore(afterAxis);

		// check that axisBefore joint matches axis before test
		assertEquals(testModel.getJoint(testName).getAxisBefore(), afterAxis);
	}

	/**
	 * Test axis linking joint and body before
	 * 
	 * @throws JointNotFoundException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAxisBefore() throws JointNotFoundException, NullParameterException, NameConflictException, SelfLoopException, InvalidParameterException {
		String testName = "Test";
		String testBodyBefore = "Body Before";
		String testBodyAfter = "Body After";

		// create a model to use for testing
		Model testModel = new Model();

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);
		// get joint linked by axis
		Joint testJoint = testModel.getJoint(testName);

		// get Body linked by axis
		Body beforeBody = testModel.getBody(testBodyBefore);

		// make axis before linking body before to joint
		Axis beforeAxis = new Axis(testJoint, beforeBody);

		// set axis linking body to joint
		testJoint.setAxisBefore(beforeAxis);

		// check that axisBefore joint matches axis before test
		assertEquals(testModel.getJoint(testName).getAxisBefore(), beforeAxis);
	}

	/**
	 * Test body after joint is correct
	 * 
	 * @throws JointNotFoundException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testBodyAfter() throws JointNotFoundException, NullParameterException, NameConflictException, SelfLoopException, InvalidParameterException {
		String testName = "Test";
		String testBodyBefore = "Body Before";
		String testBodyAfter = "Body After";

		// create a model to use for testing
		Model testModel = new Model();

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);

		// check number of joints and bodies is correct
		assertEquals(1, testModel.countJoints());
		assertEquals(2, testModel.countBodies());

		// check that the two bodies in model are the names specified
		if (testModel.getBody(testBodyBefore) == null || testModel.getBody(testBodyAfter) == null) {
			fail("Bodies not created properly");
		}

		// get the body before the joint
		Body afterBody = testModel.getBody(testBodyAfter);

		// check that body before joint matches the test body before
		assertEquals(testModel.getJoint(testName).getBodyAfter(), afterBody);
	}

	/**
	 * Test body before joint is correct
	 * 
	 * @throws JointNotFoundException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testBodyBefore() throws JointNotFoundException, NullParameterException, NameConflictException, SelfLoopException, InvalidParameterException {
		String testName = "Test";
		String testBodyBefore = "Body Before";
		String testBodyAfter = "Body After";

		// create a model to use for testing
		Model testModel = new Model();

		// create a new RevoluteCommand
		testModel.addJoint(new Revolute(testName), testBodyAfter, testBodyBefore);

		// check number of joints and bodies is correct
		assertEquals(1, testModel.countJoints());
		assertEquals(2, testModel.countBodies());

		// check that the two bodies in model are the names specified
		if (testModel.getBody(testBodyBefore) == null || testModel.getBody(testBodyAfter) == null) {
			fail("Bodies not created properly");
		}

		// get the body before the joint
		Body beforeBody = testModel.getBody(testBodyBefore);

		// check that body before joint matches the test body before
		assertEquals(testModel.getJoint(testName).getBodyBefore(), beforeBody);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#getAccelerationMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		Revolute rev = new Revolute("test");

		// new joint should have no acceleration
		PositionMatrix expectedAccMatrix = new PositionMatrix();
		Vector3 zero = new Vector3(0, 0, 0);
		expectedAccMatrix.fill(zero, zero, zero, zero);
		expectedAccMatrix.set(3, 3, 0);

		assertEquals(expectedAccMatrix, rev.getAccelerationMatrix());
	}

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#getDerivativeMatrix(imp.core.model.elements.Joint.JVAR)}.
	 * 
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivative() throws NullParameterException, InvalidParameterException {
		Revolute rev = new Revolute("test");

		rev.setJointVariable(JVAR.THETA, Math.PI / 4);
		PositionMatrix pm = rev.getDerivativeMatrix(JVAR.THETA);
		PositionMatrix testAgainst = new PositionMatrix();
		double sin = Math.sin(Math.PI / 4);
		testAgainst.fill(new Vector3(-sin, sin, 0), new Vector3(-sin, -sin, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testAgainst.set(3, 3, 0);

		assertEquals(pm, testAgainst);
	}

	/**
	 * Test method for
	 * {@link imp.core.model.joints.Revolute#getSecondDerivativeMatrix(imp.core.model.elements.Joint.JVAR, imp.core.model.elements.Joint.JVAR)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivative() throws NullParameterException, InvalidParameterException {
		Revolute rev = new Revolute("test");

		rev.setJointVariable(JVAR.THETA, Math.PI / 4);
		PositionMatrix pm = rev.getSecondDerivativeMatrix(JVAR.THETA, JVAR.THETA);
		PositionMatrix testAgainst = new PositionMatrix();
		double sin = Math.sin(Math.PI / 4);
		testAgainst.fill(new Vector3(-sin, -sin, 0), new Vector3(sin, -sin, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testAgainst.set(3, 3, 0);

		assertEquals(pm, testAgainst);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#getVelocityMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetVelocityMatrix() throws NullParameterException, InvalidParameterException {

		Revolute rev = new Revolute("test");

		// new joint should have no velocity
		PositionMatrix expectedVelocityMatrix = new PositionMatrix();
		Vector3 zero = new Vector3(0, 0, 0);
		expectedVelocityMatrix.fill(zero, zero, zero, zero);
		expectedVelocityMatrix.set(3, 3, 0);
		assertEquals(expectedVelocityMatrix, rev.getVelocityMatrix());
	}

	/**
	 * Test method for {@link imp.core.model.joints.Revolute#getQOperator(JVAR)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testGetQOperator() throws NullParameterException, InvalidParameterException {

		Revolute rev = new Revolute("test");

		// set expected Q matrix
		PositionMatrix expectedQ = new PositionMatrix();
		expectedQ.fill(new Vector3(0, 1, 0), new Vector3(-1, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		expectedQ.set(3, 3, 0);

		// compare expected to actual returned Q matrix
		assertEquals(expectedQ, rev.getQOperator(JVAR.THETA));
	}

	/**
	 * Test method for {@link imp.model.elements.Revolute#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Revolute rev = new Revolute("test");
		Revolute revCopy = new Revolute("test");
		Body b1 = new Body("b1");

		Axis theAxis = new Axis(rev, b1);
		rev.setAxisAfter(theAxis);
		rev.setAxisBefore(theAxis);

		revCopy.setAxisAfter(theAxis);
		revCopy.setAxisBefore(theAxis);

		// rev and copy should be equal
		assertTrue(rev.equals(revCopy));
		assertTrue(revCopy.equals(rev));
	}

	/**
	 * Test method for {@link imp.model.elements.Revolute#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Revolute rev = new Revolute("test");
		Revolute revDif = new Revolute("Diff");

		// should not equal different revolute
		assertFalse(rev.equals(revDif));
		assertFalse(revDif.equals(rev));
	}

	/**
	 * Test method for {@link imp.model.elements.Revolute#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObject() throws NullParameterException, InvalidParameterException {

		Revolute rev = new Revolute("rev");
		Screw scr = new Screw("scr");

		// should not equal different object type
		assertFalse(rev.equals(scr));
	}

	/**
	 * Test method for {@link imp.model.elements.Revolute#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {

		Revolute rev = new Revolute("test");

		// should not equal null cylinder
		assertFalse(rev.equals(null));
	}
}
