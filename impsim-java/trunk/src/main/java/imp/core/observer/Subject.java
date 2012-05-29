/**
 * Subject.java
 * May 7, 2011
 */
package imp.core.observer;

/**
 * Interface for the objects being observed
 * 
 * @author edmissonj
 * @edit Updated JavaDoc
 * @version 1.01
 * 
 */
public interface Subject {

	

	/**
	 * Method for adding an observer to the list of observers.
	 * 
	 * @param obv The observer to be added.
	 */
	public void addObserver(Observer obv);

	/**
	 * Method for notifying every observer watching the subject.
	 * 
	 * @param updateType The type of change that has occurred.
	 */
	public void notifyObservers(NotificationType updateType);
}
