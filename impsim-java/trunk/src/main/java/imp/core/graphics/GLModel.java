package imp.core.graphics;

import imp.core.exceptions.InvalidParameterException;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.List;

import javax.media.opengl.GL;
import javax.media.opengl.GL2;
import javax.media.opengl.GL3;

/**
 * Object used to draw data held by .OBJ files to the GLCanvas
 * @author kreierj
 * @version 2, 3/23/2012
 * @edit kreierj: Had to redo the way data was stored to make drawing work
 */
public class GLModel extends AbstractGLObject{


	/**
	 * Vertex data
	 */
	private final float[] vertexData;

	/**
	 * Color attribute data
	 */
	private final float[] colorData; 

	/**
	 * Normal attribute data
	 */
	private float[] normalData;

	/**
	 * Identifies the object on the GPU
	 */
	private IntBuffer identifier;

	/**
	 * The object's orientation
	 */
	private Mat4 orientation;

	/**
	 * Instantiates a new model object with the specified vertices, index data, and initial rotation
	 * @param name The object's unique name
	 * @param vertices The vertices to draw
	 * @param indexData The indices to draw
	 * @param initialRotation The object's initial orientation
	 */
	public GLModel(String name, Float[] vertices, Integer[] indexData, Mat4 initialRotation){
		super(name);
		this.vertexData = new float[indexData.length*4];
		this.colorData = new float[vertexData.length];

		//generate color data
		//Random r = new Random();
		float[] tempColors = new float[vertices.length];
		for (int i = 0; i < vertices.length; i++){
			if ((i+1)%4 == 0){
				tempColors[i] = 1.0f;
			}
			else{
				//tempColors[i] = r.nextFloat();
				tempColors[i] = 1.0f;
			}
		}


		int loopDataIndex = 0;
		//copy data into the arrays
		for (int i = 0; i < indexData.length; i++){
			int index = indexData[i];

			for (int j = 0; j < 4; j++){
				vertexData[loopDataIndex] = vertices[(index*4) + j];
				colorData[loopDataIndex] = tempColors[(index*4)+j];
				loopDataIndex++;
			}
		}

		normalData = calculateNormals(vertexData);
		orientation = initialRotation;

		identifier = null;
	}

	/**
	 * This method is used to setup default material values for the faces.
	 * @param gl
	 */
	private void setUpMaterials(GL3 gl){
		gl.glEnable(GL2.GL_COLOR_MATERIAL);//use the specified base colors.

		int cameraShaderProgram = Shader.getShaderProgram(Camera.CAMERA_SHADER_NAME);
		//gl.glEnable(GL2.GL_COLOR_MATERIAL_FACE);
		float[] diffuseColor = {1.0f,1.0f,1.0f,1.0f};//red, full opacity
		float[] specularColor = {0.9f,0.9f,0.9f,1.0f};//light red 
		float[] emissiveColor = {1.0f,1.0f,1.0f,1.0f};//blue
		float[] ambientColor = {0.2f,0.2f,0.2f,1.0f};//white
		float shininess = 5f;//the shiny
		int materialDiffuse = gl.glGetUniformLocation(cameraShaderProgram, "materialUniform.diffuse");
		int materialSpecular = gl.glGetUniformLocation(cameraShaderProgram, "materialUniform.specular");
		int materialEmissive = gl.glGetUniformLocation(cameraShaderProgram, "materialUniform.emmissive");
		int materialAmbient = gl.glGetUniformLocation(cameraShaderProgram, "materialUniform.ambient");
		int materialShininess = gl.glGetUniformLocation(cameraShaderProgram, "materialUniform.shininess");
		
		gl.glUniform4fv(materialDiffuse,1,diffuseColor,0);
		gl.glUniform4fv(materialSpecular,1,specularColor,0);
		gl.glUniform4fv(materialEmissive,1,emissiveColor,0);
		gl.glUniform4fv(materialAmbient,1,ambientColor,0);
		gl.glUniform1f(materialShininess,shininess);
	}

	/**
	 * This method will calculate normals for the faces passed in if none were defined.
	 * @param triangles The buffer of faces triangles making up each face.
	 * @return
	 */
	private float[] calculateNormals(float[] triangles){
		float[] normals = new float[triangles.length];
		
		for(int i = 0; i < normals.length; i+=12){
			Vec3 u = new Vec3(triangles[i],triangles[i+1],triangles[i+2]);
			Vec3 v = new Vec3(triangles[i+4],triangles[i+5],triangles[i+6]);
			Vec3 w = new Vec3(triangles[i+8],triangles[i+9],triangles[i+10]);
			

			Vec3 v1 = v.minus(u);

			Vec3 v2 = w.minus(u);

			Vec3 normal = v1.cross(v2);
			normal = normal.normalize();
			normals[i] = normal.x;
			normals[i+1] = normal.y;
			normals[i+2] = normal.z;
			normals[i+3] = 0.0f;
			
			normals[i+4] = normal.x;
			normals[i+5] = normal.y;
			normals[i+6] = normal.z;
			normals[i+7] = 0.0f;
			
			normals[i+8] = normal.x;
			normals[i+9] = normal.y;
			normals[i+10] = normal.z;
			normals[i+11] = 0.0f;
		}
		return normals;
	}

