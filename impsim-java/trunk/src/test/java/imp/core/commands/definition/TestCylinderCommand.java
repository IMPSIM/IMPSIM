/**
 * TestCylinderCommand.java
 * March 26, 2011
 */
package imp.core.commands.definition;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.definition.CylinderCommand;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Cylinder;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author edmissonj Tests for the Cylinder Command
 * @edit dykstran April 14, 2011 Updated to JUnit 4 format.
 * @version 1.1
 * 
 */
@SuppressWarnings("javadoc")
public class TestCylinderCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.CylinderCommand#CylinderCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testCylinderCommandNullParam0() throws NullParameterException, SelfLoopException {
		// tests for null data
		this.thrown.expect(NullParameterException.class);
		new CylinderCommand(null, "Body2", "name");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.CylinderCommand#CylinderCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testCylinderCommandNullParam1() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new CylinderCommand("Body1", null, "name");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.CylinderCommand#CylinderCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testCylinderCommandNullParam2() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new CylinderCommand("Body1", "Body2", null);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.CylinderCommand#CylinderCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testCylinderCommandSelfLoop() throws NullParameterException, SelfLoopException {
		// tests for self loops
		this.thrown.expect(SelfLoopException.class);
		new CylinderCommand("Body1", "Body1", "Cyl");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.CylinderCommand#CylinderCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testCylinderCommand() throws NullParameterException, SelfLoopException {
		// tests for a working set of data
		new CylinderCommand("Body1", "Body2", "name");
	}

	/**
	 * Test method for {@link imp.core.commands.definition.CylinderCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 * @throws NameConflictException
	 * @throws JointNotFoundException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testExecute() throws NameConflictException, SelfLoopException, NullParameterException, JointNotFoundException, InvalidParameterException {
		// model to try adding the joint to
		Model ml = new Model();

		// tries to run the command
		CylinderCommand cyl = new CylinderCommand("body1", "body2", "cyl");
		cyl.execute(ml);

		// check that joint was added to model
		assertEquals(1, ml.countJoints());

		// check that model contains correct joint
		assertTrue(ml.getJoint("cyl") != null);

		// check that added joint is correct type
		assertEquals(Cylinder.class, ml.getJoint("cyl").getClass());
	}

	/**
	 * Test method for {@link imp.core.commands.definition.CylinderCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		CylinderCommand cyl = new CylinderCommand("body1", "body2", "cyl");

		Point p = new Point();

		// [start] different object type
		assertFalse(cyl.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.CylinderCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		CylinderCommand cyl = new CylinderCommand("body1", "body2", "cyl");
		CylinderCommand cylCpy = new CylinderCommand("body1", "body2", "cyl");

		// [start] sunny day case
		assertTrue(cyl.equals(cylCpy));

		assertTrue(cylCpy.equals(cyl));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.CylinderCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		CylinderCommand cyl = new CylinderCommand("body1", "body2", "cyl");
		CylinderCommand cylDff = new CylinderCommand("body3", "body4", "diff");

		// [start] non equal case
		assertFalse(cyl.equals(cylDff));

		assertFalse(cylDff.equals(cyl));
	}
	
	/**
	 * Test method for {@link imp.core.commands.definition.CylinderCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		CylinderCommand cyl = new CylinderCommand("body1", "body2", "cyl");
		
		// should not equal null command
		assertFalse( cyl.equals( null ));
	}
}
