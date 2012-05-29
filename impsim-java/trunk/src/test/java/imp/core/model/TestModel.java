/**
 * TestModel.java
 * April 14, 2011
 */

package imp.core.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.BodyNotFoundException;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Axis;
import imp.core.model.Element;
import imp.core.model.Model;
import imp.core.model.elements.Body;
import imp.core.model.joints.Cylinder;
import imp.core.model.joints.Prism;
import imp.core.model.joints.Revolute;
import imp.core.model.joints.Screw;
import imp.core.model.loop.Loop;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.List;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * 
 * @author workmanj
 * @author hellmerj
 * @author dykstran Implemented more unit tests.
 * @version 1.3
 * 
 */
@SuppressWarnings("javadoc")
public class TestModel {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.Model#addBody(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddBodyNotStored() throws NameConflictException, NullParameterException, InvalidDatatypeException, InvalidParameterException {
		Model test = new Model();
		String bodyName = "testBody1";
		Body bdy;

		// [start] adding a body not in structure

		// add body to model and get body back
		bdy = test.addBody(bodyName);

		// check body has correct name
		assertEquals(bdy.getName(), bodyName);
		// check body was added to the structure
		assertEquals(test.countBodies(), 1);
		// check body in structure is correct body
		assertTrue(test.contains(bodyName, Body.class));

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addBody(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddBody() throws NameConflictException, NullParameterException, InvalidDatatypeException, InvalidParameterException {

		Model test = new Model();
		String bodyName = "testBody1";
		Body bdy;

		// [start] add Body in structure

		// body returned should be body of body name from structure
		bdy = test.addBody(bodyName);

		// check body has correct name
		assertEquals(bdy.getName(), bodyName);
		// check that duplicate body was not added to structure
		assertEquals(test.countBodies(), 1);
		// check body in structure is correct body
		assertTrue(test.contains(bodyName, Body.class));

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addBody(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddBodyNull() throws NameConflictException, NullParameterException, InvalidDatatypeException, InvalidParameterException {
		// [start] null parameter checking

		Model test = new Model();

		this.thrown.expect(NullParameterException.class);
		test.addBody(null);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJoint() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException, JointNotFoundException,
			InvalidParameterException {

		Model test = new Model();
		String testBodyBefore = "testBody1";
		String testBodyAfter = "testBody2";
		Revolute rev = new Revolute("testJoint");

		// [start] adding a new joint

		test.addJoint(rev, testBodyAfter, testBodyBefore);
		// check that joint was added to structure
		assertEquals(test.countJoints(), 1);
		// check joint added was correct
		assertTrue(test.contains("testJoint", Revolute.class));
		// check that bodies were added to structure
		assertEquals(test.countBodies(), 2);

		// [end]

	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointAxesCreation() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {

		Model test = new Model();
		String testBodyBefore = "testBody1";
		String testBodyAfter = "testBody2";
		Revolute rev = new Revolute("testJoint");
		test.addJoint(rev, testBodyAfter, testBodyBefore);

		// [start] axes for connecting to bodies

		Body bodyAfter = test.addBody(testBodyAfter);
		Body bodyBefore = test.addBody(testBodyBefore);

		// check that axis to body before is created correctly
		assertEquals(test.getJoint("testJoint").getAxisBefore().getJoint(), rev);
		assertEquals(test.getJoint("testJoint").getAxisBefore().getBody(), bodyBefore);
		// check that axis to body after is created correctly
		assertEquals(test.getJoint("testJoint").getAxisAfter().getJoint(), rev);
		assertEquals(test.getJoint("testJoint").getAxisAfter().getBody(), bodyAfter);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointDuplicate() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {

		Model test = new Model();
		String testBodyBefore = "testBody1";
		String testBodyAfter = "testBody2";
		Revolute rev = new Revolute("testJoint");
		test.addJoint(rev, testBodyAfter, testBodyBefore);

		// [start] adding duplicate joint

		test.addJoint(rev, testBodyAfter, testBodyBefore);
		// check that duplicate joint not added to structure
		assertEquals(test.countJoints(), 1);
		// check joint in structure remains correct
		assertTrue(test.contains("testJoint", Revolute.class));

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointNullParam0() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {
		Model test = new Model();

		// [start] null parameter checking

		this.thrown.expect(NullParameterException.class);
		test.addJoint(null, "testBodyAfter", "testBodyBefore");
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointNullParam1() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {
		Model test = new Model();

		this.thrown.expect(NullParameterException.class);
		test.addJoint(new Revolute("rev"), null, "testBodyBefore");
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointNullParam2() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {
		Model test = new Model();

		this.thrown.expect(NullParameterException.class);
		test.addJoint(new Revolute("rev"), "testBodyAfter", null);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointSelfLoop() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {
		Model test = new Model();

		// [start] adding a joint connecting the same body

		this.thrown.expect(SelfLoopException.class);
		test.addJoint(new Revolute("rev"), "testBodyBefore", "testBodyBefore");

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#addJoint(imp.core.model.elements.Joint, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testAddJointRigidJointCreation() throws NullParameterException, SelfLoopException, NameConflictException, InvalidDatatypeException,
			JointNotFoundException, InvalidParameterException {

		Model test = new Model();
		Screw scr = new Screw("testScrew");
		Revolute rev = new Revolute("testRevolute");

		// [start] rigid structure by placing two joints on same bodies

		test.addJoint(rev, "testBodyAfter", "testBodyBefore");

		this.thrown.expect(SelfLoopException.class);
		test.addJoint(scr, "testBodyAfter", "testBodyBefore");

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#closeLoops()}.
	 */
	@Test
	public void testCloseLoops() {

	}

	/**
	 * Test method for {@link imp.core.model.Model#contains(java.lang.String, java.lang.Object)}.
	 * 
	 * @throws InvalidDatatypeException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws JointNotFoundException
	 */
	@Test
	public void testContainsFalse() throws InvalidDatatypeException, NullParameterException, SelfLoopException, NameConflictException, JointNotFoundException {
		Model test = new Model();

		// [start] element not in structure

		assertFalse(test.contains("name", Element.class));

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#contains(java.lang.String, java.lang.Object)}.
	 * 
	 * @throws InvalidDatatypeException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testContainsJoint() throws InvalidDatatypeException, NullParameterException, SelfLoopException, NameConflictException, JointNotFoundException,
			InvalidParameterException {

		Model test = new Model();
		Revolute rev = new Revolute("testJoint");

		test.addJoint(rev, "testBody1", "testBody2");

		// [start] joint in structure

		assertTrue(test.contains("testJoint", Revolute.class));

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#contains(java.lang.String, java.lang.Object)}.
	 * 
	 * @throws InvalidDatatypeException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testContainsBody() throws InvalidDatatypeException, NullParameterException, SelfLoopException, NameConflictException, JointNotFoundException,
			InvalidParameterException {

		Model test = new Model();
		Revolute rev = new Revolute("testJoint");

		test.addJoint(rev, "testBody1", "testBody2");

		// [start] body in structure

		assertTrue(test.contains("testBody1", Body.class));

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#contains(java.lang.String, java.lang.Object)}.
	 * 
	 * @throws InvalidDatatypeException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testContainsInvalidType() throws InvalidDatatypeException, NullParameterException, SelfLoopException, NameConflictException,
			JointNotFoundException, InvalidParameterException {
		Model test = new Model();
		Revolute rev = new Revolute("testJoint");

		test.addJoint(rev, "testBody1", "testBody2");

		// [start] element of invalid type

		this.thrown.expect(InvalidDatatypeException.class);
		test.contains("testBody1", Screw.class);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#countBodies()}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testCountBodies() throws NameConflictException, NullParameterException, InvalidParameterException {
		Model test = new Model();

		test.addBody("body1");
		test.addBody("body2");
		test.addBody("body3");

		assertEquals(test.countBodies(), 3);
	}

	/**
	 * Test method for {@link imp.core.model.Model#countJoints()}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testCountJoints() throws NullParameterException, SelfLoopException, NameConflictException, JointNotFoundException, InvalidParameterException {
		Model test = new Model();

		Revolute rev = new Revolute("joint1");
		Screw scr = new Screw("joint2");
		Prism prm = new Prism("joint3");
		Cylinder cyl = new Cylinder("joint4");

		test.addJoint(rev, "body1", "body2");
		test.addJoint(scr, "body3", "body4");
		test.addJoint(prm, "body5", "body6");
		test.addJoint(cyl, "body7", "body8");

		assertEquals(test.countJoints(), 4);
	}

	/**
	 * Test method for {@link imp.core.model.Model#findKinematicLoops()}.
	 */
	@Test
	public void testFindKinematicLoops() {

	}

	/**
	 * Test method for {@link imp.core.model.Model#getBody(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetBody() throws NameConflictException, NullParameterException, InvalidParameterException {
		Model model = new Model();

		model.addBody("B1");
		model.addBody("B2");
		model.addBody("B3");

		assertEquals(model.getBody("B1"), new Body("B1"));
		assertEquals(model.getBody("B2"), new Body("B2"));
		assertEquals(model.getBody("B3"), new Body("B3"));
	}

	/**
	 * Test method for {@link imp.core.model.Model#getBodyStructure()}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetBodyStructure() throws NameConflictException, NullParameterException, InvalidParameterException {
		Model model = new Model();
		model.addBody("B1");
		model.addBody("B2");
		model.addBody("B3");

		assertTrue(model.getBodyStructure().contains("B1"));
		assertTrue(model.getBodyStructure().contains("B2"));
		assertTrue(model.getBodyStructure().contains("B3"));
	}

	/**
	 * Test method for {@link imp.core.model.Model#getGround()}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws BodyNotFoundException
	 */
	@Test
	public void testGetGroundNotSet() throws BodyNotFoundException, InvalidDatatypeException, NameConflictException, NullParameterException {
		Model test = new Model();

		// [start] no ground set

		this.thrown.expect(BodyNotFoundException.class);
		test.getGround();

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#getGround()}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws BodyNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetGround() throws BodyNotFoundException, InvalidDatatypeException, NameConflictException, NullParameterException,
			InvalidParameterException {
		Model test = new Model();

		test.setGround("testGround");

		// [start] retreiving the ground

		Body bdy = test.getGround();
		assertEquals(bdy.getName(), "testGround");

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#getJoint(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetJoint() throws NullParameterException, SelfLoopException, NameConflictException, JointNotFoundException, InvalidParameterException {
		Model model = new Model();

		Revolute rev1 = new Revolute("J1");
		Revolute rev2 = new Revolute("J2");
		Revolute rev3 = new Revolute("J3");
		model.addJoint(rev1, "B2", "B1");
		model.addJoint(rev2, "B4", "B2");
		model.addJoint(rev3, "B10", "B4");

		assertEquals(model.getJoint("J1"), rev1);
		assertEquals(model.getJoint("J2"), rev2);
		assertEquals(model.getJoint("J3"), rev3);
	}

	/**
	 * Test method for {@link imp.core.model.Model#getJointStructure()}.
	 * 
	 * @throws JointNotFoundException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetJointStructure() throws SelfLoopException, NameConflictException, NullParameterException, JointNotFoundException,
			InvalidParameterException {
		Model model = new Model();

		Revolute rev1 = new Revolute("J1");
		Revolute rev2 = new Revolute("J2");
		Revolute rev3 = new Revolute("J3");
		model.addJoint(rev1, "B2", "B1");
		model.addJoint(rev2, "B4", "B2");
		model.addJoint(rev3, "B10", "B4");

		assertTrue(model.getJointStructure().contains("J1"));
		assertTrue(model.getJointStructure().contains("J2"));
		assertTrue(model.getJointStructure().contains("J3"));
	}

	/**
	 * Test method for {@link imp.core.model.Model#getPrintStream()}.
	 */
	@Test
	public void testGetPrintStream() {
		Model model = new Model(System.out);

		assertEquals(model.getPrintStream(), System.out);
	}

	/**
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testLoops() throws IMPException {
		Model model = new Model();
		model.addBody("B1");
		model.addBody("B2");
		model.addBody("B3");
		model.addBody("B4");
		model.addBody("B5");
		model.addBody("B6");
		model.addBody("B7");
		model.addBody("B8");
		model.addBody("B9");
		model.addBody("B10");
		model.addBody("B11");
		model.addBody("B12");
		model.addBody("B13");
		model.addBody("B14");
		model.addBody("B15");
		model.addJoint(new Revolute("J1"), "B2", "B1");
		model.addJoint(new Revolute("J2"), "B4", "B2");
		model.addJoint(new Revolute("J3"), "B10", "B4");
		model.addJoint(new Revolute("J4"), "B6", "B5");
		model.addJoint(new Revolute("J5"), "B5", "B4");
		model.addJoint(new Revolute("J6"), "B6", "B7");
		model.addJoint(new Revolute("J7"), "B8", "B9");
		model.addJoint(new Revolute("J8"), "B8", "B7");
		model.addJoint(new Revolute("J9"), "B9", "B1");
		model.addJoint(new Revolute("J10"), "B13", "B1");
		model.addJoint(new Revolute("J11"), "B12", "B13");
		model.addJoint(new Revolute("J12"), "B14", "B12");
		model.addJoint(new Revolute("J13"), "B15", "B14");
		model.addJoint(new Revolute("J14"), "B15", "B11");
		model.addJoint(new Revolute("J15"), "B11", "B10");
		model.addJoint(new Revolute("J16"), "B11", "B5");
		model.addJoint(new Revolute("J17"), "B11", "B3");
		model.addJoint(new Revolute("J18"), "B8", "B3");
		model.addJoint(new Revolute("J19"), "B12", "B3");
		model.addJoint(new Revolute("J20"), "B3", "B1");
		model.setGround("B1");
		List<Loop> loops = model.findKinematicLoops();
		for (Loop loop : loops) {
			model.getPrintStream().println(loop.toString());
		}
	}

	/**
	 * Test method for {@link imp.core.model.Model#Model()}.
	 * 
	 * @throws FileNotFoundException
	 */
	@Test
	public void testModel() throws FileNotFoundException {
		new Model();
	}

	/**
	 * Test method for {@link imp.core.model.Model#Model(java.io.PrintStream)}.
	 */
	@Test
	public void testModelPrintStream() throws FileNotFoundException {
		Model test;
		File testFile = new File("test.txt");
		PrintStream ps = new PrintStream(testFile);

		// [start] valid constructor statement

		test = new Model(ps);

		// check model PrintStream is assigned correctly
		assertEquals(test.getPrintStream(), ps);

		// [end]

		ps.close();
		testFile.delete();
	}

	/**
	 * Test method for {@link imp.core.model.Model#Model(java.io.PrintStream)}.
	 */
	@Test
	public void testModelPrintStreamNull() throws FileNotFoundException {

		Model test;
		File testFile = new File("test.txt");
		PrintStream ps = new PrintStream(testFile);

		// [start] null parameter test

		test = new Model(null);

		// check that the model PrintStream was defaulted to System.out
		assertEquals(test.getPrintStream(), System.out);

		// [end]

		ps.close();
		testFile.delete();
	}

	/**
	 * Test method for {@link imp.core.model.Model#removeJoint(java.lang.String)}.
	 * 
	 * @throws JointNotFoundException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 */
	@Test
	public void testRemoveJointNotFound() throws JointNotFoundException, NullParameterException, SelfLoopException, NameConflictException {
		Model test = new Model();

		// [start] remove joint not in structure

		this.thrown.expect(JointNotFoundException.class);
		test.removeJoint("test");

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#removeJoint(java.lang.String)}.
	 * 
	 * @throws JointNotFoundException
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testRemoveJoint() throws JointNotFoundException, NullParameterException, SelfLoopException, NameConflictException, InvalidParameterException {
		Model test = new Model();
		Revolute rev = new Revolute("testJoint");

		test.addJoint(rev, "bodyAfterName", "bodyBeforeName");

		Axis beforeAxis = rev.getAxisBefore();
		Axis afterAxis = rev.getAxisAfter();

		// [start] remove joint from structure

		test.removeJoint("testJoint");
		// check that size indicates removal
		assertEquals(test.countJoints(), 0);

		// [end]

		// checks that the axis have been removed
		assertEquals(test.getBody("bodyAfterName").containsAxis(beforeAxis), false);
		assertEquals(test.getBody("bodyAfterName").containsAxis(afterAxis), false);
	}

	/**
	 * Test method for {@link imp.core.model.Model#setGround(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws BodyNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testSetGroundNewBody() throws BodyNotFoundException, InvalidDatatypeException, NameConflictException, NullParameterException,
			InvalidParameterException {
		Model test = new Model();
		Body gnd;

		// [start] set ground to new body

		test.setGround("groundName");
		gnd = new Body("groundName");
		// check that body was added
		assertEquals(test.countBodies(), 1);
		// check that ground is correct body
		assertEquals(test.getGround(), gnd);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.Model#setGround(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidDatatypeException
	 * @throws BodyNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testSetGround() throws BodyNotFoundException, InvalidDatatypeException, NameConflictException, NullParameterException,
			InvalidParameterException {

		Model test = new Model();
		Body gnd;

		test.addBody("existingGround");
		gnd = new Body("existingGround");

		// [start] set ground to existing body

		test.setGround("existingGround");
		// check that duplicate body not added
		assertEquals(test.countBodies(), 1);
		// check that ground is correct body
		assertEquals(test.getGround(), gnd);

		// [end]
	}

}
