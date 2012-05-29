package imp.core.exceptions.parser;

import static org.junit.Assert.*;
import imp.core.exceptions.parser.ParserException;

import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.Tree;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Tests the abstract parser exception
 * @author kreierj
 * @version 1.0<br>1/8/2012
 */
public class TestParserException {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	/**
	 * Tests the standard usage of the exception
	 * @throws ParserException
	 */
	public void testStandardUsage() throws ParserException{

		thrown.expect(ParserException.class);
		throw new Blah(10, 20, "Message");
		
	}

	
	@Test
	/**
	 * Tests the expected string output
	 */
	public void testExpectedStringOutput(){
		
		try{
			throw new Blah(10,20, "Message");
		}catch(ParserException e){
			assertEquals("Parsing Error (10,20): Message", e.toString());
		}
		
	}
	
	@Test
	/**
	 * Tests all the convenience methods
	 */
	public void testConvenienceMethods(){

		Tree token = new CommonTree();
		token.setTokenStartIndex(10);
		token.setTokenStopIndex(20);
		
		try{
			throw new Blah(token, "Message");
			
		}catch(ParserException e){
			assertEquals("Parsing Error (10,20): Message", e.getMessage());
		}
		
		try{
			throw new Blah(token, token, "Message");
		}catch(ParserException e){
			assertEquals("Parsing Error (10,20): Message", e.getMessage());
		}
		
	}
	
	@Test
	/**
	 * Tests for null parameters
	 */
	public void testNullParameter() {
		try{
			throw new Blah(10,20, null);
		}catch(ParserException e){
			
		}
		
	}

	/**
	 * Used for testing the abstract class ParserException
	 * @author kreierj
	 * @version 1.0<br>1/8/2012
	 */
	private class Blah extends ParserException{

		/**
		 * 
		 */
		private static final long serialVersionUID = -6898802268180046996L;

		Blah(int tIndexStart, int tIndexEnd, String tMessage) {
			super(tIndexStart, tIndexEnd, tMessage);
		}
		
		Blah(Tree token, String message) {
			super(token, message);
		}
		
		Blah(Tree tokenStart, Tree tokenEnd, String message) {
			super(tokenStart, tokenEnd, message);
		}



	}

}
