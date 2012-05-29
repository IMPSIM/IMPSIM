package imp.core.commands.joints;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.joints.Revolute;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Tests the RevoluteCommand.CreateZPinCommand
 */
public class TestRevoluteZPinCommand {

	/** Used to verify the proper exceptions are thrown. */
	@Rule
	public ExpectedException thrown = ExpectedException.none();

	Point p1, p2, p3;

	String jointName, bodyNameBefore, bodyNameAfter;

	@Before
	public void setUp() {
		p1 = new Point(10, 10, 0);
		p2 = new Point(20, 10, 0);
		p3 = new Point(0, 10, 0);
		jointName = "ZPin";
		bodyNameBefore = "LINK1";
		bodyNameAfter = "LINK2";
	}

	/**
	 * Test method for the Data ZPin Command Constructor
	 * 
	 * Test method for
	 * {@link imp.core.commands.data.DataZPinCommand#DataZPinCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataZPinCommand() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// [start] a sunny-day case
		RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3);
		// [end]
	}

	/**
	 * Test method for the Data ZPin Command Constructor
	 * 
	 * Test method for
	 * {@link imp.core.commands.data.DataZPinCommand#DataZPinCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataZPinCommandCoexistingPoints0_1() throws NullParameterException, InvalidParameterException, SelfLoopException {
		this.thrown.expect(InvalidParameterException.class);
		RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, p1, p1, p3);
	}

	/**
	 * Test method for the Data ZPin Command Constructor
	 * 
	 * Test method for
	 * {@link imp.core.commands.data.DataZPinCommand#DataZPinCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * .
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataZPinCommandCoexistingPoints0_2() throws NullParameterException, InvalidParameterException, SelfLoopException {
		this.thrown.expect(InvalidParameterException.class);
		RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p1);
	}

	/**
	 * Test method for the Data ZPin Command Constructor
	 * 
	 * Test method for
	 * {@link imp.core.commands.data.DataZPinCommand#DataZPinCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Ignore("TODO broken")
	@Test
	public void testDataZPinCommandCoexistingPoints1_2() throws NullParameterException, InvalidParameterException, SelfLoopException {
		this.thrown.expect(InvalidParameterException.class);
		RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p2);
	}

	/**
	 * Test cases for the Data ZPin Command's execute method.
	 * 
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws IMPException
	 */
	@Test
	public void testExecute() throws NullParameterException, IMPException {

		// [start] A sunny day case

		/* These points form axes that are at 180 degrees from each other (pi radians) */
		Point origin = new Point(10, 10, 0);
		Point p1 = new Point(20, 10, 0);
		Point p2 = new Point(0, 10, 0);

		Model model = new Model();

		RevoluteCommand dypc = RevoluteCommand.CreateYPin(jointName, bodyNameBefore, bodyNameAfter, origin, p1, p2);
		dypc.execute(model);

		Revolute rev = (Revolute) model.getJoint(jointName);

		PositionMatrix Txyz = rev.getAxisBefore().getShapeMatrix();
		PositionMatrix Tuvw = rev.getAxisAfter().getShapeMatrix();

		PositionMatrix xyzRight = new PositionMatrix();
		xyzRight.fill(new Vector3(1, 0, 0), new Vector3(0, 0, -1), new Vector3(0, 1, 0), new Vector3(10, 10, 0));
		PositionMatrix uvwRight = new PositionMatrix();
		uvwRight.fill(new Vector3(-1, 0, 0), new Vector3(0, 0, 1), new Vector3(0, 1, 0), new Vector3(10, 10, 0));
		PositionMatrix phiRight = new PositionMatrix();
		phiRight.fill(new Vector3(-1, 0, 0), new Vector3(0, -1, 0), new Vector3(0, 0, 1), new Vector3(0, 0, 0));
		/**
		 * Check the values in each position matrix
		 * 
		 * <pre>
		 * Txyz= 	[ 1, 0, 0,10]
		 * 			[ 0, 0, 1,10] 
		 * 			[ 0,-1, 0, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * Tuvw= 	[-1, 0, 0,10] 
		 * 			[ 0, 0, 1,10] 
		 * 			[ 0, 1, 0, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * Phi= 	[-1, 0, 0, 0] 
		 * 			[ 0,-1, 0, 0] 
		 * 			[ 0, 0, 1, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * </pre>
		 */

		assertEquals(xyzRight, Txyz);
		assertEquals(uvwRight, Tuvw);

		/* Check dot products of columns, they should be 0 */
		assertEquals(0.0, Txyz.getColumn(0).dotProduct(Txyz.getColumn(1)), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(0.0, Txyz.getColumn(0).dotProduct(Txyz.getColumn(2)), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(0.0, Txyz.getColumn(1).dotProduct(Txyz.getColumn(2)), imp.core.Constants.ERROR_TOLERANCE);

		assertEquals(0.0, Tuvw.getColumn(0).dotProduct(Tuvw.getColumn(1)), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(0.0, Tuvw.getColumn(0).dotProduct(Tuvw.getColumn(2)), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(0.0, Tuvw.getColumn(1).dotProduct(Tuvw.getColumn(2)), imp.core.Constants.ERROR_TOLERANCE);

		/* Check cross products of 2 of the first 3 columns, the result should be the unused column */
		assertTrue(Txyz.getColumn(2).equals(Txyz.getColumn(0).crossProduct(Txyz.getColumn(1))));
		assertTrue(Txyz.getColumn(0).equals(Txyz.getColumn(1).crossProduct(Txyz.getColumn(2))));
		assertTrue(Txyz.getColumn(1).equals(Txyz.getColumn(2).crossProduct(Txyz.getColumn(0))));

		assertTrue(Tuvw.getColumn(2).equals(Tuvw.getColumn(0).crossProduct(Tuvw.getColumn(1))));
		assertTrue(Tuvw.getColumn(0).equals(Tuvw.getColumn(1).crossProduct(Tuvw.getColumn(2))));
		assertTrue(Tuvw.getColumn(1).equals(Tuvw.getColumn(2).crossProduct(Tuvw.getColumn(0))));

		/* Check angle */
		PositionMatrix phi = Tuvw.inverse().multiply(Txyz);
		assertEquals(phi, phiRight);

		double angle = Math.atan2(phi.get(0, 1), phi.get(0, 0));
		assertEquals(Math.PI, angle, imp.core.Constants.ERROR_TOLERANCE);

		// check that joint was added to model
		assertEquals(1, model.countJoints());

		// check that model contains correct joint
		assertNotNull(model.getJoint(jointName));

		// check that added joint is correct type
		assertEquals(Revolute.class, model.getJoint(jointName).getClass());
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataZPinCommand#execute(imp.core.model.Model)}.
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
		Point P3 = new Point(60, 40, 0);

		// Expect an exception
		this.thrown.expect(InvalidParameterException.class);
		RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, origin, P2, P3);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataZPinCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException, SelfLoopException {

		Point p1 = new Point(10, 10, 0);
		Point p2 = new Point(20, 10, 0);
		Point p3 = new Point(0, 10, 0);

		RevoluteCommand dxc = RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3);
		RevoluteCommand dxc2 = RevoluteCommand.CreateZPin(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3);

		// [start] Sunny-day
		assertTrue(dxc.equals(dxc2));

		assertTrue(dxc2.equals(dxc));
		// [end]
	}
}
