/**
 * Function.java
 * Sep 27, 2011
 */
package imp.core.commands.expressions;

import imp.core.exceptions.IMPException;
import imp.core.expressions.Expression;
import imp.core.expressions.ExpressionType;
import imp.core.expressions.FunctionExpression;
import imp.core.expressions.FunctionSignature;
import imp.core.model.Model;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * A fake expression function
 * 
 * @author zastrowm
 * @version 1.0
 */
public class Function implements FakeExpression {

	/**
	 * The namespace of this function.
	 */
	public final String namespace;

	/**
	 * The name of this function.
	 */
	public final String name;

	/**
	 * The parameters of this function.
	 */
	public final FakeExpression parameters[];

	/**
	 * Create a new function
	 * 
	 * @param namespace the name space of the function
	 * @param name the name of the function
	 * @param args the arguments to the function
	 */
	public Function(String namespace, String name, FakeExpression... args) {
		imp.core.exceptions.NullParameterException.check(namespace, "namespace", 0);
		imp.core.exceptions.NullParameterException.check(name, "name", 1);

		this.name = name;
		this.namespace = namespace;
		this.parameters = args;
	}

	/**
	 * Create a new function
	 * 
	 * @param namespace the name space of the function
	 * @param name the name of the function
	 * @param args the arguments to the function
	 */
	public Function(String namespace, String name, List<FakeExpression> args) {

		FakeExpression[] argsArray = new FakeExpression[args.size()];

		for (int i = 0; i < args.size(); i++) {
			argsArray[i] = args.get(i);
		}

		imp.core.exceptions.NullParameterException.check(namespace, "namespace", 0);
		imp.core.exceptions.NullParameterException.check(name, "name", 1);

		this.name = name;
		this.namespace = namespace;
		this.parameters = argsArray;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.commands.expressions.FakeExpression#toExpression(imp.model.Model)
	 */
	@Override
	public Expression toExpression(Model model) throws IMPException {

		Expression[] params = new Expression[parameters.length];
		ExpressionType[] types = new ExpressionType[parameters.length];

		int i = 0;
		for (FakeExpression fakeExpression : parameters) {
			params[i] = fakeExpression.toExpression(model);
			types[i] = params[i].type;
			i++;
		}

		// create a function signature so that we can look up the function
		FunctionSignature sig = new FunctionSignature(namespace, name, types);
		imp.core.expressions.Function function = model.functionManager.getFunction(sig);

		return new FunctionExpression(function, params);
	}

	/**
	 * Convert a bunch of expressions to a binary expression. Helper method for the parser
	 * 
	 * @param namespace the namespace
	 * @param name the name
	 * @param list the list
	 * @return the fake expression
	 */
	public static FakeExpression convertToBinaryExpression(String namespace, String name, LinkedList<FakeExpression> list) {

		if (list.size() == 1) {
			return list.pop();
		}

		// keep combining the first two until we only have two expressions ie
		// "((x + y) + z)" and "a"
		while (list.size() > 2) {
			FakeExpression combo = new Function(namespace, name, list.pop(), list.pop());
			list.addFirst(combo);
		}
		return new Function(namespace, name, list.pop(), list.pop());
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		// return hashcode generated from Apache HashCodeBuilder
		return new HashCodeBuilder().append(this.namespace).append(this.name).append(this.parameters).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {

		// check if same object
		if (this == otherObject) {
			return true;
		} else if (!(otherObject instanceof Function)) {
			return false;
		} else {
			Function other = (Function) otherObject;
			// return whether EVERY attribute is the same
			return other.namespace.equals(this.namespace) && other.name.equals(this.name) && Arrays.equals(parameters, other.parameters);
		}

	}

}
