/**
 * 
 */
package imp.core.commands;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * Represents an interface for all joints in the jar
 * 
 * @author zastrowm
 */
@Retention(RetentionPolicy.RUNTIME)
public @interface JointEntry {

	/** The Constant NULL used because annotations can't default to null. */
	public static final String NULL = "NULL";

	/**
	 * The Name of the joint.
	 * 
	 * @return the string name of the joint
	 */
	public String name();

	/**
	 * The third argument used when creating the joint.
	 * 
	 * @note argument numbering starts at 3 because argument 0,1,&2 are names of joints/bodies
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg3() default NULL;

	/**
	 * The forth argument used when creating the joint.
	 * 
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg4() default NULL;

	/**
	 * The fifth argument used when creating the joint.
	 * 
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg5() default NULL;

	/**
	 * The sixth argument used when creating the joint.
	 * 
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg6() default NULL;

	/**
	 * The seventh argument used when creating the joint.
	 * 
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg7() default NULL;

	/**
	 * The eighth argument used when creating the joint.
	 * 
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg8() default NULL;

	/**
	 * The ninth argument used when creating the joint.
	 * 
	 * @return the name and description of the argument, separated by a colon
	 */
	public String arg9() default NULL;

}
