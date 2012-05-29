package imp.core.model.loop;


import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;

import java.util.LinkedList;
import java.util.List;


/**
 * Loop data structure The loop is a list of joints in the order they are found in the loop
 * 
 * @author workmanjz created 2-13-2011
 * @version 1.0
 * Removed loop closure code on 10/8 since it is now in the LoopCloser.java class
 */
public class Loop {

	protected List<Joint> loop = new LinkedList<Joint>();

	/**
	 * Add each joint to the list of joints in order
	 * 
	 * @param loop list of joints in order
	 * @param ground The body that has been assigned as ground
	 */
	public Loop(List<Joint> loop, Body ground) {
		Body lastBody = ground;
		for (int i = 0; i < loop.size(); i++) {
			for (Joint j : loop) {
				// determine next joint in the loop
				if (j.getBodyBefore() == lastBody) {
					this.loop.add(j);
					lastBody = j.getBodyAfter();
					break;
				}
			}
		}
		

	}
	/**
	 * 
	 * @return the list of both bodies and joints, this is the order of bodies and joints connecting them
	 */
	public final List<Joint> getLoop() {
		return this.loop;
	}

	/**
	 * @return a String representation of this Element
	 */
	@Override
	public String toString() {
		return this.loop.toString();
	}
}
