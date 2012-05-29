/**
 * TestDataScrewCommand.java
 * March 27, 2011
 * @author hellmerj
 */

package imp.core.commands.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataScrewCommand;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Screw;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * This is the TestDataScrewCommand class. It is responsible for testing the DataScrewCommand class. It checks that all
 * invalid data is correctly detected and that the position matrices were properly created.
 * 
 * @author hellmerj
 * @edit dykstran April 14, 2011 Edited to JUnit 4 format.
 * @version 1.1
 */
@SuppressWarnings("javadoc")
public class TestDataScrewCommand {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	double helic;
	Point p1;
	Point p2;
	Point p3;
	String name;

	@Before
	public void setUp() {
		helic = 1.0;
		p1 = new Point(0, 0, 0);
		p2 = new Point(0, 0, 8);
		p3 = new Point(8, 0, 0);
		name = "Screw";
	}

	/**
	 * This is the testDataScrewCommand method. It is responsible for testing the DataScrewCommand constructor. It
	 * checks that all null parameters and invalid data are caught.
	 * 
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommand() throws InvalidParameterException, NullParameterException {
		// [start] sunny-day case
		new DataScrewCommand(helic, p1, p2, p3, name);
		// [end]

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandNullParam1() throws InvalidParameterException, NullParameterException {
		// ********** test null data **********
		this.thrown.expect(NullParameterException.class);
		new DataScrewCommand(helic, null, p2, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandNullParam2() throws InvalidParameterException, NullParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataScrewCommand(helic, p1, null, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandNullParam3() throws InvalidParameterException, NullParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataScrewCommand(helic, p1, p2, null, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandNullParam4() throws InvalidParameterException, NullParameterException {
		this.thrown.expect(NullParameterException.class);
		new DataScrewCommand(helic, p1, p2, p3, null);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandInvalidHelic() throws InvalidParameterException, NullParameterException {
		// ********** test invalid data **********
		this.thrown.expect(InvalidParameterException.class);
		new DataScrewCommand(0, p1, p2, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandCoexistingPoints1_2() throws InvalidParameterException, NullParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new DataScrewCommand(helic, p1, p1, p3, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandCoexistingPoints1_3() throws InvalidParameterException, NullParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new DataScrewCommand(helic, p1, p2, p1, name);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataScrewCommand#DataScrewCommand(double, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testDataScrewCommandCoexistingPoints2_3() throws InvalidParameterException, NullParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new DataScrewCommand(helic, p1, p2, p2, name);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#execute(imp.core.model.Model)}.
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
		DataScrewCommand dsc = new DataScrewCommand(helic, p1, p2, p3, "test");

		this.thrown.expect(NullParameterException.class);
		dsc.execute(null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#execute(imp.core.model.Model)}.
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
		DataScrewCommand dsc = new DataScrewCommand(helic, p1, p2, p3, "empty");

		this.thrown.expect(JointNotFoundException.class);
		dsc.execute(new Model());
		// [end]
	}

	/**
	 * This is the testExecute method. It is responsible for testing the execute method of the DataScrewCommand. It
	 * checks that the matrices are created correctly and the angles and slide distances are set correctly.
	 * 
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 * @throws MatrixIndexOutOfBoundsException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 */
	@Test
	public void testExecute() throws InvalidParameterException, NullParameterException, JointNotFoundException, InvalidDatatypeException,
			MatrixIndexOutOfBoundsException, SelfLoopException, NameConflictException {

		// model used for testing
		Model testModel = new Model();

		// helical angle for test joint
		double helic = 1.0;
		// points defining the test joint
		Point origin = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 8);
		Point p3 = new Point(8, 0, 0);
		// name of test joints
		String name = "Screw";
		// name of test bodies
		String bodyBefore = "body1";
		String bodyAfter = "body2";

		// test DataScrewCommand
		DataScrewCommand dsc = null;

		// create DataScrewCommand for specified joint values
		dsc = new DataScrewCommand(helic, origin, p2, p3, name);

		// [start] a sunny day case

