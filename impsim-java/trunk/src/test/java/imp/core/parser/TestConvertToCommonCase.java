/**
 * 
 */
package imp.core.parser;

import static org.junit.Assert.assertEquals;
import imp.core.exceptions.NullParameterException;
import imp.core.parser.SimpleParser;

import org.junit.Before;
import org.junit.Test;

/**
 * Test the SimpleParser.convertToCommonCase method
 * 
 * @author zastrowm
 * 
 */
@SuppressWarnings("javadoc")
public class TestConvertToCommonCase {

	String cases[][];

	@Test
	public void convertToCommonCase() {

		// test each case
		for (int i = 0; i < this.cases.length; i++) {
			String singleTest[] = this.cases[i];
			assertEquals("Case " + i, singleTest[1], SimpleParser.convertToCommonCase(singleTest[0]));
		}

	}

	@Before
	public void setUp() {

		String temp[][] = {
				// what we test, what it should be
				{ "ABCDEFGHIJKL", "ABCDEFGHIJKL" }, // basic testing of converting to uppercase
				{ "abcdefghijkl", "ABCDEFGHIJKL" }, { "aBcDeFgHiJkL", "ABCDEFGHIJKL" }, { "AbCdEfGhIjKl", "ABCDEFGHIJKL" },
				{ "aBc\"DeF\"gHi", "ABC\"DeF\"GHI" }, // verify that quoted items are not converted
				{ "aBc\"D`\"eF\"gHi", "ABC\"D`\"eF\"GHI" }, // verify that escaped quotes inside quotes are preserved
				{ "aBc\"D`\"\"gHi", "ABC\"D`\"\"GHI" }, // should work with the escaped quote right next to the closing
														// quote
				{ "aBc\\\"EeF", "ABC\\\"EeF" }, // this is an invalid string, the second half should be converted left
												// alone
				{ "\"", "\"" }, // Single quote, nothing to convert
				{ "\"aBc", "\"ABC" }, // Single quote, everything should be converted
				{ "aBc\"", "ABC\"" }, // Single quote, everything should be converted
				{ "AbC~\"test\"", "ABC~\"test\"" }, // escape character does nothing outside of quoted string
				{ "", "" } // empty string should remain empty
		};

		this.cases = temp;
	}

	/**
	 * Test null.
	 */
	@Test(expected = NullParameterException.class)
	public void testNull() {
		SimpleParser.convertToCommonCase(null);
	}

}
