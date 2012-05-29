/**
 * TestPrismCommand.java
 * April 7, 2011
 */
package imp.core.commands.definition;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.definition.PrismCommand;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Prism;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the prism command.
 * 
 * @author dykstran
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestPrismCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.commands.definition.PrismCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testExecute() throws NullParameterException, NameConflictException, SelfLoopException, JointNotFoundException, InvalidParameterException {
		// Create a model for this test
		Model testModel = new Model();

		// Bodies for use in this test
		String bodyBefore = "Body1";
		String bodyAfter = "Body2";

		// The prism joint name
		String jointName = "test";

		// The prism command to use during this test
		PrismCommand prismCommand = null;

		prismCommand = new PrismCommand(bodyBefore, bodyAfter, jointName);

		// Execute the command, making sure no exceptions are thrown
		prismCommand.execute(testModel);

		// check that joint was added to model
		assertEquals(1, testModel.countJoints());

		// check that model contains correct joint
		assertTrue(testModel.getJoint(jointName) != null);

		// Check the class type
		assertEquals(Prism.class, testModel.getJoint(jointName).getClass());
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.PrismCommand#PrismCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testPrismCommandNullParam2() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new PrismCommand("body1", "body2", null);

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.PrismCommand#PrismCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testPrismCommandNullParam1() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new PrismCommand("body1", null, "Test");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.PrismCommand#PrismCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testPrismCommandNullParam0() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new PrismCommand(null, "body2", "Test");
	}

	/**
	 * Test method for {@link imp.core.commands.definition.PrismCommand#PrismCommand(String, String, String)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testPrismCommandSelfLoop() throws NullParameterException, SelfLoopException {
		// test for self loops
		this.thrown.expect(SelfLoopException.class);
		new PrismCommand("Body1", "Body1", "Prism");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.PrismCommand#PrismCommand(java.lang.String, java.lang.String, java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testPrismCommand() throws NullParameterException, SelfLoopException {
		// Sunny-day case
		new PrismCommand("Body1", "Body2", "Test");
	}

	/**
	 * Test method for {@link imp.core.commands.definition.PrismCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		PrismCommand prm = new PrismCommand("body1", "body2", "cyl");

		Point p = new Point();

		// [start] different object type
		assertFalse(prm.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.PrismCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		PrismCommand prm = new PrismCommand("body1", "body2", "cyl");
		PrismCommand prmCpy = new PrismCommand("body1", "body2", "cyl");

		// [start] sunny day case
		assertTrue(prm.equals(prmCpy));

		assertTrue(prmCpy.equals(prm));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.PrismCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		PrismCommand prm = new PrismCommand("body1", "body2", "cyl");
		PrismCommand prmDff = new PrismCommand("body3", "body4", "diff");

		// [start] non equal case
		assertFalse(prm.equals(prmDff));

		assertFalse(prmDff.equals(prm));
	}

	/**
	 * Test method for {@link imp.core.commands.definition.PrismCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		PrismCommand prm = new PrismCommand("body1", "body2", "cyl");
		
		// should not equal null command
		assertFalse( prm.equals( null ));
	}
}
