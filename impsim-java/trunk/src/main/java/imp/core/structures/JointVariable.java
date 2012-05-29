/**
 * JointVariable.java
 * March 31, 2011
 */
package imp.core.structures;

import imp.core.model.elements.Joint;
import imp.core.model.elements.Joint.JVAR;
import imp.core.observer.AbstractSubject;
import imp.core.observer.NotificationType;

/**
 * Represents a joint variable for a joint. This contains movement information for a particular joint.
 * 
 * @author edmissonj
 * @edit edmissonj Added observer pattern.
 * @edit dykstran Updated JavaDoc
 * @version 1.11
 */
public class JointVariable extends AbstractSubject {

	/**
	 * The magnitude of the joint variable.
	 */
	private double magnitude;

	/**
	 * The joint variable's velocity.
	 */
	private double velocity;

	/**
	 * The joint variable's acceleration.
	 */
	private double acceleration;

	/**
	 * The joint varaible's type.
	 */
	private JVAR type;

	/**
	 * Creates a new joint variable with the specified magnitude.
	 * 
	 * @param mag the magnitude of the joint variable.
	 */
	public JointVariable(double mag) {
		this.magnitude = mag;
		this.velocity = 0;
		this.acceleration = 0;

	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {

		// check if same object
		if (this == otherObject) {
			return true;
		}

		// check if passed object is a JointVariable
		if (!(otherObject instanceof JointVariable)) {
			return false;
		} else {
			// cast object into cylinder for comparison
			JointVariable otherJVar = (JointVariable) otherObject;
			// return whether EVERY attribute is the same
			return this.type.equals(otherJVar.type) && this.acceleration == otherJVar.acceleration && this.magnitude == otherJVar.magnitude
					&& this.velocity == otherJVar.velocity;
		}
	}

	/**
	 * Get the acceleration of this joint variable.
	 * 
	 * @return the acceleration.
	 */
	public double getAcceleration() {
		return this.acceleration;
	}

	/**
	 * Get the magnitude of this joint variable.
	 * 
	 * @return the magnitude.
	 */
	public double getMagnitude() {

		return this.magnitude;
	}

	/**
	 * Gets the joint variable type of this joint variable.
	 * 
	 * @return the type of this joint variable.
	 */
	public JVAR getType() {
		return this.type;
	}

	/**
	 * Get the velocity of this joint variable.
	 * 
	 * @return the velocity of this joint variable.
	 */
	public double getVelocity() {
		return this.velocity;
	}

	/**
	 * Set the acceleration of this joint variable.
	 * 
	 * @param acceleration the new acceleration of the joint variable.
	 */
	public void setAcceleration(double acceleration) {
		if (this.type == Joint.JVAR.PHI) {
			this.notifyObservers(NotificationType.phiAccleration);
		} else if (this.type == Joint.JVAR.PSI) {
			this.notifyObservers(NotificationType.psiAccleration);
		} else if (this.type == Joint.JVAR.THETA) {
			this.notifyObservers(NotificationType.thetaAccleration);
		} else if (this.type == Joint.JVAR.XDISPLACEMENT) {
			this.notifyObservers(NotificationType.xAccleration);
		} else if (this.type == Joint.JVAR.YDISPLACEMENT) {
			this.notifyObservers(NotificationType.yAccleration);
		} else if (this.type == Joint.JVAR.ZDISPLACEMENT) {
			this.notifyObservers(NotificationType.zAccleration);
		}
		this.acceleration = acceleration;
	}

	/**
	 * Set the magnitude of this joint variable.
	 * 
	 * @param magnitude the new magnitude of the joint variable.
	 */
	public void setMagnitude(double magnitude) {
		if (this.type == Joint.JVAR.PHI) {
			this.notifyObservers(NotificationType.phiMagnitude);
		} else if (this.type == Joint.JVAR.PSI) {
			this.notifyObservers(NotificationType.psiMagnitude);
		} else if (this.type == Joint.JVAR.THETA) {
			this.notifyObservers(NotificationType.thetaMagnitude);
		} else if (this.type == Joint.JVAR.XDISPLACEMENT) {
			this.notifyObservers(NotificationType.xMagnitude);
		} else if (this.type == Joint.JVAR.YDISPLACEMENT) {
			this.notifyObservers(NotificationType.yMagnitude);
		} else if (this.type == Joint.JVAR.ZDISPLACEMENT) {
			this.notifyObservers(NotificationType.zMagnitude);
		}
		this.magnitude = magnitude;
	}

	/**
	 * Sets the type of joint variable.
	 * 
	 * @param type the JVAR type to set this joint variable to.
	 */
	public void setType(JVAR type) {
		this.type = type;
	}

	/**
	 * Set the velocity of this joint variable.
	 * 
	 * @param velocity the new velocity of this joint variable.
	 */
	public void setVelocity(double velocity) {
		if (this.type == Joint.JVAR.PHI) {
			this.notifyObservers(NotificationType.phiVelocity);
		} else if (this.type == Joint.JVAR.PSI) {
			this.notifyObservers(NotificationType.psiVelocity);
		} else if (this.type == Joint.JVAR.THETA) {
			this.notifyObservers(NotificationType.thetaVelocity);
		} else if (this.type == Joint.JVAR.XDISPLACEMENT) {
			this.notifyObservers(NotificationType.xVelocity);
		} else if (this.type == Joint.JVAR.YDISPLACEMENT) {
			this.notifyObservers(NotificationType.yVelocity);
		} else if (this.type == Joint.JVAR.ZDISPLACEMENT) {
			this.notifyObservers(NotificationType.zVelocity);
		}
		this.velocity = velocity;
	}
}
