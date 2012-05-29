/**
 * 
 */
package imp.core.commands.joints;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.Model;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Revolute;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;
import imp.unittests.ParameterHelper;

import java.util.Arrays;
import java.util.Collection;

import junitparams.JUnitParamsRunner;
import junitparams.Parameters;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.junit.runner.RunWith;

/**
 * @author zastrowm
 * 
 */
@RunWith(JUnitParamsRunner.class)
public class TestRevoluteCommand {

	/** Used to verify the proper exceptions are thrown. */
	@Rule
	public ExpectedException thrown = ExpectedException.none();

	Point p1, p2, p3, p4;

	String jointName, bodyNameBefore, bodyNameAfter;

	@Before
	public void setUp() {
		p1 = new Point(10, 10, 0);
		p2 = new Point(10, 20, 0);
		p3 = new Point(20, 10, 0);
		p4 = new Point(5, 10, 0);
		jointName = "PIN";
		bodyNameBefore = "LINK1";
		bodyNameAfter = "LINK2";
	}

	/*
	 * Test data generator. This method is called the the JUnit parameterized test runner and returns a Collection of
	 * Arrays. For each Array in the Collection, each array element corresponds to a parameter in the constructor.
	 */

	public static Collection<Object[]> generateData() {
		// In this example, the parameter generator returns a List of
		// arrays. Each array has two elements: { datum, expected }.
		// These data are hard-coded into the class, but they could be
		// generated or loaded in any way you like.

		return Arrays.asList(new Object[][] { { "AGCCG", "AGTTA" }, { "AGTTA", "GATCA" }, { "GGGAT", "AGCCA" } });
	}

	@SuppressWarnings("unused")
	private Object[] nullParameters() {
		setUp(); // setup isn't called for parameters, so call it manually
		return ParameterHelper.returnSingleNullSet(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);
	}

	@Test
	@Parameters(method = "nullParameters")
	public void testConstructorForNull(String jointName, String bodyNameBefore, String bodyNameAfter, Point origin, Point commonAxis, Point bodyAxisFirst,
			Point bodyAxisSecond) throws SelfLoopException {

		this.thrown.expect(NullParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, commonAxis, bodyAxisFirst, bodyAxisSecond);
	}

	/**
	 * Test method for {@link imp.commands.definition.RevoluteCommand#RevoluteCommand())}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 */
	@Test
	public void testRevoluteCommandSelfLoop() throws NullParameterException, SelfLoopException {
		this.thrown.expect(SelfLoopException.class);
		new RevoluteCommand("Rev", "Body1", "Body1", p1, p2, p3, p4);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataRevoluteCommand#DataRevoluteCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataRevoluteCommand() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// [start] sunny-day case
		// This should pass
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);
		// [end]
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataRevoluteCommand#DataRevoluteCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataRevoluteCommandCoexistingPoints0_1() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// Duplicate points defining axes
		this.thrown.expect(InvalidParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p1, p3, p4);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataRevoluteCommand#DataRevoluteCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataRevoluteCommandCoexistingPoints0_2() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// Duplicate points defining axes
		this.thrown.expect(InvalidParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p1, p4);

	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataRevoluteCommand#DataRevoluteCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataRevoluteCommandCoexistingPoints0_3() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// Duplicate points defining axes
		this.thrown.expect(InvalidParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p1);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataRevoluteCommand#DataRevoluteCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataRevoluteCommandCoexistingPoints1_2() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// Duplicate points defining axes
		this.thrown.expect(InvalidParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p2, p4);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.data.DataRevoluteCommand#DataRevoluteCommand(imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, imp.core.structures.Point, java.lang.String)}
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testDataRevoluteCommandCoexistingPoints1_3() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// Duplicate points defining axes
		this.thrown.expect(InvalidParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p2);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws IMPException
	 */
	@Test
	public void testExecuteNullModel() throws NullParameterException, IMPException {
		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);

		this.thrown.expect(NullParameterException.class);
		drc.execute(null);
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#execute(imp.core.model.Model)}.
	 * 
	 * @author dykstran
	 * @throws IMPException
	 */
	@Test
	public void testExecute180DegreeAxes() throws IMPException {

		/* These points form axes that are at 180 degrees from each other (pi radians) */
		Point origin = new Point(10, 10, 0);
		Point axis = new Point(10, 20, 0);
		Point p1 = new Point(20, 10, 0);
		Point p2 = new Point(5, 10, 0);

		// [start] A sunny day case

		Model model = new Model();

		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, axis, p1, p2);

		drc.execute(model);
		Joint rev = model.getJoint(jointName);

		PositionMatrix Txyz = rev.getAxisBefore().getShapeMatrix();
		PositionMatrix Tuvw = rev.getAxisAfter().getShapeMatrix();
		PositionMatrix phi = Tuvw.inverse().multiply(Txyz);

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

		PositionMatrix expectedTxyz = new PositionMatrix(new double[][] { { 1, 0, 0, 10 }, { 0, 0, 1, 10 }, { 0, -1, 0, 0 }, { 0, 0, 0, 1 } });
		PositionMatrix expectedTuvw = new PositionMatrix(new double[][] { { -1, 0, 0, 10 }, { 0, 0, 1, 10 }, { 0, 1, 0, 0 }, { 0, 0, 0, 1 } });

		// because the constructor of the PositionMatrix drops anything in the last column, these values must be
		// re-added. Joe E
		Vector3 v = new Vector3(10, 10, 0);
		expectedTxyz.setColumn(3, v);
		expectedTuvw.setColumn(3, v);

		assertTrue(expectedTxyz.equals(Txyz));
		assertTrue(expectedTuvw.equals(Tuvw));

