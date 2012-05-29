/**
 * FunctionSignature.java
 * Sep 18, 2011
 */
package imp.core.expressions;

import imp.core.exceptions.expressions.InvalidFunctionSignature;

import java.util.Arrays;

import org.apache.commons.lang3.builder.HashCodeBuilder;

/**
 * 
 * 
 * @author zastrowm
 * @version 1.0
 */
public class FunctionSignature {

	public final String name;
	public final String namespace;

	public final ExpressionType returnType;
	public final ExpressionType[] parameterTypes;

	/**
	 * @param namespace the namespace of the function
	 * @param name the name of the function
	 * @param returnType the return type of the function
	 * @param parameterTypes the parameter types of the function
	 */
	public FunctionSignature(String namespace, String name, ExpressionType returnType, ExpressionType[] parameterTypes) {
		this.namespace = namespace.toLowerCase();
		this.name = name.toLowerCase();
		this.returnType = returnType;
		this.parameterTypes = parameterTypes;
	}

	/**
	 * @param namespace the namespace of the function
	 * @param name the name of the function
	 * @param parameterTypes the parameter types of the function
	 */
	public FunctionSignature(String namespace, String name, ExpressionType[] parameterTypes) {
		this(namespace, name, ExpressionType.invalid, parameterTypes);
	}

	/**
	 * Instantiates a new function signature.
	 * 
	 * @param namespace the namespace
	 * @param name the name
	 * @param method the method
	 * @throws InvalidFunctionSignature the invalid function signature
	 */
	public FunctionSignature(String namespace, String name, MethodDelgate method) throws InvalidFunctionSignature {
		this.namespace = namespace;
		this.name = name;
		this.returnType = method.returnType;
		this.parameterTypes = method.parameterTypes;
	}

	/**
	 * Get the fully qualified function name
	 * 
	 * @return the fully qualified name
	 */
	public String getFullName() {
		return namespace + "~" + name;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return String.format("%s %s~%s(%s)", returnType, namespace, name, Arrays.toString(parameterTypes));
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		return new HashCodeBuilder().append(name).append(namespace).append(parameterTypes).toHashCode();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(obj instanceof FunctionSignature))
			return false;
		FunctionSignature other = (FunctionSignature) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		if (namespace == null) {
			if (other.namespace != null)
				return false;
		} else if (!namespace.equals(other.namespace))
			return false;
		if (!Arrays.equals(parameterTypes, other.parameterTypes))
			return false;
		return true;
	}

	/**
	 * Whether or not one signature matches another
	 * 
	 * @param sig the signature to compare to
	 * @param withNamespace true if the namespace should be compared
	 * @return true if they match
	 */
	public boolean matches(FunctionSignature sig, boolean withNamespace) {

		boolean nameParameterMatch = sig.name.equals(this.name) && Arrays.equals(sig.parameterTypes, this.parameterTypes);

		if (!withNamespace)
			return nameParameterMatch;
		else
			return nameParameterMatch && sig.namespace.equals(this.namespace);
	}

}
