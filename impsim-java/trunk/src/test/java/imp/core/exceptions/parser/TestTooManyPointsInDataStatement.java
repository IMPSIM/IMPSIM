package imp.core.exceptions.parser;



import imp.core.exceptions.parser.TooManyPointsInDataStatement;

import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.Tree;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Test class intended to test the exception thrown when a data statement contains 
 * too many points
 * @author kreierj
 * @version 1.0<br> 1/8/2012
 */
public class TestTooManyPointsInDataStatement {
	
	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	/**
	 * Tests the standard usage
	 * @throws TooManyPointsInDataStatement
	 */
	public void testStandardUsage() throws TooManyPointsInDataStatement{

		
		Tree token = new CommonTree();
		token.setTokenStartIndex(10);
		token.setTokenStopIndex(20);
		
		thrown.expect(TooManyPointsInDataStatement.class);
		throw new TooManyPointsInDataStatement(token, 5, 10);
		
	}
	
	@Test
	/**
	 * Tests the convenience method
	 * @throws TooManyPointsInDataStatement
	 */
	public void testConvenienceMethod() throws TooManyPointsInDataStatement{
		Tree token = new CommonTree();
		token.setTokenStartIndex(10);
		token.setTokenStopIndex(20);
		
		thrown.expect(TooManyPointsInDataStatement.class);
		throw new TooManyPointsInDataStatement(token, token, 5, 10);
	}
}
