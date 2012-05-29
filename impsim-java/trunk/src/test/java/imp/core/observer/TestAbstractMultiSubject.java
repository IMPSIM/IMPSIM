package imp.core.observer;

import static org.junit.Assert.*;

import imp.core.observer.AbstractMultiSubject;
import imp.core.observer.BodyObserver;
import imp.core.observer.NotificationType;
import imp.core.observer.Observer;

import java.util.EnumSet;

import org.junit.Test;

public class TestAbstractMultiSubject {

	@Test
	public void testAddObserver1() {
		EnumSet<NotificationType> es = NotificationType.all(NotificationType.loopClosureComplete, NotificationType.modelAfterCompile);
		AbstractMultiSubject ams = new AbstractMultiSubject();
		Observer o = new BodyObserver(es);
		ams.addObserver(o);
		assertTrue(ams.observers.get(NotificationType.unspecified).contains(o));
	}
	
	@Test
	public void testAddObserver2() {
		EnumSet<NotificationType> es = NotificationType.all(NotificationType.loopClosureComplete, NotificationType.modelAfterCompile);
		AbstractMultiSubject ams = new AbstractMultiSubject();
		Observer o = new BodyObserver(es);
		ams.addObserver(o, NotificationType.loopClosureComplete);
		assertTrue(ams.observers.get(NotificationType.loopClosureComplete).contains(o));
	}
	
	@Test
	public void testAddObserver3() {
		EnumSet<NotificationType> es = NotificationType.all(NotificationType.loopClosureComplete, NotificationType.modelAfterCompile);
		AbstractMultiSubject ams = new AbstractMultiSubject();
		Observer o = new BodyObserver(es);
		ams.addObserver(o, es);
		assertTrue(ams.observers.get(NotificationType.loopClosureComplete).contains(o));
		assertTrue(ams.observers.get(NotificationType.modelAfterCompile).contains(o));
		
	}

}
