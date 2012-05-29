package imp.core.exceptions.parser;

/**
 * This Exception is thrown to indicate that a OBJ file has bad formatting.
 * @author kuszewskij
 *
 */
public class OBJFileFormatException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6843297367933250289L;


	/**
	 * Constructor for this exception
	 * @param message The message describing why the exception was thrown.
	 */
	public OBJFileFormatException(String message){
		super(message);
	}
}
