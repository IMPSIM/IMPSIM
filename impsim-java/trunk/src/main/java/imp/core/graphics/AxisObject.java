package imp.core.graphics;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.List;

import javax.media.opengl.GL;
import javax.media.opengl.GL3;


/**
 * This class is responsible for displaying the axis for a mechanical linkage
 * @author kreierj
 * @version 1, 4/29/12
 */
public class AxisObject extends AbstractGLObject{


	/**
	 * The object's orientation
	 */
	private Mat4 orientation;

	/**
	 * The axis data
	 */
	private static float[] lineData = new float[]{
		//x axis
		1,0,0,1,
		-1,0,0,1,

		//y axis
		0,1,0,1,
		0,-1,0,1,

		//z axis
		0,0,1,1,
		0,0,-1,1
	};

	/**
	 * The axis colores
	 */
	private static float[] colorData = new float[]{
		1,0,0,1,
		1,0,0,1,
		0,1,0,1,
		0,1,0,1,
		0,0,1,1,
		0,0,1,1,
	};

	/**
	 * The GL identifier
	 */
	private IntBuffer identifier;


	/**
	 * Instantiates a new axis object with the specified name and initial orientation
	 * @param name
	 * @param initialOrientation
	 */
	public AxisObject(String name, Mat4 initialOrientation) {
		super(name);
		if (initialOrientation == null){
			throw new NullParameterException("Initial orientation cannot be null", 2);
		}
		identifier = IntBuffer.allocate(2);
		this.orientation = initialOrientation;


	}

	@Override
	public void draw(GL3 gl) {

		//binding the array buffer
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

		//indicating we will use the orientation matrix
		Camera.setOrientationMatrix(orientation);
		Camera.useOrientationMatrix(true);

		//set up vertex pointers
		gl.glEnableVertexAttribArray(0);
		gl.glEnableVertexAttribArray(1);

		gl.glVertexAttribPointer(0,4,GL.GL_FLOAT, false, 0, 0);
		gl.glVertexAttribPointer(1,4,GL.GL_FLOAT, false, 0, lineData.length*SIZE_OF_FLOAT);

		//draw the lines
		gl.glDrawArrays(GL.GL_LINES, 0, 8*SIZE_OF_FLOAT);

		//unbind the pointers
		gl.glDisableVertexAttribArray(0);
		gl.glDisableVertexAttribArray(1);

		//unbind the orientation matrix
		Camera.useOrientationMatrix(false);

		//unbind the buffer
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);

	}

	@Override
	public void initialize(GL3 gl) {
		float[] data = new float[lineData.length+colorData.length];

		//copy line data into one object
		for (int i = 0; i < lineData.length; i++){
			data[i] = lineData[i];
		}

		//copy color data into one object
		for (int i = 0; i < colorData.length; i++){
			data[lineData.length + i] = colorData[i];
		}

		//create pointer to the array
		FloatBuffer vertexPositions = FloatBuffer.wrap(data);

		//generate the identifier from the GPU
		gl.glGenBuffers(2, identifier);

		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

		gl.glBufferData(GL.GL_ARRAY_BUFFER, vertexPositions.capacity()*SIZE_OF_FLOAT, vertexPositions, GL3.GL_STREAM_DRAW);

		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
	}

	@Override
	public void dispose(GL3 gl) {
		gl.glDeleteBuffers(2, identifier);
	}

	@Override
	public void updateData(GL3 gl, List<Float> newData, DATA_TYPE dataType) {
		if (dataType == DATA_TYPE.ORIENTATION_DATA){
			if (newData.size() != 16){
				try{
					throw new InvalidParameterException("Data for orientation not correct size", 1);
				} catch (InvalidParameterException e){
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
