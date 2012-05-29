/**
 * Gear.java
 * May 11, 2011
 */

package imp.core.model.joints;

import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.elements.Joint;
import imp.core.observer.Observer;
import imp.core.structures.PositionMatrix;

import java.util.List;

/**
 * Class for holding the data of a gear joint
 * 
 * @author hellmerj, dykstran
 * @version 1.1
 */
public class Gear extends Joint {

	// TODO Implement gear joint

	/**
	 * Creates a new gear joint with the given name.
	 * 
	 * @param name the name of the new joint.
	 * @throws NullParameterException thrown if the name is null.
	 * @throws InvalidParameterException thrown if the name is empty.
	 */
	public Gear(String name) throws NullParameterException, InvalidParameterException {
		super(name);
	}

	@Override
	public PositionMatrix getAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		return null;
	}

	@Override
	public PositionMatrix getDerivativeMatrix(JVAR variableType) throws NullParameterException, InvalidParameterException {
		return null;
	}

	@Override
	public List<JVAR> getJVARs() {
		return null;
	}

	@Override
	public PositionMatrix getPhiMatrix() {
		return null;
	}

	@Override
	public PositionMatrix getQOperator(JVAR jvar) {
		return null;
	}

	@Override
	public PositionMatrix getSecondDerivativeMatrix(JVAR thisType, JVAR previousType) throws NullParameterException, InvalidParameterException {
		return null;
	}

	@Override
	public PositionMatrix getVelocityMatrix() throws NullParameterException, InvalidParameterException {
		return null;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {
		return false;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.observer.Subject#addObserver(imp.observer.Observer)
	 */
	@Override
	public void addObserver(Observer obv) {

	}

	/*
	 * (non-Javadoc)
	 * @see imp.model.elements.Joint#hashCode()
	 */
	@Override
	public int hashCode() {
		return 0;
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return null;
	}
}
