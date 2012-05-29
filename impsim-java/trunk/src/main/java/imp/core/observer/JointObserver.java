/**
 * JointObserver.java
 * May 7, 2011
 */
package imp.core.observer;

import java.util.EnumSet;

/**
 * Class for observing the changes in joints and joint variables
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public abstract class JointObserver implements Observer {

	/**
	 * Contains the type of subject the observer is watching
	 */
	protected EnumSet<NotificationType> watchTypes;

	/**
	 * Creates a new joint observer.
	 * 
	 * @param watchTypes the types of updates the observer is presenting.
	 */
	public JointObserver(EnumSet<NotificationType> watchTypes) {
		this.watchTypes = watchTypes;
	}

	/*
	 * (non-Javadoc)
	 * @see imp.observer.Observer#update(int)
	 */
	@Override
	public void update(NotificationType updateType) {
		if (watchTypes.contains(updateType)) {
			this.execute();
		}
	}

}
