/**
 * 
 */
package imp.core.observer;

import imp.core.exceptions.IMPException;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Cylinder;
import imp.core.model.joints.Revolute;
import imp.core.observer.JointObserver;
import imp.core.observer.NotificationType;

import java.util.EnumSet;

import org.junit.Test;

/**
 * @author edmissonj
 * 
 */
@SuppressWarnings("javadoc")
public class TestJointObserver {

	public class JointObserverTester extends JointObserver {

		public JointObserverTester(EnumSet<NotificationType> watchTypes) {
			super(watchTypes);
		}

		@Override
		public void update(NotificationType updateType) {
			if (this.watchTypes.contains(updateType)) {
				this.execute();
			}
		}

		@Override
		public void execute() {
		}

	}

	/**
	 * Test method for {@link imp.core.observer.JointObserver#update(int)}.
	 */
	@Test
	public void testUpdate() throws IMPException {
		Cylinder c1 = new Cylinder("CYlinder");
		JointObserver obv = new JointObserverTester(EnumSet.allOf(NotificationType.class));
		Revolute r1 = new Revolute("Rev");
		c1.setJointVariable(JVAR.THETA, 0);
		c1.setJointVariable(JVAR.ZDISPLACEMENT, 0);
		c1.addObserver(obv);
		r1.setJointVariable(JVAR.THETA, 0);
		r1.addObserver(obv);

		// tests zdisplacement
		c1.getJointVariable(JVAR.ZDISPLACEMENT).setVelocity(78);
		c1.getJointVariable(JVAR.ZDISPLACEMENT).setAcceleration(15);
		c1.setJointVariable(JVAR.ZDISPLACEMENT, 7);

		// tests theta
		r1.getJointVariable(JVAR.THETA).setVelocity(78);
		r1.getJointVariable(JVAR.THETA).setAcceleration(15);
		r1.setJointVariable(JVAR.THETA, 7);
	}

}
