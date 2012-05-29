/*
 * 
 */
package imp.core.commands;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.apache.commons.lang3.StringUtils;

/**
 * A class that can be used to created joints loaded dynamically.
 * 
 * @author zastrowm
 */
public class JointBuilder {

	/** The constructor or static method that can be used to create the joint command. */
	private final Object creatorReference;

	/** True if creatorReference represents a static method. */
	private final boolean isStaticMethod;

	/** The [display] name of the joint command. */
	public final String name;

	/** The arguments for the joint command. */
	private List<JointArgumentInfo> arguments = new ArrayList<JointArgumentInfo>();

	/**
	 * Instantiates a new joint builder.
	 * 
	 * @param annotation the annotation that was annotating the joint
	 * @param associatedMethod the method that was annotated
	 * @throws Exception the exception
	 */
	/* package */JointBuilder(JointEntry annotation, Method associatedMethod) throws Exception {
		isStaticMethod = true;
		name = annotation.name();
		creatorReference = associatedMethod;
		Class<?>[] parameters = associatedMethod.getParameterTypes();

		initArguments(parameters, annotation);
	}

	/**
	 * Instantiates a new joint builder.
	 * 
	 * @param annotation the annotation that was annotating the joint
	 * @param associatedClass the class that was annotated
	 * @throws Exception the exception
	 */
	/* package */JointBuilder(JointEntry annotation, Class<?> associatedClass) throws Exception {
		isStaticMethod = false;
		name = annotation.name();
		Constructor<?> constructor = associatedClass.getConstructors()[0];
		creatorReference = constructor;
		Class<?>[] parameters = constructor.getParameterTypes();

		initArguments(parameters, annotation);
	}

	/**
	 * Initializes the arguments for the JointBuilder
	 * 
	 * @param parameters the parameters associated with the joint
	 * @param annotation the annotation that annotated the joint
	 * @throws Exception the exception
	 */
	private void initArguments(Class<?>[] parameters, JointEntry annotation) throws Exception {
		if (parameters[0] != String.class || parameters[1] != String.class || parameters[2] != String.class)
			throw new Exception("First three arguments of a " + JointEntry.class.getSimpleName() + "constructor must be strings");

		// add the first three arguments, which are always the same
		arguments.add(new JointArgumentInfo(String.class, "JointName", "The name of the joint to create", 0));
		arguments.add(new JointArgumentInfo(String.class, "BodyNameBefore", "The name of the first body being joined", 1));
		arguments.add(new JointArgumentInfo(String.class, "BodyNameAfter", "The name of the second body being joined", 2));

		// add each parameter
		addIfNonNull(annotation.arg3(), 3, parameters);
		addIfNonNull(annotation.arg4(), 4, parameters);
		addIfNonNull(annotation.arg5(), 5, parameters);
		addIfNonNull(annotation.arg6(), 6, parameters);
		addIfNonNull(annotation.arg7(), 7, parameters);
		addIfNonNull(annotation.arg8(), 8, parameters);
		addIfNonNull(annotation.arg9(), 9, parameters);

		arguments = Collections.unmodifiableList(arguments);
	}

	/**
	 * Creates an instance of the join
	 * 
	 * @param args the arguments to pass to the command to create a new instance
	 * @return the command created as a result
	 * @throws InvocationTargetException if the method is not available
	 * @throws IllegalArgumentException if the incorrect type of arguments was passed
	 * @throws IllegalAccessException if the method cannot be called by the user
	 * @throws InstantiationException if the method is not available
	 */
	public Command createInstance(Object... args) throws IllegalAccessException, IllegalArgumentException, InvocationTargetException, InstantiationException {
		if (isStaticMethod) {
			return (Command) (((Method) creatorReference).invoke(null, args));
		} else {
			return (Command) (((Constructor<?>) creatorReference).newInstance(args));
		}
	}

	/**
	 * Gets the arguments associated with the joint.
	 * 
	 * @return the arguments
	 */
	public List<JointArgumentInfo> getArguments() {
		return this.arguments;
	}

	/**
	 * Adds an argument if it is not the default value (NULL)
	 * 
	 * @param argumentText the argument text containing the name and the description
	 * @param paramNumber the parameter number that the argument represents, 0 based
	 * @param parameters all of the parameters for the method/constructor
	 * @throws Exception if the method fails for any reason
	 */
	private void addIfNonNull(String argumentText, int paramNumber, Class<?>[] parameters) throws Exception {
		if (!argumentText.equals(JointEntry.NULL)) {

			String[] parts = StringUtils.split(argumentText, ":", 2);
			if (parts.length != 2) {
				throw new Exception("Argument texts must have name and description seperated by :");
			}

			if (paramNumber >= parameters.length) {
				throw new Exception("Argument number exceeds number of parameters in constructor: " + paramNumber + " >= " + parameters.length);
			}

			// TODO check to make sure size of length = number of parameters
			arguments.add(new JointArgumentInfo(parameters[paramNumber], parts[0], parts[1], paramNumber));
		}
	}
}
