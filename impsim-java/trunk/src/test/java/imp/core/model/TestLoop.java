/**
 * TestLoop.java
 * February 24, 2011
 */
package imp.core.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import imp.core.commands.data.DataXSlideCommand;
import imp.core.commands.joints.RevoluteCommand;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.LoopException;
import imp.core.model.elements.Joint;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Prism;
import imp.core.model.loop.Loop;
import imp.core.model.loop.LoopVariable;
import imp.core.structures.Point;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import org.junit.Test;

/**
 * Unit tests for the Loop class.
 * 
 * @author dykstran klehmc
 * @edit edmissonj September 25, 2011 Added a method for testing loop closure of single variable loops.
 */
@SuppressWarnings("javadoc")
public class TestLoop {

	@Test
	public void testLoop() throws IMPException {
		Model model = new Model();
		RevoluteCommand dr1 = RevoluteCommand.CreateZPin("J1", "FRAME", "A", new Point(0, 0, 0), new Point(10, 0, 0), new Point(10, 0, 1));
		RevoluteCommand dr2 = RevoluteCommand.CreateZPin("J2", "A", "B", new Point(0, 10, 0), new Point(10, 10, 0), new Point(10, 10, 1));
		RevoluteCommand dr3 = RevoluteCommand.CreateZPin("J3", "B", "C", new Point(10, 10, 0), new Point(20, 10, 0), new Point(20, 10, 1));
		RevoluteCommand dr4 = RevoluteCommand.CreateZPin("J4", "C", "FRAME", new Point(10, 0, 0), new Point(20, 0, 0), new Point(20, 0, 1));
		dr1.execute(model);
		dr2.execute(model);
		dr3.execute(model);
		dr4.execute(model);
		model.setGround("FRAME");
		List<Loop> loops = model.findKinematicLoops();
		for (Loop loop : loops) {
			model.getPrintStream().println(loop.toString());
		}
		List<LoopVariable> vars = new ArrayList<LoopVariable>();
		vars.add(new LoopVariable("J2", JVAR.THETA, 10 * (Math.PI / 180)));
		model.closeLoops(vars);
	}

	/**
	 * Test method for {@link imp.core.model.loop.Loop#Loop()}.
	 */
	@Test
	public void testLoopConstructor() throws IMPException {
		// builds the model to hold the loop
		Model m = new Model();
		RevoluteCommand dr4 = RevoluteCommand.CreateZPin("R4", "d", "a", new Point(30, 0, 0), new Point(40, -10, 0), new Point(40, 0, 0));
		RevoluteCommand dr3 = RevoluteCommand.CreateZPin("R3", "c", "d", new Point(20, 10, 0), new Point(30, 10, 0), new Point(30, 0, 0));
		RevoluteCommand dr2 = RevoluteCommand.CreateZPin("R2", "b", "c", new Point(10, 10, 0), new Point(20, 20, 0), new Point(20, 10, 0));
		RevoluteCommand dr1 = RevoluteCommand.CreateZPin("R1", "a", "b", new Point(0, 0, 0), new Point(10, 0, 0), new Point(10, 10, 0));
		dr1.execute(m);
		dr2.execute(m);
		dr3.execute(m);
		dr4.execute(m);
		m.setGround("a");

		// creates something to test against
		List<Joint> j = new LinkedList<Joint>();
		j.add(m.getJoint("R1"));
		j.add(m.getJoint("R2"));
		j.add(m.getJoint("R3"));
		j.add(m.getJoint("R4"));

		// verifies that the list of joints in the loop is correct
		Loop l1 = new Loop(j, m.getGround());
		assertEquals(l1.getLoop(), j);
	}

