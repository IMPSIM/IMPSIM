/**
 * TestXSlideCommand.java
 * March 30, 2011
 */
package imp.core.commands.definition;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.definition.XSlideCommand;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the XSlide command.
 * 
 * @author dykstran
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestXSlideCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.XSlideCommand#XSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testXSlideCommandNullParam0() throws NullParameterException, SelfLoopException {
		// ************Null parameter check*************
		this.thrown.expect(NullParameterException.class);
		new XSlideCommand(null, "b2", "slide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.XSlideCommand#XSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testXSlideCommandNullParam1() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new XSlideCommand("b1", null, "slide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.XSlideCommand#XSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testXSlideCommandNullParam2() throws NullParameterException, SelfLoopException {
		this.thrown.expect(NullParameterException.class);
		new XSlideCommand("b1", "b2", null);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.XSlideCommand#XSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testXSlideCommandSelfLoop() throws NullParameterException, SelfLoopException {
		this.thrown.expect(SelfLoopException.class);
		new XSlideCommand("Body1", "Body1", "XSlide");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.definition.XSlideCommand#XSlideCommand(java.lang.String, java.lang.String, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testXSlideCommand() throws NullParameterException, SelfLoopException {
		// ****************Sunny Day***********
		new XSlideCommand("b1", "b2", "slide");
	}

	/**
	 * Test method for {@link imp.core.commands.definition.XSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, SelfLoopException {

		XSlideCommand xsc = new XSlideCommand("body1", "body2", "cyl");

		Point p = new Point();

		// [start] different object type
		assertFalse(xsc.equals(p));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.XSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, SelfLoopException {

		XSlideCommand xsc = new XSlideCommand("body1", "body2", "cyl");
		XSlideCommand xscCpy = new XSlideCommand("body1", "body2", "cyl");

		// [start] sunny day case
		assertTrue(xsc.equals(xscCpy));

		assertTrue(xscCpy.equals(xsc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.definition.XSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, SelfLoopException {

		XSlideCommand xsc = new XSlideCommand("body1", "body2", "cyl");
		XSlideCommand xscDff = new XSlideCommand("body3", "body4", "diff");

		// [start] non equal case
		assertFalse(xsc.equals(xscDff));

		assertFalse(xscDff.equals(xsc));
	}
	
	/**
	 * Test method for {@link imp.core.commands.definition.XSlideCommand#execute(Object)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, SelfLoopException {

		XSlideCommand xsc = new XSlideCommand("body1", "body2", "cyl");
		
		// should not equal null command
		assertFalse( xsc.equals( null ));
	}
}
