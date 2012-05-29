/**
 * TestFunction.java
 */
package imp.core.commands.expressions;

import static org.junit.Assert.assertEquals;
import imp.core.commands.expressions.FakeExpression;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.commands.expressions.Function;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.NullParameterException;
import imp.core.expressions.Expression;
import imp.core.expressions.ExpressionType;
import imp.core.expressions.FunctionSignature;
import imp.core.expressions.FunctionTest.TestClass;
import imp.core.model.Model;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author hellmerj Test for the function expression
 * @version 2.0
 * @edit kuszewskij Added some more test cases
 */
@SuppressWarnings("javadoc")
public class TestFunction {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for
	 * {@link imp.core.commands.expressions.Function#Function(java.lang.String, java.lang.String, imp.core.commands.expressions.FakeExpression[])}
	 * .
	 */
	@Test
	public void testFunction() {

		String name = "name"; // name of the function
		String nameSpace = "nameSpace"; // name space of the function
		FakeExpression parameters[] = new FakeExpression[3]; // arguments of the function

		// invoke Function constructor
		new Function(nameSpace, name, parameters);
	}

	/**
	 * Test method for {@link imp.commands.expressions.Function#Function(java.lang.String, java.lang.String, import
	 * java.util.List<imp.commands.expressions.FakeExpression>)} .
	 */
	@Test
	public void testFunctionConstructorList() {

		String name = "name"; // name of the function
		String nameSpace = "nameSpace"; // name space of the function
		List<FakeExpression> parameters = new ArrayList<FakeExpression>(); // arguments of the function
		parameters.add(new FakeExpressionLiteral(1.1));
		// invoke Function constructor
		new Function(nameSpace, name, parameters);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.expressions.Function#Function(java.lang.String, java.lang.String, imp.core.commands.expressions.FakeExpression[])}
	 * .
	 */
	@Test
	public void testFunctionNullParam0() {

		String name = "name"; // name of the function
		FakeExpression parameters[] = new FakeExpression[3]; // arguments of the function

		// Function constructor with null nameSpace, expected to throw NullParameterException
		this.thrown.expect(NullParameterException.class);
		new Function(null, name, parameters);
	}

	/**
	 * Test method for
	 * {@link imp.core.commands.expressions.Function#Function(java.lang.String, java.lang.String, imp.core.commands.expressions.FakeExpression[])}
	 * .
	 */
	@Test
	public void testFunctionNullParam1() {

		String nameSpace = "nameSpace"; // name space of the function
		FakeExpression parameters[] = new FakeExpression[3]; // arguments of the function

		// Function constructor with null nameSpace, expected to throw NullParameterException
		this.thrown.expect(NullParameterException.class);
		new Function(nameSpace, null, parameters);
	}

	/**
	 * Test method for {@link imp.commands.expressions.Function#Function(java.lang.String, java.lang.String,
	 * List<imp.commands.expressions.FakeExpression>)} .
	 */
	@Test
	public void testFunctionListNullParam0() {

		String name = "name"; // name of the function
		List<FakeExpression> parameters = new ArrayList<FakeExpression>(); // arguments of the function
		parameters.add(new FakeExpressionLiteral(1.1));

		// should throw an exception because of the null namespace
		this.thrown.expect(NullParameterException.class);
		new Function(null, name, parameters);
	}

	/**
	 * Test method for {@link imp.commands.expressions.Function#Function(java.lang.String, java.lang.String,
	 * List<imp.commands.expressions.FakeExpression>)} .
	 */
	@Test
	public void testFunctionListNullParam1() {

		String nameSpace = "nameSpace"; // name space of the function
		List<FakeExpression> parameters = new ArrayList<FakeExpression>(); // arguments of the function
		parameters.add(new FakeExpressionLiteral(1.1));

		// should throw an exception because of the null for name
		this.thrown.expect(NullParameterException.class);
		new Function(nameSpace, null, parameters);
	}

	/**
	 * Test method for {@link imp.core.commands.expressions.Function#toExpression(imp.core.model.Model)}.
	 * 
	 * @throws IMPException
	 */
	@Test
	public void testToExpression() throws IMPException {

		// model for testing
		Model testModel = new Model();

		// name space of the function
		String nameSpace = "";
		// name of the function
		String name = "max";

		// literal expressions for function parameters
		FakeExpressionLiteral ln = new FakeExpressionLiteral(3.14);
		FakeExpressionLiteral ln2 = new FakeExpressionLiteral(3.15);

		// arguments of the function
		FakeExpression parameters[] = { ln, ln2 };

		// arguments of the expression
		Expression expParams[] = { ln.toExpression(testModel), ln2.toExpression(testModel) };

		// create the new function
		Function f = new Function(nameSpace, name, parameters);

		// add test methods to functionManager
		testModel.functionManager.addFunctions(new TestClass());

		// create matching functionSignature
		FunctionSignature fs = new FunctionSignature("", "max", new ExpressionType[] { ExpressionType.number, ExpressionType.number });
		// get function matching signature from manager
		imp.core.expressions.Function fu = testModel.functionManager.getFunction(fs);

		// create expression for function from manager
		imp.core.expressions.FunctionExpression fe = new imp.core.expressions.FunctionExpression(fu, expParams);

		// check that created expression and expression from toExpression() match
		assertEquals(fe, f.toExpression(testModel));
	}

	/**
	 * Test method for {@link
	 * imp.commands.expressions.Function#convertToBinaryExpression(java.lang.String,java.lang.String,java.util.
	 * LinkedList<imp.commands.expressions.FakeExpression>;)}.
	 * 
	 * @throws IMPException thrown by calling to expression
	 * 
	 */
	@Test
	public void testConvertToBinaryExpression() throws IMPException {
		String nameSpace = "Ninja";
		String name = "Turtles";
		LinkedList<FakeExpression> list = new LinkedList<FakeExpression>();

		// populate the list so that it has more than 2 elements in it
		list.add(new FakeExpressionLiteral(0.0));
		list.add(new FakeExpressionLiteral(1.1));
		list.add(new FakeExpressionLiteral(2.2));

		Function.convertToBinaryExpression(nameSpace, name, list);
	}

	/**
	 * Test method for {@link imp.commands.expressions.Function#equals(java.lang.Object}.
	 * 
	 * @throws IMPException thrown by calling to expression
	 * 
	 */
	@Test
	public void testEquals() throws IMPException {
		String nameSpace = "Ninja";
		String name = "Turtles";
		LinkedList<FakeExpression> list = new LinkedList<FakeExpression>();

		// populate the list so that it has more than 2 elements in it
		list.add(new FakeExpressionLiteral(0.0));

		Function f0 = new Function(nameSpace, name, list);
		Function f1 = new Function(nameSpace, name, list);

		assertEquals(f0.equals(f1), true);
	}

	/**
	 * Test method for {@link imp.commands.expressions.Function#equals(java.lang.Object}.
	 * 
	 * @throws IMPException thrown by calling to expression
	 * 
	 */
	@Test
	public void testEqualsDifferentInstance() throws IMPException {
		String nameSpace = "Ninja";
		String name = "Turtles";
		LinkedList<FakeExpression> list = new LinkedList<FakeExpression>();

		// populate the list so that it has more than 2 elements in it
		list.add(new FakeExpressionLiteral(0.0));

		Function f0 = new Function(nameSpace, name, list);

		assertEquals(f0.equals(1), false);
	}

	/**
	 * Test method for {@link imp.commands.expressions.Function#equals(java.lang.Object}.
	 * 
	 * @throws IMPException thrown by calling to expression
	 * 
	 */
	@Test
	public void testEqualsSame() throws IMPException {
		String nameSpace = "Ninja";
		String name = "Turtles";
		LinkedList<FakeExpression> list = new LinkedList<FakeExpression>();

		// populate the list so that it has more than 2 elements in it
		list.add(new FakeExpressionLiteral(0.0));

		Function f0 = new Function(nameSpace, name, list);

		assertEquals(f0.equals(f0), true);
	}
}
