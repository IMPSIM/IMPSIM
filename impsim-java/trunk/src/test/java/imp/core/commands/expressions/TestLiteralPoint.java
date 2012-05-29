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
 * This class tests creating a FakeExpressionLiteral using the constructor that accepts a point
 *
 */
public class TestLiteralPoint {
	
	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	public void testConstructorPoint(){
		Point p = new Point();
		new FakeExpressionLiteral(p);
	}
	
	@Test
	public void testToExpression() throws IMPException{
		Point p = new Point();
		FakeExpressionLiteral fake = new FakeExpressionLiteral(p);
		assertEquals(fake.toExpression(new Model()),new ExpressionLiteral(p));
	}
	
	@Test
	public void testEqualsPoint(){
		Point p = new Point();
		FakeExpressionLiteral fake = new FakeExpressionLiteral(p);
		assertEquals(fake.equals(fake),true);//see if fake equals itself
		assertEquals(fake.equals(null),false);
		assertEquals(fake.equals(42),false);//test equals on an object that is not even the same class
	}
	
	@Test
	public void testEqualsNullPointParam(){
		this.thrown.expect(NullParameterException.class);
		new FakeExpressionLiteral((Point) null);
	}
	
	@Test
	public void testEqualsDifferentLiteralValue(){
		Point p1 = new Point();
		Point p2 = new Point(1,1,1);
		FakeExpressionLiteral fake = new FakeExpressionLiteral(p1);
		FakeExpressionLiteral param = new FakeExpressionLiteral(p2);
		assertEquals(fake.equals(param),false);
	}
	
	@Test
	public void testEqualsDifferentType(){
		Point p = new Point();
		FakeExpressionLiteral fake = new FakeExpressionLiteral(p);
		FakeExpressionLiteral param = new FakeExpressionLiteral(0.0);
		assertEquals(fake.equals(param),false);
		
		param = new FakeExpressionLiteral(0.0);//test with a double expression
		assertEquals(fake.equals(param),false);
		
		param = new FakeExpressionLiteral(new double[]{0.0,1.1});//test with double[]
		assertEquals(fake.equals(param),false);
		
		param = new FakeExpressionLiteral("String parameter");//test with String
		assertEquals(fake.equals(param),false);
		
		param = new FakeExpressionLiteral(new String[]{"String parameter"});//test with String[]
		assertEquals(fake.equals(param),false);
		
		param = new FakeExpressionLiteral(new Point[]{new Point()});//test with Point[]
		assertEquals(fake.equals(param),false);
	}
}
