package imp.core.graphics;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.fail;
import imp.core.observer.NotificationType;

import java.util.List;

import javax.media.opengl.GL3;

import org.junit.Test;

/**
 * Test class to test the functionality of the AbstractDataSource
 * 
 * @author kreierj
 * @version 1
 */
public class TestDataSource {
	/**
	 * Make sure no problems occur during construction
	 */
	@Test
	public void testConstructors() {
		AbstractDataSource mock = new MockDataSource();

		AbstractGLObject object = new MockGLObject("Object");

		// calling all the empty calls to prevent them from dragging down coverage
		mock.execute();
		mock.update((GL3) null);
		mock.update((NotificationType) null);

		object.dispose(null);
		object.draw(null);
		object.updateData(null, null, null);
		object.initialize(null);

		// check the null name exception
		try {
			object = new MockGLObject(null);
			fail("Null pointer exception should have been thrown for null name");
		} catch (NullPointerException e) {
			// expected exception
		}
	}

	/**
	 * Tests accessors for the data source
	 */
	@Test
	public void testAccessors() {

		AbstractDataSource mockSource = new MockDataSource();
		AbstractGLObject mockObject = new MockGLObject("Object 1");

		// put the object in the list
		mockSource.putObject(mockObject);

		// test getObject
		AbstractGLObject testObject = mockSource.getObject("Object 1");
		assertEquals(mockObject, testObject);

		// test object list
		List<AbstractGLObject> list = mockSource.getObjects();
		assertEquals(1, list.size());
		assertEquals(mockObject, list.get(0));

		// remove the object
		testObject = mockSource.removeObject("Object 1");
		assertEquals(mockObject, testObject);

		// make sure it actually removed it
		testObject = mockSource.removeObject("Object 1");
		assertNull(testObject);

		// test the duplicate object name exception
		mockSource.putObject(mockObject);
		try {
			mockSource.putObject(mockObject);
			fail("Duplicate name exception should have been thrown");
		} catch (DuplicateNameException e) {
			// expected exception
		}
	}

	/**
	 * Mock class for the data source
	 * 
	 * @author kreierj
	 * 
	 */
	private class MockDataSource extends AbstractDataSource {

		@Override
		public void execute() {

		}

		@Override
		public void update(NotificationType updateType) {

		}

		@Override
		public void update(GL3 gl) {

		}
	}

	/**
	 * Mock class for the GL object
	 * 
	 * @author kreierj
	 * 
	 */
	private class MockGLObject extends AbstractGLObject {

		public MockGLObject(String name) {
			super(name);
		}

		@Override
		public void draw(GL3 gl) {

		}

		@Override
		public void initialize(GL3 gl) {

		}

		@Override
		public void dispose(GL3 gl) {

		}

		@Override
		public void updateData(GL3 gl, List<Float> newData, DATA_TYPE dataType) {

		}
	}
}
