package imp.core.graphics;

import imp.core.exceptions.ShaderException;
import imp.core.graphics.Mat4;
import imp.core.graphics.Vec3;

import java.nio.charset.CharacterCodingException;
import java.util.LinkedList;

import javax.media.opengl.GL;
import javax.media.opengl.GL3;

public class Camera {

	/**
	 * Position of the camera
	 */
	private Vec3 position;

	/**
	 * Direction the camera is looking
	 */
	private Vec3 direction;

	/**
	 * Direction above the camera
	 */
	private Vec3 up;

	/**
	 * Near frustum
	 */
	private float near;

	/**
	 * Far frustum
	 */
	private float far;

	/**
	 * GLCanvas height
	 */
	private int windowHeight;

	/**
	 * GLCavas width
	 */
	private int windowWidth;

	/**
	 * handle to "cameraToClip"
	 */
	int cameraToClipUniform;

	/**
	 * handle to "cameraToClip"
	 */
	int modelToWorldUniform;

	/**
	 * handle to "useOrientationMatrix"
	 */
	private static int useOrientationMatrixHandle;

	/**
	 * handle to "up"
	 */
	int cameraUpUniform;


	/**
	 * handle to "direction"
	 */
	int cameraDirectionUniform;

	/**
	 * handle to "direction"
	 */
	int cameraPositionUniform;

	/**
	 * handle to the orientationMatrix used for drawing meshes.
	 */
	private static int orientationMatrix;
	
	/**
	 * handle to the boolean used to indicate if the object being drawn should be drawn using lighting to show 3 dimensions.
	 */
	private static int draw3DUniform = 0;
	
	/**
	 * This vector represents the velocity vector for the cameras forward movement.
	 */
	Vec3 forwardVelocity = new Vec3(0,0,0);

	/**
	 * This vector represents the velocity vector for the cameras backward movement.
	 */
	Vec3 backVelocity = new Vec3(0,0,0);

	/**
	 * This vector represents the velocity vector for the cameras left movement.
	 */
	Vec3 leftVelocity = new Vec3(0,0,0);

	/**
	 * This vector represents the velocity vector for the cameras right movement.
	 */
	Vec3 rightVelocity = new Vec3(0,0,0);

	/**
	 * This vector represents the velocity vector for the cameras up movement.
	 */
	Vec3 upVelocity = new Vec3(0,0,0);

	/**
	 * This vector represents the velocity vector for the cameras down movement.
	 */
	Vec3 downVelocity = new Vec3(0,0,0);

	/**
	 * The GL3 that this camera uses to set uniforms in the one and only camera shader.
	 */
	private static GL3 g;

