package imp.core.exceptions.expressions;

import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.List;
import java.util.Map.Entry;

import imp.core.expressions.Function;
import imp.core.expressions.FunctionSignature;

import org.junit.Test;

public class TestExpressionExceptions {
	
	
	
	@Test
	public void testFunctionAlreadyExists(){
		FunctionSignature f = new FunctionSignature("required", "strings", null, null);
		FunctionAlreadyExists e = new FunctionAlreadyExists(f);
		
		assertEquals(f, e.signature);
	}

	
	@Test
	public void testFunctionAmbiguous(){
		FunctionSignature f = new FunctionSignature("required", "strings", null, null);
		List<Entry<FunctionSignature, Function>> m = new ArrayList<Entry<FunctionSignature, Function>>();
		FunctionAmbiguous e = new FunctionAmbiguous(f, m, false);
		
		assertEquals(f, e.signature);
		assertEquals(m, e.matches);
	}
	
	@Test
	public void testFunctionSignatureDoesNotExist(){
		FunctionSignature f = new FunctionSignature("required", "strings", null, null);
		FunctionSignatureDoesNotExist e = new FunctionSignatureDoesNotExist(f);
		
		assertEquals(f, e.signature);
	}
	
	/*
	 * Testing constructors, all go unused intentionally
	 */
	@SuppressWarnings("unused")
	@Test
	public void testInvalidFunctionSignature(){
		InvalidFunctionSignature e = new InvalidFunctionSignature(0, FunctionSignature.class);
		
		e = new InvalidFunctionSignature(FunctionSignature.class);
		
		e = new InvalidFunctionSignature();
	}
	
	
}
