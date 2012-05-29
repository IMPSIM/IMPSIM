package imp.core.graphics;

import static org.junit.Assert.*;

import org.junit.Test;


/**
 * Class or testing the unctionality o the Mat4 class
 * @author kreierj
 * @version 1
 */
public class TestMat4 {
	
	/**
	 * Tests that the constructors construct correctly. Assumes raw value works.
	 */
	@Test
	public void testConstructors(){
		//test diagonal constructor
		Mat4 testMat = new Mat4(1.0f);
		
		float[] mat = testMat.raw();
		assertEquals(1.0, mat[0], .001);
		assertEquals(1.0, mat[5], .001);
		assertEquals(1.0, mat[10], .001);
		assertEquals(1.0, mat[15], .001);
		
		assertEquals(0.0, mat[1],.001);
		assertEquals(0.0, mat[2],.001);
		assertEquals(0.0, mat[3],.001);
		assertEquals(0.0, mat[4],.001);
		assertEquals(0.0, mat[6],.001);
		assertEquals(0.0, mat[7],.001);
		assertEquals(0.0, mat[8],.001);
		assertEquals(0.0, mat[9],.001);
		assertEquals(0.0, mat[11],.001);
		assertEquals(0.0, mat[12],.001);
		assertEquals(0.0, mat[13],.001);
		assertEquals(0.0, mat[14],.001);
		
		//end test
		
		
		//with input matrix
		float[] input = new float[] {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16
		};
		
		testMat = new Mat4(input);
		
		mat = testMat.raw();
		assertEquals(1, mat[0],.001);
		assertEquals(2, mat[1],.001);
		assertEquals(3, mat[2],.001);
		assertEquals(4, mat[3],.001);
		assertEquals(5, mat[4],.001);
		assertEquals(6, mat[5],.001);
		assertEquals(7, mat[6],.001);
		assertEquals(8, mat[7],.001);
		assertEquals(9, mat[8],.001);
		assertEquals(10, mat[9],.001);
		assertEquals(11, mat[10],.001);
		assertEquals(12, mat[11],.001);
		assertEquals(13, mat[12],.001);
		assertEquals(14, mat[13],.001);
		assertEquals(15, mat[14],.001);
		assertEquals(16, mat[15],.001);
		//end test
		
		
		//as copy
		
		Mat4 testMat2 = new Mat4(testMat);
		mat = testMat2.raw();
		
		assertEquals(1, mat[0],.001);
		assertEquals(2, mat[1],.001);
		assertEquals(3, mat[2],.001);
		assertEquals(4, mat[3],.001);
		assertEquals(5, mat[4],.001);
		assertEquals(6, mat[5],.001);
		assertEquals(7, mat[6],.001);
		assertEquals(8, mat[7],.001);
		assertEquals(9, mat[8],.001);
		assertEquals(10, mat[9],.001);
		assertEquals(11, mat[10],.001);
		assertEquals(12, mat[11],.001);
		assertEquals(13, mat[12],.001);
		assertEquals(14, mat[13],.001);
		assertEquals(15, mat[14],.001);
		assertEquals(16, mat[15],.001);
		
		//end test
		
	}
	
	/**
	 * Tests matrix multiplication
	 */
	@Test
	public void testMultiply(){
		
		float[] input = new float[] {
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12,
				13, 14, 15, 16
			};
		
		//multiplied by identity
		Mat4 mat1 = new Mat4(input);
		Mat4 mat2 = new Mat4(1.0f);
		
		Mat4 result = mat1.multiply(mat2);
		
		float[] mat = result.raw();
		
		assertEquals(1, mat[0],.001);
		assertEquals(2, mat[1],.001);
		assertEquals(3, mat[2],.001);
		assertEquals(4, mat[3],.001);
		assertEquals(5, mat[4],.001);
		assertEquals(6, mat[5],.001);
		assertEquals(7, mat[6],.001);
		assertEquals(8, mat[7],.001);
		assertEquals(9, mat[8],.001);
		assertEquals(10, mat[9],.001);
		assertEquals(11, mat[10],.001);
		assertEquals(12, mat[11],.001);
		assertEquals(13, mat[12],.001);
		assertEquals(14, mat[13],.001);
		assertEquals(15, mat[14],.001);
		assertEquals(16, mat[15],.001);
		
		//end test
		
		
		//multiplied by itsel
		mat2 = new Mat4(input);
		
		result = mat1.multiply(mat2);
		
		mat = result.raw();
		assertEquals(90, mat[0],.001);
		assertEquals(100, mat[1],.001);
		assertEquals(110, mat[2],.001);
		assertEquals(120, mat[3],.001);
		assertEquals(202, mat[4],.001);
		assertEquals(228, mat[5],.001);
		assertEquals(254, mat[6],.001);
		assertEquals(280, mat[7],.001);
		assertEquals(314, mat[8],.001);
		assertEquals(356, mat[9],.001);
		assertEquals(398, mat[10],.001);
		assertEquals(440, mat[11],.001);
		assertEquals(426, mat[12],.001);
		assertEquals(484, mat[13],.001);
		assertEquals(542, mat[14],.001);
		assertEquals(600, mat[15],.001);
		
		//end test
		
	}
	
