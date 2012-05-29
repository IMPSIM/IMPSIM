/**
 * TestScrewCommand.java
 * March 27, 2011
 * @author hellmerj
 */

package imp.core.commands.definition;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.definition.ScrewCommand;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Screw;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * This is the TestScrewCommand class. It tests the ScrewCommand class used to create a new Screw joint and add it to
 * the model.
 * 
 * @author hellmerj
 * @edit dykstran April 14, 2011 Updated to JUnit 4 format.
 * @version 1.1
 */
@SuppressWarnings("javadoc")
public class TestScrewCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * This is the testExecute method. It is responsible for testing the ScrewCommand execute method. It checks that the
	 * joint and bodies were added to the model and that they are correct.
	 * 
	 * Test method for {@link imp.core.commands.definition.ScrewCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testExecute() throws NullParameterException, NameConflictException, SelfLoopException, JointNotFoundException, InvalidParameterException {

		// model for testing
		Model testModel = new Model();

		// command to test
		ScrewCommand sc = null;

		// name of joint
		String name = "Screw";
		// name of first body
		String bodyBefore = "Body1";
		// name of second body
		String bodyAfter = "Body2";

		// create the screw command
		sc = new ScrewCommand(bodyBefore, bodyAfter, name);

		// execute the screw command
		sc.execute(testModel);

		// check that joint was added
		assertEquals(1, testModel.countJoints());

		// check that joint added matches name
		assertTrue(testModel.getJoint(name) != null);

		// check that joint added matches type
		assertEquals(Screw.class, testModel.getJoint(name).getClass());

		// check that bodies were added
		assertEquals(2, testModel.countBodies());

		// check that bodies added match names
		assertTrue(testModel.getBody(bodyBefore) != null);
		assertTrue(testModel.getBody(bodyAfter) != null);

	}

	/**
	 * This is the testScrewCommand test method. It is responsible for testing the ScrewCommand constructor. It checks
	 * that exceptions are being thrown correctly and values are properly assigned.
	 * 
	 * Test method for
	 * {@link imp.core.commands.definition.ScrewCommand#ScrewCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testScrewCommandNullParam0() throws NullParameterException, SelfLoopException {
		// ********** test null data **********
		this.thrown.expect(NullParameterException.class);
		new ScrewCommand(null, "body2", "Screw");
	}

	/**
	 * This is the testScrewCommand test method. It is responsible for testing the ScrewCommand constructor. It checks
	 * that exceptions are being thrown correctly and values are properly assigned.
	 * 
	 * Test method for
	 * {@link imp.core.commands.definition.ScrewCommand#ScrewCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testScrewCommandNullParam1() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new ScrewCommand("body1", null, "Screw");
	}

	/**
	 * This is the testScrewCommand test method. It is responsible for testing the ScrewCommand constructor. It checks
	 * that exceptions are being thrown correctly and values are properly assigned.
	 * 
	 * Test method for
	 * {@link imp.core.commands.definition.ScrewCommand#ScrewCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testScrewCommandNullParam2() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new ScrewCommand("body1", "body2", null);
	}

	/**
	 * This is the testScrewCommand test method. It is responsible for testing the ScrewCommand constructor. It checks
	 * that exceptions are being thrown correctly and values are properly assigned.
	 * 
	 * Test method for
	 * {@link imp.core.commands.definition.ScrewCommand#ScrewCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testScrewCommandSelfLoop() throws NullParameterException, SelfLoopException {
		this.thrown.expect(SelfLoopException.class);
		new ScrewCommand("Body1", "Body1", "Screw");
	}

	/**
	 * This is the testScrewCommand test method. It is responsible for testing the ScrewCommand constructor. It checks
	 * that exceptions are being thrown correctly and values are properly assigned.
	 * 
	 * Test method for
	 * {@link imp.core.commands.definition.ScrewCommand#ScrewCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testScrewCommand() throws NullParameterException, SelfLoopException {
		// ********** test valid data **********
		new ScrewCommand("body1", "body2", "Screw");

		// commented out by MDZ (3 April 2011 - we need to test this another way, not via setters and getters)
		// check that names were properly stored
		// assertEquals(bodyBefore, sc.getBodyBefore());
		// assertEquals(bodyAfter, sc.getBodyAfter());
		// assertEquals(name, sc.getName());
	}

	/**
	 * Test method for {@link imp.core.commands.definition.ScrewCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		ScrewCommand scr = new ScrewCommand("body1", "body2", "cyl");

		Point p = new Point();

		// [start] different object type
		assertFalse(scr.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.ScrewCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		ScrewCommand scr = new ScrewCommand("body1", "body2", "cyl");
		ScrewCommand scrCpy = new ScrewCommand("body1", "body2", "cyl");

		// [start] sunny day case
		assertTrue(scr.equals(scrCpy));

		assertTrue(scrCpy.equals(scr));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.ScrewCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		ScrewCommand scr = new ScrewCommand("body1", "body2", "cyl");
		ScrewCommand scrDff = new ScrewCommand("body3", "body4", "diff");

		// [start] non equal case
		assertFalse(scr.equals(scrDff));

		assertFalse(scrDff.equals(scr));
	}
	
	/**
	 * Test method for {@link imp.core.commands.definition.ScrewCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		ScrewCommand scr = new ScrewCommand("body1", "body2", "cyl");
		
		// should not equal null command
		assertFalse( scr.equals( null ));
	}
}
