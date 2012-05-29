/**
 * ElementMap.java
 * May 11, 2011
 */
package imp.core.model;

import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

/**
 * Represents a map of elements in a model.
 * 
 * @author biesew
 * @edit dykstran Updated JavaDoc
 * @version 1.01
 * @param <V> the type of the elements contained in this map.
 */
public class ElementMap<V extends Element> implements Iterable<V> {

	/**
	 * The map of all elements in this data structure.
	 */
	private Map<String, V> elements;

	/**
	 * A set of all the element names used within a single model.
	 */
	private Set<String> commonElementNames;

	/**
	 * Creates a new map of elements as a copy of the passed map.
	 * 
	 * @param map A map of elements
	 */
	public ElementMap(ElementMap<V> map) {
		if (map == null) {
			throw new NullParameterException("The element map can't be null", 0);
		}
		this.commonElementNames = new HashSet<String>(map.commonElementNames);
		this.elements = new HashMap<String, V>(map.elements);
	}

	/**
	 * Creates a new map of elements.
	 * 
	 * @param names The set of all the element names used within a single model.
	 */
	public ElementMap(Set<String> names) {
		if (names == null) {
			throw new NullParameterException("The set of names can't be null", 0);
		}
		this.commonElementNames = names;
		this.elements = new HashMap<String, V>();
	}

	/**
	 * Returns a unique, deterministic key for a given string, i.e. the string is returned in upper case.
	 * 
	 * @param key The key to use.
	 * @return The unique version of the given key.
	 */
	private String computeKey(String key) {
		return key.toUpperCase();
	}

	/**
	 * Returns true if this map contains a mapping for the specified key.
	 * <p>
	 * More formally, returns true if and only if this map contains a mapping for a key k such that (key==null ? k==null
	 * : key.equals(k)). (There can be at most one such mapping.)
	 * <p>
	 * 
	 * @see <a
	 *      href="http://download.oracle.com/javase/6/docs/api/java/util/Map.html#containsKey(java.lang.Object)">Map.containsKey(java.lang.Object)</a>
	 * 
	 * @param name The name of an Element object whose presence in this map is to be tested.
	 * @return True if this map contains an Element object for the specified key, false otherwise.
	 */
	public boolean contains(String name) {
		return this.elements.containsKey(this.computeKey(name));
	}

	/**
	 * Returns the Element object to which the specified key is mapped, or null if this map contains no mapping for the
	 * key.
	 * 
	 * <p>
	 * More formally, if this map contains a mapping from a key k to a value v such that (key==null ? k==null :
	 * key.equals(k)), then this method returns v; otherwise it returns null. (There can be at most one such mapping.)
	 * <p>
	 * If this map permits null values, then a return value of null does not necessarily indicate that the map contains
	 * no mapping for the key; it's also possible that the map explicitly maps the key to null. The containsKey
	 * operation may be used to distinguish these two cases.
	 * <p>
	 * 
	 * <pre>
	 * From <a href='http://download.oracle.com/javase/6/docs/api/java/util/Map.html#get(java.lang.Object)'>Map.get(java.lang.Object)</a>
	 * </pre>
	 * 
	 * @param name The name of an element object which is to be returned.
	 * @return The Element object to which the specified key is mapped, or null if there is no mapping for the key.
	 */
	public V get(String name) {
		return this.elements.get(this.computeKey(name));
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Iterable#iterator()
	 */
	@Override
	public Iterator<V> iterator() {
		return this.elements.values().iterator();
	}

	/**
	 * Associates the specified value with the specified key in this map (optional operation). If the map previously
	 * contained a mapping for the key, the old value is replaced by the specified value. (A map m is said to contain a
	 * mapping for a key k if and only if m.containsKey(k) would return true.)
	 * 
	 * <pre>
	 * From <a href='http://download.oracle.com/javase/6/docs/api/java/util/Map.html#put(K, V)'>Map.put(K, V)</a>
	 * </pre>
	 * 
	 * @param value The Element object to put into the map.
	 * @return The previous value associated with the name of the value or null if there wasn't one.
	 * @throws NameConflictException Thrown if the name conflicts with an element already present in the model.
	 */
	public V put(V value) throws NameConflictException {
		String key = this.computeKey(value.getName());
		if ((this.elements.containsKey(key)) || (!this.commonElementNames.contains(key))) {
			this.commonElementNames.add(key);
			return this.elements.put(key, value);
		} else {
			throw new NameConflictException(value.getName());
		}
	}

	/**
	 * Removes the mapping for a key from this map if it is present (optional operation). More formally, if this map
	 * contains a mapping from key k to value v such that (key==null ? k==null : key.equals(k)), that mapping is
	 * removed. (The map can contain at most one such mapping.)
	 * <p>
	 * Returns the value to which this map previously associated the key, or null if the map contained no mapping for
	 * the key.
	 * <p>
	 * If this map permits null values, then a return value of null does not necessarily indicate that the map contained
	 * no mapping for the key; it's also possible that the map explicitly mapped the key to null.
	 * <p>
	 * The map will not contain a mapping for the specified key once the call returns.
	 * 
	 * <pre>
	 * From <a href=
	 * 'http://download.oracle.com/javase/6/docs/api/java/util/Map.html#remove(java.lang.Object)'>Map.remove(java.lang.Object)</a>
	 * </pre>
	 * 
	 * @param name The name of the desired element.
	 * @return The element associated with the name given.
	 */
	public V remove(String name) {
		String key = this.computeKey(name);
		V returnValue = this.elements.remove(key);
		if (returnValue != null) {
			this.commonElementNames.remove(key);
		}
		return returnValue;
	}

	/**
	 * Returns the number of key-value mappings in this map. If the map contains more than Integer.MAX_VALUE elements,
	 * returns Integer.MAX_VALUE.
	 * 
	 * <pre>
	 * From <a href='http://download.oracle.com/javase/6/docs/api/java/util/Map.html#size()'>Map.size()</a>
	 * </pre>
	 * 
	 * @return The number of elements in the map.
	 */
	public int size() {
		return this.elements.size();
	}

	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object otherObject) {

		// check if same object
		if (this == otherObject) {
			return true;
		}

		// check if object passed in is ElementMap
		if (!(otherObject instanceof ElementMap)) {
			return false;
		} else {
			// cast object into ElementMap for comparison
			ElementMap<?> otherMap = (ElementMap<?>) otherObject;
			// return whether EVERY attribute is the same
			return otherMap.commonElementNames.equals(this.commonElementNames) && otherMap.elements.equals(this.elements);
		}
	}
}
