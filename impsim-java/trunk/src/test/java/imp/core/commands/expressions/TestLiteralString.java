/**
 * 
 */
package imp.core.commands.expressions;

import static org.junit.Assert.assertEquals;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.NullParameterException;
import imp.core.expressions.ExpressionLiteral;
import imp.core.model.Model;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author hellmerj
 * 
 */
@SuppressWarnings("javadoc")
public class TestLiteralString {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	private String value;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		value = "test";
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralString#LiteralString(java.lang.String)}.
	 */
	@Test
	public void testLiteralString() {
		new FakeExpressionLiteral(value);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralString#LiteralString(java.lang.String)}.
	 */
	@Test
	public void testLiteralStringNullParam() {
		this.thrown.expect(NullParameterException.class);
		new FakeExpressionLiteral((String) null);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralString#toExpression(imp.core.model.Model)}.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testToExpression() throws IMPException {
		FakeExpressionLiteral ls = new FakeExpressionLiteral(value);

		assertEquals(ls.toExpression(new Model()), new ExpressionLiteral(value));
	}

}
