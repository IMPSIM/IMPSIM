package imp.core.graphics;

import imp.core.exceptions.ShaderException;

import java.nio.charset.CharacterCodingException;

import javax.media.opengl.GL3;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.GLException;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

public class TestShader extends AbstractGraphics implements GLEventListener {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * good GLSL code defining a vertex shader.
	 */
	private final String[] goodVertexShaderGLSL = { "#version 330 \n" + "layout (location = 0) in vec4 in_Position;\n" + "layout (location = 1) in vec4 in_Color;\n"
			+ "out vec4 passColor;\n" + "uniform mat4 modelToWorld;\n" + "uniform mat4 worldToCamera;\n" + "uniform mat4 cameraToClip;\n"
			+ "void main(void) {\n" + "	gl_Position = cameraToClip * worldToCamera * modelToWorld * in_Position;\n" + "	passColor = in_Color;\n" + "}\n" };

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

	@AfterClass
	public static void closeView() {
		view.dispose();
	}



	@Test
	public void testGettingExistingProgram() {
		Shader.getShaderProgram(Camera.CAMERA_SHADER_NAME);
	}

	@Test
	public void testGettingNonexistingProgram() {
		thrown.expect(NullPointerException.class);
		Shader.getShaderProgram("blah");
	}
}
