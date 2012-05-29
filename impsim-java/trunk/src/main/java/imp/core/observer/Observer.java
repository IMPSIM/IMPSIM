/**
 * Observer.java
 * May 7, 2011
 */
package imp.core.observer;

/**
 * Interface for observers.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * 
 */
public interface Observer {

	/**
	 * Method for doing what the observer thinks must be done.
	 */
	public void execute();

	/**
	 * Method for the subject to update the observer.
	 * 
	 * @param updateType The type of update executing.
	 */
	public void update(NotificationType updateType);
}
