/**
 * 
 */
package imp.core.commands.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataCylinderCommand;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Cylinder;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author edmissonj
 * @edit dykstran April 14, 2011 Converted to JUnit 4 format.
 * 
 */
@SuppressWarnings("javadoc")
public class TestDataCylinderCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	Point p1;
	Point p2;
	Point p3;

	@Before
	public void setUp() {
		p1 = new Point(0, 0, 0);
		p2 = new Point(0, 0, 5);
		p3 = new Point(5, 0, 0);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommand() throws NullParameterException, InvalidParameterException {

		// creates a valid command
		new DataCylinderCommand(p1, p2, p3, "cyl");
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandCoexistingPoints0_1() throws NullParameterException, InvalidParameterException {

		// [start] tests coexisting values
		this.thrown.expect(InvalidParameterException.class);
		new DataCylinderCommand(p1, p1, p3, "cyl");
		// [end]
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandCoexistingPoints0_2() throws NullParameterException, InvalidParameterException {

		// [start] tests coexisting values
		this.thrown.expect(InvalidParameterException.class);
		new DataCylinderCommand(p1, p2, p1, "cyl");
		// [end]
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandCoexistingPoints1_2() throws NullParameterException, InvalidParameterException {

		// [start] tests coexisting values
		this.thrown.expect(InvalidParameterException.class);
		new DataCylinderCommand(p1, p2, p2, "cyl");
		// [end]
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandNullParam0() throws NullParameterException, InvalidParameterException {

		// [start] tests null values
		this.thrown.expect(NullParameterException.class);
		new DataCylinderCommand(null, p2, p3, "cyl");

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandNullParam1() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataCylinderCommand(p1, null, p3, "cyl");

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandNullParam2() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataCylinderCommand(p1, p2, null, "cyl");

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataCylinderCommand#DataCylinderCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testDataCylinderCommandNullParam3() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataCylinderCommand(p1, p2, p3, null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#execute(imp.core.model.Model)}.
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
		DataCylinderCommand dc = new DataCylinderCommand(p1, p2, p3, "test");

		this.thrown.expect(NullParameterException.class);
		dc.execute(null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#execute(imp.core.model.Model)}.
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
		DataCylinderCommand dc = new DataCylinderCommand(p1, p2, p3, "empty");

		this.thrown.expect(JointNotFoundException.class);
		dc.execute(new Model());
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#execute(imp.core.model.Model)}.
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
	public void testExecute() throws NullParameterException, InvalidParameterException, JointNotFoundException, InvalidDatatypeException,
			MatrixIndexOutOfBoundsException, SelfLoopException, NameConflictException {

		Point origin = new Point(0, 0, 0);
		Point axis = new Point(0, 0, 5);
		Point hp = new Point(5, 0, 0);

		// [start] sunny-day case
		Cylinder cyl = null;
		cyl = new Cylinder("cyl");

		Model ml = new Model();

		ml.addJoint(cyl, "Body1", "Body2");

		// run a valid command
		DataCylinderCommand dcc = new DataCylinderCommand(origin, axis, hp, "cyl");
		dcc.execute(ml);

		/**
		 * matrix to check the values out of the DataCylinderCommand Txyz= [ 1, 0, 0, 0] [ 0, 1, 0, 0] [ 0, 0, 1, 0] [
		 * 0, 0, 0, 1]
		 * 
		 */
		PositionMatrix Txyz = new PositionMatrix();

		assertEquals(cyl.getAxisAfter().getShapeMatrix(), Txyz);

		assertEquals(cyl.getAxisBefore().getShapeMatrix(), Txyz);

		// check the angle and displacement
		assertEquals(0, cyl.getJointVariable(JVAR.THETA).getMagnitude(), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(0, cyl.getJointVariable(JVAR.ZDISPLACEMENT).getMagnitude(), imp.core.Constants.ERROR_TOLERANCE);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#execute(imp.core.model.Model)}.
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
		// Expect an exception
		this.thrown.expect(InvalidParameterException.class);
		new DataCylinderCommand(origin, P2, P3, "test");
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Point origin = new Point(0, 0, 0);
		Point axis = new Point(0, 0, 5);
		Point hp = new Point(5, 0, 0);

		DataCylinderCommand dcc = new DataCylinderCommand(origin, axis, hp, "test");

		// [start] Test different object type
		assertFalse(dcc.equals(origin));
		// [end]

	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Point origin = new Point(0, 0, 0);
		Point axis = new Point(0, 0, 5);
		Point hp = new Point(5, 0, 0);

		DataCylinderCommand dcc = new DataCylinderCommand(origin, axis, hp, "test");
		DataCylinderCommand dcc2 = new DataCylinderCommand(origin, axis, hp, "test");
		
		// [start] Sunny-day
		assertTrue(dcc.equals(dcc2));

		assertTrue(dcc2.equals(dcc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Point origin = new Point(0, 0, 0);
		Point axis = new Point(0, 0, 5);
		Point hp = new Point(5, 0, 0);

		DataCylinderCommand dcc = new DataCylinderCommand(origin, axis, hp, "test");
		DataCylinderCommand dcc2 = new DataCylinderCommand(axis, origin, hp, "diff");

		// [start] non equal commands
		assertFalse(dcc.equals(dcc2));

		assertFalse(dcc2.equals(dcc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataCylinderCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException { 
		
		Point origin = new Point(0, 0, 0);
		Point axis = new Point(0, 0, 5);
		Point hp = new Point(5, 0, 0);

		DataCylinderCommand dcc = new DataCylinderCommand(origin, axis, hp, "test");
		
		// null command
		assertFalse( dcc.equals( null ) );
	}
}
