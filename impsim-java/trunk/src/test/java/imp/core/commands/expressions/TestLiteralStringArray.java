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
public class TestLiteralStringArray {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	private String[] values;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		values = new String[] { "testValue1", "testValue2" };
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralStringArray#LiteralStringArray(java.lang.String[])}.
	 */
	@Test
	public void testLiteralStringArray() {
		new FakeExpressionLiteral(values);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralStringArray#LiteralStringArray(java.lang.String[])}.
	 */
	@Test
	public void testLiteralStringArrayNullParam() {
		this.thrown.expect(NullParameterException.class);
		new FakeExpressionLiteral((String[]) null);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralStringArray#toExpression(imp.core.model.Model)}.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testToExpression() throws IMPException {
		FakeExpressionLiteral lsa = new FakeExpressionLiteral(values);

		assertEquals(lsa.toExpression(new Model()), new ExpressionLiteral(values));
	}

}
