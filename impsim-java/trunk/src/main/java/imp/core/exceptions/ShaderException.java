/* ShaderException.java
 */
package imp.core.exceptions;

/**
 * Exceptions dealing with OpenGL Shaders.
 * 
 * @author klehmc
 * @version 1.0
 */
public class ShaderException extends IMPException {

	private static final long serialVersionUID = 1264901094662038523L;

	/**
	 * Represents an exception during shader usage.
	 * 
	 * @param message The message...
	 */
	public ShaderException(String message) {
		super(message);
	}
}
