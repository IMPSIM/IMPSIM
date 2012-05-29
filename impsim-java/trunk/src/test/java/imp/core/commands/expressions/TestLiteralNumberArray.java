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
public class TestLiteralNumberArray {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	private double[] values;

	@Before
	public void setUp() {
		values = new double[] { 3.14, 6.28 };
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralNumberArray#LiteralNumberArray(double[])}.
	 */
	@Test
	public void testLiteralNumberArray() {

		new FakeExpressionLiteral(values);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralNumberArray#LiteralNumberArray(double[])}.
	 */
	@Test
	public void testLiteralNumberArrayNullParam() {

		this.thrown.expect(NullParameterException.class);
		new FakeExpressionLiteral((double[]) null);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralNumberArray#toExpression(imp.core.model.Model)}.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testToExpression() throws IMPException {

		FakeExpressionLiteral lna = new FakeExpressionLiteral(values);

		assertEquals(lna.toExpression(new Model()), new ExpressionLiteral(values));
	}

}
