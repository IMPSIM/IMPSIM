/**
 * LoopVariable.java
 */
package imp.core.model.loop;

import imp.core.model.elements.Joint.JVAR;

/**
 * This class is used in loop closure to keep all data for a changed joint.
 * 
 * @author workmanjz
 * 
 */
public class LoopVariable {

	private String joint = "";
	private JVAR jvarType;
	private double magnitude = 0.0;

	/**
	 * 
	 * @param joint name of the joint being changed
	 * @param jvar which jvar is being modified
	 * @param magnitude magnitude of the change(in radians)
	 */
	public LoopVariable(String joint, JVAR jvar, double magnitude) {
		jvarType = jvar;
		this.joint = joint;
		this.magnitude = magnitude;
	}

	/**
	 * Gets the joint that is in variance.
	 * 
	 * @return the name of the joint
	 */
	public String getJoint() {
		return joint;
	}

	/**
	 * Gets the jvar type that is changing.
	 * 
	 * @return the JVAR type that is changing
	 */
	public JVAR getJvarType() {
		return jvarType;
	}

	/**
	 * Gets the magnitude the joint is changing.
	 * 
	 * @return the magnitude of the JVAR changing.
	 */
	public double getMagnitude() {
		return magnitude;
	}

}
