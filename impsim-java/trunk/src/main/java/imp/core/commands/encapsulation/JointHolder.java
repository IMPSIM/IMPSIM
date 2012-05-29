/**
 * JointHolder.java
 */
package imp.core.commands.encapsulation;

import imp.core.model.elements.Joint;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

/**
 * Class for encapsulating joints
 * @author zastrowm
 *
 */
public class JointHolder {
	
	private Joint joint;
	
	/**
	 * Instantiates a new joint holder.
	 *
	 * @param j the j
	 */
	public JointHolder(Joint j) {
		joint = j;
	}
	
	/**
	 * Gets the after position matrix.
	 *
	 * @return the after position matrix
	 */
	public PositionMatrix getAfterPositionMatrix() {
		return joint.getAxisAfter().getAbsolutePosition().copy();
	}
	
	/**
	 * Gets the before position matrix.
	 *
	 * @return the before position matrix
	 */
	public PositionMatrix getBeforePositionMatrix() {
		return joint.getAxisBefore().getAbsolutePosition().copy();
	}
	
	/**
	 * Gets the position of the joint
	 *
	 * @return the position of the joint
	 */
	public Point getPosition() {
		PositionMatrix pm = getBeforePositionMatrix();
		return new Point(pm.get(0, 3), pm.get(1, 3), pm.get(2, 3));
	}
	
	/**
	 * Gets the name.
	 *
	 * @return the name
	 */
	public String getName() {
		return joint.getName();
	}
	
	public String getModelFile(){
		
		return "";
	}
	
	
}
