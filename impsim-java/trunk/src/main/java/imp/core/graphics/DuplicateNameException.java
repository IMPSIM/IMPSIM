package imp.core.graphics;

/**
 * Exception thrown when an object that requires unique names has a duplicate name
 * @author kreierj
 * @version 1
 */
public class DuplicateNameException extends RuntimeException {
	
	/**
	 * Generated serial version id
	 */
	private static final long serialVersionUID = -1465594765712542951L;
	
	/**
	 * The duplicate name
	 */
	public String name;
	
	/**
	 * Constructor for the exception
	 * @param name The name that was duplicated
	 */
	DuplicateNameException(String name){
		super("GL Object "+name+" already exists. GL Objects cannot have duplicate names");
	}
}
