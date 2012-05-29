/**
 * TestDataZSlideCommand.java
 * April 7, 2011
 */
package imp.core.commands.data;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataZSlideCommand;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the ZSlide data command.
 * 
 * @author dykstran
 * @version 1.0
 * 
 */
@SuppressWarnings("javadoc")
public class TestDataZSlideCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataZSlideCommand#DataZSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataZSlideCommand() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(1, 1, 1);
		String name = "test";

		// valid data statement
		new DataZSlideCommand(p1, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataZSlideCommand#DataZSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataZSlideCommandNullParam0() throws NullParameterException, InvalidParameterException {
		String name = "test";

		this.thrown.expect(NullParameterException.class);
		new DataZSlideCommand(null, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataZSlideCommand#DataZSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataZSlideCommandNullParam1() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(1, 1, 1);

		this.thrown.expect(NullParameterException.class);
		new DataZSlideCommand(p1, null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataZSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataZSlideCommand dzc = new DataZSlideCommand(p1, "test");

		// [start] Test different object type
		assertFalse(dzc.equals(p1));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataZSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataZSlideCommand dzc = new DataZSlideCommand(p1, "test");
		DataZSlideCommand dzc2 = new DataZSlideCommand(p1, "test");

		// [start] Sunny-day
		assertTrue(dzc.equals(dzc2));

		assertTrue(dzc2.equals(dzc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataZSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataZSlideCommand dzc = new DataZSlideCommand(p1, "test");

		p1 = new Point(1, 1, 1);

		DataZSlideCommand dzc2 = new DataZSlideCommand(p1, "diff");

		// [start] non equal commands
		assertFalse(dzc.equals(dzc2));

		assertFalse(dzc2.equals(dzc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataZSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {
		
		Point p1 = new Point(0, 0, 0);

		DataZSlideCommand dzc = new DataZSlideCommand(p1, "test");
		
		// should not equal null command
		assertFalse( dzc.equals( null ));
	}
}
