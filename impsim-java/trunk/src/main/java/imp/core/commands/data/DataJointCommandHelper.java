/**
 * DataJointCommandHelper.java
 * April 2, 2011
 */
package imp.core.commands.data;

import imp.core.exceptions.MatrixIndexOutOfBoundsException;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;

/**
 * Class for calculating data needed by multiple Data Joint Commands.
 * 
 * @author edmissonj
 * @edit dykstran Updated JavaDoc
 * @version 1.1
 * 
 */
public class DataJointCommandHelper {

	/**
	 * Method for calculating a shape matrix from given points.
	 * 
	 * @param axis The common axis of the joints.
	 * @param initial The origin of the axis.
	 * @param x The point on the x axis.
	 * @return The shape matrix of this joint.
	 * @throws MatrixIndexOutOfBoundsException Thrown if an index beyond the matrices is requested.
	 */
	public static PositionMatrix calculateShapeMatrix(Point axis, Point initial, Point x) throws MatrixIndexOutOfBoundsException {
		// determines the vector form of the common axis
		Vector3 commonAxis = new Vector3(axis);
		Vector3 origin = new Vector3(initial);
		Vector3 z = commonAxis.subtract(origin).normalize();

		// normalizes the vector of the x axis
		// makes the x axis orthogonal
		Vector3 beforeX = z.crossProduct((new Vector3(x)).subtract(origin)).normalize().crossProduct(z);
		Vector3 beforeY = z.crossProduct(beforeX);

		// creates the position matrix to be returned
		PositionMatrix retVal = new PositionMatrix();

		// sets the values in the first column of the matrix to the vector form of the common axis
		retVal.fill(beforeX, beforeY, z, origin);

		return retVal;

	}
}
