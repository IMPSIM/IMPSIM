package imp.core.graphics;

import imp.core.exceptions.ShaderException;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.charset.CharacterCodingException;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.media.opengl.GL;
import javax.media.opengl.GL2ES2;
import javax.media.opengl.GL3;

/**
 * Compiler for GLSL shader programs.
 * 
 * @author klehmc
 * @version 2
 * @edit kreierj did some refactoring, made methods static, and performed minor edits
 */
public class Shader {

	/**
	 * Stores shader identifiers based on their unique name identifier
	 */
	private static HashMap<String, Integer> shaderPrograms = new HashMap<String, Integer>();
	private static List<Integer> shaderObjects = new ArrayList<Integer>();
	private static GL3 gl;
	
	/**
	 * Compiles a shader into an object
	 * @param g GL3
	 * @param shaderType GL3 shader type
	 * @param shaderCode The code to compile as a size 1 string array
	 * @return identifier for the shader object
	 * @throws ShaderException
	 * @throws CharacterCodingException
	 */
	public static int compileShader(GL3 g, int shaderType, String[] shaderCode) throws ShaderException, CharacterCodingException{
		gl = g;
		//identify shader
		int shader = g.glCreateShader(shaderType);
		g.glShaderSource(shader, 1, shaderCode,(IntBuffer) null);

		//compile the shader
		g.glCompileShader(shader);

		//error checking		
		validateShader(g, shader, false);
		
		shaderObjects.add(shader);

		//return the shader id number
		return shader;
	}

	/**
	 * Links several shader objects together
	 * @param g GL3
	 * @param shaderList list of shader object identifiers
	 * @param name Unique identifier for shader
	 * @return identifier for the program
	 * @throws ShaderException
	 * @throws CharacterCodingException
	 */
	public static int createShaderProgram(GL3 g, List<Integer> shaderList, String name) throws ShaderException, CharacterCodingException{
		//identify the program
		int program = g.glCreateProgram();

		//attach all compiled shaders
		for(int i = 0; i < shaderList.size(); i++){
			g.glAttachShader(program, shaderList.get(i));
		}

		//perform linking algorithm
		g.glLinkProgram(program);

		//error checking		
		validateShader(g, program, true);
		if (shaderPrograms.get(name) != null){
			try{
				throw new ShaderException("Shader with name "+name+" already exists");
			}
			catch(ShaderException e){
				System.out.println(e.getMessage());
			}
		}
		else{
			shaderPrograms.put(name, program);
		}

		return program;
	}

	/**
	 * Deletes a shader program
	 * @param g GL3
	 * @param name Name of the shader program
	 * @return succesful
	 */
	public static boolean deleteShaderProgram(GL3 g, String name){
		Integer program = shaderPrograms.get(name);
		if (program != null){
			g.glDeleteProgram(program);
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * Clean up all the valid shader objects and programs.
	 */
	public static void dispose() {
		// stop using the current shader
		gl.glUseProgram(0);

		// wipe all the shader programs
		for (Map.Entry<String, Integer> entry : shaderPrograms.entrySet()) {
			gl.glDeleteProgram(entry.getValue());
		}
		
		// wipe all the shader obects
		for (Integer i : shaderObjects) {
			gl.glDeleteShader(i);
		}
	}

	/**
	 * Obtains a shader ID based on the shader name
	 * @param name shader name
	 * @return shader identifier
	 */
	public static int getShaderProgram(String name){
		return shaderPrograms.get(name);
	}

	/**
	 * Checks the status of the shader.
	 * 
	 * @param gl The OpenGL context.
	 * @param pid The id of the shader program we want to validate.
	 * @param identifies if the validation is for linking or not
	 * @throws CharacterCodingException Thrown when a failure message fails to decode.
	 * @throws ShaderException Thrown when the shader program fails to validate.
	 * 
	 * @author klehmc
	 * @edit kuszewskij Changed which method it uses to get the id based on whether or not program linking or shader compiling.
	 */
	private static void validateShader(GL3 gl, int pid, boolean linking) throws ShaderException, CharacterCodingException {
		// used to return values
		IntBuffer ib = IntBuffer.allocate(1);

		// query the status of the program
		if(linking){
			gl.glGetProgramiv(pid, GL2ES2.GL_LINK_STATUS, ib);
		}else{
			gl.glGetShaderiv(pid, GL2ES2.GL_COMPILE_STATUS, ib);
		}
		
		int linkStatus = ib.get(0);

		// if sad times throw a fit
		if (linkStatus == GL.GL_FALSE) {
			
			if (linking) {
				gl.glGetProgramiv(pid, GL2ES2.GL_INFO_LOG_LENGTH, ib);
			} else {
				gl.glGetShaderiv(pid, GL2ES2.GL_INFO_LOG_LENGTH, ib);
			}

			int bufLen = ib.get(0);

			ByteBuffer bb = ByteBuffer.allocate(bufLen + 1);


			if (linking){
				gl.glGetProgramInfoLog(pid, bufLen, null, bb);
				throw new ShaderException("Linker failure: " + byteBufferToString(bb));
				
			} else {
				gl.glGetShaderInfoLog(pid, bufLen, null, bb);
				throw new ShaderException("Compiler failure: "+byteBufferToString(bb));
			}
		}
	}

	/**
	 * Converts the JOGL messages from ByteBuffers to Strings.
	 * 
	 * @param buffer The ByteBuffer to be converted
	 * @return A string of characters encoded with the default charset.
	 * @throws CharacterCodingException Thrown when we don't use the right charset.
	 */
	private static String byteBufferToString(ByteBuffer buffer) throws CharacterCodingException {
		final Charset charset = Charset.defaultCharset();
		final CharsetDecoder decoder = charset.newDecoder();
		String data = "";

		int old_position = buffer.position();
		data = decoder.decode(buffer).toString();
		// Reset to keep things peachy
		buffer.position(old_position);

		return data;
	}
}
