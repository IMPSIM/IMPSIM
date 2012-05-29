/**
 * TestDataXSlideCommand.java
 * April 7, 2011
 */
package imp.core.commands.data;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataXSlideCommand;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the DataXSlideCommand
 * 
 * @author dykstran
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestDataXSlideCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataXSlideCommand#DataXSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataXSlideCommand() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(1, 1, 1);
		String name = "test";

		// valid data statement
		new DataXSlideCommand(p1, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataXSlideCommand#DataXSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataXSlideCommandNullParam0() throws NullParameterException, InvalidParameterException {
		String name = "test";

		this.thrown.expect(NullParameterException.class);
		new DataXSlideCommand(null, name);

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataXSlideCommand#DataXSlideCommand(imp.core.structures.Point, java.lang.String)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataXSlideCommandNullParam1() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(1, 1, 1);

		this.thrown.expect(NullParameterException.class);
		new DataXSlideCommand(p1, null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataXSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataXSlideCommand dpc = new DataXSlideCommand(p1, "test");

		// [start] Test different object type
		assertFalse(dpc.equals(p1));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataXSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataXSlideCommand dpc = new DataXSlideCommand(p1, "test");
		DataXSlideCommand dpc2 = new DataXSlideCommand(p1, "test");

		// [start] Sunny-day
		assertTrue(dpc.equals(dpc2));

		assertTrue(dpc2.equals(dpc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataXSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);

		DataXSlideCommand dpc = new DataXSlideCommand(p1, "test");

		p1 = new Point(1, 1, 1);

		DataXSlideCommand dpc2 = new DataXSlideCommand(p1, "diff");

		// [start] non equal commands
		assertFalse(dpc.equals(dpc2));

		assertFalse(dpc2.equals(dpc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataXSlideCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {
		
		Point p1 = new Point(0, 0, 0);

		DataXSlideCommand dpc = new DataXSlideCommand(p1, "test");
		
		// should not equal null command
		assertFalse( dpc.equals( null ));
	}
}