	/**
	 * Tests the perspective calculations
	 */
	@Test
	public void testPerspective(){
		
		Mat4 testMat = new Mat4(1.0f);
		
		testMat.perspective(45.0f, 16.0f/9.0f, 1.0f, 1000f);
		
		float[] mat = testMat.raw();
		assertEquals(1.35799513, mat[0],.001);//expected results calculated by hand
		assertEquals(0, mat[1],.001);
		assertEquals(0, mat[2],.001);
		assertEquals(0, mat[3],.001);
		assertEquals(0, mat[4],.001);
		assertEquals(2.4142, mat[5],.001);
		assertEquals(0, mat[6],.001);
		assertEquals(0, mat[7],.001);
		assertEquals(0, mat[8],.001);
		assertEquals(0, mat[9],.001);
		assertEquals(-1.002, mat[10],.001);
		assertEquals(-1.0, mat[11],.001);
		assertEquals(0, mat[12],.001);
		assertEquals(0, mat[13],.001);
		assertEquals(-2.002, mat[14],.001);
		assertEquals(0, mat[15],.001);
		
	}
	
	/**
	 * Tests scaling
	 */
	@Test
	public void testScale(){
		float[] input = new float[] {
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12,
				13, 14, 15, 16
			};
		
		//scalar input
		Mat4 testMat = new Mat4(input);
		
		testMat.scale(2.0f, 3.0f, 4.0f);
		
		float[] mat = testMat.raw();
		assertEquals(2, mat[0],.001);
		assertEquals(4, mat[1],.001);
		assertEquals(6, mat[2],.001);
		assertEquals(8, mat[3],.001);
		assertEquals(15, mat[4],.001);
		assertEquals(18, mat[5],.001);
		assertEquals(21, mat[6],.001);
		assertEquals(24, mat[7],.001);
		assertEquals(36, mat[8],.001);
		assertEquals(40, mat[9],.001);
		assertEquals(44, mat[10],.001);
		assertEquals(48, mat[11],.001);
		assertEquals(13, mat[12],.001);
		assertEquals(14, mat[13],.001);
		assertEquals(15, mat[14],.001);
		assertEquals(16, mat[15],.001);
		//end test
		
		//vector input
		testMat = new Mat4(input);
		
		testMat.scale(new Vec3(2.0f, 3.0f, 4.0f));
		
		mat = testMat.raw();
		assertEquals(2, mat[0],.001);
		assertEquals(4, mat[1],.001);
		assertEquals(6, mat[2],.001);
		assertEquals(8, mat[3],.001);
		assertEquals(15, mat[4],.001);
		assertEquals(18, mat[5],.001);
		assertEquals(21, mat[6],.001);
		assertEquals(24, mat[7],.001);
		assertEquals(36, mat[8],.001);
		assertEquals(40, mat[9],.001);
		assertEquals(44, mat[10],.001);
		assertEquals(48, mat[11],.001);
		assertEquals(13, mat[12],.001);
		assertEquals(14, mat[13],.001);
		assertEquals(15, mat[14],.001);
		assertEquals(16, mat[15],.001);
		//end test
	}
	
