package imp.core.exceptions;

/**
 * Thrown when an attempt to retrieve a JointBuilder from the DynamicJointBuilder that doesn't exist
 * 
 * @author zastrowm
 */
public class NonExistentJointEntry extends IMPException {

	/** The id used in serialization */
	private static final long serialVersionUID = 4770282874813207712L;

	/**
	 * Instantiates a new non existent joint entry.
	 * 
	 * @param jointName the joint name that is not registered
	 */
	public NonExistentJointEntry(String jointName) {
		super(String.format("The joint type %s is not registered", jointName));

	}

}