	@Override
	public void draw(GL3 gl) {

		//bind to the GPU
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

		//pass the orientation to the GPU
		Camera.setOrientationMatrix(orientation);
		Camera.useOrientationMatrix(true);

		Camera.draw3D(true);//tell the shader to draw the image in 3D using lighting.

		gl.glEnableVertexAttribArray(0); //enable attribute 0 (position)
		gl.glEnableVertexAttribArray(1); //enable attribute 1 (color)
		gl.glEnableVertexAttribArray(2);//enable the normal attributes 

		setUpMaterials(gl);
		
		//set up vertex pointers
		gl.glVertexAttribPointer(0, 4, GL.GL_FLOAT, false, 0, 0);
		gl.glVertexAttribPointer(1, 4, GL.GL_FLOAT, false, 0, vertexData.length*SIZE_OF_FLOAT);
		gl.glVertexAttribPointer(2, 4, GL.GL_FLOAT, false, 0, vertexData.length*SIZE_OF_FLOAT+colorData.length*SIZE_OF_FLOAT);

		//draw loopData.size vertices as triangles
		gl.glDrawArrays(GL.GL_TRIANGLES, 0, vertexData.length/4);

		gl.glDisableVertexAttribArray(0);
		gl.glDisableVertexAttribArray(1);
		gl.glDisableVertexAttribArray(2);

		//disable using the orientation matrix and 3D drawing.
		Camera.useOrientationMatrix(false);
		Camera.draw3D(false);

		//unbind from the GPU
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
	}

	@Override
	public void initialize(GL3 gl) {
		//copy loopData information into data
		normalData = calculateNormals(vertexData);
		float[] data = new float[vertexData.length+colorData.length+normalData.length];
		for (int i = 0; i < vertexData.length; i++){
			data[i] = vertexData[i];
		}

		//copy colorData information into data
		for (int i = 0; i < colorData.length; i++){
			data[vertexData.length + i] = colorData[i];
		}

		//copy normalData information into data
		for (int i = 0; i < normalData.length; i++){
			data[vertexData.length+colorData.length + i] = normalData[i];
		}

		FloatBuffer vertexPositions = FloatBuffer.wrap(data);
		identifier = IntBuffer.allocate(3);

		//generate the identifier
		gl.glGenBuffers(3, identifier);

		//bind the object
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

		//copy data to the GPU
		gl.glBufferData(GL.GL_ARRAY_BUFFER, vertexPositions.capacity() * SIZE_OF_FLOAT, vertexPositions, GL3.GL_STREAM_DRAW);

		//unbind the object
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
	}

	@Override
	public void dispose(GL3 gl) {
		gl.glDeleteBuffers(3, identifier);
	}

	@Override
	public void updateData(GL3 gl, List<Float> newData, DATA_TYPE dataType) {
		if (dataType == DATA_TYPE.VERTEX_DATA){
			//check that the data is the right size
			if (newData.size() != vertexData.length){
				try {
					throw new InvalidParameterException("Color data size did not match vertex data size", 2);
				} catch (InvalidParameterException e) {
					e.printStackTrace();
				}
			}

			for (int i = 0; i < newData.size(); i++){
				vertexData[i] = newData.get(i);
			}

			FloatBuffer vertexPositions = FloatBuffer.wrap(vertexData);

			//bind to the GPU
			gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

			//copy data to the GPU
			gl.glBufferSubData(GL.GL_ARRAY_BUFFER, 0, vertexPositions.capacity()*SIZE_OF_FLOAT, vertexPositions);
			
			//unbind
			gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
		}
		else if(dataType == DATA_TYPE.COLOR_DATA){
			//check that the data is the right size
			if (newData.size() != colorData.length){
				try {
					throw new InvalidParameterException("Color data size did not match vertex data size", 1);
				} catch (InvalidParameterException e) {
					e.printStackTrace();
				}
			}

			for (int i = 0; i < newData.size(); i++){
				colorData[i] = newData.get(i);
			}

			FloatBuffer vertexPositions = FloatBuffer.wrap(colorData);

			//bind to the GPU
			gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

			//copy data to the GPU
			gl.glBufferSubData(GL.GL_ARRAY_BUFFER, vertexData.length*Float.SIZE, vertexPositions.capacity()*Float.SIZE, vertexPositions);

			//unbind
			gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
		}

		else if (dataType == DATA_TYPE.ORIENTATION_DATA){
			//check that the data is the right size
			if (newData.size() != 16){
				try{
					throw new InvalidParameterException("Data for orientation not correct size",1);
				}catch(InvalidParameterException e){
					e.printStackTrace();
				}
			}

			float[] data = new float[newData.size()];
			for (int i = 0; i < newData.size(); i++){
				data[i] = newData.get(i);
			}
			orientation = new Mat4(data);
		}
	}


}
