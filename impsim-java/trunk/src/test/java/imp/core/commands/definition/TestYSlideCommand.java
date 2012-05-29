/**
 * TestYSlideCommand.java
 * March 30, 2011
 */
package imp.core.commands.definition;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.definition.YSlideCommand;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the YSlide command.
 * 
 * @author dykstran
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestYSlideCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.YSlideCommand#YSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testYSlideCommandNullParam0() throws NullParameterException, SelfLoopException {
		// Null Parameter checking
		this.thrown.expect(NullParameterException.class);
		new YSlideCommand(null, "b2", "slide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.YSlideCommand#YSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testYSlideCommandNullParam1() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new YSlideCommand("b1", null, "slide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.YSlideCommand#YSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testYSlideCommandNullParam2() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new YSlideCommand("b1", "b2", null);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.YSlideCommand#YSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testYSlideCommandSelfLoop() throws NullParameterException, SelfLoopException {
		this.thrown.expect(SelfLoopException.class);
		new YSlideCommand("Body1", "Body1", "YSlide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.YSlideCommand#YSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testYSlideCommand() throws NullParameterException, SelfLoopException {
		// sunny day
		new YSlideCommand("b1", "b2", "slide");
	}

	/**
	 * Test method for {@link imp.core.commands.definition.YSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		YSlideCommand ysc = new YSlideCommand("body1", "body2", "cyl");

		Point p = new Point();

		// [start] different object type
		assertFalse(ysc.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.YSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		YSlideCommand ysc = new YSlideCommand("body1", "body2", "cyl");
		YSlideCommand yscCpy = new YSlideCommand("body1", "body2", "cyl");

		// [start] sunny day case
		assertTrue(ysc.equals(yscCpy));

		assertTrue(yscCpy.equals(ysc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.YSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		YSlideCommand ysc = new YSlideCommand("body1", "body2", "cyl");
		YSlideCommand yscDff = new YSlideCommand("body3", "body4", "diff");

		// [start] non equal case
		assertFalse(ysc.equals(yscDff));

		assertFalse(yscDff.equals(ysc));
	}
	
	/**
	 * Test method for {@link imp.core.commands.definition.YSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		YSlideCommand ysc = new YSlideCommand("body1", "body2", "cyl");
		
		// should not equal null command
		assertFalse( ysc.equals( null ));
	}
}
