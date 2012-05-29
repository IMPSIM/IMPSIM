package imp.core.exceptions.parser;

import static org.junit.Assert.*;
import imp.core.exceptions.parser.IncorrectNumberOfPoints;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Test class intended to test the exception thrown when there is an incorrect number of points
 * @author kreierj
 * @version 1.0<br> 1/8/2012
 */
public class TestIncorrectNumberOfPoints {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	/**
	 * Tests the standard usages of the exception
	 * @throws IncorrectNumberOfPoints
	 */
	public void testStandardUsage() throws IncorrectNumberOfPoints{

		//expect that the exception is thrown with no other errors
		thrown.expect(IncorrectNumberOfPoints.class);
		throw new IncorrectNumberOfPoints(1,3);
	}

	@Test
	/**
	 * Tests the case where there are too many points
	 */
	public void testTooManyPoints(){
		try{
			throw new IncorrectNumberOfPoints(1,3);
		}
		catch(IncorrectNumberOfPoints e){
			assertEquals("Too many points in data statement. Expected 1 but found 3", e.getMessage());
		}
	}

	@Test
	/**
	 * Tests the case where there are not enoough points
	 */
	public void testNotEnoughPoints(){
		try{
			throw new IncorrectNumberOfPoints(3,1);
		}
		catch(IncorrectNumberOfPoints e){
			assertEquals("Not enough points in data statement. Expected 3 but found 1", e.getMessage());
		}
	}
}
