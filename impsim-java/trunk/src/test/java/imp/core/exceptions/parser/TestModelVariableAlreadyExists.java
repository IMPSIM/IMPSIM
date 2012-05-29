package imp.core.exceptions.parser;

import static org.junit.Assert.*;
import imp.core.exceptions.parser.ModelVariableAlreadyExists;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Test class intended to test the exception thrown when a model variable already exists
 * @author kreierj
 * @version 1.0<br>1/8/2012
 *
 */
public class TestModelVariableAlreadyExists {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	/**
	 * Tests the standard usage of the exception
	 */
	public void testStandardUsage() throws ModelVariableAlreadyExists{

		thrown.expect(ModelVariableAlreadyExists.class);
		throw new ModelVariableAlreadyExists("Cat");
	}

	@Test
	/**
	 * Tests the 
	 * @throws ModelVariableAlreadyExists
	 */
	public void testNullParameter() throws ModelVariableAlreadyExists {
		thrown.expect(ModelVariableAlreadyExists.class);
		throw new ModelVariableAlreadyExists(null);

	}
	
	@Test
	/**
	 * Tests expected string output for the exception
	 */
	public void testExpectedStringOutput(){
		try{
			throw new ModelVariableAlreadyExists("Cat");
		}catch(ModelVariableAlreadyExists e){
			assertEquals("The variable Cat already exists in this model", e.getMessage());
		}
	}

}
