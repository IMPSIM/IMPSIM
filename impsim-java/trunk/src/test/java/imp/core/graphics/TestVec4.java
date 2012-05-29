package imp.core.graphics;

import static org.junit.Assert.*;

import org.junit.Test;

/**
 * Tests the functionality of the Vec4 class
 * @author kreierj
 * @version 1
 */
public class TestVec4 {
	
	/**
	 * Tests the constructors
	 */
	@Test
	public void testConstructor(){
		
		Vec4 testVec = new Vec4(new float[]{1,2,3,4});
		
		assertEquals(1, testVec.x, 0.001);
		assertEquals(2, testVec.y, 0.001);
		assertEquals(3, testVec.z, 0.001);
		assertEquals(4, testVec.w, 0.001);
		
		
		testVec = new Vec4(1,2,3,4);
		
		assertEquals(1, testVec.x, 0.001);
		assertEquals(2, testVec.y, 0.001);
		assertEquals(3, testVec.z, 0.001);
		assertEquals(4, testVec.w, 0.001);
		
		testVec = new Vec4(new Vec3(1,2,3), 4);
		
		assertEquals(1, testVec.x, 0.001);
		assertEquals(2, testVec.y, 0.001);
		assertEquals(3, testVec.z, 0.001);
		assertEquals(4, testVec.w, 0.001);
		
	}
	
	/**
	 * Tests the magnitude calculations
	 */
	@Test
	public void testMagnitude(){
		Vec4 testVec = new Vec4(1,2,3,4);
		
		float result = testVec.length();
		
		assertEquals(5.4772, result, 0.001);
		
		result = testVec.magnitude();
		
		assertEquals(5.4772, result, 0.001);
	}
	
	/**
	 * Tests the minus operation
	 */
	@Test
	public void testMinus(){
		Vec4 testVec1 = new Vec4(1,2,3,4);
		Vec4 testVec2 = new Vec4(5,6,7,8);
		
		Vec4 result = testVec1.minus(testVec2);
		
		assertEquals(-4, result.x, 0.001);
		assertEquals(-4, result.y, 0.001);
		assertEquals(-4, result.z, 0.001);
		assertEquals(-4, result.w, 0.001);
	}
	
	/**
	 * Tests the multiply operation
	 */
	@Test
	public void testMultiply(){
		Vec4 testVec1 = new Vec4(1,2,3,4);
		
		Vec4 result = testVec1.multiply(2);
		
		assertEquals(2, result.x, 0.001);
		assertEquals(4, result.y, 0.001);
		assertEquals(6, result.z, 0.001);
		assertEquals(8, result.w, 0.001);
	}
	
	/**
	 * Tests the normalize operation
	 */
	@Test
	public void testNormalize(){
		Vec4 testVec1 = new Vec4(1,2,3,4);
		
		Vec4 result = testVec1.normalize();
		
		assertEquals(0.1825, result.x, 0.001);
		assertEquals(0.3651, result.y, 0.001);
		assertEquals(0.5477, result.z, 0.001);
		assertEquals(0.7302, result.w, 0.001);
		
		//test the length is still 1
		float length = result.length();
		assertEquals(1, length, 0.001);
	}

	/**
	 * Tests the plus operation
	 */
	@Test
	public void testPlus(){
		Vec4 testVec1 = new Vec4(1,2,3,4);
		Vec4 testVec2 = new Vec4(5,6,7,8);
		
		Vec4 result = testVec1.plus(testVec2);
		
		assertEquals(6, result.x, 0.001);
		assertEquals(8, result.y, 0.001);
		assertEquals(10, result.z, 0.001);
		assertEquals(12, result.w, 0.001);
	}
}
