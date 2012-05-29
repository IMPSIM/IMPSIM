/**
 * TestZSlideCommand.java
 * March 30, 2011 
 */
package imp.core.commands.definition;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.definition.ZSlideCommand;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the ZSlide command.
 * 
 * @author dykstran
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestZSlideCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.ZSlideCommand#ZSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testZSlideCommandNullParam0() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new ZSlideCommand(null, "b2", "slide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.ZSlideCommand#ZSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testZSlideCommandNullParam1() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new ZSlideCommand("b1", null, "slide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.ZSlideCommand#ZSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testZSlideCommandNullParam2() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new ZSlideCommand("b1", "b2", null);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.ZSlideCommand#ZSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testZSlideCommandSelfLoop() throws NullParameterException, SelfLoopException {
		this.thrown.expect(SelfLoopException.class);
		new ZSlideCommand("Body1", "Body1", "ZSlide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.ZSlideCommand#ZSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testZSlideCommand() throws NullParameterException, SelfLoopException {
		new ZSlideCommand("b1", "b2", "slide");

	}

	/**
	 * Test method for {@link imp.core.commands.definition.ZSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		ZSlideCommand zsc = new ZSlideCommand("body1", "body2", "cyl");

		Point p = new Point();

		// [start] different object type
		assertFalse(zsc.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.ZSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		ZSlideCommand zsc = new ZSlideCommand("body1", "body2", "cyl");
		ZSlideCommand zscCpy = new ZSlideCommand("body1", "body2", "cyl");

		// [start] sunny day case
		assertTrue(zsc.equals(zscCpy));

		assertTrue(zscCpy.equals(zsc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.ZSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		ZSlideCommand zsc = new ZSlideCommand("body1", "body2", "cyl");
		ZSlideCommand zscDff = new ZSlideCommand("body3", "body4", "diff");

		// [start] non equal case
		assertFalse(zsc.equals(zscDff));

		assertFalse(zscDff.equals(zsc));
	}

	/**
	 * Test method for {@link imp.core.commands.definition.ZSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		ZSlideCommand zsc = new ZSlideCommand("body1", "body2", "cyl");
		
		// should not equal null command
		assertFalse( zsc.equals( null ));
	}
}
