/**
 * 
 */
package imp.core.observer;

import java.util.LinkedList;
import java.util.List;

/**
 * 
 * 
 * @author zastrowm
 *
 */
public class AbstractSubject implements Subject {

	private List<Observer> observers = new LinkedList<Observer>();
	
	@Override
	public void addObserver(Observer obv) {
		observers.add(obv);
	}

	@Override
	public void notifyObservers(NotificationType updateType) {
		for (Observer obs : observers) {
			obs.update(updateType);
		}
		
	}

}
