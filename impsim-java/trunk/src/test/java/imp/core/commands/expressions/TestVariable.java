/**
 * 
 */
package imp.core.commands.expressions;

import static org.junit.Assert.assertEquals;
import imp.core.commands.expressions.Variable;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.parser.ModelVariableAlreadyExists;
import imp.core.exceptions.parser.ModelVariableDoesNotExist;
import imp.core.expressions.Expression;
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
public class TestVariable {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	private String name;

	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		name = "testName";
	}

	/**
	 * Test method for {@link imp.core.commands.expressions.Variable#Variable(java.lang.String)}.
	 */
	@Test
	public void testVariable() {
		new Variable(name);
	}

	/**
	 * Test method for {@link imp.core.commands.expressions.Variable#Variable(java.lang.String)}.
	 */
	@Test
	public void testVariableNullParameter() {
		this.thrown.expect(NullParameterException.class);
		new Variable(null);
	}

	/**
	 * Test method for {@link imp.core.commands.expressions.Variable#toExpression(imp.core.model.Model)}.
	 * 
	 * @throws ModelVariableDoesNotExist
	 * @throws ModelVariableAlreadyExists
	 */
	@Test
	public void testToExpression() throws ModelVariableDoesNotExist, ModelVariableAlreadyExists {

		Model testModel = new Model();
		Expression enl = new ExpressionLiteral(3.14);

		testModel.variableManager.add(name, enl);

		Variable var = new Variable(name);

		assertEquals(var.toExpression(testModel), enl);
	}
	
	/**
	 * Test method for {@link imp.core.commands.expressions.Variable#Equals(java.lang.Object)}.
	 * 
	 */
	@Test
	public void testEquals(){
		Variable v = new Variable("name");
		
		//self
		assertEquals(v.equals(v),true);
		
		//different instance
		assertEquals(v.equals(1),false);
		
		//same attributes
		Variable v2 = new Variable("name");
		assertEquals(v.equals(v2),true);
		
		//different attributes
		Variable v3 = new Variable("name2");
		assertEquals(v.equals(v3),false);
	}

}
