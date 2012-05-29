/**
 * TestElement.java
 * February 24, 2011
 */
package imp.core.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Element;
import imp.core.model.elements.Body;
import imp.core.structures.Point;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the Element class.
 * 
 * @author dykstran klehmc
 * @version 1.0
 * 
 */
@SuppressWarnings("javadoc")
public class TestElement {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.Element#Element(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testElement() throws NullParameterException, InvalidParameterException {

		Element el = new Body("Element");

		assertNotNull(el);
	}

	/**
	 * Test method for {@link imp.core.model.Element#getName()}.
	 * 
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetName() throws NullParameterException, InvalidParameterException {
		String name = new String("Body");
		Element el = new Body(name);

		assertEquals(name, el.getName());
	}

	/**
	 * Test method for {@link imp.core.model.Element#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Element e = new Body("Body");

		Point p = new Point();

		// different object type
		assertFalse(e.equals(p));
	}

	/**
	 * Test method for {@link imp.core.model.Element#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Element e = new Body("Body");
		Element eCpy = new Body("Body");

		// sunny day
		assertTrue(e.equals(eCpy));
		assertTrue(eCpy.equals(e));
	}

	/**
	 * Test method for {@link imp.core.model.Element#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Element e = new Body("Body");
		Element eDiff = new Body("DiffBody");

		// non equal
		assertFalse(e.equals(eDiff));
		assertFalse(eDiff.equals(e));
	}
	
	/**
	 * Test method for {@link imp.core.model.Element#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {

		Element e = new Body("Body");
		
		// should not equal null element
		assertFalse(e.equals( null ));
	}
}
