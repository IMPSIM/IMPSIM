/*
 * Author: Jake Kuszewski
 * SDL IMP Team Cycle 12
 * 2/12/2012
 */

package imp.core.graphics;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 * This class tests the AbstractModelView class. It focuses on using its methods to control the camera.
 * 
 * @author kuszewskij
 * 
 */
public class TestAbstractModelView {
	/**
	 * Since AbstractModelView is abstract, need a concrete instance of one to test. Only use one because it takes a
	 * while to get the graphics to start. Also prevents problems with trying to create multiple versions of the same
	 * shader name.
	 */
	private static ModelViewTestVersion view;

	@BeforeClass
	public static void setView() {
		view = new ModelViewTestVersion();// create the ModelView this test class uses.
		view.startGraphics();
		try {
			Thread.sleep(500);// need to wait a bit to let the graphics that the camera uses initialize.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	@Before
	public void setCamPosition() {
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positve y direction
	}
	
	@AfterClass
	public static void closeView() {
		view.dispose();
	}

	@Test
	public void testMoveRight() {
		// facing forwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards along the positive z direction (out of
															// screen).
		view.moveRight(1f);
		Vec3 expectedVec = new Vec3(-1f, 0, 0);// should have moved to the left by one unit relative to a viewer looking
												// into the screen.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing left
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(-1f, 0, 0));// start facing to the left
		view.moveRight(1f);
		expectedVec = new Vec3(0, 0, -1f);// should have moved to into the screen by one unit along the negative z
											// direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing right
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing to the right along the positive x axis.
		view.moveRight(1f);
		expectedVec = new Vec3(0, 0, 1f);// should have moved out of the screen by one unit relative to someone looking
											// into the screen (in the positive z direction).
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing backwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, -1f));// start facing backwards in the negative z direction (into
															// screen).
		view.moveRight(1f);
		expectedVec = new Vec3(1f, 0, 0);// should have moved to the right by one unit
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing up
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 1f, 0));// start facing up.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));// up relative to the camera is out of the screen in the
															// positive z direction.
		view.moveRight(1f);
		expectedVec = new Vec3(1f, 0, 0);// should have moved to the right by one along the positive x axis.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing down
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing down in the negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, -1f));// up relative to the camera is in to the screen in the
															// negative z direction.
		view.moveRight(1f);
		expectedVec = new Vec3(1f, 0, 0);// should have moved to the right by one
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);
	}

	@Test
	public void testMoveLeft() {
		// facing forwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards in the positive z direction.
		view.moveLeft(1f);
		Vec3 expectedVec = new Vec3(1f, 0, 0);// should have moved to the left by one unit in the positive x direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing left
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(-1f, 0, 0));// start facing in the negative x direction.
		view.moveLeft(1f);
		expectedVec = new Vec3(0, 0, 1f);// should have moved to the left by one unit in the positive z axis.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing right
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing in the positive x direction.
		view.moveLeft(1f);
		expectedVec = new Vec3(0, 0, -1f);// should have moved to the left by one unit in the negative z direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing backwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, -1f));// start facing backwards in the negative z direction.
		view.moveLeft(1f);
		expectedVec = new Vec3(-1f, 0, 0);// should have moved to the left by one unit in the negative x direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing up with up vector out of screen
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 1f, 0));// start facing up in the positive y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));
		view.moveLeft(1f);
		expectedVec = new Vec3(-1f, 0, 0);// should have moved to the left by one unit in the negative x direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing down
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing down in the negatve y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, -1f));
		view.moveLeft(1f);
		expectedVec = new Vec3(-1f, 0, 0);// should have moved to the left by one unit in the negative x direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

	}

	@Test
	public void testMoveUp() {
		// facing forwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards in the positive z direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveUp(1f);
		Vec3 expectedVec = new Vec3(0, 1f, 0);// should have moved up by one unit in the positive y direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing left
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(-1f, 0, 0));// start facing in the negative x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveUp(1f);
		expectedVec = new Vec3(0, 1f, 0);// should have moved up by one unit in the positive y direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing right
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing towards the positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveUp(1f);
		expectedVec = new Vec3(0, 1f, 0);// should have moved to the up by one unit along the positive y axis.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing backwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, -1f));// start facing backwards in the negative z direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveUp(1f);
		expectedVec = new Vec3(0, 1f, 0);// should have moved up one unit in the positive y direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing up towards the positive y axis with up vector pointing out of screen towards the positive z axis.
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 1f, 0));// start facing up.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));
		view.moveUp(1f);
		expectedVec = new Vec3(0, 0, 1f);// should have moved up along the positive z axis.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing down
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing down in the negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, -1f));
		view.moveUp(1f);
		expectedVec = new Vec3(0, 0, -1f);// should have moved up by one unit in the negative z direction
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);
	}

	@Test
	public void testMoveDown() {
		// facing forwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards in the positive z direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction
		view.moveDown(1f);
		Vec3 expectedVec = new Vec3(0, -1f, 0);// should have moved down along the negative direction by one
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing left
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(-1f, 0, 0));// start facing along the negative x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveDown(1f);
		expectedVec = new Vec3(0, -1f, 0);// should have moved down by one unit in the negative y direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing right
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing in the positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveDown(1f);
		expectedVec = new Vec3(0, -1f, 0);// should have moved down one unit in the negative y direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing backwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, -1f));// start facing backwards in the negative z direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveDown(1f);
		expectedVec = new Vec3(0, -1f, 0);// should have moved in the negative y direction by one unit.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing up towards the positive y axis with up vector pointing out of screen towards the positive z axis.
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 1f, 0));// start facing up towards the positive y axis.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));
		view.moveDown(1f);
		expectedVec = new Vec3(0, 0, -1f);// should have moved down along the negative z axis.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing down
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing down in the negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, -1f));
		view.moveDown(1f);
		expectedVec = new Vec3(0, 0, 1f);// should have moved along the positive z axis by one unit
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);
	}

	@Test
	public void testMoveForward() {
		// facing forwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction
		view.moveForward(1f);
		Vec3 expectedVec = new Vec3(0, 0, 1f);// should have moved forwards one unit in the z direction
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing left
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(-1f, 0, 0));// start facing in the negative x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveForward(1f);
		expectedVec = new Vec3(-1f, 0, 0);// should have moved one unit in the negative x direction
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing right
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing in the positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveForward(1f);
		expectedVec = new Vec3(1f, 0, 0);// should have moved one unit in the positive x direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing backwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, -1f));// start facing backwards in the negative z direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveForward(1f);
		expectedVec = new Vec3(0, 0, -1f);// should have moved forwards one unit in the negative z direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing up towards the positive y axis with up vector pointing out of screen towards the positive z axis.
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 1f, 0));// start facing up.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));
		view.moveForward(1f);
		expectedVec = new Vec3(0, 1f, 0);// should have moved forwards in the positive y axis one unit.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing down
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing down in the negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, -1f));
		view.moveForward(1f);
		expectedVec = new Vec3(0, -1f, 0);// should have moved one unit in the negative y direction one unit.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);
	}

	@Test
	public void testMoveBackwards() {
		// facing forwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positve y direction
		view.moveBackward(1f);
		Vec3 expectedVec = new Vec3(0, 0, -1f);// should have moved back along the negative z direction by one
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .001);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing left
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(-1f, 0, 0));// start facing in the negative x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveBackward(1f);
		expectedVec = new Vec3(1f, 0, 0);// should have moved to the right one unit in the positive x direction
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing right
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing in the positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveBackward(1f);
		expectedVec = new Vec3(-1f, 0, 0);// should have moved back one unit in the negative x direction.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing backwards
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, -1f));// start facing in the negative z direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));
		view.moveBackward(1f);
		expectedVec = new Vec3(0, 0, 1f);// should have moved back one unit in the positive z direction
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing up towards the positive y axis with up vector pointing out of screen towards the positive z axis.
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 1f, 0));// start facing up in the positive y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));
		view.moveBackward(1f);
		expectedVec = new Vec3(0, -1f, 0);// should have moved up along the negative z axis one unit.
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);

		// facing down
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing down in the negative y axis.
		view.getCamera().setUpVector(new Vec3(0, 0, -1f));
		view.moveBackward(1f);
		expectedVec = new Vec3(0, 1f, 0);// should have moved along the positive y axis by one unit
		assertEquals(view.getCamera().getPosition().x, expectedVec.x, .1);
		assertEquals(view.getCamera().getPosition().y, expectedVec.y, .001);
		assertEquals(view.getCamera().getPosition().z, expectedVec.z, .001);
	}

	@Test
	public void testSmoothMoveRight() {
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		Vec3 startPos = view.getCamera().getPosition();
		view.moveSmoothRight(1f);
		try {
			Thread.sleep(100);// let the camera move a bit.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		assertTrue(startPos.x > view.getCamera().getPosition().x);

		view.stopSmoothRightMovement();
		Vec3 end = view.getCamera().getPosition();// the position of the camera after it stops moving.
		try {
			Thread.sleep(50);// let the camera get some time to stop moving.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertEquals(end.x, view.getCamera().getPosition().x, 0.001f);
	}

	@Test
	public void testSmoothMoveLeft() {
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		Vec3 startPos = view.getCamera().getPosition();
		view.moveSmoothLeft(1f);
		try {
			Thread.sleep(100);// let the camera move a bit.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertTrue(startPos.x < view.getCamera().getPosition().x);

		view.stopSmoothLeftMovement();
		Vec3 end = view.getCamera().getPosition();// the position of the camera after it stops moving.
		try {
			Thread.sleep(50);// let the camera get some time to stop moving.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertEquals(end.x, view.getCamera().getPosition().x, 0.001f);
	}

	@Test
	public void testSmoothUp() {

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positve y direction

		Vec3 startPos = view.getCamera().getPosition();
		view.moveSmoothUp(1f);
		try {
			Thread.sleep(100);// let the camera move a bit.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertTrue(startPos.y < view.getCamera().getPosition().y);

		view.stopSmoothUpMovement();
		Vec3 end = view.getCamera().getPosition();// the position of the camera after it stops moving.
		try {
			Thread.sleep(50);// let the camera get some time to stop moving.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertEquals(end.y, view.getCamera().getPosition().y, 0.001f);
	}

	@Test
	public void testSmoothDown() {

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		Vec3 startPos = view.getCamera().getPosition();
		view.moveSmoothDown(1f);
		try {
			Thread.sleep(100);// let the camera move a bit.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertTrue(startPos.y > view.getCamera().getPosition().y);

		view.stopSmoothDownMovement();
		Vec3 end = view.getCamera().getPosition();// the position of the camera after it stops moving.
		try {
			Thread.sleep(50);// let the camera get some time to stop moving.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertEquals(end.y, view.getCamera().getPosition().y, 0.001f);
	}

	@Test
	public void testSmoothForward() {

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positve y direction

		Vec3 startPos = view.getCamera().getPosition();
		view.moveSmoothForward(1f);
		try {
			Thread.sleep(100);// let the camera move a bit.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertTrue(startPos.z < view.getCamera().getPosition().z);

		view.stopSmoothForwardMovement();
		Vec3 end = view.getCamera().getPosition();// the position of the camera after it stops moving.
		try {
			Thread.sleep(50);// let the camera get some time to stop moving.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertEquals(end.z, view.getCamera().getPosition().z, 0.001f);
	}

	@Test
	public void testSmoothBackward() {
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positve y direction

		Vec3 startPos = view.getCamera().getPosition();
		view.moveSmoothBackward(1f);
		try {
			Thread.sleep(100);// let the camera move a bit.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertTrue(startPos.z > view.getCamera().getPosition().z);

		view.stopSmoothBackwardMovement();
		Vec3 end = view.getCamera().getPosition();// the position of the camera after it stops moving.
		try {
			Thread.sleep(50);// let the camera get some time to stop moving.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		assertEquals(end.z, view.getCamera().getPosition().z, 0.001f);
	}

	@Test
	public void testRotatingRight() {
		// camera starts facing towards positive z direction and should now be facing the negative x direction after
		// rotating right 90 degrees.
		view.rotateRight((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should still be pointed along
																				// the positive y axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(1f, 0, 0));// cameras up is in the positive x direction

		// camera starts facing towards positive z direction and should now be facing the positive y direction after
		// rotating left 90 degrees.
		view.rotateRight((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 1f, .001f);// up vector should still be pointed along
																				// the positive x axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, -1f, 0));// cameras up is in the negative y direction

		// camera starts facing towards positive z direction and should now be facing the positive x direction after
		// rotating left 90 degrees.
		view.rotateRight((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should still be pointed along
																				// the negative y axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}

	@Test
	public void testRotatingLeft() {
		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positve y direction

		// camera starts facing towards positive z direction and should now be facing the positive x direction after
		// rotating left 90 degrees.
		view.rotateLeft((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should still be pointed along
																				// the positive y axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(1f, 0, 0));// cameras up is in the positive x direction

		// camera starts facing towards positive z direction and should now be facing the negative y direction after
		// rotating left 90 degrees.
		view.rotateLeft((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 1f, .001f);// up vector should still be pointed along
																				// the positive x axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, 0, 1));// start facing forwards.
		view.getCamera().setUpVector(new Vec3(0, -1f, 0));// cameras up is in the negative y direction

		// camera starts facing towards positive z direction and should now be facing the negative x direction after
		// rotating left 90 degrees.
		view.rotateLeft((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should still be pointed along
																				// the negative y axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}

	@Test
	public void testRotatingUp() {
		view.rotateUp((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should now be pointed along
																				// the negative z axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, -1f, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		// camera starts facing towards positive x direction and should now be facing the positive y direction after
		// rotating up 90 degrees.
		view.rotateUp((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, -1f, .001f);// up vector should be pointed along the
																				// negative x axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));// cameras up is in the positive z direction

		// camera starts facing towards negative y direction and should now be facing the positive z direction after
		// rotating up 90 degrees.
		view.rotateUp((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 1f, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should still be pointed along
																				// the negative y axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}

	@Test
	public void testRotatingDown() {
		view.rotateDown((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should now be pointed along
																				// the positive z axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 1f, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		// camera starts facing towards positive x direction and should now be facing the negative y direction after
		// rotating down 90 degrees.
		view.rotateDown((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 1f, .001f);// up vector should be pointed along the
																				// positive x axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));// cameras up is in the positive z direction

		// camera starts facing towards negative y direction and should now be facing the negative z direction after
		// rotating down 90 degrees.
		view.rotateDown((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, -1f, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// up vector should still be pointed along
																				// the negative y axis.
		assertEquals(view.getCamera().getUpVector().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}

	@Test
	public void testRotatingClockwise() {
		view.rollClockwise((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0f, .001f);// should still be pointed in the same
																				// direction.
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 1f, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, -1f, .001f);// but the up vector should be pointed
																				// towards the negative x axis now.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		view.rollClockwise((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 1f, .001f);// After rolling the camera should still
																				// be looking in the same direction.
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// but the up vector should be pointing in
																				// the positize z axis now.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 1f, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));// cameras up is in the positive z direction

		view.rollClockwise((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);// After rolling the camera should still
																				// be looking in the same direction.
		assertEquals(view.getCamera().getDirection().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, -1f, .001f);// but now the up vector should be
																				// pointed in the negative x direction
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}

	@Test
	public void testRotatingCounterClockwise() {
		view.rollCounterClockwise((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0f, .001f);// should still be pointed in the same
																				// direction.
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 1f, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 1f, .001f);// but the up vector should be pointed
																				// towards the positive x axis now.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(1f, 0, 0));// start facing positive x direction.
		view.getCamera().setUpVector(new Vec3(0, 1f, 0));// cameras up is in the positive y direction

		view.rollCounterClockwise((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 1f, .001f);// After rolling the camera should still
																				// be looking in the same direction.
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// but the up vector should be pointing in
																				// the negative z axis now.
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, -1f, .001f);

		view.getCamera().setPosition(new Vec3(0, 0, 0));// start at origin
		view.getCamera().setDirection(new Vec3(0, -1f, 0));// start facing negative y direction.
		view.getCamera().setUpVector(new Vec3(0, 0, 1f));// cameras up is in the positive z direction

		view.rollCounterClockwise((float) ((Math.PI / 180.0) * 90.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 0, .001f);// After rolling the camera should still
																				// be looking in the same direction.
		assertEquals(view.getCamera().getDirection().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 1f, .001f);// but now the up vector should be pointed
																				// in the positive x direction
		assertEquals(view.getCamera().getUpVector().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}

	@Test
	public void testRotatingArbitraryAxis() {
		// rotate about an axis that points at a 45 degree angle from the x axis
		view.getCamera().rotateAboutArbitraryAxis(new Vec3(1f, 0, 1f), (float) ((Math.PI / 180.0) * 180.0));
		assertEquals(view.getCamera().getDirection().normalize().x, 1f, .001f);// The camera should have rotated 180
																				// degrees so that it now points along
																				// the x direction
		assertEquals(view.getCamera().getDirection().normalize().y, 0, .001f);
		assertEquals(view.getCamera().getDirection().normalize().z, 0, .001f);

		assertEquals(view.getCamera().getUpVector().normalize().x, 0, .001f);// The cameras up vector should now be in
																				// the negative y direction.
		assertEquals(view.getCamera().getUpVector().normalize().y, -1f, .001f);
		assertEquals(view.getCamera().getUpVector().normalize().z, 0, .001f);
	}
}