		/* Check angle */
		phi = Txyz.inverse().multiply(Tuvw);

		PositionMatrix expectedPhi = new PositionMatrix(new double[][] { { -1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });
		assertTrue(expectedPhi.equals(phi));

		/* Check angle */
		double angle = Math.atan2(phi.get(1, 0), phi.get(0, 0));
		assertEquals(Math.PI, angle, imp.core.Constants.ERROR_TOLERANCE);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#execute(imp.core.model.Model)}.
	 * 
	 * @author dykstran
	 * @throws IMPException
	 */
	@Test
	public void testExecute45DegreeAxes() throws IMPException {

		// [start] Another sunny day case

		/* These points form axes that are at -45 degrees from each other (-pi/4 radians) */
		Point origin = new Point(50, 50, 0);
		Point axis = new Point(50, 50, 10);
		Point p1 = new Point(60, 50, 0);
		Point p2 = new Point(60, 40, 0);

		Model model = new Model();

		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, axis, p1, p2);

		drc.execute(model);
		Joint rev = model.getJoint(jointName);

		PositionMatrix Txyz = rev.getAxisBefore().getShapeMatrix();
		PositionMatrix Tuvw = rev.getAxisAfter().getShapeMatrix();

		/**
		 * Check the values in each position matrix
		 * 
		 * <pre>
		 * 
		 * root(2)/2 = .707...
		 * 
		 * Tuvw= 	[ .707, .707, 0, 50]
		 * 			[-.707, .707, 0, 50] 
		 * 			[    0,    0, 1,  0] 
		 * 			[    0,    0, 0,  1]
		 * 
		 * Txyz= 	[ 1, 0, 0,50] 
		 * 			[ 0, 1, 0,50] 
		 * 			[ 0, 0, 1, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * Phi= 	[ .707, .707, 0, 0]
		 * 			[-.707, .707, 0, 0] 
		 * 			[    0,    0, 1, 0] 
		 * 			[    0,    0, 0, 1]
		 * 
		 * </pre>
		 */

		double root = (Math.sqrt(2)) / 2;
		double negRoot = -root;

		PositionMatrix expectedTuvw = new PositionMatrix(new double[][] { { root, root, 0, 50 }, { negRoot, root, 0, 50 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });
		PositionMatrix expectedTxyz = new PositionMatrix(new double[][] { { 1, 0, 0, 50 }, { 0, 1, 0, 50 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });

		// because the constructor of the PositionMatrix drops anything in the last column, these values must be
		// re-added. Joe E
		Vector3 v = new Vector3(50, 50, 0);
		expectedTxyz.setColumn(3, v);
		expectedTuvw.setColumn(3, v);

		assertEquals(expectedTxyz, Txyz);
		assertEquals(expectedTuvw, Tuvw);

		/* Check angle */
		PositionMatrix phi = Txyz.inverse().multiply(Tuvw);

		PositionMatrix expectedPhi = new PositionMatrix(new double[][] { { root, root, 0, 0 }, { negRoot, root, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });
		assertEquals(expectedPhi, phi);

		double angle = Math.atan2(phi.get(1, 0), phi.get(0, 0));
		assertEquals(-Math.PI / 4, angle, imp.core.Constants.ERROR_TOLERANCE);

		// check that joint was added to model
		assertEquals(1, model.countJoints());

		// check that model contains correct joint
		assertTrue(model.getJoint(jointName) != null);

		// check that added joint is correct type
		assertEquals(Revolute.class, model.getJoint(jointName).getClass());
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataPrismCommand#execute(imp.core.model.Model)}.
	 * 
	 * @throws NullParameterException
	 * @throws IMPException
	 */
	@Test
	public void testExecuteClosePoint() throws NullParameterException, IMPException {
		// [start] Points too close checking

		/* The angle of the first axes is 10 degrees, the (exclusive) limit on closeness */
		Point origin = new Point(0, 0, 0);
		Point axis = new Point(0, 0, 1);
		double x = Math.tan(Math.PI / 18);
		Point p1 = new Point(x, 0, 1);
		Point p2 = new Point(60, 40, 0);

		this.thrown.expect(InvalidParameterException.class);
		new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, origin, axis, p1, p2);

		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException, SelfLoopException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		Point p4 = new Point(10, 10, 10);

		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);

		// [start] Test different object type
		assertFalse(drc.equals(p1));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException, SelfLoopException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		Point p4 = new Point(10, 10, 10);

		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);
		RevoluteCommand drc2 = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);

		// [start] Sunny-day
		assertTrue(drc.equals(drc2));

		assertTrue(drc2.equals(drc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException, SelfLoopException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		Point p4 = new Point(10, 10, 10);

		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);
		RevoluteCommand drc2 = new RevoluteCommand("dif", bodyNameBefore, bodyNameAfter, p2, p1, p3, p4);

		// [start] non equal commands
		assertFalse(drc.equals(drc2));

		assertFalse(drc2.equals(drc));
		// [end]
	}

	/**
	 * Test method for {@link imp.core.commands.data.DataRevoluteCommand#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 * @throws SelfLoopException
	 */
	@Test
	public void testEqualsNull() throws NullParameterException, InvalidParameterException, SelfLoopException {

		Point p1 = new Point(0, 0, 0);
		Point p2 = new Point(0, 0, 5);
		Point p3 = new Point(5, 0, 0);
		Point p4 = new Point(10, 10, 10);

		RevoluteCommand drc = new RevoluteCommand(jointName, bodyNameBefore, bodyNameAfter, p1, p2, p3, p4);

		// Should not equal null command
		assertFalse(drc.equals(null));
	}
}
