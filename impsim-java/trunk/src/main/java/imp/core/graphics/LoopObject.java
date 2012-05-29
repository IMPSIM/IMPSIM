package imp.core.graphics;

import imp.core.exceptions.InvalidParameterException;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.List;

import javax.media.opengl.GL;
import javax.media.opengl.GL3;

/**
 * Defines how an IMP Loop is displayed to the GL Canvas
 * @author kreierj
 * @version 1
 */
public class LoopObject extends AbstractGLObject{


	/**
	 * Vertex data
	 */
	private float[] loopData;

	/**
	 * Color attribute data
	 */
	private float[] colorData;

	/**
	 * Identifies the object on the GPU
	 */
	private IntBuffer identifier;

	/**
	 * Creates a new loop object with the specified vertex and color data
	 * @param name Unique name
	 * @param ld Vertex Data
	 * @param cd Color data
	 */
	public LoopObject(String name, List<Float> ld, List<Float> cd) {
		super(name);
		this.loopData = new float[ld.size()];
		this.colorData = new float[cd.size()];

		//check that the parameters have the same size data
		if (ld.size() != cd.size()){
			try {
				throw new InvalidParameterException("Color data size did not match vertex data size", 2);
			} catch (InvalidParameterException e) {
				e.printStackTrace();
			}
		}

		//copy data into the arrays
		for (int i = 0; i < ld.size(); i++){
			this.loopData[i] = ld.get(i);
			this.colorData[i] = cd.get(i);
		}
		
		identifier = null;


	}

	@Override
	public void draw(GL3 gl) {

		/*
		// Uncomment to demonstrate sterling engine defect
		if (getName().equals("Loop0")){
			System.out.println("Yo");
		}
		*/
		//bind to the GPU
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));


		gl.glEnableVertexAttribArray(0); //enable attribute 0 (position)
		gl.glEnableVertexAttribArray(1); //enable attribute 1 (color)


		//set up vertex pointers
		gl.glVertexAttribPointer(0, 4, GL.GL_FLOAT, false, 0, 0);
		gl.glVertexAttribPointer(1, 4, GL.GL_FLOAT, false, 0, loopData.length*SIZE_OF_FLOAT);

		//draw loopData.size vertices as a line strip
		gl.glDrawArrays(GL.GL_LINE_STRIP, 0, (loopData.length)/SIZE_OF_FLOAT);

		gl.glDisableVertexAttribArray(0);
		gl.glDisableVertexAttribArray(1);

		//unbind from the GPU
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);

	}

	@Override
	public void initialize(GL3 gl) {
		//copy loopData information into data
		float[] data = new float[loopData.length+colorData.length];
		for (int i = 0; i < loopData.length; i++){
			data[i] = loopData[i];
		}

		//copy colorData information into data
		for (int i = 0; i < colorData.length; i++){
			data[loopData.length + i] = colorData[i];
		}

		FloatBuffer vertexPositions = FloatBuffer.wrap(data);
		identifier = IntBuffer.allocate(2);

		//generate the identifier
		gl.glGenBuffers(2, identifier);

		//bind the object
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, identifier.get(1));

		//copy data to the GPU
		gl.glBufferData(GL.GL_ARRAY_BUFFER, vertexPositions.capacity() * SIZE_OF_FLOAT, vertexPositions, GL3.GL_STREAM_DRAW);

		//unbind the object
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
	}

	@Override
	public void dispose(GL3 gl) {
		gl.glDeleteBuffers(2, identifier);
	}

	@Override
	public void updateData(GL3 gl, List<Float> newData, DATA_TYPE dataType) {
		if (dataType == DATA_TYPE.VERTEX_DATA){
			//check that the data is the right size
			if (newData.size() != loopData.length){
				try {
					throw new InvalidParameterException("Color data size did not match vertex data size", 2);
				} catch (InvalidParameterException e) {
					e.printStackTrace();
				}
			}
			
			for (int i = 0; i < newData.size(); i++){
				loopData[i] = newData.get(i);
			}

			FloatBuffer vertexPositions = FloatBuffer.wrap(loopData);

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
					throw new InvalidParameterException("Color data size did not match vertex data size", 2);
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
			gl.glBufferSubData(GL.GL_ARRAY_BUFFER, loopData.length*Float.SIZE, vertexPositions.capacity()*Float.SIZE, vertexPositions);

			//unbind
			gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
		}


	}


}
