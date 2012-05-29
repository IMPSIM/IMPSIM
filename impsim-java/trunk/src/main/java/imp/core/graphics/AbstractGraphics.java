package imp.core.graphics;

import imp.core.exceptions.ShaderException;

import java.nio.charset.CharacterCodingException;
import java.util.ArrayList;
import java.util.List;

import javax.media.opengl.GL;
import javax.media.opengl.GL3;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLEventListener;



/**
 * This class is meant to define the graphics engine of the IMP program such that low end graphics calls are abstracted away from higher level design
 * @author kreierj
 * @version 1
 */
public abstract class AbstractGraphics implements GLEventListener{

	/**
	 * Camera object holding all projection matrices and lookAt calculations
	 */
	private Camera cam;

	/**
	 * Object from which graphics data is obtained
	 */
	private AbstractDataSource ds;

	/**
	 * Data source flagged as needed to have its objects disposed of
	 */
	private AbstractDataSource oldDS;

	private static List<Exception> exceptions;

	/**
	 * Default constructor needed for basic initialization
	 */
	public AbstractGraphics(){

		//initialize camera and data source
		cam = null;
		ds = null;
		oldDS = null;
		exceptions = new ArrayList<Exception>();

	}

	private void setUpLights(GL3 gl){
		//init light properties
		int cameraShaderProgram = Shader.getShaderProgram(Camera.CAMERA_SHADER_NAME);
		float[] lightPosition = {6.0f,3.0f,-3.0f,1.0f};//the position of light0
		float[] lightColorAmbient = {0.9f, 1.0f, 1.0f, 1f};//ambient color
		float[] lightColorSpecular = {0.8f, 0.8f, 0.8f, 1f};//specular color
		float[] lightColorDiffuse = {0.8f, 0.8f, 0.8f, 1f};//specular color
		int light0Pos = gl.glGetUniformLocation(cameraShaderProgram, "light0Uniform.position");
		int light0Ambient = gl.glGetUniformLocation(cameraShaderProgram, "light0Uniform.ambient");
		int light0Specular = gl.glGetUniformLocation(cameraShaderProgram, "light0Uniform.specular");
		int light0Diffuse = gl.glGetUniformLocation(cameraShaderProgram, "light0Uniform.diffuse");
		gl.glUniform4fv(light0Pos,1,lightPosition,0);
		gl.glUniform4fv(light0Ambient,1,lightColorAmbient,0);
		gl.glUniform4fv(light0Specular,1,lightColorSpecular,0);
		gl.glUniform4fv(light0Diffuse,1,lightColorDiffuse,0);

		//use a second light
		float[] lightPosition2 = {-6.0f,-3.0f,3.0f,1.0f};//the position of light1
		float[] lightColorAmbient2 = {0.9f, 0.9f, 0.9f, 1f};//ambient color
		float[] lightColorSpecular2 = {0.8f, 0.8f, 0.8f, 1f};//specular color
		float[] lightColorDiffuse2 = {0.8f, 0.8f, 0.8f, 1f};//specular color
		int light1Pos = gl.glGetUniformLocation(cameraShaderProgram, "light1Uniform.position");
		int light1Ambient = gl.glGetUniformLocation(cameraShaderProgram, "light1Uniform.ambient");
		int light1Specular = gl.glGetUniformLocation(cameraShaderProgram, "light1Uniform.specular");
		int light1Diffuse = gl.glGetUniformLocation(cameraShaderProgram, "light1Uniform.diffuse");
		gl.glUniform4fv(light1Pos,1,lightPosition2,0);
		gl.glUniform4fv(light1Ambient,1,lightColorAmbient2,0);
		gl.glUniform4fv(light1Specular,1,lightColorSpecular2,0);
		gl.glUniform4fv(light1Diffuse,1,lightColorDiffuse2,0);
	}