	/**
	 * Test code for single loop single variable closure.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testSingleClosure() throws IMPException {
		// creates a square model of 4 revolutes
		Model model = new Model();
		RevoluteCommand dr1 = RevoluteCommand.CreateZPin("J1", "FRAME", "A", new Point(0, 0, 0), new Point(10, 0, 0), new Point(10, 0, 1));
		RevoluteCommand dr2 = RevoluteCommand.CreateZPin("J2", "A", "B", new Point(0, 10, 0), new Point(10, 10, 0), new Point(10, 10, 1));
		RevoluteCommand dr3 = RevoluteCommand.CreateZPin("J3", "B", "C", new Point(10, 10, 0), new Point(20, 10, 0), new Point(20, 10, 1));
		RevoluteCommand dr4 = RevoluteCommand.CreateZPin("J4", "C", "FRAME", new Point(10, 0, 0), new Point(20, 0, 0), new Point(20, 0, 1));
		dr1.execute(model);
		dr2.execute(model);
		dr3.execute(model);
		dr4.execute(model);
		model.setGround("FRAME");

		System.out.println(model.getJoint("J2").getJointVariable(JVAR.THETA).getMagnitude());
		List<LoopVariable> vars = new ArrayList<LoopVariable>();
		// moves one revolute 10 degrees
		vars.add(new LoopVariable("J2", JVAR.THETA, 10 * (Math.PI / 180)));
		model.findKinematicLoops();
		model.closeLoops(vars);

		// checks that the joints are now 80 degrees
		assertEquals(model.getJoint("J1").getJointVariable(JVAR.THETA).getMagnitude(), -10 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("J2").getJointVariable(JVAR.THETA).getMagnitude(), 10 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("J3").getJointVariable(JVAR.THETA).getMagnitude(), -10 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("J4").getJointVariable(JVAR.THETA).getMagnitude(), 10 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);

		for (Joint j : model.getJointStructure()) {
			System.out.println("Final position for joint: " + j.getName() + "is:");
			System.out.println(j.getBodyAfter().getPositionMatrix().toString());
			System.out.println(j.getAxisBefore().getAbsolutePosition().toString());
			System.out.println(j.getAxisAfter().getAbsolutePosition().toString());
		}

	}

	@Test
	public void testPistonClosure() throws IMPException {
		Model m2 = new Model();// creates a new model with a prism joint
		m2.addJoint(new Prism("P"), "3", "Ground");

		RevoluteCommand.CreateZPin("R1", "Ground", "1", new Point(0, 0, 0), new Point(10, 0, 0), new Point(0, 3, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R2", "1", "2", new Point(0, 3, 0), new Point(0, 0, 0), new Point(4, 0, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R3", "2", "3", new Point(4, 0, 0), new Point(0, 3, 0), new Point(10, 0, 0)).execute(m2);
		new DataXSlideCommand(new Point(4, 0, 0), "P").execute(m2);

		// prints out the values of the angles or displacement
		System.out.println("R1 " + m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
		System.out.println("R2 " + m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
		System.out.println("R3 " + m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
		System.out.println("P " + m2.getJoint("P").getJointVariable(JVAR.ZDISPLACEMENT).getMagnitude());

		m2.setGround("Ground");
		List<LoopVariable> vars2 = new ArrayList<LoopVariable>();
		// moves the first high revolute 1 degrees
		vars2.add(new LoopVariable("R1", JVAR.THETA, 1 * (Math.PI / 180)));
		m2.findKinematicLoops();
		m2.closeLoops(vars2);

		// checks that all joints have the proper magnitudes after closure
		// assertEquals(m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude(), 45*(Math.PI/180));
		// assertEquals(m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude(), 90*(Math.PI/180));
		// assertEquals(m2.getJoint("P").getJointVariable(JVAR.THETA).getMagnitude(), 4.1421356);
		// assertEquals(m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude(), 45*(Math.PI/180));
	}

	/**
	 * \ test with 5 revolutes in an M formation
	 * 
	 * @throws IMPException
	 */
	/**
	 * Removed because it is failing due to underconstrainment
	 * 
	 * @Test
	 * @Ignore("failing") public void testLargerModelLoops() throws IMPException { Model m2 = new Model();// creates a
	 *                    new model with a 5 revolutes in an M m2.addJoint(new Revolute("R1"), "Ground", "1");
	 *                    m2.addJoint(new Revolute("R2"), "1", "2"); m2.addJoint(new Revolute("R3"), "2", "3");
	 *                    m2.addJoint(new Revolute("R4"), "3", "4"); m2.addJoint(new Revolute("R5"), "4", "Ground");
	 * 
	 *                    new DataZPinCommand(new Point(0, 0, 0), new Point(10, 0, 0), new Point(5, 5, 0),
	 *                    "R1").execute(m2); new DataZPinCommand(new Point(5, 5, 0), new Point(0, 0, 0), new Point(10,
	 *                    0, 0), "R2").execute(m2); new DataZPinCommand(new Point(10, 0, 0), new Point(5, 5, 0), new
	 *                    Point(15, 5, 0), "R3").execute(m2); new DataZPinCommand(new Point(15, 5, 0), new Point(10, 0,
	 *                    0), new Point(20, 0, 0), "R4").execute(m2); new DataZPinCommand(new Point(20, 0, 0), new
	 *                    Point(15, 5, 0), new Point(0, 0, 0), "R5").execute(m2);
	 * 
	 *                    // displays the current valeus System.out.println("R1 " +
	 *                    m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
	 *                    System.out.println("R2 " + m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude() * 180
	 *                    / Math.PI); System.out.println("R3 " +
	 *                    m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
	 *                    System.out.println("R4 " + m2.getJoint("R4").getJointVariable(JVAR.THETA).getMagnitude() * 180
	 *                    / Math.PI); System.out.println("R5 " +
	 *                    m2.getJoint("R5").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
	 * 
	 *                    m2.setGround("Ground"); List<LoopVariable> vars2 = new ArrayList<LoopVariable>(); // moves the
	 *                    first high revolute 1 degrees vars2.add(new LoopVariable("R2", JVAR.THETA, 0)); vars2.add(new
	 *                    LoopVariable("R1", JVAR.THETA, 0)); vars2.add(new LoopVariable("R3", JVAR.THETA, 0));
	 *                    vars2.add(new LoopVariable("R4", JVAR.THETA, 0)); vars2.add(new LoopVariable("R5", JVAR.THETA,
	 *                    0)); m2.findKinematicLoops(); m2.closeLoops(vars2);
	 * 
	 *                    // discover joint variables after closure System.out.println("R1 " +
	 *                    m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
	 *                    System.out.println("R2 " + m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude() * 180
	 *                    / Math.PI); System.out.println("R3 " +
	 *                    m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
	 *                    System.out.println("R4 " + m2.getJoint("R4").getJointVariable(JVAR.THETA).getMagnitude() * 180
	 *                    / Math.PI); System.out.println("R5 " +
	 *                    m2.getJoint("R5").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); }
	 */

