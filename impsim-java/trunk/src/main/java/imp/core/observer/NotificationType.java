/**
 * UpdateType.java
 * Oct 9, 2011
 */
package imp.core.observer;

import java.util.EnumSet;

/**
 * The type of update that an observer is presenting
 * 
 * @author zastrowm
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public enum NotificationType {

	unspecified,

	name, position,

	// JOINT VARS
	thetaVelocity, thetaAccleration, thetaMagnitude, phiVelocity, phiAccleration, phiMagnitude, psiVelocity, psiAccleration, psiMagnitude, xVelocity, xAccleration, xMagnitude, yVelocity, yAccleration, yMagnitude, zVelocity, zAccleration, zMagnitude,

	loopClosureComplete,

	modelBeforeCompile, modelAfterCompile, modelBeginRun, modelEndRun,

	modelTick,

	;

	/**
	 * Make an EnumSet containing all of the types passed in
	 * 
	 * @param types the types that the EnumSet should contain
	 * @return the EnumSet composed of the passed in types
	 */
	public static EnumSet<NotificationType> all(NotificationType... types) {
		EnumSet<NotificationType> all = EnumSet.of(types[0]);

		for (int i = 1; i < types.length; i++) {
			all.add(types[i]);
		}
		return all;
	}
}
