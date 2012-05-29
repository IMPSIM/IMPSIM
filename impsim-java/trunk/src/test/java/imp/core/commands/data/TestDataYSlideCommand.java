/**
 * TestDataYSlideCommand.java
 * April 7, 2011
 */
package imp.core.commands.data;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataYSlideCommand;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the YSlide data command.
 * 
 * @author dykstran
 * @version 1.0
 * 
 */
@SuppressWarnings("javadoc")
public class TestDataYSlideCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataYSlideCommand#DataYSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataYSlideCommand() throws NullParameterException, InvalidParameterException {
		Point origin = new Point(1, 1, 1);
		String name = "test";

		// valid data statement
		new DataYSlideCommand(origin, name);

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataYSlideCommand#DataYSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataYSlideCommandNullParam0() throws NullParameterException, InvalidParameterException {
		String name = "test";

		this.thrown.expect(NullParameterException.class);
		new DataYSlideCommand(null, name);

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataYSlideCommand#DataYSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataYSlideCommandNullParam1() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(1, 1, 1);

		this.thrown.expect(NullParameterException.class);
		new DataYSlideCommand(p1, null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataYSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataYSlideCommand dyc = new DataYSlideCommand(p1, "test");

		// [start] Test different object type
		assertFalse(dyc.equals(p1));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataYSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataYSlideCommand dyc = new DataYSlideCommand(p1, "test");
		DataYSlideCommand dyc2 = new DataYSlideCommand(p1, "test");

		// [start] Sunny-day
		assertTrue(dyc.equals(dyc2));

		assertTrue(dyc2.equals(dyc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataYSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataYSlideCommand dyc = new DataYSlideCommand(p1, "test");

		p1 = new Point(1, 1, 1);

		DataYSlideCommand dyc2 = new DataYSlideCommand(p1, "diff");

		// [start] non equal commands
		assertFalse(dyc.equals(dyc2));

		assertFalse(dyc2.equals(dyc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataYSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {
		
		Point p1 = new Point(0, 0, 0);

		DataYSlideCommand dyc = new DataYSlideCommand(p1, "test");
		
		// should not equal null commands
		assertFalse( dyc.equals( null ));
	}
}
