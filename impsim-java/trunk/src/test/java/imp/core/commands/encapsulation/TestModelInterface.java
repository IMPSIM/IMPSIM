package imp.core.commands.encapsulation;

import static org.junit.Assert.*;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.model.elements.Joint;
import imp.core.model.joints.Revolute;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Tests the Interface between the Plugin and the Core
 * @author ebertb
 * @version 1.0
 */
public class TestModelInterface {
	
	

	/**
	 * The type of exception expected during testing.
	 */
	@Rule
	public ExpectedException thrown = ExpectedException.none();
	
	/**
	 * Tests the first getBodies() Method
	 */
	@Test
	public void testGetBodiesMethodOne(){
		
		mockInterface mi = new mockInterface();
		mi.init();
		mi.addBo();
		
		assertTrue(mi.getBodies().contains("He"));
		assertTrue(mi.getBodies().contains("Go"));
		assertTrue(mi.getBodies().contains("Test"));
	}
	
	/**
	 * Tests the getJoints() method
	 */
	@Test
	public void testGetJointsMethod(){
		mockInterface mi = new mockInterface();
		mi.init();
		mi.addJo();
		
		assertTrue(mi.getJoints().contains("A1"));
		assertTrue(mi.getJoints().contains("A2"));
		assertTrue(mi.getJoints().contains("A3"));
	}
	
	private class mockInterface extends CoreAPI{
		public void addBo(){
			try {
				model.addBody("Go");
				model.addBody("He");
				model.addBody("Test");
			} catch (NullParameterException e) {
				e.printStackTrace();
			} catch (NameConflictException e) {
				e.printStackTrace();
			} catch (InvalidParameterException e) {
				e.printStackTrace();
			}
			
		}
		
		public void init(){
			try {
				ch = new CommandHolder(model);
			} catch (FunctionAlreadyExists e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		public void addJo(){
			Joint A1;
			Joint A2;
			Joint A3;
			try {
				A1 = new Revolute("A1");
				A2 = new Revolute("A2");
				A3 = new Revolute("A3");
				
				model.addJoint(A1, "A", "B");
				model.addJoint(A2, "B", "C");
				model.addJoint(A3, "C", "D");
			} catch (NullParameterException e) {
				e.printStackTrace();
			} catch (InvalidParameterException e) {
				e.printStackTrace();
			} catch (SelfLoopException e) {
				e.printStackTrace();
			} catch (NameConflictException e) {
				e.printStackTrace();
			} catch (JointNotFoundException e) {
				e.printStackTrace();
			}
			
			
			
			
		}
	}
}