	@Override
	public final void display(GLAutoDrawable g) {
		synchronized(this){
			GL3 gl = g.getGL().getGL3();

			//remove old objects
			disposeOld(gl);

			if(ds != null){ //make sure there is something to get data from

				ds.update(gl);


				//get Objects
				List<AbstractGLObject> objects = null;

				objects = this.getGLObjects();


				//clear color
				gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				gl.glClearDepth(1.0f);
				gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);


				//have camera calculate its projection matrix and bind its uniforms
				cam.lookAt(gl);

				//bind camera shader program
				gl.glUseProgram(Shader.getShaderProgram(Camera.CAMERA_SHADER_NAME));

				//for each object
				for (int i = 0; i < objects.size(); i++){
					//draw the object
					setUpLights(gl);
					objects.get(i).draw(gl);
				}

				//unbind shader program
				gl.glUseProgram(0);
			}
		}

	}

	@Override
	public final void dispose(GLAutoDrawable g) {

		GL3 gl = g.getGL().getGL3();

		//get the list of objects from the data source
		List<AbstractGLObject> objects = null;
		if (ds != null){
			objects = ds.getObjects();
			if (objects != null){
				//for each object
				for (int i = 0; i < objects.size(); i++){
					//dispose the object
					objects.get(i).dispose(gl);
				}
			}
		}

		Shader.dispose();
	}

	@Override
	public final void init(GLAutoDrawable g) {

		GL3 gl = g.getGL().getGL3();
		System.out.println("Initializing " + gl.glGetString(GL.GL_VENDOR) + " OpenGL " + gl.glGetString(GL.GL_VERSION));


		//		//initialize culling properties 
		gl.glEnable(GL.GL_CULL_FACE);   
		gl.glCullFace(GL.GL_BACK);      
		gl.glFrontFace(GL.GL_CCW);
		//		gl.glDisable(GL.GL_CULL_FACE);//face culling disbaled

		//initialize camera
		try {
			cam = new Camera(gl);
		} catch (ShaderException e) {
			exceptions.add(e);
		} catch (CharacterCodingException e) {
			exceptions.add(e);
		}
		
		
		System.out.println("Initialization Complete");
	}

	@Override
	public final void reshape(GLAutoDrawable g, int x, int y, int width, int height) {
		GL3 gl = g.getGL().getGL3();

		//update camera with new information
		cam.setWindowWidth(width);
		cam.setWindowHeight(height);

		cam.updatePerspective(gl);


	}

	/**
	 * Returns the camera object driving the viewport
	 * @return
	 */
	public Camera getCamera(){
		return cam;
	}

	/**
	 * Returns the list of GLObjects being drawn
	 * @return
	 * @throws Exception 
	 */
	public List<AbstractGLObject> getGLObjects() throws NullPointerException{
		if (ds != null){
			return ds.getObjects();
		}
		else{
			throw new NullPointerException("No graphics data source set");
		}

	}

	/**
	 * Sets the command holder from which data will be obtained
	 * @param newCommandHolder
	 */
	public void setGraphicsDataSource(AbstractDataSource newDataSource){
		synchronized(this){
			oldDS = ds; //flag current data source as needing to be disposed of
			ds = newDataSource; //set the new reference
		}
	}

	/**
	 * Disposes of all objects maintained by the oldDS object
	 * @param gl
	 */
	private void disposeOld(GL3 gl){
		List<AbstractGLObject> objects = null;
		if (oldDS != null){
			objects = oldDS.getObjects();
			if (objects != null){
				//for each object
				for (int i = 0; i < objects.size(); i++){
					//dispose the object
					objects.get(i).dispose(gl);
				}
			}

			oldDS = null;
		}
	}



	/**
	 * Used for encapsulating all exceptions outside of GL method calls. Returns if there are pending exceptions 
	 * awaiting handling
	 * @return True if there are pending exceptions
	 */
	public static boolean hasExceptions(){
		if(exceptions.size() > 0){
			return true;
		}
		else{
			return false;
		}
	}

	/**
	 * Throws all exceptions that are pending
	 * @throws ShaderException if there were any problems with shader initialization
	 * @throws CharacterCodingException if there were any character encoding problems
	 */
	public static void throwExceptions() throws ShaderException, CharacterCodingException{

		for (int i = 0; i < exceptions.size(); i++){
			Exception e = exceptions.get(i);
			if (e instanceof ShaderException){
				throw (ShaderException)e;
			}
			else if (e instanceof CharacterCodingException){
				throw (CharacterCodingException)e;
			}
		}
	}
}
