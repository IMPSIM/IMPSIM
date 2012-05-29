/**
 * TestScrew.java
 * April 17, 2011
 */
package imp.core.model.joints;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.Constants;
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
 * @author hellmerj
 * @version 1.0
 */
@SuppressWarnings("javadoc")
public class TestScrew {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getAccelerationMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		Screw scr = new Screw("test");

		// set joint variable magnitude and acceleration
		scr.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		scr.getJointVariable(JVAR.ZDISPLACEMENT).setAcceleration(3);
		// set helical angle
		scr.setHelicAngle(0.75);

		// get acceleration matrix to test
		PositionMatrix acc = scr.getAccelerationMatrix();

		/**
		 * Create expected acceleration matrix
		 * 
		 * [.9690, -2.839, 0, 0] [2.839, .9690, 0, 0] [0, 0, 0, 0] [0, 0, 0, 0]
		 */
		PositionMatrix expected = new PositionMatrix();
		// sine and cosine of displacement/helical angle times JVAR acc value
		double sin = Math.sin(8 / .75) * 3;
		double cos = Math.cos(8 / .75) * 3;
		expected.fill(new Vector3(-cos, -sin, 0), new Vector3(sin, -cos, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		expected.set(3, 3, 0);

		// check returned acceleration is correct
		assertEquals(expected, acc);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getAngle()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetAngle() throws NullParameterException, InvalidParameterException {
		Screw screw = new Screw("test");
		screw.setHelicAngle(.75);

		assertEquals(screw.getAngle(), 0, Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getDerivativeMatrix(imp.core.model.elements.Joint.JVAR)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivativeMatrix() throws NullParameterException, InvalidParameterException {
		Screw scr = new Screw("test");

		// set joint variable magnitude
		scr.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		// set helical angle
		scr.setHelicAngle(0.75);

		// get derivative matrix to test
		PositionMatrix deriv = scr.getDerivativeMatrix(JVAR.ZDISPLACEMENT);

		/**
		 * Create expected derivative matrix
		 * 
		 * [.9464, .3230, 0, 0] [-.3230, .9464, 0, 0] [0, 0, 0, 1] [0, 0, 0, 0]
		 */
		PositionMatrix expected = new PositionMatrix();
		// sine and cosine of displacement/helical angle
		double sin = Math.sin(8 / .75);
		double cos = Math.cos(8 / .75);
		expected.fill(new Vector3(-sin, cos, 0), new Vector3(-cos, -sin, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 1));
		expected.set(3, 3, 0);

		// check returned derivative is correct
		assertEquals(expected, deriv);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getDisplacement()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDisplacement() throws NullParameterException, InvalidParameterException {
		Screw screw = new Screw("test");

		assertEquals(screw.getDisplacement(), 0, Constants.ERROR_TOLERANCE);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getHelicAngle()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetHelicAngle() throws NullParameterException, InvalidParameterException {
		Screw screw = new Screw("test");

		screw.setHelicAngle(42);

		assertEquals(42, screw.getHelicAngle(), Constants.ERROR_TOLERANCE);

	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getPhiMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetPhiMatrix() throws NullParameterException, InvalidParameterException {
		Screw scr = new Screw("test");

		// set joint variable magnitude
		scr.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		// set helical angle
		scr.setHelicAngle(0.75);

		// get phi matrix to test
		PositionMatrix phi = scr.getPhiMatrix();

		/**
		 * Create expected phi matrix
		 * 
		 * [-.3230, .9464, 0, 0] [-.9464, -.3230, 0, 0] [0, 0, 1, 8] [0, 0, 0, 1]
		 */
		PositionMatrix expected = new PositionMatrix();
		// sine and cosine of displacement/helical angle
		double sin = Math.sin(8 / .75);
		double cos = Math.cos(8 / .75);
		expected.fill(new Vector3(cos, sin, 0), new Vector3(-sin, cos, 0), new Vector3(0, 0, 1), new Vector3(0, 0, 8));

		// check returned phi is correct
		assertEquals(expected, phi);
	}

	/**
	 * Test method for
	 * {@link imp.core.model.joints.Screw#getSecondDerivativeMatrix(imp.core.model.elements.Joint.JVAR, imp.core.model.elements.Joint.JVAR)}
	 * .
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivativeMatrix() throws NullParameterException, InvalidParameterException {
		Screw scr = new Screw("test");

		// set joint variable magnitude
		scr.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		// set helical angle
		scr.setHelicAngle(0.75);

		// get second derivative matrix to test
		PositionMatrix secDeriv = scr.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.ZDISPLACEMENT);

		/**
		 * Create expected second derivative matrix
		 * 
		 * [.3230, -.9464, 0, 0] [.9464, .3230, 0, 0] [0, 0, 0, 0] [0, 0, 0, 0]
		 */
		PositionMatrix expected = new PositionMatrix();
		// sine and cosine of displacement/helicalangle
		double sin = Math.sin(8 / .75);
		double cos = Math.cos(8 / .75);
		expected.fill(new Vector3(-cos, -sin, 0), new Vector3(sin, -cos, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		expected.set(3, 3, 0);

		// check returned second derivative is correct
		assertEquals(expected, secDeriv);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getVelocityMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetVelocityMatrix() throws NullParameterException, InvalidParameterException {
		Screw scr = new Screw("test");

		// set joint variable magnitude and velocity
		scr.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		scr.getJointVariable(JVAR.ZDISPLACEMENT).setVelocity(3);
		// set helical angle
		scr.setHelicAngle(0.75);

		// get velocity matrix to test
		PositionMatrix vel = scr.getVelocityMatrix();

		/**
		 * Create expected velocity matrix
		 * 
		 * [2.839, .9690, 0, 0] [-.9690, 2.839, 0, 0] [0, 0, 0, 3] [0, 0, 0, 0]
		 */
		PositionMatrix expected = new PositionMatrix();
		// sine and cosine of displacement/helical angle times velocity
		double sin = Math.sin(8 / .75) * 3;
		double cos = Math.cos(8 / .75) * 3;
		expected.fill(new Vector3(-sin, cos, 0), new Vector3(-cos, -sin, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 3));
		expected.set(3, 3, 0);

		// check returned velocity matrix is correct
		assertEquals(expected, vel);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#Screw(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testScrew() throws NullParameterException, InvalidParameterException {
		new Screw("test");
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#Screw(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testScrewNullParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new Screw(null);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#Screw(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testScrewInvalidParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new Screw("");
	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#setHelicAngle(double)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testSetHelicAngle() throws NullParameterException, InvalidParameterException {
		Screw screw = new Screw("test");

		screw.setHelicAngle(57);

		assertEquals(57, screw.getHelicAngle(), Constants.ERROR_TOLERANCE);

	}

	/**
	 * Test method for {@link imp.core.model.joints.Screw#getQOperator()}
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testQOperator() throws NullParameterException, InvalidParameterException {
		Screw screw = new Screw("test");

		// 90 degress
		double angle = Math.PI / 2;
		screw.setHelicAngle(angle);

		PositionMatrix actual = screw.getQOperator(JVAR.PHI);

		/**
		 * From documentation:
		 * 
		 * <pre>
		 * [  0, -1/s, 0, 0]
		 * [1/s,    0, 0, 0]
		 * [  0,    0, 0, 1]
		 * [  0,    0, 0, 0]
		 * </pre>
		 * 
		 * Where s (sigma) is the helical angle of the joint.
		 */
		PositionMatrix expected = new PositionMatrix(new double[][] { { 0, -(1 / angle), 0, 0 }, { (1 / angle), 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 0, 0 } });

		assertEquals(expected, actual);
	}

	/**
	 * Test method for {@link imp.model.elements.Screw#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {
		 
		Screw scr = new Screw("test");
		Screw scrCopy = new Screw("test");
		Body b1 = new Body("b1");
		
		Axis theAxis = new Axis(scr, b1);
		scr.setAxisAfter(theAxis);
		scr.setAxisBefore(theAxis);
		
		scrCopy.setAxisAfter(theAxis);
		scrCopy.setAxisBefore(theAxis);
		
		// scr and copy should be equal
		assertTrue( scr.equals( scrCopy ));
		assertTrue( scrCopy.equals( scr ));
	 }
	
	/**
	 * Test method for {@link imp.model.elements.Screw#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {
		
		Screw scr = new Screw("test");
		Screw scrDif = new Screw("Diff");
		
		// should not equal different screw
		assertFalse(scr.equals(scrDif));
		assertFalse(scrDif.equals(scr));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Screw#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObject() throws NullParameterException, InvalidParameterException {
		
		Screw scr = new Screw("scr");
		Cylinder cyl = new Cylinder("cyl");
		
		// should not equal different object type
		assertFalse(scr.equals(cyl));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Screw#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {
		
		Screw scr = new Screw("test");
		
		// should not equal null cylinder
		assertFalse(scr.equals( null ));
	}
}
