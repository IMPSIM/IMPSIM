package imp.core.commands.expressions;

import static org.junit.Assert.assertEquals;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.NullParameterException;
import imp.core.expressions.ExpressionLiteral;
import imp.core.model.Model;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * 
 * @author kuszewskij
 * 
 */
public class TestLiteralPointArray {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	public void testConstructorPoint() {
		new FakeExpressionLiteral(new Point[] { new Point() });
	}

	@Test
	public void testToExpression() throws IMPException {
		FakeExpressionLiteral fake = new FakeExpressionLiteral(new Point[] { new Point() });
		assertEquals(
				fake.toExpression(new Model()).equals(
						new ExpressionLiteral(new Point[] { new Point() })), true);
	}

	@Test
	public void testEqualsDiffObjectSameValue() {
		FakeExpressionLiteral fake = new FakeExpressionLiteral(new Point[] { new Point() });
		FakeExpressionLiteral param = new FakeExpressionLiteral(new Point[] { new Point() });
		assertEquals(fake.equals(param), true);
	}

	@Test
	public void testEqualsPoint() {
		FakeExpressionLiteral fake = new FakeExpressionLiteral(new Point[] { new Point() });
		assertEquals(fake.equals(fake), true);// see if fake equals itself
		assertEquals(fake.equals(null), false);
		assertEquals(fake.equals(42), false);// test equals on an object that is
												// not even the same class
	}

	@Test
	public void testEqualsNullPointParam() {
		this.thrown.expect(NullParameterException.class);
		new FakeExpressionLiteral((Point) null);
	}

	@Test
	public void testEqualsDifferentLiteralValue() {
		FakeExpressionLiteral fake = new FakeExpressionLiteral(new Point[] { new Point() });
		FakeExpressionLiteral param = new FakeExpressionLiteral(new Point[] { new Point(1, 1, 1) });
		assertEquals(fake.equals(param), false);
	}

	@Test
	public void testEqualsDifferentType() {
		FakeExpressionLiteral fake = new FakeExpressionLiteral(new Point[] { new Point() });
		FakeExpressionLiteral param = new FakeExpressionLiteral(0.0);
		assertEquals(fake.equals(param), false);

		param = new FakeExpressionLiteral(0.0);// test with a double expression
		assertEquals(fake.equals(param), false);

		param = new FakeExpressionLiteral(new double[] { 0.0, 1.1 });// test
																		// with
																		// double[]
		assertEquals(fake.equals(param), false);

		param = new FakeExpressionLiteral("String parameter");// test with
																// String
		assertEquals(fake.equals(param), false);

		param = new FakeExpressionLiteral(new String[] { "String parameter" });// test
																				// with
																				// String[]
		assertEquals(fake.equals(param), false);

		param = new FakeExpressionLiteral(new Point());// test with Point
		assertEquals(fake.equals(param), false);
	}
}
