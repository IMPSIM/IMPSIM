package imp.core.graphics;

import imp.core.observer.Observer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.media.opengl.GL3;

/**
 * Data holder for GL objects
 * @author kreierj
 * @version 1
 */
public abstract class AbstractDataSource implements Observer {


	/**
	 * Reference to the GL objects by name
	 */
	private Map<String, AbstractGLObject> objects;

	/**
	 * List of GL Object references for quicker search
	 */
	private List<String> references;

	/**
	 * Object used for synchronization
	 */
	private Object lox = new String("Lox");

	/**
	 * Required constructor
	 */
	public AbstractDataSource(){
		references = new ArrayList<String>();
		objects = new HashMap<String, AbstractGLObject>();
	}

	/**
	 * Puts the object into the mapping
	 * @param name Unique name of the object
	 * @param object The object
	 */
	public void putObject(AbstractGLObject object){
		synchronized(lox){
			AbstractGLObject obj = objects.put(object.getName(), object);
			if (obj == null){ //null return means there was no previous mapping for that object
				references.add(object.getName());
			}
			else{
				//TODO: should this be a runtime exception or not?
				throw new DuplicateNameException(object.getName());
			}
		}
	}

	/**
	 * Removes an object from the data source
	 * @param name The object's name
	 * @return The removed object, or null if no object named "name"
	 */
	public AbstractGLObject removeObject(String name){
		AbstractGLObject obj = null;
		synchronized(lox){
			obj = objects.remove(name);
			if (obj != null){
				references.remove(obj.getName());
			}
			return obj;
		}
	}

	/**
	 * Obtains the list of all GLObjects
	 * @return List of AbstractGLObjects
	 */
	public List<AbstractGLObject> getObjects(){
		List<AbstractGLObject> list = new ArrayList<AbstractGLObject>(objects.size());
		synchronized(lox){

			for (int i = 0; i < references.size(); i++){
				list.add(objects.get(references.get(i)));
			}
			return list;
		}
	}

	/**
	 * Obtains a single AbstractGLObject
	 * @param name The object's name
	 * @return The named object, or null if not in the map of objects
	 */
	public AbstractGLObject getObject(String name){
		synchronized(lox){
			return objects.get(name);
		}
	}
	
	/**
	 * This method is used for any graphics object updates needing to be done prior to rendering.
	 * @param gl OpenGL3
	 */
	public abstract void update(GL3 gl);

}
