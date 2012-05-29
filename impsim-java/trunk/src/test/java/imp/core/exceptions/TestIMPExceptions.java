package imp.core.exceptions;

import static org.junit.Assert.*;
import imp.core.exceptions.IMPArgumentException;
import imp.core.exceptions.IMPFileNotFoundException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.ParserRecognitionError;
import imp.core.exceptions.SavingException;
import imp.core.exceptions.ShaderException;
import imp.core.exceptions.WrappedException;

import org.antlr.runtime.RecognitionException;
import org.junit.Test;

public class TestIMPExceptions {

	@Test
	public void testNullParameterException() {
		NullParameterException e = new NullParameterException("hello" ,0);
		assertEquals(e.getParamNum(), 0);
	}
	
	@Test
	public void testInvalidParameterException() {
		InvalidParameterException e = new InvalidParameterException("hello" ,0);
		assertEquals(e.getParamNum(), 0);
	}
	
	@Test
	public void testWrappedException() {
		InvalidParameterException b = new InvalidParameterException("hello" ,0);
		WrappedException e = new WrappedException(b);
		assertEquals(e.innerException, b);
	}
	
	@Test
	public void testShaderException() {
		ShaderException e = new ShaderException("Error");
		assertEquals(e.getMessage(), "Error");
	}
	
	@Test
	public void testSavingException() {
		SavingException e = new SavingException("Error");
		assertEquals(e.getMessage(), "Error");
	}
	
	@SuppressWarnings("deprecation")
	@Test
	public void testParserRecognitionError() {
		String[] tok = new String[]{"Hello", "World"};
		RecognitionException re = new RecognitionException();
		ParserRecognitionError e = new ParserRecognitionError(tok, re);
		assertEquals(e.getMessage(), "ParserRecognitionError");
		assertEquals(e.tokenNames, tok);
		assertEquals(e.recognitionException, re);
	}
	
	@Test
	public void testNameConflictException() {
		NameConflictException e = new NameConflictException("Joint");
		assertEquals(e.getMessage(), "An element named `Joint` is already present in this model.");
	}
	
	@Test
	public void testMatrixIndexOutOfBoundsException() {
		MatrixIndexOutOfBoundsException e = new MatrixIndexOutOfBoundsException("Problems");
		assertEquals(e.getMessage(), "Problems");
	}

	@Test
	public void testIMPFileNotFoundException() {
		IMPFileNotFoundException e = new IMPFileNotFoundException("Problems");
		assertEquals(e.getMessage(), "Problems");
	}
	
	@Test
	public void testIMPArgumentException() {
		IMPArgumentException e = new IMPArgumentException("Problems");
		assertEquals(e.getMessage(), "Problems");
	}
}
