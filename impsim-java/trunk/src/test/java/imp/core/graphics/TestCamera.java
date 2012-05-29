package imp.core.graphics;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import imp.core.exceptions.ShaderException;

import java.nio.charset.CharacterCodingException;
import java.util.Random;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author kuszewskij
 * 
 */
public class TestCamera {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Since AbstractModelView is abstract, need a concrete instance of one to test. Only use one because it takes a
	 * while to get the graphics to start. Also prevents problems with trying to create multiple versions of the same
	 * shader name.
	 */
	private static ModelViewTestVersion view;

	private static Camera camera;

	@BeforeClass
	public static void setView() {
		view = new ModelViewTestVersion();// create the ModelView this test class uses. also creates a new camera
		view.startGraphics();
		try {
			Thread.sleep(500);// need to wait a bit to let the graphics that the camera uses initialize.
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		camera = view.getCamera();// set the camera after the model view creates one.
	}
	
	@AfterClass
	public static void closeView() {
		camera = null;
		view.dispose();
	}

	@Test
	public void testConstructorNullParam() {
		try {
			thrown.expect(NullPointerException.class);
			new Camera(null);// try feeding it null
			fail();// Exceptions should be thrown up for the ui to grab. If it doesn't throw an exception then fail the
					// test.
		} catch (ShaderException e) {
			// this was expected
		} catch (CharacterCodingException e) {
			// this was expected
		}
	}

	@Test
	public void testSettingPosition() {
		Random r = new Random();
		int x;
		int y;
		int z;
		for (int i = 0; i < 100; i++) {// test setting the camera to a new position a few times at random locations
			x = r.nextInt(10000);
			y = r.nextInt(10000);
			z = r.nextInt(10000);
			camera.setPosition(new Vec3(x, y, z));
			assertEquals(camera.getPosition().x, x, 0.001f);
			assertEquals(camera.getPosition().y, y, 0.001f);
			assertEquals(camera.getPosition().z, z, 0.001f);
		}
	}

	@Test
	public void testSettingDirection() {
		Random r = new Random();
		int x;
		int y;
		int z;
		for (int i = 0; i < 100; i++) {// test setting the cameras look directions to a few random directions.
			x = r.nextInt(10000);
			y = r.nextInt(10000);
			z = r.nextInt(10000);
			camera.setDirection(new Vec3(x, y, z));
			assertEquals(camera.getDirection().x, x, 0.001f);
			assertEquals(camera.getDirection().y, y, 0.001f);
			assertEquals(camera.getDirection().z, z, 0.001f);
		}
	}

	@Test
	public void testSettingUpVector() {
		Random r = new Random();
		int x;
		int y;
		int z;
		for (int i = 0; i < 100; i++) {// test setting the cameras up vector to point in a few different values.
			x = r.nextInt(10000);
			y = r.nextInt(10000);
			z = r.nextInt(10000);
			camera.setUpVector(new Vec3(x, y, z));
			assertEquals(camera.getUpVector().x, x, 0.001f);
			assertEquals(camera.getUpVector().y, y, 0.001f);
			assertEquals(camera.getUpVector().z, z, 0.001f);
		}
	}

	@Test
	public void testSettingfarFrustrum() {
		Random r = new Random();
		float frustrum;
		for (int i = 0; i < 100; i++) {// test setting the cameras far frustrum to a few different values.
			frustrum = r.nextFloat();
			camera.setFarFrustum(frustrum);
			assertEquals(camera.getFarFrustrum(), frustrum, 0.001f);
		}
	}

	@Test
	public void testSettingNearFrustrum() {
		Random r = new Random();
		float frustrum;
		for (int i = 0; i < 100; i++) {// test setting the cameras near frustrum to a few random values.
			frustrum = r.nextFloat();
			camera.setNearFrustum(frustrum);
			assertEquals(camera.getNearFrustrum(), frustrum, 0.001f);
		}
	}
}