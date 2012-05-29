/**
 * BofyObserver.java
 * May 7, 2011
 */
package imp.core.observer;

import java.util.EnumSet;

/**
 * Class for observing the changes in bodies.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public class BodyObserver implements Observer {

	/**
	 * Flag denoting which things (joint variables, etc) to observe.
	 */
	EnumSet<NotificationType> watchTypes;

	/**
	 * Creates a new observer.
	 * 
	 * @param type Flag denoting what to watch.
	 */
	public BodyObserver(EnumSet<NotificationType> type) {
		this.watchTypes = type;
	}

	/**
	 * (non-Javadoc)
	 * 
	 * @see imp.core.observer.Observer#execute()
	 */
	@Override
	public void execute() {
		// TODO Implement method
	}

	/**
	 * (non-Javadoc)
	 * 
	 * @see imp.core.observer.Observer#update(imp.core.observer.NotificationType)
	 */
	@Override
	public void update(NotificationType updateType) {
		if (watchTypes.contains(updateType)) {
			this.execute();
		}
	}
}