		// create the test joint
		Screw testScrew = new Screw(name);

		// add test joint to the model
		testModel.addJoint(testScrew, bodyAfter, bodyBefore);

		// execute the DataScrewCommand
		dsc.execute(testModel);

		/**
		 * <pre>
		 * matrix to check the values 
		 * Txyz= 	[ 1, 0, 0, 0] 
		 * 			[ 0, 1, 0, 0] 
		 * 			[ 0, 0, 1, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * Tuvw= 	[ 1, 0, 0, 0] 
		 * 			[ 0, 1, 0, 0] 
		 * 			[ 0, 0, 1, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * </pre>
		 * 
		 */

		// shape matrix for xyz(before) axis
		PositionMatrix txyz = testScrew.getAxisBefore().getShapeMatrix();
		PositionMatrix expected = new PositionMatrix(new double[][] { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });

		assertEquals(txyz, expected);

		// shape matrix for uvw(after) matrix
		PositionMatrix tuvw = testScrew.getAxisAfter().getShapeMatrix();

		// check uvw matrix equals tested xyz matrix
		assertEquals(txyz, tuvw);

		// check helical angle
		assertEquals(helic, testScrew.getHelicAngle(), imp.core.Constants.ERROR_TOLERANCE);
		// check angle between bodies
		assertEquals(0, testScrew.getAngle(), imp.core.Constants.ERROR_TOLERANCE);
		// check slide distance(translation) between bodies
		assertEquals(0, testScrew.getDisplacement(), imp.core.Constants.ERROR_TOLERANCE);

		// [end]
	}

	/**
	 * This is the testExecute method. It is responsible for testing the execute method of the DataScrewCommand. It
	 * checks that the matrices are created correctly and the angles and slide distances are set correctly.
	 * 
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 * @throws MatrixIndexOutOfBoundsException
	 * @throws InvalidDatatypeException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws SelfLoopException
	 */
	@Test
	public void testExecuteClosePoints() throws InvalidParameterException, NullParameterException, JointNotFoundException, InvalidDatatypeException,
			MatrixIndexOutOfBoundsException, SelfLoopException, NameConflictException {

		// [start] Points too close checking

		/* The angle of the first axes is 10 degrees, the (exclusive) limit on closeness */
		Point origin = new Point(0, 0, 0);
		double x = Math.tan(Math.PI / 18);
		Point p2 = new Point(x, 0, 1);
		Point p3 = new Point(2 * x, 0, 1);

		// Expect an exception
		this.thrown.expect(InvalidParameterException.class);
		new DataScrewCommand(helic, origin, p2, p3, name);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		double helic = 1.0;

		DataScrewCommand dsc = new DataScrewCommand(helic, p1, p2, p3, "test");

		// [start] Test different object type
		assertFalse(dsc.equals(p1));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		double helic = 1.0;

		DataScrewCommand dsc = new DataScrewCommand(helic, p1, p2, p3, "test");
		DataScrewCommand dsc2 = new DataScrewCommand(helic, p1, p2, p3, "test");

		// [start] Test different object type
		assertFalse(dsc.equals(p1));
		// [end]

		// [start] Sunny-day
		assertTrue(dsc.equals(dsc2));

		assertTrue(dsc2.equals(dsc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		double helic = 1.0;

		DataScrewCommand dsc = new DataScrewCommand(helic, p1, p2, p3, "test");
		DataScrewCommand dsc2 = new DataScrewCommand(helic, p2, p1, p3, "diff");

		// [start] Test different object type
		assertFalse(dsc.equals(p1));
		// [end]

		// [start] non equal commands
		assertFalse(dsc.equals(dsc2));

		assertFalse(dsc2.equals(dsc));
		// [end]
	}
	
	/**
	 * Test method for {@link imp.core.commands.data.DataScrewCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException {
		
		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		double helic = 1.0;

		DataScrewCommand dsc = new DataScrewCommand(helic, p1, p2, p3, "test");
		
		// should not be equal to null command
		assertFalse( dsc.equals( null ));
	}
}
