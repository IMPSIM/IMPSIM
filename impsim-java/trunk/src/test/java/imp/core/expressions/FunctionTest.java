package imp.core.expressions;

import static org.junit.Assert.assertEquals;
import imp.core.Constants;
import imp.core.exceptions.WrappedException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.exceptions.expressions.FunctionAmbiguous;
import imp.core.exceptions.expressions.FunctionSignatureDoesNotExist;
import imp.core.exceptions.expressions.InvalidFunctionSignature;
import imp.core.exceptions.expressions.MethodReturnValue;
import imp.core.expressions.Expression;
import imp.core.expressions.ExpressionLiteral;
import imp.core.expressions.ExpressionType;
import imp.core.expressions.FunctionLibrary;
import imp.core.expressions.FunctionManager;
import imp.core.expressions.FunctionSignature;
import imp.core.expressions.MethodDelgate;
import imp.core.model.Model;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Test adding functions to the function manager
 * 
 * @author zastrowm
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class FunctionTest {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	final double left = 3.4;
	final double right = 9343.0;

	static Method[] methods;

	static FunctionSignature minFunction, maxFunction;

	/**
	 * Static initializer block
	 */
	static {
		try {
			// get the max/min methods
			methods = new Method[] { TestClass.class.getMethod("max", double.class, double.class),
					TestClass.class.getMethod("min", double.class, double.class), };

			maxFunction = new FunctionSignature("", "max", new ExpressionType[] { ExpressionType.number, ExpressionType.number });
			minFunction = new FunctionSignature("", "min", new ExpressionType[] { ExpressionType.number, ExpressionType.number });

		} catch (Exception e) {
			assert (false);
		}
	}

	/**
	 * Test to amek sure that expressions are evaluating correcting
	 * 
	 * @throws WrappedException the wrapped exception
	 * @throws MethodReturnValue the method return value
	 * @throws SecurityException the security exception
	 * @throws NoSuchMethodException the no such method exception
	 * @throws InvalidFunctionSignature the invalid function signature
	 * @throws FunctionAlreadyExists the function already exists
	 */
	@Test
	public void testFunctions() throws WrappedException, MethodReturnValue, SecurityException, NoSuchMethodException, InvalidFunctionSignature,
			FunctionAlreadyExists {

		// the function needs an array of arguments
		Expression[] args = new Expression[] { new ExpressionLiteral(left), new ExpressionLiteral(right) };

		// Get the max/min functions
		imp.core.expressions.Function maxFunc = new imp.core.expressions.Function("", "max", new MethodDelgate(new TestClass(), methods[0]));
		imp.core.expressions.Function mixFunc = new imp.core.expressions.Function("", "min", new MethodDelgate(new TestClass(), methods[1]));

		// create expressions to execute
		imp.core.expressions.FunctionExpression maxFunction = new imp.core.expressions.FunctionExpression(maxFunc, args);
		imp.core.expressions.FunctionExpression minFunction = new imp.core.expressions.FunctionExpression(mixFunc, args);

		// get the raw value of execution
		Double maxRet = (Double) maxFunction.rawValue();
		Double minRet = (Double) minFunction.rawValue();

		// make sure that the results are correct
		assertEquals(right, maxRet, Constants.ERROR_TOLERANCE);
		assertEquals(left, minRet, Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test adding a class to a function manager
	 * 
	 * @throws FunctionAlreadyExists the function already exists
	 * @throws FunctionSignatureDoesNotExist the function signature does not exist
	 * @throws FunctionAmbiguous the function ambiguous
	 * @throws IllegalArgumentException the illegal argument exception
	 * @throws IllegalAccessException the illegal access exception
	 * @throws InvocationTargetException the invocation target exception
	 */
	@Test
	public void testClass() throws FunctionAlreadyExists, FunctionSignatureDoesNotExist, FunctionAmbiguous, IllegalArgumentException, IllegalAccessException,
			InvocationTargetException {
		// create a function manager
		FunctionManager funcManager = new FunctionManager();
		// add all methods in the class
		funcManager.addFunctions(new TestClass());

		// get the max function sig
		FunctionSignature sig = new FunctionSignature("", "max", new ExpressionType[] { ExpressionType.number, ExpressionType.number });
		// execute
		double result = (Double) funcManager.getFunction(sig).method.invoke(left, right);
		// verify
		assertEquals(result, right, Constants.ERROR_TOLERANCE);

		// get the min funciton sig
		FunctionSignature sig2 = new FunctionSignature("", "min", new ExpressionType[] { ExpressionType.number, ExpressionType.number });
		// execute
		double result2 = (Double) funcManager.getFunction(sig2).method.invoke(left, right);
		// verify
		assertEquals(result2, left, Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test adding a class that fails
	 * 
	 * @throws FunctionAlreadyExists the function already exists
	 */
	@Test
	public void testAddClassFail() throws FunctionAlreadyExists {
		// can't add the same function with the same function sig
		FunctionManager funcManager = new FunctionManager();
		funcManager.addFunctions(new TestClass());

		thrown.expect(FunctionAlreadyExists.class);
		funcManager.addFunctions(new TestClass());
	}

	/**
	 * Test adding a method to a function manager that fails
	 * 
	 * @throws FunctionAlreadyExists the function already exists
	 * @throws InvalidFunctionSignature the invalid function signature
	 * @throws SecurityException the security exception
	 * @throws NoSuchMethodException the no such method exception
	 */
	@Test
	public void testAddMethodFail() throws FunctionAlreadyExists, InvalidFunctionSignature, SecurityException, NoSuchMethodException {
		FunctionManager funcManager = new FunctionManager();
		funcManager.addFunctions(new TestClass());
		// can't add a function with the same sig as an already added function
		imp.core.expressions.Function maxFunc = new imp.core.expressions.Function("", "max", new MethodDelgate(new TestClass(), methods[0]));

		thrown.expect(FunctionAlreadyExists.class);
		funcManager.addFunction(maxFunc);
	}

	/**
	 * Test adding a method to a function manager with a different namespace
	 * 
	 * @throws Exception the exception
	 */
	@Test
	public void testAddMethodWithAlternativeNamespace() throws Exception {
		FunctionManager funcManager = new FunctionManager();
		funcManager.addFunctions(new TestClass());

		// Perfectly fine, it's in a different namespace!
		imp.core.expressions.Function maxFunc = new imp.core.expressions.Function("mycore", "max", new MethodDelgate(new TestClass(), methods[0]));
		funcManager.addFunction(maxFunc);
	}

	/**
	 * Test adding a function name that already exists but not calling the function iwth a namespace
	 * 
	 * @throws FunctionAlreadyExists the function already exists
	 * @throws InvalidFunctionSignature the invalid function signature
	 * @throws SecurityException the security exception
	 * @throws NoSuchMethodException the no such method exception
	 * @throws FunctionSignatureDoesNotExist the function signature does not exist
	 * @throws FunctionAmbiguous the function ambiguous
	 */
	@Test
	public void testNoNamespaceCollisionFailure() throws FunctionAlreadyExists, InvalidFunctionSignature, SecurityException, NoSuchMethodException,
			FunctionSignatureDoesNotExist, FunctionAmbiguous {
		FunctionManager funcManager = new FunctionManager();
		funcManager.addFunctions(new TestClass());

		// Perfectly fine, it's in a different namespace!
		imp.core.expressions.Function maxFunc = new imp.core.expressions.Function("mycore", "max", new MethodDelgate(new TestClass(), methods[0]));
		funcManager.addFunction(maxFunc);

		// but to retrieve it we need to mention the namespace
		thrown.expect(FunctionAmbiguous.class);
		funcManager.getFunction(maxFunction);
	}

	/**
	 * Same as testNoNamespaceCollisionFailure() but actually using a namespace to call it
	 * 
	 * @throws Exception the exception
	 */
	@Test
	public void testNoNamespaceCollisionSuccess() throws Exception {
		FunctionManager funcManager = new FunctionManager();
		funcManager.addFunctions(new TestClass());

		// Perfectly fine, it's in a different namespace!
		imp.core.expressions.Function maxFunc = new imp.core.expressions.Function("mycore", "max", new MethodDelgate(new TestClass(), methods[0]));
		funcManager.addFunction(maxFunc);

		// but to retrieve it we need to mention the namespace
		FunctionSignature sig = new FunctionSignature("mycore", "max", new ExpressionType[] { ExpressionType.number, ExpressionType.number });
		;
		funcManager.getFunction(sig);
	}

	/**
	 * Test case insensitivity of adding functions
	 * 
	 * @throws FunctionAlreadyExists the function already exists
	 * @throws InvalidFunctionSignature the invalid function signature
	 * @throws SecurityException the security exception
	 * @throws NoSuchMethodException the no such method exception
	 */
	@Test
	public void testCaseInsensitivity() throws FunctionAlreadyExists, InvalidFunctionSignature, SecurityException, NoSuchMethodException {
		// create a function manager
		FunctionManager funcManager = new FunctionManager();
		// add all methods in the class
		funcManager.addFunctions(new TestClass());

		// get the max function sig
		FunctionSignature maxFuncUpper = new FunctionSignature("", "MAX", new ExpressionType[] { ExpressionType.number, ExpressionType.number });
		FunctionSignature maxFuncLower = new FunctionSignature("", "max", new ExpressionType[] { ExpressionType.number, ExpressionType.number });

		assertEquals(maxFuncLower, maxFuncUpper);
	}

	/**
	 * Test class for adding methods
	 */
	public static class TestClass implements FunctionLibrary {
		@imp.core.expressions.attributes.Function("max")
		static public double max(double a, double b) {
			return Math.max(a, b);
		}

		@imp.core.expressions.attributes.Function("min")
		static public double min(double a, double b) {
			return Math.min(a, b);
		}

		@Override
		public void initialize(Model model) {
			// TODO Auto-generated method stub

		}
	}

}
