/**
 * 
 */
package imp.core.commands.expressions;

import static org.junit.Assert.assertEquals;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.exceptions.IMPException;
import imp.core.expressions.ExpressionLiteral;
import imp.core.model.Model;

import org.junit.Test;

/**
 * @author hellmerj
 * 
 */
@SuppressWarnings("javadoc")
public class TestLiteralNumber {

	/**
	 * Test method for {@link imp.commands.expressions.LiteralNumber#LiteralNumber(double)}.
	 */
	@Test
	public void testLiteralNumber() {
		new FakeExpressionLiteral(3.14);
	}

	/**
	 * Test method for {@link imp.commands.expressions.LiteralNumber#toExpression(imp.core.model.Model)}.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testToExpression() throws IMPException {

		double num = 3.14;

		FakeExpressionLiteral ln = new FakeExpressionLiteral(num);

		assertEquals(ln.toExpression(new Model()), new ExpressionLiteral(num));
	}

}