	@Test
	public void testMultipleLoops() throws IMPException {
		System.out.println("Test Multiple Loops");
		Model model = new Model();
		RevoluteCommand.CreateZPin("J1", "FRAME", "A", new Point(0, 0, 0), new Point(10, 0, 0), new Point(10, 0, 1)).execute(model);
		RevoluteCommand.CreateZPin("J2", "A", "B", new Point(0, 10, 0), new Point(10, 10, 0), new Point(10, 10, 1)).execute(model);
		RevoluteCommand.CreateZPin("J3", "B", "C", new Point(10, 10, 0), new Point(20, 10, 0), new Point(20, 10, 1)).execute(model);
		RevoluteCommand.CreateZPin("J4", "C", "FRAME", new Point(10, 0, 0), new Point(20, 0, 0), new Point(20, 0, 1)).execute(model);
		RevoluteCommand.CreateZPin("J5", "C", "D", new Point(10, 10, 0), new Point(20, 10, 0), new Point(20, 10, 1)).execute(model);
		RevoluteCommand.CreateZPin("J6", "D", "E", new Point(20, 10, 0), new Point(30, 10, 0), new Point(30, 10, 1)).execute(model);
		RevoluteCommand.CreateZPin("J7", "E", "FRAME", new Point(20, 0, 0), new Point(30, 0, 0), new Point(30, 0, 1)).execute(model);
		model.setGround("FRAME");

		System.out.println(model.getJoint("J2").getJointVariable(JVAR.THETA).getMagnitude());
		List<LoopVariable> vars = new ArrayList<LoopVariable>();
		// moves one revolute 10 degrees
		vars.add(new LoopVariable("J2", JVAR.THETA, 10 * (Math.PI / 180)));
		model.findKinematicLoops();
		model.closeLoops(vars);

		assertEquals(model.getJoint("J1").getJointVariable(JVAR.THETA).getMagnitude(), -10 * (Math.PI / 180), Math.pow(10, -6));// checks
																																// that
																																// the
																																// joints
																																// are
																																// now
																																// 80
																																// degrees
		assertEquals(model.getJoint("J2").getJointVariable(JVAR.THETA).getMagnitude(), 10 * (Math.PI / 180), Math.pow(10, -6));
		assertEquals(model.getJoint("J3").getJointVariable(JVAR.THETA).getMagnitude(), -10 * (Math.PI / 180), Math.pow(10, -6));
		assertEquals(model.getJoint("J4").getJointVariable(JVAR.THETA).getMagnitude(), 10 * (Math.PI / 180), Math.pow(10, -6));

		for (Joint j : model.getJointStructure()) {
			System.out.println("Final position for joint: " + j.getName() + "is:");
			System.out.println(j.getAxisBefore().getAbsolutePosition().toString());
			System.out.println(j.getAxisAfter().getAbsolutePosition().toString());
		}
	}

