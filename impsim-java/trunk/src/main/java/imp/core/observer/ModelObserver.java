/**
 * ModelObserver.java
 * May 7, 2011
 */
package imp.core.observer;

import java.util.EnumSet;

/**
 * Class for observing models and the changes it has.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public abstract class ModelObserver implements Observer {

	/**
	 * Enumeration containing what type of subject is being observed.
	 */
	private EnumSet<NotificationType> watchTypes;

	/**
	 * Creates a new observer on the model with the specified types.
	 * 
	 * @param watchTypes the types this observer presents.
	 */
	public ModelObserver(EnumSet<NotificationType> watchTypes) {
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
