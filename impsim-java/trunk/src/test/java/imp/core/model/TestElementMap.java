/**
 * TestElementMap.java
 * February 24, 2011
 */
package imp.core.model;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.model.Element;
import imp.core.model.ElementMap;
import imp.core.model.elements.Body;
import imp.core.structures.Point;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * Unit tests for the ElementMap.java class.
 * 
 * @author dykstran klehmc
 * @version 1.0
 * 
 */
@SuppressWarnings("javadoc")
public class TestElementMap {

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.model.ElementMap#contains(java.lang.String)}.
	 * 
	 * @throws NameConflictException
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testContains() throws NameConflictException, NullParameterException, InvalidParameterException {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> map = new ElementMap<Body>(nameSet);
		Body body = new Body(name);

		map.put(body);

		assertTrue(map.contains(name));
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#ElementMap(java.util.Set)}.
	 */
	@Test
	public void testElementMap() {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> t = new ElementMap<Body>(nameSet);

		ElementMap<Body> map = new ElementMap<Body>(t);

		assertNotNull(map);
		assertEquals(t, map);
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#ElementMap(java.util.Set)}.
	 */
	@Test
	public void testElementMapNull() {
		ElementMap<Body> n = null;

		this.thrown.expect(NullParameterException.class);
		new ElementMap<Body>(n);
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#ElementMap(java.util.Set)}.
	 */
	@Test
	public void testElementMapSet() {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> map = new ElementMap<Body>(nameSet);

		assertNotNull(map);
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#ElementMap(java.util.Set)}.
	 */
	@Test
	public void testElementMapSetNull() {
		Set<String> nameSet = null;

		this.thrown.expect(NullParameterException.class);
		new ElementMap<Body>(nameSet);
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#get(java.lang.String)} and
	 * {@link imp.core.model.ElementMap#put(imp.core.model.Element)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testGetPut() throws NullParameterException, NameConflictException, InvalidParameterException {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> map = new ElementMap<Body>(nameSet);

		Body body = new Body(name);

		map.put(body);

		assertEquals(body, map.get(name));
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#iterator()}.
	 */
	@Test
	public void testIterator() {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> map = new ElementMap<Body>(nameSet);

		Iterator<Body> itr = map.iterator();

		assertNotNull(itr);
	}

	/**
	 * Test method for .
	 * 
	 * 
	 * /** Test method for {@link imp.core.model.ElementMap#remove(java.lang.String)}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testRemove() throws NullParameterException, NameConflictException, InvalidParameterException {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> map = new ElementMap<Body>(nameSet);

		Body body = new Body(name);

		map.put(body);

		assertEquals(body, map.remove(name));
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#size()}.
	 * 
	 * @throws NullParameterException
	 * @throws NameConflictException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testSize() throws NullParameterException, NameConflictException, InvalidParameterException {
		String name = new String("Susie");
		Set<String> nameSet = new HashSet<String>();
		nameSet.add(name);
		ElementMap<Body> map = new ElementMap<Body>(nameSet);

		Body body = new Body(name);

		map.put(body);

		// 1 element has been added
		assertEquals(1, map.size());
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseObjectType() throws NullParameterException, InvalidParameterException {

		Set<String> nameSet = new HashSet<String>();
		nameSet.add("BodyName");
		ElementMap<Element> map = new ElementMap<Element>(nameSet);

		Point p = new Point();

		// different object type
		assertFalse(map.equals(p));
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEquals() throws NullParameterException, InvalidParameterException {

		Set<String> nameSet = new HashSet<String>();
		nameSet.add("BodyName");
		ElementMap<Element> map = new ElementMap<Element>(nameSet);
		ElementMap<Element> mapCpy = new ElementMap<Element>(nameSet);

		// sunny day
		assertTrue(map.equals(mapCpy));
		assertTrue(mapCpy.equals(map));
	}

	/**
	 * Test method for {@link imp.core.model.ElementMap#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalse() throws NullParameterException, InvalidParameterException {

		Set<String> nameSet = new HashSet<String>();
		nameSet.add("BodyName");
		ElementMap<Element> map = new ElementMap<Element>(nameSet);
		Set<String> nameSetDiff = new HashSet<String>();
		nameSetDiff.add("BodyName2");
		ElementMap<Element> mapDiff = new ElementMap<Element>(nameSetDiff);

		// non equal
		assertFalse(map.equals(mapDiff));
		assertFalse(mapDiff.equals(map));
	}
	
	/**
	 * Test method for {@link imp.core.model.ElementMap#equals(Object)}.
	 * 
	 * @throws InvalidParameterException
	 * @throws NullParameterException
	 */
	@Test
	public void testEqualsFalseNull() throws NullParameterException, InvalidParameterException {

		Set<String> nameSet = new HashSet<String>();
		nameSet.add("BodyName");
		ElementMap<Element> map = new ElementMap<Element>(nameSet);
		
		// should not equal null map
		assertFalse(map.equals( null ));
	}
}