	/**
	 * Test of 6 revolutes in a tall rectangle
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testLargerModelLoops2() throws IMPException {
		Model m2 = new Model();// creates a new model with 6 revolutes in a tall rectangle
		RevoluteCommand.CreateZPin("R1", "Ground", "1", new Point(0, 0, 0), new Point(10, 0, 0), new Point(0, 10, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R2", "1", "2", new Point(0, 10, 0), new Point(0, 0, 0), new Point(0, 20, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R3", "2", "3", new Point(0, 20, 0), new Point(0, 10, 0), new Point(10, 20, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R4", "3", "4", new Point(10, 20, 0), new Point(0, 20, 0), new Point(10, 10, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R5", "4", "5", new Point(10, 10, 0), new Point(10, 20, 0), new Point(10, 0, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R6", "5", "Ground", new Point(10, 0, 0), new Point(10, 10, 0), new Point(0, 0, 0)).execute(m2);

		m2.setGround("Ground");
		List<LoopVariable> vars2 = new ArrayList<LoopVariable>();
		// moves the first high revolute 10 degrees
		vars2.add(new LoopVariable("R2", JVAR.THETA, 10 * (Math.PI / 180)));
		vars2.add(new LoopVariable("R1", JVAR.THETA, 0));
		vars2.add(new LoopVariable("R6", JVAR.THETA, 0));
		m2.findKinematicLoops();

		m2.closeLoops(vars2);

		// checks that the values are what they should be
		assertEquals(m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude(), 90 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude(), 190 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude(), 80 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R4").getJointVariable(JVAR.THETA).getMagnitude(), 100 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R5").getJointVariable(JVAR.THETA).getMagnitude(), 170 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R6").getJointVariable(JVAR.THETA).getMagnitude(), 90 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * test that loop closure can't close something impossible to close
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testBrokenClosure() throws IMPException {
		// creates a square model of 4 revolutes
		Model model = new Model();
		RevoluteCommand.CreateZPin("J1", "FRAME", "A", new Point(0, 0, 0), new Point(10, 0, 0), new Point(10, 0, 1)).execute(model);
		RevoluteCommand.CreateZPin("J2", "A", "B", new Point(0, 10, 0), new Point(10, 10, 0), new Point(10, 10, 1)).execute(model);
		RevoluteCommand.CreateZPin("J3", "B", "C", new Point(10, 10, 0), new Point(20, 10, 0), new Point(20, 10, 1)).execute(model);
		RevoluteCommand.CreateZPin("J4", "C", "FRAME", new Point(10, 0, 0), new Point(20, 0, 0), new Point(20, 0, 1)).execute(model);
		model.setGround("FRAME");

		System.out.println(model.getJoint("J2").getJointVariable(JVAR.THETA).getMagnitude());

		List<LoopVariable> vars = new ArrayList<LoopVariable>();
		// moves one revolute 10 degrees
		// moves another revolute 10 degrees against the movement of the first revolute
		vars.add(new LoopVariable("J2", JVAR.THETA, 10 * (Math.PI / 180)));
		vars.add(new LoopVariable("J3", JVAR.THETA, 10 * (Math.PI / 180)));
		model.findKinematicLoops();
		boolean broke = false;
		// tries to close the loop
		try {
			model.closeLoops(vars);
		} catch (LoopException e) {
			broke = true;
		}
		assertTrue(broke);
	}

	/**
	 * test with 5 revolutes in an M formation
	 * 
	 * @throws IMPException
	 */
	/**
	 * Removed because it is failing due to underconstrainment
	 * 
	 * @Test //@Ignore("failing") public void testMultivariableLoops() throws IMPException { Model m2 = new Model();//
	 *       creates a new model with 5 revolutes in an M m2.addJoint(new Revolute("R1"), "Ground", "1");
	 *       m2.addJoint(new Revolute("R2"), "1", "2"); m2.addJoint(new Revolute("R3"), "2", "3"); m2.addJoint(new
	 *       Revolute("R4"), "3", "4"); m2.addJoint(new Revolute("R5"), "4", "Ground");
	 * 
	 *       new DataZPinCommand(new Point(0, 0, 0), new Point(10, 0, 0), new Point(5, 5, 0), "R1").execute(m2); new
	 *       DataZPinCommand(new Point(5, 5, 0), new Point(0, 0, 0), new Point(10, 0, 0), "R2").execute(m2); new
	 *       DataZPinCommand(new Point(10, 0, 0), new Point(5, 5, 0), new Point(15, 5, 0), "R3").execute(m2); new
	 *       DataZPinCommand(new Point(15, 5, 0), new Point(10, 0, 0), new Point(20, 0, 0), "R4").execute(m2); new
	 *       DataZPinCommand(new Point(20, 0, 0), new Point(15, 5, 0), new Point(0, 0, 0), "R5").execute(m2);
	 * 
	 *       // displays current jvars System.out.println("R1 " +
	 *       m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R2 " +
	 *       m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R3 " +
	 *       m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R4 " +
	 *       m2.getJoint("R4").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R5 " +
	 *       m2.getJoint("R5").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI);
	 * 
	 *       m2.setGround("Ground"); List<LoopVariable> vars2 = new ArrayList<LoopVariable>(); // moves the outer
	 *       revolutes to form a rectangle vars2.add(new LoopVariable("R1", JVAR.THETA, 45 * (Math.PI / 180)));
	 *       vars2.add(new LoopVariable("R2", JVAR.THETA, 0 * (Math.PI / 180))); vars2.add(new LoopVariable("R3",
	 *       JVAR.THETA, 90 * (Math.PI / 180))); vars2.add(new LoopVariable("R4", JVAR.THETA, 0 * (Math.PI / 180)));
	 *       vars2.add(new LoopVariable("R5", JVAR.THETA, 45 * (Math.PI / 180)));
	 * 
	 *       m2.findKinematicLoops(); m2.closeLoops(vars2);
	 * 
	 *       // discover joint variables after closure System.out.println("R1 " +
	 *       m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R2 " +
	 *       m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R3 " +
	 *       m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R4 " +
	 *       m2.getJoint("R4").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); System.out.println("R5 " +
	 *       m2.getJoint("R5").getJointVariable(JVAR.THETA).getMagnitude() * 180 / Math.PI); }
	 */

