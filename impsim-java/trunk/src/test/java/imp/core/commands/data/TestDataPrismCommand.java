/**
 * TestDataPrismCommand.java
 * March 27, 2011
 */
package imp.core.commands.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataPrismCommand;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Prism;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the DataPrismCommand
 * 
 * @author dykstran
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestDataPrismCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	Point p1;
	Point p2;
	Point p3;
	String name;

	@Before
	public void setUp() {
		p1 = new Point(0, 0, 0);
		p2 = new Point(0, 10, 0);
		p3 = new Point(10, 0, 0);
		name = "test";
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommand() throws NullParameterException, InvalidParameterException {

		// valid data statement
		new DataPrismCommand(p1, p2, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandNullParam0() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataPrismCommand(null, p2, p3, name);

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandNullParam1() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataPrismCommand(p1, null, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandNullParam2() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataPrismCommand(p1, p2, null, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandNullParam3() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataPrismCommand(p1, p2, p3, null);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandCoexistingPoints0_1() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new DataPrismCommand(p1, p1, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandCoexistingPoints0_2() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new DataPrismCommand(p1, p2, p1, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataPrismCommand#DataPrismCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataPrismCommandCoexistingPoints1_2() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new DataPrismCommand(p1, p2, p2, name);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws MatrixIndexOutOfBoundsException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 */
	@Test
	public void testExecuteNullModel() throws NullParameterException, InvalidParameterException, JointNotFoundException, InvalidDatatypeException,
			MatrixIndexOutOfBoundsException, SelfLoopException, NameConflictException {
		DataPrismCommand dp = new DataPrismCommand(p1, p2, p3, "test");

		this.thrown.expect(NullParameterException.class);
		dp.execute(null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws MatrixIndexOutOfBoundsException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 */
	@Test
	public void testExecuteMissingJoint() throws NullParameterException, InvalidParameterException, JointNotFoundException, InvalidDatatypeException,
			MatrixIndexOutOfBoundsException, SelfLoopException, NameConflictException {
		// [start] attempt to execute on a non existent joint
		DataPrismCommand dp = new DataPrismCommand(p1, p2, p3, "empty");

		this.thrown.expect(JointNotFoundException.class);
		dp.execute(new Model());
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 * @throws InvalidParameterException
	 * @throws MatrixIndexOutOfBoundsException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 */
	@Test
	public void testExecute() throws SelfLoopException, NameConflictException, NullParameterException, InvalidParameterException, JointNotFoundException,
			InvalidDatatypeException, MatrixIndexOutOfBoundsException {

		Point origin = new Point(10, 10, 0);
		Point P2 = new Point(10, 10, 10);
		Point P3 = new Point(20, 10, 0);
		String name = "test";

		// [start] Sunny day case

		/* Create a new joint and model */
		Prism prism = new Prism("test");

		Model model = new Model();

		model.addJoint(prism, "body1", "body2");

		DataPrismCommand dpc = new DataPrismCommand(origin, P2, P3, name);

		dpc.execute(model);

		/**
		 * Check the values in each position matrix
		 * 
		 * <pre>
		 * Txyz= [ 1, 0, 0,10]
		 * 		 [ 0, 1, 0,10]
		 * 		 [ 0, 0, 1, 0]
		 * 		 [ 0, 0, 0, 1]
		 * 
		 * Tuvw= [ 1, 0, 0,10]
		 * 		 [ 0, 1, 0,10]
		 * 		 [ 0, 0, 1, 0]
		 * 		 [ 0, 0, 0, 1]
		 * 
		 * Phi= [ 1, 0, 0, 0]
		 * 		[ 0, 1, 0, 0]
		 * 		[ 0, 0, 1, 0]
		 * 		[ 0, 0, 0, 1]
		 * 
		 * </pre>
		 */

		PositionMatrix Txyz = prism.getAxisBefore().getShapeMatrix();
		PositionMatrix Tuvw = prism.getAxisAfter().getShapeMatrix();

		// Construction expected matrix for assertion, fixed to match correct positionmatrix
		PositionMatrix expected = new PositionMatrix(new double[][] { { 1, 0, 0, 10 }, { 0, 1, 0, 10 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });
//		expected.setColumn(3, new Vector3(10, 10, 0));

		assertEquals(Txyz, expected);
		assertEquals(Tuvw, expected);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws MatrixIndexOutOfBoundsException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 */
	@Test
	public void testExecuteClosePoints() throws NullParameterException, InvalidParameterException, JointNotFoundException, InvalidDatatypeException,
			MatrixIndexOutOfBoundsException, SelfLoopException, NameConflictException {

		// [start] Points too close checking

		/* The angle of the first axes is 10 degrees, the (exclusive) limit on closeness */
		Point origin = new Point(0, 0, 0);
		double x = Math.tan(Math.PI / 18);
		Point P2 = new Point(x, 0, 1);
		Point P3 = new Point(2 * x, 0, 1);
		System.out.println(origin.getAngleBetween(P3, P2));
		// Expect an exception
		this.thrown.expect(InvalidParameterException.class);
		new DataPrismCommand(origin, P2, P3, name);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);

		DataPrismCommand dpc = new DataPrismCommand(p1, p2, p3, "test");

		// [start] Test different object type
		assertFalse(dpc.equals(p1));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);

		DataPrismCommand dpc = new DataPrismCommand(p1, p2, p3, "test");
		DataPrismCommand dpc2 = new DataPrismCommand(p1, p2, p3, "test");

		// [start] Sunny-day
		assertTrue(dpc.equals(dpc2));

		assertTrue(dpc2.equals(dpc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {
		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);

		DataPrismCommand dpc = new DataPrismCommand(p1, p2, p3, "test");
		DataPrismCommand dpc2 = new DataPrismCommand(p2, p1, p3, "diff");

		// [start] non equal commands
		assertFalse(dpc.equals(dpc2));

		assertFalse(dpc2.equals(dpc));
		// [end]
	}
	
	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {
		
		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);

		DataPrismCommand dpc = new DataPrismCommand(p1, p2, p3, "test");
		
		// null command should not be equal
		assertFalse( dpc.equals( null ));
	}
}
