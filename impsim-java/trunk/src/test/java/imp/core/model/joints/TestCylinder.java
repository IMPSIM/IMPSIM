/**
 * TestCylinder.java
 */
package imp.core.model.joints;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Axis;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint.JVAR;
import imp.core.model.joints.Cylinder;
import imp.core.model.joints.Screw;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author edmissonj
 * @author dykstran Implemented some ignored tests.
 * @version 1.1
 * 
 */
@SuppressWarnings("javadoc")
public class TestCylinder {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#Cylinder(java.lang.String)}.
	 * 
	 * @throws NullParameterException failure
	 * @throws InvalidParameterException failure
	 */
	@Test
	public void testCylinder() throws NullParameterException, InvalidParameterException {
		new Cylinder("test");
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#Cylinder(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testCylinderNullParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new Cylinder(null);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#Cylinder(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testCylinderInvalidParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new Cylinder("");
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getAccelerationMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// new joint should have no acceleration
		PositionMatrix expectedAccMatrix = new PositionMatrix();
		Vector3 zero = new Vector3(0, 0, 0);
		expectedAccMatrix.fill(zero, zero, zero, zero);
		expectedAccMatrix.set(3, 3, 0);

		assertEquals(expectedAccMatrix, cyl.getAccelerationMatrix());
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getDerivativeMatrix(imp.core.model.elements.Joint.JVAR)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivativeMatrixTheta() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// [start] derivative with respect to theta of initialized phi matrix

		/**
		 * <pre>
		 * 		 	[ 0, -1, 0, 0] 
		 * 			[ 1, 0, 0, 0]
		 * 			[ 0, 0, 0, 0] 
		 * 			[ 0, 0, 0, 0]
		 * 
		 * </pre>
		 */

		PositionMatrix testTheta = new PositionMatrix();
		testTheta.set(0, 0, 0);
		testTheta.set(0, 1, -1);
		testTheta.set(1, 0, 1);
		testTheta.set(1, 1, 0);
		testTheta.set(2, 2, 0);
		testTheta.set(3, 3, 0);

		assertEquals(cyl.getDerivativeMatrix(JVAR.THETA), testTheta);
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getDerivativeMatrix(imp.core.model.elements.Joint.JVAR)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivativeMatrixZDisp() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");
		// [start] derivative with respect to zdisp of initialized phi matrix

		/**
		 * <pre>
		 * 			[ 0, 0, 0, 0 ]
		 * 			[ 0, 0, 0, 0 ]
		 * 			[ 0, 0, 0, 1 ]
		 * [ 0, 0, 0, 0 ]
		 */

		PositionMatrix testTheta = new PositionMatrix();
		testTheta.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 1));
		testTheta.set(3, 3, 0);

		assertEquals(cyl.getDerivativeMatrix(JVAR.ZDISPLACEMENT), testTheta);
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getDerivativeMatrix(imp.core.model.elements.Joint.JVAR)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivativeMatrixThetaCase2() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");
		// [start] derivative with respect to theta of updated theta JVAR magnitude

		/*
		 * <pre> [ -(sqrt(3))/2, -0.5, 0, 0 ] [ 0.5, -(sqrt(3))/2, 0, 0 ] [ 0, 0, 0, 0 ] [ 0, 0, 0, 0 ] </pre>
		 */

		cyl.setJointVariable(JVAR.THETA, Math.PI / 3);
		PositionMatrix pmTheta = cyl.getDerivativeMatrix(JVAR.THETA);
		PositionMatrix testTheta = new PositionMatrix();
		double sin = Math.sin(Math.PI / 3);
		double cos = Math.cos(Math.PI / 3);
		testTheta.fill(new Vector3(-sin, cos, 0), new Vector3(-cos, -sin, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testTheta.set(3, 3, 0);

		assertEquals(pmTheta, testTheta);
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getDerivativeMatrix(imp.core.model.elements.Joint.JVAR)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivativeMatrixZDispCase2() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// [start] derivative with respect to zdisp with updated zdisp JVAR magnitude

		/*
		 * <pre> [ 0 0 0 0 ] [ 0 0 0 0 ] [ 0 0 0 1 ] [ 0 0 0 0 ] </pre>
		 */

		cyl.setJointVariable(JVAR.ZDISPLACEMENT, 10);

		PositionMatrix pmZdist = cyl.getDerivativeMatrix(JVAR.ZDISPLACEMENT);
		PositionMatrix testZdist = new PositionMatrix();
		testZdist.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 1));
		testZdist.set(3, 3, 0);

		assertEquals(pmZdist, testZdist);
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getPhiMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetPhiMatrix() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// [start] test initial phi matrix

		/**
		 * <pre>
		 * Phi = 	[ 1, 0, 0, 0] 
		 * 			[ 0, 1, 0, 0]
		 * 			[ 0, 0, 1, 0] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * </pre>
		 */

		PositionMatrix expectedPhi = new PositionMatrix();
		assertEquals(cyl.getPhiMatrix(), expectedPhi);
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getPhiMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetPhiMatrixZDispChange() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");
		// [start] test phi for set JVAR zdisp magnitude

		/**
		 * <pre>
		 * Phi = 	[ 1, 0, 0, 0] 
		 * 			[ 0, 1, 0, 0]
		 * 			[ 0, 0, 1, 8] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * </pre>
		 */

		cyl.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		PositionMatrix expectedPhi = new PositionMatrix();
		// set zdisp position in expected
		expectedPhi.set(3, 2, 8);

		assertEquals(cyl.getPhiMatrix(), expectedPhi);
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getPhiMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetPhiMatrixThetaChange() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");
		// [start] test phi for set JVAR theta magnitude

		/**
		 * <pre>
		 * Phi = 	[ 0, 1, 0, 0] 
		 * 			[ -1, 0, 0, 0]
		 * 			[ 0, 0, 1, 8] 
		 * 			[ 0, 0, 0, 1]
		 * 
		 * </pre>
		 */

		cyl.setJointVariable(JVAR.THETA, Math.PI / 2);

		// set expected values based on JVAR
		PositionMatrix expectedPhi = new PositionMatrix();
		expectedPhi.set(0, 0, 0);
		expectedPhi.set(0, 1, -1);
		expectedPhi.set(1, 0, 1);
		expectedPhi.set(1, 1, 0);

		assertEquals(cyl.getPhiMatrix(), expectedPhi);

		// [end]

	}

	/**
	 * Test method for
	 * {@link imp.core.model.joints.Cylinder#getSecondDerivativeMatrix(imp.core.model.elements.Joint.JVAR, imp.core.model.elements.Joint.JVAR)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivativeMatrixThetaTheta() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// [start] second derivative of theta with respect to theta

		/*
		 * <pre>
		 */

		cyl.setJointVariable(JVAR.THETA, Math.PI / 4);

		// test when it is theta with respect to theta
		PositionMatrix pm = cyl.getSecondDerivativeMatrix(JVAR.THETA, JVAR.THETA);

		PositionMatrix testAgainst = new PositionMatrix();
		double sin = Math.sin(Math.PI / 4);
		testAgainst.fill(new Vector3(-sin, -sin, 0), new Vector3(sin, -sin, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testAgainst.set(3, 3, 0);

		assertEquals(pm, testAgainst);
	}

	/**
	 * Test method for
	 * {@link imp.core.model.joints.Cylinder#getSecondDerivativeMatrix(imp.core.model.elements.Joint.JVAR, imp.core.model.elements.Joint.JVAR)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivativeMatrixThetaZDisp() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// test when it is theta with respect to zdis
		// test when it is theta with respect to theta
		PositionMatrix testAgainst = new PositionMatrix();

		PositionMatrix pm = cyl.getSecondDerivativeMatrix(JVAR.THETA, JVAR.ZDISPLACEMENT);

		testAgainst = new PositionMatrix();
		testAgainst.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testAgainst.set(3, 3, 0);

		assertEquals(pm, testAgainst);
	}

	/**
	 * Test method for
	 * {@link imp.core.model.joints.Cylinder#getSecondDerivativeMatrix(imp.core.model.elements.Joint.JVAR, imp.core.model.elements.Joint.JVAR)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivativeMatrixZDispZDisp() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// test when it is zdist with respect to zdis
		// test when it is theta with respect to theta
		PositionMatrix testAgainst = new PositionMatrix();

		PositionMatrix pm = cyl.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.ZDISPLACEMENT);

		testAgainst.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testAgainst.set(3, 3, 0);

		assertEquals(pm, testAgainst);
	}

	/**
	 * Test method for
	 * {@link imp.core.model.joints.Cylinder#getSecondDerivativeMatrix(imp.core.model.elements.Joint.JVAR, imp.core.model.elements.Joint.JVAR)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivativeMatrixZDispTheta() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// test when it is zdis with respect to theta
		// test when it is theta with respect to theta
		PositionMatrix testAgainst = new PositionMatrix();

		PositionMatrix pm = cyl.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.THETA);

		testAgainst.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		testAgainst.set(3, 3, 0);

		assertEquals(pm, testAgainst);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getVelocityMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetVelocityMatrixInitial() throws NullParameterException, InvalidParameterException {

		Cylinder cyl = new Cylinder("test");

		// [start] velocity of new joint with have no velocity

		/*
		 * <pre> vel = [ 0 0 0 0 ] [ 0 0 0 0 ] [ 0 0 0 0 ] [ 0 0 0 0 ] </pre>
		 */

		PositionMatrix expectedVelocityMatrix = new PositionMatrix();
		Vector3 zero = new Vector3(0, 0, 0);
		expectedVelocityMatrix.fill(zero, zero, zero, zero);
		expectedVelocityMatrix.set(3, 3, 0);
		assertEquals(expectedVelocityMatrix, cyl.getVelocityMatrix());
		// [end]
	}

	/**
	 * Test method for {@link imp.core.model.joints.Cylinder#getVelocityMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetVelocityMatrix() throws NullParameterException, InvalidParameterException {
		Cylinder cyl = new Cylinder("test");

		// [start] velocity with set joint variable magnitude and velocity

		/*
		 * <pre> vel = [ -8 0 0 0 ] [ 0 -8 0 0 ] [ 0 0 0 10 ] [ 0 0 0 0 ]
		 */

		cyl.setJointVariable(JVAR.THETA, Math.PI / 2);
		cyl.getJointVariable(JVAR.THETA).setVelocity(8);

		cyl.setJointVariable(JVAR.ZDISPLACEMENT, 10);
		cyl.getJointVariable(JVAR.ZDISPLACEMENT).setVelocity(10);

		PositionMatrix expectedVelocityMatrix = new PositionMatrix();
		expectedVelocityMatrix.fill(new Vector3(-8, 0, 0), new Vector3(0, -8, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 10));
		expectedVelocityMatrix.set(3, 3, 0);

		assertEquals(expectedVelocityMatrix, cyl.getVelocityMatrix());
		// [end]
	}

	/**
	 * Test method for (@link {@link imp.core.model.joints.Cylinder#getQOperator(JVAR)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testGetQOperatorDisplacement() throws NullParameterException, InvalidParameterException {

		Cylinder cyl = new Cylinder("test");

		PositionMatrix expectedQ = new PositionMatrix();
		expectedQ.fill(new Vector3(0, 1, 0), new Vector3(-1, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		expectedQ.set(3, 3, 0);

		assertEquals(expectedQ, cyl.getQOperator(JVAR.ZDISPLACEMENT));
	}

	/**
	 * Test method for (@link {@link imp.core.model.joints.Cylinder#getQOperator(JVAR)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testGetQOperatorRotation() throws NullParameterException, InvalidParameterException {

		Cylinder cyl = new Cylinder("test");

		// set the expected
		PositionMatrix expectedQ = new PositionMatrix();
		expectedQ.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 1));
		expectedQ.set(3, 3, 0);

		// compare the expected with the actual returned Q matrix
		assertEquals(expectedQ, cyl.getQOperator(JVAR.THETA));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Cylinder#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {
		 
		Cylinder cyl = new Cylinder("test");
		Cylinder cylCopy = new Cylinder("test");
		Body b1 = new Body("b1");
		
		Axis theAxis = new Axis(cyl, b1);
		cyl.setAxisAfter(theAxis);
		cyl.setAxisBefore(theAxis);
		
		cylCopy.setAxisAfter(theAxis);
		cylCopy.setAxisBefore(theAxis);
		
		// cyl and copy should be equal
		assertTrue( cyl.equals( cylCopy ));
		assertTrue( cylCopy.equals( cyl ));
	 }
	
	/**
	 * Test method for {@link imp.model.elements.Cylinder#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {
		
		Cylinder cyl = new Cylinder("test");
		Cylinder cylDif = new Cylinder("Diff");
		
		// should not equal different cylinder
		assertFalse(cyl.equals(cylDif));
		assertFalse(cylDif.equals(cyl));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Cylinder#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObject() throws NullParameterException, InvalidParameterException {
		
		Cylinder cyl = new Cylinder("cyl");
		Screw scr = new Screw("scr");
		
		// should not equal different object type
		assertFalse(cyl.equals(scr));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Cylinder#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {
		
		Cylinder cyl = new Cylinder("test");
		
		// should not equal null cylinder
		assertFalse(cyl.equals( null ));
	}
}
