/**
 * AbstractMultiSubject.java
 * Oct 15, 2011
 */
package imp.core.observer;

import java.util.EnumSet;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * An implementation of a Subject for which the Subject can fire different types of events
 * 
 * @author zastrowm
 * @version 1.0
 */
public class AbstractMultiSubject implements Subject {

	HashMap<NotificationType, List<Observer>> observers = new HashMap<NotificationType, List<Observer>>();
	
	@Override
	public void addObserver(Observer obv) {
		addObserver(obv, NotificationType.unspecified);
	}
	

	/**
	 * Observe all of the events passed in
	 * 
	 * @param obv the observer
	 * @param types the types to observer
	 */
	public void addObserver(Observer obv, NotificationType ... types) {
		for (NotificationType type : types)
			getList(type).add(obv);
	}
	
	/**
	 * Observe all of the events passed in
	 * 
	 * @param obv the observer
	 * @param types the types to observer
	 */
	public void addObserver(Observer obv, EnumSet<NotificationType> types) {
		for (NotificationType type : types)
			getList(type).add(obv);
	}

	@Override
	public void notifyObservers(NotificationType updateType) {
		
		if (updateType != NotificationType.unspecified) {
			for (Observer obs : getList(updateType)) {
				obs.update(updateType);
			}
		}	
		
		for (Observer obs : getList(NotificationType.unspecified)) {
			obs.update(updateType);
		}		
	}
	
	/**
	 * Get the list for a specific observer type, creating it if necessary
	 * 
	 * @param updateType the update type to retrieve
	 * @return the list associated with that update type
	 */
	private List<Observer> getList(NotificationType updateType) {
		if (observers.containsKey(updateType)) {
			return observers.get(updateType);
		} else {
			List<Observer> l = new LinkedList<Observer>();
			observers.put(updateType, l);
			return l;
		}
	}
	
}
