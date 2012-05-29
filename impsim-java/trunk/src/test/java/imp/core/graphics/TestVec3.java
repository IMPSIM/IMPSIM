package imp.core.graphics;

import static org.junit.Assert.*;

import org.junit.Test;

/**
 * Tests the functionality of the Vec3 class
 * @author kreierj
 * @version 1
 */
public class TestVec3 {

	/**
	 * Tests the constructors
	 */
	@Test
	public void testConstructor(){
		
		Vec3 testVec = new Vec3(new float[]{1,2,3});
		
		assertEquals(1, testVec.x, .0001);
		assertEquals(2, testVec.y, .0001);
		assertEquals(3, testVec.z, .0001);
		
		testVec = new Vec3(1,2,3);
		
		assertEquals(1, testVec.x, .001);
		assertEquals(2, testVec.y, .001);
		assertEquals(3, testVec.z, .001);
		
		
	}
	
	/**
	 * Tests the cross product
	 */
	@Test
	public void testCross(){
		Vec3 testVec1 = new Vec3(1,2,3);
		Vec3 testVec2 = new Vec3(4,5,6);
		
		Vec3 result = testVec1.cross(testVec2);
		
		assertEquals(-3.0, result.x, .001);
		assertEquals(6, result.y, .001);
		assertEquals(-3.0, result.z, .001);
		
		
	}
	
	/**
	 * Tests magitude and length calculations
	 */
	@Test
	public void testMagnitude(){
		
		Vec3 testVec = new Vec3(1,2,3);
		
		float result = testVec.length();
		
		assertEquals(3.7416, result, 0.001);
		
		result = testVec.magnitude();
		
		assertEquals(3.7416, result, 0.001);
	}
	
	/**
	 * Tests minus operation
	 */
	@Test
	public void testMinus(){
		
		Vec3 testVec1 = new Vec3(1,2,3);
		Vec3 testVec2 = new Vec3(4,5,6);
		
		Vec3 result = testVec1.minus(testVec2);
		
		assertEquals(-3, result.x, .001);
		assertEquals(-3, result.y, .001);
		assertEquals(-3, result.z, .001);
	}
	
	/**
	 * Tests multiply operation
	 */
	@Test
	public void testMultiply(){
		
		Vec3 testVec = new Vec3(1,2,3);
		
		Vec3 result = testVec.multiply(2);
		
		assertEquals(2, result.x, .001);
		assertEquals(4, result.y, .001);
		assertEquals(6, result.z, .001);	
		
	}
	
	/**
	 * Tests normalize operation
	 */
	@Test
	public void testNormalize(){
		
		Vec3 testVec = new Vec3(1,2,3);
		
		Vec3 result = testVec.normalize();
		
		assertEquals(0.26726, result.x, .001);
		assertEquals(0.53452, result.y, .001);
		assertEquals(0.80178, result.z, .001);
		
		
		//make sure its length is 1
		float length = result.length();
		
		assertEquals(1.0, length, .001);
		
	}
	
	/**
	 * Tests plus operation
	 */
	@Test
	public void testPlus(){
		Vec3 testVec1 = new Vec3(1,2,3);
		Vec3 testVec2 = new Vec3(4,5,6);
		
		Vec3 result = testVec1.plus(testVec2);
		
		assertEquals(5, result.x, .001);
		assertEquals(7, result.y, .001);
		assertEquals(9, result.z, .001);
	}
	
	/**
	 * Test to Matrix Operation
	 */
	@Test
	public void testToMatrix(){
		Vec3 testVec = new Vec3(1,2,3);
		
		float[] mat = testVec.toMatrix().raw();
		
		assertEquals(1, mat[0], 0.001);
		assertEquals(0, mat[1], 0.001);
		assertEquals(0, mat[2], 0.001);
		assertEquals(0, mat[3], 0.001);
		assertEquals(0, mat[4], 0.001);
		assertEquals(2, mat[5], 0.001);
		assertEquals(0, mat[6], 0.001);
		assertEquals(0, mat[7], 0.001);
		assertEquals(0, mat[8], 0.001);
		assertEquals(0, mat[9], 0.001);
		assertEquals(3, mat[10], 0.001);
		assertEquals(0, mat[11], 0.001);
		assertEquals(0, mat[12], 0.001);
		assertEquals(0, mat[12], 0.001);
		assertEquals(0, mat[13], 0.001);
		assertEquals(0, mat[14], 0.001);
		assertEquals(1, mat[15], 0.001);
		
		
	}
}
