/**
 * TestGroundCommand.java
 * April 14, 2011
 */
package imp.core.commands.definition;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.GroundCommand;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Revolute;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author edmissonj
 * @edit dykstran April 14, 2011 Updated to JUnit 4 format.
 * @version 1.1
 * 
 */
@SuppressWarnings("javadoc")
public class TestGroundCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testExecute() throws IMPException {
		Model ml = new Model();

		// creates a new body for the ground
		GroundCommand gc = new GroundCommand("Body1");
		gc.execute(ml);

		// joint instead of body
		ml.addBody("Body1");
		ml.addBody("Body2");
		ml.addJoint(new Revolute("Joint1"), "Body2", "Body1");
		gc = new GroundCommand("Joint1");
		this.thrown.expect(InvalidDatatypeException.class);
		gc.execute(ml);

		// passing test
		gc = new GroundCommand("Body1");
		gc.execute(ml);

	}

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#GroundCommand(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 */
	@Test
	public void testGroundCommandNullParam() throws NullParameterException {
		this.thrown.expect(NullParameterException.class);
		new GroundCommand(null);
	}

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#GroundCommand(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 */
	@Test
	public void testGroundCommand() throws NullParameterException {
		new GroundCommand("Body1");
	}

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		GroundCommand gnd = new GroundCommand("body1");

		Point p = new Point();

		// [start] different object type
		assertFalse(gnd.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		GroundCommand gnd = new GroundCommand("body1");
		GroundCommand gndCpy = new GroundCommand("body1");

		// [start] sunny day case
		assertTrue(gnd.equals(gndCpy));

		assertTrue(gndCpy.equals(gnd));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		GroundCommand gnd = new GroundCommand("body1");
		GroundCommand gndDff = new GroundCommand("body3");

		// [start] non equal case
		assertFalse(gnd.equals(gndDff));

		assertFalse(gndDff.equals(gnd));
	}

	/**
	 * Test method for {@link imp.core.commands.GroundCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		GroundCommand gnd = new GroundCommand("body1");
		
		// should not equal null command
		assertFalse( gnd.equals( null ));
	}
}
