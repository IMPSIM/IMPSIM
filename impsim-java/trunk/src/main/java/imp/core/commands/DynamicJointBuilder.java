package imp.core.commands;

import imp.core.exceptions.NonExistentJointEntry;
import imp.core.exceptions.WrappedException;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;

import org.apache.commons.lang3.ArrayUtils;

/**
 * Class to find all implemented joints in the jar, and allow creation of those joints
 * 
 * @author zastrowm
 */
public class DynamicJointBuilder {

	/** All of the joints in the system. */
	private static HashMap<String, JointBuilder> joints = new HashMap<String, JointBuilder>();

	/**
	 * Instantiates a new dynamic joint builder. Private to disallow instances
	 */
	private DynamicJointBuilder() {
	}

	static {
		try {

			// put all joints that should be able to be created here:
			//@formatter:off
			Class<?>[] classes = new Class<?>[]{
				imp.core.commands.joints.CylinderCommand.class,
				imp.core.commands.joints.RevoluteCommand.class,
				imp.core.commands.joints.PrismCommand.class,
			};
			//@formatter:on

			// go through all the classes with the annotation and add them
			for (Class<?> aClass : classes) {

				// make sure that we actually have the annotation
				if (aClass.getAnnotation(JointEntry.class) == null)
					continue;

				JointEntry annotation = aClass.getAnnotation(JointEntry.class);
				JointBuilder builder = new JointBuilder(annotation, aClass);
				joints.put(annotation.name().toLowerCase(), builder);

				// go through all the methods of the class with that annotation as well
				for (Method aMethod : aClass.getMethods()) {
					if (aMethod.isAnnotationPresent(JointEntry.class)) {
						// only static methods are allowed
						if (!Modifier.isStatic(aMethod.getModifiers())) {
							throw new Exception("Only methods that are static can be annotated with " + JointEntry.class.getSimpleName());
						}

						JointEntry methodAnnotation = aMethod.getAnnotation(JointEntry.class);
						JointBuilder methodBuilder = new JointBuilder(methodAnnotation, aMethod);
						joints.put(methodAnnotation.name().toLowerCase(), methodBuilder);

					}
				}

			}

		} catch (Exception e) {
			// scream that there is a PROBLEM
			throw new RuntimeException(e);
		}
	}

	/**
	 * Check to see if a joint with the specified name is registered.
	 * 
	 * @param type the type of joint to test
	 * @return true, if the joint is registered, false otherwise
	 */
	public static boolean containsType(String type) {
		return joints.containsKey(type.toLowerCase());
	}

	/**
	 * Creates an instance of a joint
	 * 
	 * @param jointType the joint type to create
	 * @param args the arguments to pass to the joint
	 * @return the command that was created for the joint
	 * @throws NonExistentJointEntry if the joint entry does not exist
	 * @throws InvocationTargetException if the method is not available
	 * @throws IllegalArgumentException if the incorrect type of arguments was passed
	 * @throws IllegalAccessException if the method cannot be called by the user
	 * @throws InstantiationException if the method is not available
	 */
	public static Command createInstance(String jointType, String jointName, String body1, String body2, Object... args) throws NonExistentJointEntry,
			WrappedException {
		try {
			args = ArrayUtils.addAll(new Object[] { jointName, body1, body2 }, args);
			return getJointBuilder(jointType).createInstance(args);

			// catch any other invocation exceptions and wrap them in IMPException
		} catch (IllegalAccessException e) {
			throw new WrappedException(e);
		} catch (IllegalArgumentException e) {
			throw new WrappedException(e);
		} catch (InvocationTargetException e) {
			throw new WrappedException(e);
		} catch (InstantiationException e) {
			throw new WrappedException(e);
		}
	}

	/**
	 * Gets the joint builder associated with a joint type.
	 * 
	 * @param jointType the type of joint associated with the joint builder
	 * @return the joint builder
	 * @throws NonExistentJointEntry if the joint entry has not been registered with the system
	 */
	public static JointBuilder getJointBuilder(String jointType) throws NonExistentJointEntry {
		if (!joints.containsKey(jointType.toLowerCase())) {
			throw new NonExistentJointEntry(jointType);
		}

		return joints.get(jointType.toLowerCase());
	}

	/**
	 * Gets the all builders registered to the system.
	 * 
	 * @return all of the builders registered to the system.
	 */
	public static Collection<JointBuilder> getAllBuilders() {
		// make sure that they cannot modify it!
		return Collections.unmodifiableCollection(joints.values());
	}
}
