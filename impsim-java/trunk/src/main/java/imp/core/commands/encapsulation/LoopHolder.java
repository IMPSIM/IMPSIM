/**
 * LoopHolder.java
 */
package imp.core.commands.encapsulation;

import imp.core.model.elements.Joint;
import imp.core.model.loop.Loop;

import java.util.LinkedList;
import java.util.List;

/**
 * Class for encapsulating Loops
 * @author zastrowm
 *
 */
public class LoopHolder {

	private Loop loop;
	
	/**
	 * Instantiates a new loop holder.
	 *
	 * @param loop the loop
	 */
	public LoopHolder(Loop  loop) {
		this.loop = loop;
	}
	
	/**
	 * Gets the joints in the loop
	 *
	 * @return the joints
	 */
	public List<JointHolder> getJoints() {
		List<JointHolder> joints = new LinkedList<JointHolder>();
		
		for (Joint j : loop.getLoop()) {
			joints.add(new JointHolder(j));
		}
		
		return joints;
	}
	

	
}