	/**
	 * Tests setting indexes and columns
	 */
	@Test
	public void testSet(){
		
		Mat4 testMat = new Mat4(1.0f);
		
		//scalar input
		testMat.set(2, 2, 4.0f);
		
		float[] mat = testMat.raw();
		assertEquals(1, mat[0],.001);
		assertEquals(0, mat[1],.001);
		assertEquals(0, mat[2],.001);
		assertEquals(0, mat[3],.001);
		assertEquals(0, mat[4],.001);
		assertEquals(1, mat[5],.001);
		assertEquals(0, mat[6],.001);
		assertEquals(0, mat[7],.001);
		assertEquals(0, mat[8],.001);
		assertEquals(0, mat[9],.001);
		assertEquals(4, mat[10],.001);
		assertEquals(0, mat[11],.001);
		assertEquals(0, mat[12],.001);
		assertEquals(0, mat[13],.001);
		assertEquals(0, mat[14],.001);
		assertEquals(1, mat[15],.001);
		
		//end test
		
		//vector input
		testMat = new Mat4(1.0f);
		
		testMat.set(1, new Vec4(2,3,4,5));
		
		mat = testMat.raw();
		assertEquals(1, mat[0],.001);
		assertEquals(0, mat[1],.001);
		assertEquals(0, mat[2],.001);
		assertEquals(0, mat[3],.001);
		assertEquals(2, mat[4],.001);
		assertEquals(3, mat[5],.001);
		assertEquals(4, mat[6],.001);
		assertEquals(5, mat[7],.001);
		assertEquals(0, mat[8],.001);
		assertEquals(0, mat[9],.001);
		assertEquals(1, mat[10],.001);
		assertEquals(0, mat[11],.001);
		assertEquals(0, mat[12],.001);
		assertEquals(0, mat[13],.001);
		assertEquals(0, mat[14],.001);
		assertEquals(1, mat[15],.001);
		
		//end test
	}
	
	/**
	 * Tests matrix translation
	 */
	@Test
	public void testTranslate(){
		//scalar input
		float[] input = new float[] {
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12,
				13, 14, 15, 16
			};
		
		Mat4 testMat = new Mat4(input);
		
		testMat.translate(2, 3, 4);
		
		float[] mat = testMat.raw();
		
		assertEquals(1, mat[0],.001);
		assertEquals(2, mat[1],.001);
		assertEquals(3, mat[2],.001);
		assertEquals(4, mat[3],.001);
		assertEquals(5, mat[4],.001);
		assertEquals(6, mat[5],.001);
		assertEquals(7, mat[6],.001);
		assertEquals(8, mat[7],.001);
		assertEquals(9, mat[8],.001);
		assertEquals(10, mat[9],.001);
		assertEquals(11, mat[10],.001);
		assertEquals(12, mat[11],.001);
		assertEquals(66, mat[12],.001);
		assertEquals(76, mat[13],.001);
		assertEquals(86, mat[14],.001);
		assertEquals(96, mat[15],.001);
		
		//end test
		
		
		//vector input
		
		testMat = new Mat4(input);
		
		testMat.translate(new Vec3(2,3,4));
		
		assertEquals(1, mat[0],.001);
		assertEquals(2, mat[1],.001);
		assertEquals(3, mat[2],.001);
		assertEquals(4, mat[3],.001);
		assertEquals(5, mat[4],.001);
		assertEquals(6, mat[5],.001);
		assertEquals(7, mat[6],.001);
		assertEquals(8, mat[7],.001);
		assertEquals(9, mat[8],.001);
		assertEquals(10, mat[9],.001);
		assertEquals(11, mat[10],.001);
		assertEquals(12, mat[11],.001);
		assertEquals(66, mat[12],.001);
		assertEquals(76, mat[13],.001);
		assertEquals(86, mat[14],.001);
		assertEquals(96, mat[15],.001);
		
		
		//end test
		
	}
	
	
	/**
	 * Tests matrix transposing
	 */
	@Test
	public void testTranspose(){
		
		float[] input = new float[] {
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 11, 12,
				13, 14, 15, 16
			};
		
		Mat4 testMat = new Mat4(input);
		
		testMat = testMat.transpose();
		
		float[] mat = testMat.raw();
		
		assertEquals(1, mat[0],.001);
		assertEquals(5, mat[1],.001);
		assertEquals(9, mat[2],.001);
		assertEquals(13, mat[3],.001);
		assertEquals(2, mat[4],.001);
		assertEquals(6, mat[5],.001);
		assertEquals(10, mat[6],.001);
		assertEquals(14, mat[7],.001);
		assertEquals(3, mat[8],.001);
		assertEquals(7, mat[9],.001);
		assertEquals(11, mat[10],.001);
		assertEquals(15, mat[11],.001);
		assertEquals(4, mat[12],.001);
		assertEquals(8, mat[13],.001);
		assertEquals(12, mat[14],.001);
		assertEquals(16, mat[15],.001);
		
	}
	
	

}
