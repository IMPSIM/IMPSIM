package imp.core.graphics;

import java.util.List;

import javax.media.opengl.GL3;


/**
 * An object that is drawn using OpenGL
 * @author kreierj
 * @version 1.0
 */
public abstract class AbstractGLObject {
	
	
	public static final int SIZE_OF_FLOAT = 4;
	public static final int SIZE_OF_SHORT = 2;
	
//	/**
//	 * Indicator for vertex data type
//	 */
//	public static final int VERTEX_DATA = 0;
//
//	/**
//	 * Indicator for color data type
//	 */
//	public static final int COLOR_DATA = 1;
//	
//	/**
//	 * Indicator for rotation data type
//	 */
//	public static final int ORIENTATION_DATA = 2;
	
	public static enum DATA_TYPE {
		VERTEX_DATA,
		COLOR_DATA,
		ORIENTATION_DATA
	};
	
	/**
	 * Uniquely identifying name
	 */
	private String name;
	
	
	/**
	 * Required constructor for the GL Object
	 * @param name The object's unique name
	 */
	public AbstractGLObject(String name){
		if (name == null){
			throw new NullPointerException("Name cannot be null");
		}
		this.name = name;
	}
	
	/**
	 * Returns the object's name
	 * @return
	 */
	public String getName(){
		return name;
	}
	
	/**
	 * Draws the GL object to the screen using currently stored attribute data
	 * @param gl
	 */
	public abstract void draw(GL3 gl);
	
	/**
	 * Initializes the object to the GPU
	 */
	public abstract void initialize(GL3 gl);
	
	/**
	 * Removes the object from the GPU
	 */
	public abstract void dispose(GL3 gl);

	/**
	 * Updates the object's data
	 * @param gl Graphics library
	 * @param newData The new data
	 * @param dataType The data type as defined by the object implementation
	 */
	public abstract void updateData(GL3 gl, List<Float> newData, DATA_TYPE type);
}