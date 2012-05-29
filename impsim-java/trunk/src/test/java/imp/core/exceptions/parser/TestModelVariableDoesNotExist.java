package imp.core.exceptions.parser;

import static org.junit.Assert.*;
import imp.core.exceptions.parser.ModelVariableAlreadyExists;
import imp.core.exceptions.parser.ModelVariableDoesNotExist;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Test class intended to test the exception thrown when a model variable is requested but
 * does not exist
 * @author kreierj
 * @version 1.0<br>1/8/2012
 *
 */
public class TestModelVariableDoesNotExist {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	/**
	 * Tests the standard usage of the exception
	 */
	public void testStandardUsage(){

		try{
			throw new ModelVariableDoesNotExist("Cat");
		}
		catch(ModelVariableDoesNotExist e){
			assertEquals("The variable Cat does not exist in this model", e.getMessage());
		}
	}

	@Test
	/**
	 * Tests null parameters of the exception
	 * @throws ModelVariableAlreadyExists
	 */
	public void testNullParameter() throws ModelVariableAlreadyExists {
		thrown.expect(ModelVariableAlreadyExists.class);
		throw new ModelVariableAlreadyExists(null);

	}

}
