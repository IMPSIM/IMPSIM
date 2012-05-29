/**
 * 
 */
package imp.core.observer;

import static org.junit.Assert.assertEquals;
import imp.core.exceptions.IMPException;
import imp.core.model.elements.Body;
import imp.core.observer.BodyObserver;
import imp.core.observer.NotificationType;
import imp.core.structures.PositionMatrix;

import org.junit.Test;

/**
 * @author edmissonj
 * 
 */
@SuppressWarnings("javadoc")
public abstract class TestBodyObserver {

	public class BodyObserverTester extends BodyObserver {

		/**
		 * True if this is a test.
		 */
		public boolean test = false;

		public BodyObserverTester(NotificationType watchTypes) {
			super(NotificationType.all(watchTypes));
		}

		/*
		 * (non-Javadoc)
		 * @see imp.observer.Observer#execute()
		 */
		@Override
		public void execute() {

			this.test = true;
		}
	}

	/**
	 * Test method for {@link imp.core.observer.BodyObserver#update(int)}.
	 */
	@Test
	public void testUpdate() throws IMPException {
		Body b1 = new Body("B1");
		BodyObserver obv = new BodyObserverTester(NotificationType.position);// creates a new observer watching position
		b1.addObserver(obv);
		b1.setPositionMatrixNotify(new PositionMatrix(), true);// causes the body to notify
		assertEquals(true, ((BodyObserverTester) (obv)).test);

		Body b2 = new Body("B2");
		BodyObserver obv2 = new BodyObserverTester(NotificationType.thetaVelocity);// creates a new observer watching
																					// something else
		b2.addObserver(obv2);
		b2.setPositionMatrixNotify(new PositionMatrix(), true);// causes the body to notify
		assertEquals(false, ((BodyObserverTester) (obv2)).test);
	}

}