	/**
	 * The thread that controls the smooth movement of the camera.
	 */
	private Thread movementThread = new Thread(new Runnable(){

		@Override
		public void run() {
			int timeBetween = 10;
			Vec3 noMove = new Vec3(0,0,0);

			//while the cameras doesn't have any where to move.
			while(backVelocity.equals(noMove)==false
					&& forwardVelocity.equals(noMove)==false
					&& leftVelocity.equals(noMove)==false
					&& rightVelocity.equals(noMove)==false
					&& upVelocity.equals(noMove)==false
					&& downVelocity.equals(noMove)==false){

				position = position.plus(backVelocity);
				position = position.plus(forwardVelocity);
				position = position.plus(rightVelocity);
				position = position.plus(leftVelocity);
				position = position.plus(upVelocity);
				position = position.plus(downVelocity);
				try {
					Thread.sleep(timeBetween);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

	});

	/**
	 * The GLSL code defining the vertex shader. It will use the transformation matrices passed in as uniforms to 
	 * show the world from the cameras view.
	 * @edit: kuszewski: added the look at math into this shader. The world to camera matrix is now calculated in the shader. 
	 */
	private String[] vertexShaderGLSL = { 
			"#version 330 \n" +
					"layout (location = 0) in vec4 in_Position;\n" +
					"layout (location = 1) in vec4 in_Color;\n" +
					"layout (location = 2) in vec4 in_Normal;\n" +
					
					"struct lightStruct{\n"+//custom structure defining lights
					"	vec4 position;\n"+
					"	vec4 ambient;\n"+
					"	vec4 diffuse;\n"+
					"	vec4 specular;\n"+
					"	vec4 modelAmbient;\n"+
					"};\n"+
					
					"struct materialStruct{\n"+//custom structure defining materials
					"	vec4 ambient;\n"+
					"	vec4 diffuse;\n"+
					"	vec4 emissive;\n"+
					"	vec4 specular;\n"+
					"	float shininess;\n"+
					"};\n"+

					//uniforms that are supplied by the outside.
					"uniform mat4 modelToWorld;\n" +
					"uniform mat4 cameraToClip;\n" +
					"uniform mat4 orientationMatrix;\n" +
					"uniform bool useOrientationMatrix;\n" +
					"uniform vec3 direction;\n"+
					"uniform vec3 up;\n"+
					"uniform vec3 position;\n"+
					"uniform int draw3D;\n"+
					"uniform lightStruct light0Uniform;\n"+
					"uniform lightStruct light1Uniform;\n"+
					"uniform materialStruct materialUniform;\n"+

					//values passed on to the fragment shader.
					"out vec4 passColor;\n" +
					"flat out int color3D;\n"+
					"out lightStruct light0;\n"+
					"out lightStruct light1;\n"+
					"out materialStruct material;\n"+
					"out vec4 diffuse,diffuse2;\n"+
					"out vec4 halfVector,halfVector2;\n"+
					"out vec4 normal;\n"+
					"out vec4 lightPosition,lightPosition2;\n"+
					
					"void main(void) {\n" +
					"	vec4 ambient,ambient2,globalAmbient;\n"+
					
					//set up the world to Camera matrix used by the lighting calculations and orientating the model.
					"   mat4 rotationMat = mat4(1.0);\n"+
					"   rotationMat[0] = vec4(normalize(cross(direction.xyz,up.xyz)),0.0);\n"+
					"   rotationMat[1] = vec4(normalize(up),0.0);\n"+
					"   rotationMat[2] = vec4(-1.0 * direction,0.0);\n"+
					"   mat4 translationMat = mat4(1.0);\n"+
					"   translationMat[3] = vec4(position*-1.0,0.0);\n"+
					"   mat4 worldToCamera = transpose(rotationMat) * translationMat;\n"+

					"   color3D = draw3D;\n"+
					"if(draw3D == 1){\n"+//only 3D objects need lighting, if its not 3d then use the flat colors given in the passed in buffer.
						//lighting
					"  	light0 = light0Uniform;\n"+
					"  	light1 = light1Uniform;\n"+
					"  	material = materialUniform;\n"+
					"  	normal =  normalize(worldToCamera * modelToWorld * orientationMatrix * in_Normal);\n"+
					"  	lightPosition = normalize(light0.position);\n"+
					"  	lightPosition2 = normalize(light1.position);\n"+

						//calculate diffuse and ambient color from light 0
					"  	diffuse = in_Color * light0.diffuse;\n"+
					"  	ambient = material.ambient * light0.ambient;\n"+

						//calculate diffuse and ambient color from light 1
					"  	diffuse2 = in_Color * light1.diffuse;\n"+
					" 	 ambient2 = material.ambient * light1.ambient;\n"+

					"  	globalAmbient = material.ambient * vec4(.2,.2,.2,1.0);\n"+
					
					"  	halfVector2 = (vec4(position,0.0) - (orientationMatrix *in_Position)) - (vec4(position,0.0) - lightPosition2);\n"+//calculate the halfVector between the camera's position and the direction of the two light sources.	
					"  	halfVector = (vec4(position,0.0) - (orientationMatrix *in_Position)) - (vec4(position,0.0) - lightPosition);\n"+	

					"  	gl_FrontColor = (globalAmbient+ambient+ambient2);\n"+
					"}else {\n"+
					" 	gl_FrontColor = in_Color;\n"+
					"}\n"+
					//end lighting
					
					"	if (useOrientationMatrix){\n" +
					"		gl_Position = cameraToClip * worldToCamera * modelToWorld * orientationMatrix * in_Position;\n" +
					"	} else { \n" +
					"		gl_Position = cameraToClip * worldToCamera * modelToWorld * in_Position;\n" +
					"	}" +
					"	passColor = vec4(gl_FrontColor.xyz,1.0);\n" +
					"}\n" 
	};




	/**
	 * The GLSL fragment shader code. It just colors the shapes based on the color attribute defined in the vertex array.
	 */
	private String[] fragmentShaderGLSL = {
			"#version 330\n" +
					"struct lightStruct{\n"+//custom structure defining lights
					"	vec4 position;\n"+
					"	vec4 ambient;\n"+
					"	vec4 diffuse;\n"+
					"	vec4 specular;\n"+
					"	vec4 modelAmbient;\n"+
					"};\n"+
					"struct materialStruct{\n"+//custom structure defining materials
					"	vec4 ambient;\n"+
					"	vec4 diffuse;\n"+
					"	vec4 emissive;\n"+
					"	vec4 specular;\n"+
					"	float shininess;\n"+
					"};\n"+
					
					//values passed in from the vertexShader
					"in vec4 diffuse,diffuse2;\n"+
					"in vec4 halfVector,halfVector2;\n"+
					"in vec4 normal;\n"+
					"in vec4 lightPosition,lightPosition2;\n"+
					"in vec4 passColor;\n" +
					"in lightStruct light0;\n"+
					"in lightStruct light1;\n"+
					"in materialStruct material;\n"+
					"flat in int color3D;\n"+
					
					"out vec4 out_Color;\n" +//the final color of the pixle
					
					"void main(void) {\n" +
					"vec4 color = passColor;\n"+
					"if(color3D == 1){\n"+
					"  	float cos = max(dot(normal, lightPosition), 0.0);\n"+
					"  	float cos2 = max(dot(normal, lightPosition2), 0.0);\n"+
					"  	color += (cos * diffuse)+(cos2 * diffuse2);\n"+//the diffuse color is set
					"	if (cos > 0.0) {\n"+
							//calculate the specular component for light 0
					"		float NdotHV = max(dot(normal.xyz, halfVector.xyz),0.0);\n"+
					"		vec4 specular = material.specular * light0.specular * pow(NdotHV,material.shininess);\n"+
					"  	 	color += specular;\n"+
						"}\n"+
					
					"	if (cos2 > 0.0) {\n"+
							//calculate the specular component for light 1
					"		float NdotHV2 = max(dot(normal.xyz, halfVector2.xyz),0.0);\n"+
					"		vec4 specular2 = material.specular * light1.specular * pow(NdotHV2,material.shininess);\n"+
					"		color+=specular2;\n"+
					"	}\n"+
					"}\n"+
					"	out_Color = color;\n" +
					"}\n"
	};

	/**
	 * This is the name of the camera shader program
	 */
	public static final String CAMERA_SHADER_NAME = "CAMERA_SHADER";

	/**
	 * Initializes the camera
	 * @param gl
	 * @throws CharacterCodingException 
	 * @throws ShaderException If the shader could not be compiled
	 */
	public Camera(GL3 gl) throws ShaderException, CharacterCodingException{

		g=gl;
		//initialize the cameras attributes to default values.

		near = 1.0f;
		far = 1000.0f;

		up = new Vec3(0,1,0);
		position = new Vec3(0,0,0);
		direction = new Vec3(0,0,-1);

		initializeCamera(gl);
		draw3D(false);
	}

	/**
	 * Performs gl initializations
	 * @param gl
	 * @throws CharacterCodingException if the shader could not be created and complied. 
	 * @throws ShaderException 
	 */
	private void initializeCamera(GL3 gl) throws ShaderException, CharacterCodingException{

		//initialize depth properties
		gl.glEnable(GL.GL_DEPTH_TEST);
		gl.glDepthMask(true);
		gl.glDepthFunc(GL.GL_LEQUAL);
		gl.glDepthRange(0.0f, 1.0f);
		gl.glEnable(GL3.GL_DEPTH_CLAMP);

		//initialize blending properties
		gl.glEnable(GL.GL_BLEND);
		gl.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);

		//create camera shader
		//compile the shader code
		try{
			int vertexShader = Shader.compileShader(gl,GL3.GL_VERTEX_SHADER , vertexShaderGLSL);//NOTE: the camera is not close enough to the GUI, so throw any exceptions up until they can be caught
			int fragmentShader = Shader.compileShader(gl,GL3.GL_FRAGMENT_SHADER,fragmentShaderGLSL);//by a level of the code that can directly inform the user via the GUI?

			//link shaders into a program
			LinkedList<Integer> tempShaderParam = new LinkedList<Integer>();
			tempShaderParam.add(vertexShader);
			tempShaderParam.add(fragmentShader);
			Shader.createShaderProgram(gl,tempShaderParam, CAMERA_SHADER_NAME);

			//tell the GL3 object to use the shader program
			gl.glUseProgram(Shader.getShaderProgram(CAMERA_SHADER_NAME));

			//grab the index of the uniforms
			int cameraShaderProgram = Shader.getShaderProgram(CAMERA_SHADER_NAME);
			modelToWorldUniform = gl.glGetUniformLocation(cameraShaderProgram, "modelToWorld");
			cameraToClipUniform = gl.glGetUniformLocation(cameraShaderProgram, "cameraToClip");
			orientationMatrix = gl.glGetUniformLocation(cameraShaderProgram, "orientationMatrix");
			useOrientationMatrixHandle = gl.glGetUniformLocation(cameraShaderProgram, "useOrientationMatrix");


			cameraDirectionUniform = gl.glGetUniformLocation(cameraShaderProgram, "direction");
			cameraUpUniform = gl.glGetUniformLocation(cameraShaderProgram, "up");
			cameraPositionUniform = gl.glGetUniformLocation(cameraShaderProgram, "position");
			

			draw3DUniform = gl.glGetUniformLocation(cameraShaderProgram, "draw3D");

			Mat4 m = new Mat4(1.0f);
			g.glUniformMatrix4fv(modelToWorldUniform, 1,false, m.raw(),0);
			g.glUniformMatrix4fv(cameraToClipUniform, 1,false, m.raw(),0);
			g.glUniformMatrix4fv(orientationMatrix, 1,false, m.raw(),0);
		}catch(Exception e){
			e.printStackTrace();
		}
		finally{
			gl.glUseProgram(0);
		}

	}

	/**
	 * The method will rotate the camera about an arbitrary axis passed to it.
	 * @param axis the axis relative to rotate the camera about.
	 * @param degrees the degrees to rotate by.
	 */
	public void rotateAboutArbitraryAxis(Vec3 axis, float degrees){
		axis = axis.normalize();
		Vec3 lookdir = getDirection();//get the current direction the camera is looking.

		Vec3 upVec = getUpVector();//get which way is pointing up relative to the camera.

		//set up the matrix that will hold the cameras direction vector, and the cameras up vector.
		Mat4 vecs = new Mat4(0);		
		vecs.set(0, 0, lookdir.x);
		vecs.set(0, 1, lookdir.y);
		vecs.set(0, 2, lookdir.z);
		vecs.set(0, 3, 0f);

		vecs.set(1, 0, upVec.x);
		vecs.set(1, 1, upVec.y);
		vecs.set(1, 2, upVec.z);
		vecs.set(1, 3, 0f);

		float sin = (float) Math.sin(degrees);//calculate sin and cos once ans save the value to prevent having to call it several times later.
		float cos = (float) Math.cos(degrees);

		float ux = axis.x;//the x value of the normalized axis vector
		float uy = axis.y;//the y value of the normalized axis vector
		float uz = axis.z;//the z value of the normalized axis vector

		//set up the rotation matrix
		Mat4 rotateMat = new Mat4(new float[]{
				(cos + (ux*ux*(1-cos))), 	((ux*uy*(1-cos))-(uz*sin)),	((ux*uz*(1-cos))+(uy*sin)),	0f,
				uy*ux*(1-cos)+uz*sin,		cos+uy*uy*(1-cos),			uy*uz*(1-cos)-ux*sin,		0f,
				uz*ux*(1-cos)-uy*sin,		uz*uy*(1-cos)+ux*sin,		cos+uz*uz*(1-cos),			0f,
				0f,0f,0f,1f
		});

		vecs = rotateMat.multiply(vecs);//rotate the cameras up and direction vectors.

		//now reset the cameras vector to their new values
		setUpVector(new Vec3(vecs.raw()[4],vecs.raw()[5],vecs.raw()[6]));
		setDirection(new Vec3(vecs.raw()[0],vecs.raw()[1],vecs.raw()[2]));
	}

	/**
	 * Moves the camera backwards with the specified speed relative to the opposite direction it is facing.
	 * @param speed The speed of the camera.
	 */
	public void moveBackwards(float speed){
		backVelocity = direction.normalize().multiply(-1*speed);//create a vector that is in the direction the camera is facing with a magnitude equal to the speed.
		if(movementThread.isAlive() == false){
			movementThread.start();
		}
	}

	/**
	 * Stop the camera from moving backwards by setting its backwards velocity to a vector with magnitude 0. If the camera was not moving backwards then this method has no effect.
	 */
	public void stopBackwards(){
		backVelocity = new Vec3(0,0,0);
	}

	/**
	 * Moves the camera forwards with the specified speed relative to the direction its facing.
	 * @param speed The speed of the camera.
	 */
	public void moveForward(float speed){
		forwardVelocity = direction.normalize().multiply(speed);//create a vector that is in the direction the camera is facing with a magnitude equal to the speed.
		if(movementThread.isAlive() == false){
			movementThread.start();
		}
	}

	/**
	 * Stop the camera from moving forwards by setting its forwards velocity to a vector with magnitude 0. If the camera was not moving forwards then this method has no effect.
	 */
	public void stopForward(){
		forwardVelocity = new Vec3(0,0,0);
	}

	/**
	 * Moves the camera down with the specified speed relative to its down direction.
	 * @param speed The speed of the camera.
	 */
	public void moveDown(float speed){
		downVelocity = up.normalize().multiply(-1*speed);//create a vector that is in the direction the camera is facing with a magnitude equal to the speed.
		if(movementThread.isAlive() == false){
			movementThread.start();
		}
	}

	/**
	 * Stop the camera from moving down by setting its down velocity to a vector with magnitude 0. If the camera was not moving down then this method has no effect.
	 */
	public void stopDown(){
		downVelocity = new Vec3(0,0,0);
	}

	/**
	 * Moves the camera up with the specified speed relative to its up direction.
	 * @param speed The speed of the camera.
	 */
	public void moveUp(float speed){
		upVelocity = up.normalize().multiply(speed);//create a vector that is in the direction the camera is facing with a magnitude equal to the speed.
		if(movementThread.isAlive() == false){
			movementThread.start();
		}
	}

	/**
	 * Stop the camera from moving up by setting its up velocity to a vector with magnitude 0. If the camera was not moving up then this method has no effect.
	 */
	public void stopUp(){
		upVelocity = new Vec3(0,0,0);
	}

	/**
	 * Moves the camera to the left with the specified speed relative to its left direction.
	 * @param speed The speed of the camera.
	 */
	public void moveLeft(float speed){
		Vec3 leftDir = direction.cross(up).multiply(-1f);//get the x axis direction relative to the camera
		leftVelocity = leftDir.normalize().multiply(speed);//create a vector that is in the direction the camera is facing with a magnitude equal to the speed.
		if(movementThread.isAlive() == false){
			movementThread.start();
		}
	}

	/**
	 * Stop the camera from moving left by setting its left velocity to a vector with magnitude 0. If the camera was not moving left then this method has no effect.
	 */
	public void stopLeft(){
		leftVelocity = new Vec3(0,0,0);
	}

	/**
	 * Moves the camera to the right with the specified speed relative to its right direction.
	 * @param speed The speed of the camera.
	 */
	public void moveRight(float speed){
		Vec3 rightDir = direction.cross(up);//get the x axis direction relative to the camera
		rightVelocity = rightDir.normalize().multiply(speed);//create a vector that is in the direction the camera is facing with a magnitude equal to the speed.
		if(movementThread.isAlive() == false){
			movementThread.start();
		}
	}

	/**
	 * Stop the camera from moving right by setting its right velocity to a vector with magnitude 0. If the camera was not moving right then this method has no effect.
	 */
	public void stopRight(){
		rightVelocity = new Vec3(0,0,0);
	}

	/**
	 * Gets the camera eye position
	 * @return
	 */
	public Vec3 getPosition(){
		return position;
	}

	/**
	 * Gets the cameras near frustrum distance
	 * @return
	 */
	public float getNearFrustrum(){
		return near;
	}

	/**
	 * Gets the cameras far frustrum distance
	 * @return
	 */
	public float getFarFrustrum(){
		return far;
	}

	/**
	 * Gets the camera reference point
	 * @return
	 */
	public Vec3 getDirection(){
		return direction;
	}

	/**
	 * Gets the camera's up vector
	 * @return
	 */
	public Vec3 getUpVector(){
		return up;
	}

	/**
	 * Sets the camera's up vector
	 * @param newUp
	 */
	public void setUpVector(Vec3 newUp){
		up = newUp;
	}

	/**
	 * Sets the camera's position
	 * @param newPos
	 */
	public void setPosition(Vec3 newPos){
		position = newPos;
	}

	/**
	 * Sets the camera's direction
	 * @param newDir
	 */
	public void setDirection(Vec3 newDir){
		direction = newDir;
	}


	/**
	 * Sets the  windowHeight
	 * @param height
	 */
	public void setWindowHeight(int height){
		this.windowHeight = height;

	}

	/**
	 * Sets the window width
	 * @param width
	 */
	public void setWindowWidth(int width){
		this.windowWidth = width;

	}

	/**
	 * Sets the near frustrum
	 * @param near
	 */
	public void setNearFrustum(float near){
		this.near = near;

	}

	/**
	 * Sets the far frustrum
	 * @param far
	 */
	public void setFarFrustum(float far){
		this.far = far;

	}

	/**
	 * Calling this method will cause the Cameras shader to be used, or cause the shader to not be used if in use.
	 * @param enable True if the cameras shader should be used, false otherwise.
	 * @param g
	 */
	public void enableCameraShader(boolean enable, GL3 g){
		if(enable){
			g.glUseProgram(Shader.getShaderProgram(CAMERA_SHADER_NAME));
		}else{
			g.glUseProgram(0);
		}
	}

	/**
	 * Calling this method will push a 4x4 orientation matrix to the shader to apply to the verticies being drawn so that their local coordinate system is
	 * aligned with the orientation matrix. To enable/disable using this matrix a call to useOrientationMatrix() should be made.
	 * 
	 * @param matrix The 4x4 orientation matrix.
	 */
	public static void setOrientationMatrix(Mat4 matrix){
		g.glUniformMatrix4fv(orientationMatrix,1,false,matrix.raw(),0);
	}

	/**
	 * Calling this method will enable using the 4x4 orientation matrix when drawing one of the imported models. Once the call to draw the model is made you 
	 * should make a call to this method and pass in false otherwise the orientation matrix will be applied to any vertices passed in after it too.
	 * 
	 * @param use true to enable the orientation matrix, false to disable it.
	 */
	public static void useOrientationMatrix(boolean use){
		if(use){
			g.glUniform1i(useOrientationMatrixHandle,1);
		}else{
			g.glUniform1i(useOrientationMatrixHandle,0);
		}
	}
	
	/**
	 * Calling this method will enable using the 4x4 orientation matrix when drawing one of the imported models. Once the call to draw the model is made you 
	 * should make a call to this method and pass in false otherwise the orientation matrix will be applied to any vertices passed in after it too.
	 * 
	 * @param use true to enable the orientation matrix, false to disable it.
	 */
	public static void draw3D(boolean use){
		if(use){
			g.glUniform1i(draw3DUniform,1);
		}else{
			g.glUniform1i(draw3DUniform,0);
		}
	}

	/**
	 * Recalculates modelToWorld, worldToCamera, and cameraToClip, and sends those values to the shader
	 * @param g
	 */
	public void lookAt(GL3 g){
		//calculate matrices
		// look direction
		enableCameraShader(true,g);
		g.glUniform3fv(cameraUpUniform,1,up.raw(),0);
		g.glUniform3fv(cameraPositionUniform,1,position.raw(),0);
		g.glUniform3fv(cameraDirectionUniform,1,direction.raw(),0);
		enableCameraShader(false,g);
	}



	/**
	 * Updates the camera perspective
	 * @param g
	 */
	public void updatePerspective(GL3 g){
		enableCameraShader(true,g);
		Mat4 mat = new Mat4(1.0f);
		mat.perspective(45.0f, (windowWidth/(float)windowHeight), near, far);

		g.glUniformMatrix4fv(cameraToClipUniform,1,false,mat.raw(),0);

		g.glViewport(0, 0, windowWidth, windowHeight);
		enableCameraShader(false,g);
	}
}
