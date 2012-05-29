/**
 * TestPrism.java
 * March 31, 2011
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
import imp.core.model.joints.Prism;
import imp.core.model.joints.Screw;
import imp.core.structures.PositionMatrix;
import imp.core.structures.Vector3;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the prism class.
 * 
 * @author dykstran
 * @edited dykstran April 10, 2011 Added @Ignore annotations for tests not yet implemented.
 * @author hellmerj Tested matrices (acceleration, derivative, phi, second derivative, and velocity)
 * @version 1.2
 * 
 */
@SuppressWarnings("javadoc")
public class TestPrism {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.joints.Prism#getAccelerationMatrix()}.
	 * 
	 * @throws NullParameterException Null joint variable type passed to get second derivative method
	 * @throws InvalidParameterException Invalid joint variable type passed
	 */
	@Test
	public void testGetAccelerationMatrix() throws NullParameterException, InvalidParameterException {
		Prism prm = new Prism("test");

		// set displacement joint variable magnitude and acceleration
		prm.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		prm.getJointVariable(JVAR.ZDISPLACEMENT).setAcceleration(3);

		// get acceleration matrix to test
		PositionMatrix acc = prm.getAccelerationMatrix();

		/**
		 * Create expected acceleration Matrix
		 * 
		 * [0,0,0,0] [0,0,0,0] [0,0,0,0] [0,0,0,0]
		 */
		PositionMatrix expected = new PositionMatrix();
		expected.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		expected.set(3, 3, 0);

		// check that returned acceleration is correct
		assertEquals(expected, acc);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#getDerivativeMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetDerivativeMatrix() throws NullParameterException, InvalidParameterException {
		Prism prm = new Prism("test");

		// set displacement joint variable magnitude
		prm.setJointVariable(JVAR.ZDISPLACEMENT, 8);

		// get derivative of prism to test
		PositionMatrix deriv = prm.getDerivativeMatrix(JVAR.ZDISPLACEMENT);

		/**
		 * Create Expected derivative matrix
		 * 
		 * <pre>
		 * [0,0,0,1] 
		 * [0,0,0,0] 
		 * [0,0,0,0] 
		 * [0,0,0,0]
		 * </pre>
		 */
		PositionMatrix expected = new PositionMatrix();
		expected.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 1));
		expected.set(3, 0, 0);
		expected.set(3, 1, 0);
		expected.set(3, 2, 0);
		expected.set(3, 3, 0);

		// check that returned derivative is correct
		assertEquals(expected, deriv);

		// another test
		prm = new Prism("test2");

		prm.setJointVariable(JVAR.ZDISPLACEMENT, 2);

		deriv = prm.getDerivativeMatrix(JVAR.ZDISPLACEMENT);

		expected = new PositionMatrix();
		expected.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 1));
		expected.set(3, 0, 0);
		expected.set(3, 1, 0);
		expected.set(3, 2, 0);
		expected.set(3, 3, 0);

		assertEquals(expected, deriv);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#getPhiMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */

	@Test
	public void testGetPhiMatrix() throws NullParameterException, InvalidParameterException {
		Prism prm = new Prism("test");

		// set magnitude of joint variable
		prm.setJointVariable(JVAR.ZDISPLACEMENT, 8);

		// get prism phi matrix to test
		PositionMatrix phi = prm.getPhiMatrix();

		/**
		 * Create expected phi matrix
		 * 
		 * [1,0,0,8] [0,1,0,0] [0,0,1,0] [0,0,0,1]
		 */
		PositionMatrix expected = new PositionMatrix();
		expected.set(2, 3, 8);

		// check that returned phi matrix is correct
		assertEquals(expected, phi);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#getSecondDerivativeMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetSecondDerivativeMatrix() throws NullParameterException, InvalidParameterException {
		Prism prm = new Prism("test");

		// set magnitude of joint variable
		prm.setJointVariable(JVAR.ZDISPLACEMENT, 8);

		// get prism second derivative matrix to test
		PositionMatrix secDeriv = prm.getSecondDerivativeMatrix(JVAR.ZDISPLACEMENT, JVAR.ZDISPLACEMENT);

		/**
		 * Create expected second derivative matrix
		 * 
		 * [0,0,0,0] [0,0,0,0] [0,0,0,0] [0,0,0,0]
		 */
		PositionMatrix expected = new PositionMatrix();
		expected.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
		expected.set(3, 3, 0);

		// check that returned matrix is correct
		assertEquals(expected, secDeriv);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#getVelocityMatrix()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetVelocityMatrix() throws NullParameterException, InvalidParameterException {
		Prism prm = new Prism("test");

		// set magnitude and velocity of joint variable
		prm.setJointVariable(JVAR.ZDISPLACEMENT, 8);
		prm.getJointVariable(JVAR.ZDISPLACEMENT).setVelocity(3);

		// get prism velocity matrix to test
		PositionMatrix vel = prm.getVelocityMatrix();

		/**
		 * Create expected velocity matrix
		 * 
		 * [0,0,0,3] [0,0,0,0] [0,0,0,0] [0,0,0,0]
		 */
		PositionMatrix expected = new PositionMatrix();
		expected.fill(new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 0), new Vector3(0, 0, 3));
		expected.set(3, 3, 0);

		// check that returned velocity matrix is correct
		assertEquals(expected, vel);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#Prism(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testPrism() throws NullParameterException, InvalidParameterException {
		new Prism("prism");
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#Prism(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testPrismNullParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(NullParameterException.class);
		new Prism(null);
	}

	/**
	 * Test method for {@link imp.core.model.joints.Prism#Prism(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testPrismInvalidParam() throws NullParameterException, InvalidParameterException {
		this.thrown.expect(InvalidParameterException.class);
		new Prism("");
	}

	/**
	 * Test method for {@link imp.model.joints.Prims#getQOperator()}
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */

	@Test
	public void testQOperator() throws NullParameterException, InvalidParameterException {
		Prism psm = new Prism("test");

		PositionMatrix actual = psm.getQOperator(JVAR.ZDISPLACEMENT);
		PositionMatrix expected = new PositionMatrix(new double[][] { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 0, 0 } });

		assertEquals(expected, actual);
	}

	/**
	 * Test method for {@link imp.model.elements.Prism#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {
		 
		Prism prm = new Prism("test");
		Prism prmCopy = new Prism("test");
		Body b1 = new Body("b1");
		
		Axis theAxis = new Axis(prm, b1);
		prm.setAxisAfter(theAxis);
		prm.setAxisBefore(theAxis);
		
		prmCopy.setAxisAfter(theAxis);
		prmCopy.setAxisBefore(theAxis);
		
		// prm and copy should be equal
		assertTrue( prm.equals( prmCopy ));
		assertTrue( prmCopy.equals( prm ));
	 }
	
	/**
	 * Test method for {@link imp.model.elements.Prismr#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {
		
		Prism prm = new Prism("test");
		Prism prmDif = new Prism("Diff");
		
		// should not equal different cylinder
		assertFalse(prm.equals(prmDif));
		assertFalse(prmDif.equals(prm));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Prism#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObject() throws NullParameterException, InvalidParameterException {
		
		Prism prm = new Prism("prm");
		Screw scr = new Screw("scr");
		
		// should not equal different object type
		assertFalse(prm.equals(scr));
	}
	
	/**
	 * Test method for {@link imp.model.elements.Prism#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {
		
		Prism prm = new Prism("test");
		
		// should not equal null prism
		assertFalse(prm.equals( null ));
	}
}
