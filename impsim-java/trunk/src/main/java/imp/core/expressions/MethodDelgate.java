/**
 * 
 */
package imp.core.expressions;

import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.expressions.InvalidFunctionSignature;

import java.lang.reflect.Method;

/**
 * A container so that we can easily call methods
 * 
 * @author zastrowm
 * 
 */
public class MethodDelgate {

	private final Object instance;
	private final Method method;

	public final ExpressionType returnType;
	public final ExpressionType[] parameterTypes;

	public MethodDelgate(Object instance, Method method) throws InvalidFunctionSignature {
		NullParameterException.check(instance, "instance", 0);
		NullParameterException.check(method, "method", 1);

		this.instance = instance;
		this.method = method;

		// set the return type
		this.returnType = ExpressionType.convertType(method.getReturnType());

		// it must return a valid type:
		if (this.returnType == ExpressionType.invalid)
			throw new InvalidFunctionSignature(method.getReturnType());

		// it must be public at least
		if ((method.getModifiers() & java.lang.reflect.Modifier.PUBLIC) == 0) {
			throw new InvalidFunctionSignature();
		}

		// get the parameter types
		Class<?> paramTypes[] = method.getParameterTypes();
		parameterTypes = new ExpressionType[paramTypes.length];

		// convert the parameter types to ExpressionTypes
		for (int i = 0; i < paramTypes.length; i++) {
			parameterTypes[i] = ExpressionType.convertType(paramTypes[i]);
			if (parameterTypes[i] == ExpressionType.invalid || parameterTypes[i] == ExpressionType.none)
				throw new InvalidFunctionSignature(i, paramTypes[i]);
		}

	}

	/**
	 * Invoke the method on the object
	 * 
	 * @param params the parameters to execute the function with
	 * @return the result of running the function
	 */
	public Object invoke(Object... params) {
		try {
			return method.invoke(instance, params);
		} catch (Exception e) {
			return null;
		}
	}

}
