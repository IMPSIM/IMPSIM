package imp.core.commands;

import imp.core.structures.Point;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

public class TestJointBuilder {

	Point p1;
	Point p2;
	Point p3;

	@Before
	public void setUp() {
		p1 = new Point(0, 0, 0);
		p2 = new Point(0, 0, 5);
		p3 = new Point(5, 0, 0);
	}

	@Rule
	public ExpectedException thrown = ExpectedException.none();

	@Test
	public void TestBasic() throws Exception {
		DynamicJointBuilder.createInstance("cylinder", "jointName", "body1", "body2", p1, p2, p3);
	}
}
