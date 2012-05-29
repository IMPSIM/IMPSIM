package imp.core.observer;

import static org.junit.Assert.*;

import imp.core.observer.NotificationType;

import java.util.EnumSet;

import org.junit.Test;

public class TestNotificationType {

	@Test
	public void testAll() {
		EnumSet<NotificationType> es = NotificationType.all(NotificationType.loopClosureComplete, NotificationType.modelAfterCompile);
		assertTrue(es.contains(NotificationType.loopClosureComplete));
		assertTrue(es.contains(NotificationType.modelAfterCompile));
	}

}