	/**
	 * Test of 6 revolutes in a tall rectangle
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testMultivariableLoops2() throws IMPException {
		Model m2 = new Model();// creates a new model with 5 revolutes
		RevoluteCommand.CreateZPin("R1", "Ground", "1", new Point(0, 0, 0), new Point(10, 0, 0), new Point(0, 10, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R2", "1", "2", new Point(0, 10, 0), new Point(0, 0, 0), new Point(0, 20, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R3", "2", "3", new Point(0, 20, 0), new Point(0, 10, 0), new Point(10, 20, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R4", "3", "4", new Point(10, 20, 0), new Point(0, 20, 0), new Point(10, 10, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R5", "4", "5", new Point(10, 10, 0), new Point(10, 20, 0), new Point(10, 0, 0)).execute(m2);
		RevoluteCommand.CreateZPin("R6", "5", "Ground", new Point(10, 0, 0), new Point(10, 10, 0), new Point(0, 0, 0)).execute(m2);

		m2.setGround("Ground");
		List<LoopVariable> vars2 = new ArrayList<LoopVariable>();
		// moves the first high revolute 30 degrees and the last high revolute by -30
		vars2.add(new LoopVariable("R2", JVAR.THETA, 30 * (Math.PI / 180)));
		vars2.add(new LoopVariable("R5", JVAR.THETA, -30 * (Math.PI / 180)));
		vars2.add(new LoopVariable("R1", JVAR.THETA, 0));
		vars2.add(new LoopVariable("R6", JVAR.THETA, 0));
		m2.findKinematicLoops();
		m2.closeLoops(vars2);

		// checks that they are all what they should be
		assertEquals(m2.getJoint("R1").getJointVariable(JVAR.THETA).getMagnitude(), 90 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R2").getJointVariable(JVAR.THETA).getMagnitude(), 210 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R3").getJointVariable(JVAR.THETA).getMagnitude(), 60 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R4").getJointVariable(JVAR.THETA).getMagnitude(), 120 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R5").getJointVariable(JVAR.THETA).getMagnitude(), 150 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(m2.getJoint("R6").getJointVariable(JVAR.THETA).getMagnitude(), 90 * (Math.PI / 180), imp.core.Constants.ERROR_TOLERANCE);
	}

	/**
	 * Method for ensuring a known working model continues to pass
	 * 
	 * @throws IMPException
	 */
	@Test
	public void stephensonSixAxisIntegrationRuns() throws IMPException {
		Model model = new Model();

		RevoluteCommand.CreateZPin("A0", "Ground", "2", new Point(41, 27, 0), new Point(50, 27, 0), new Point(81, 132, 0)).execute(model);
		RevoluteCommand.CreateZPin("A", "2", "3", new Point(81, 132, 0), new Point(41, 27, 0), new Point(381, 283, 0)).execute(model);
		RevoluteCommand.CreateZPin("C", "2", "5", new Point(55, 192, 0), new Point(81, 132, 0), new Point(278, 414, 0)).execute(model);
		RevoluteCommand.CreateZPin("B0", "Ground", "4", new Point(374, 85, 0), new Point(474, 85, 0), new Point(381, 283, 0)).execute(model);
		RevoluteCommand.CreateZPin("B", "4", "3", new Point(381, 283, 0), new Point(374, 85, 0), new Point(81, 132, 0)).execute(model);
		RevoluteCommand.CreateZPin("E", "4", "6", new Point(513, 329, 0), new Point(381, 283, 0), new Point(278, 414, 0)).execute(model);
		RevoluteCommand.CreateZPin("D", "6", "5", new Point(278, 414, 0), new Point(513, 329, 0), new Point(55, 192, 0)).execute(model);
		model.setGround("Ground");

		List<LoopVariable> loopVars = new ArrayList<LoopVariable>();
		loopVars.add(new LoopVariable("A0", JVAR.THETA, 1 * (Math.PI / 180)));

		assertEquals(model.getJoint("A0").getJointVariable(JVAR.THETA).getMagnitude(), 1.2068173702852525, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("A").getJointVariable(JVAR.THETA).getMagnitude(), 2.401086001855142, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("C").getJointVariable(JVAR.THETA).getMagnitude(), 1.9450394740128443, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("B0").getJointVariable(JVAR.THETA).getMagnitude(), 1.535457509542245, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("B").getJointVariable(JVAR.THETA).getMagnitude(), -1.0691467909916437, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("E").getJointVariable(JVAR.THETA).getMagnitude(), -.6823859848545019, imp.core.Constants.ERROR_TOLERANCE);
		assertEquals(model.getJoint("D").getJointVariable(JVAR.THETA).getMagnitude(), -2.01138007388143, imp.core.Constants.ERROR_TOLERANCE);
	}

}