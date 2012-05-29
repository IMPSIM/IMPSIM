package imp.core;

import static org.junit.Assert.assertTrue;
import imp.core.commands.JointExpressionCommand;
import imp.core.commands.encapsulation.CommandHolder;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.commands.joints.RevoluteCommand;
import imp.core.exceptions.IMPException;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.structures.Point;

import org.junit.Test;

@SuppressWarnings("javadoc")
public class testStephensonSixBar {

	@Test
	public void stephensonSixAxisIntegrationRuns() throws IMPException {
		Model model = new Model();
		CommandHolder ch = new CommandHolder(model);

		RevoluteCommand a0 = RevoluteCommand.CreateZPin("A0", "Ground", "2", new Point(41, 27, 0), new Point(50, 27, 0), new Point(81, 132, 0));
		a0.execute(model);
		RevoluteCommand a = RevoluteCommand.CreateZPin("A", "2", "3", new Point(81, 132, 0), new Point(41, 27, 0), new Point(381, 283, 0));
		a.execute(model);
		RevoluteCommand c = RevoluteCommand.CreateZPin("C", "2", "5", new Point(55, 192, 0), new Point(81, 132, 0), new Point(278, 414, 0));
		c.execute(model);
		RevoluteCommand b0 = RevoluteCommand.CreateZPin("B0", "Ground", "4", new Point(374, 85, 0), new Point(474, 85, 0), new Point(381, 283, 0));
		b0.execute(model);
		RevoluteCommand b = RevoluteCommand.CreateZPin("B", "4", "3", new Point(381, 283, 0), new Point(374, 85, 0), new Point(81, 132, 0));
		b.execute(model);
		RevoluteCommand e = RevoluteCommand.CreateZPin("E", "4", "6", new Point(513, 329, 0), new Point(381, 283, 0), new Point(278, 414, 0));
		e.execute(model);
		RevoluteCommand d = RevoluteCommand.CreateZPin("D", "6", "5", new Point(278, 414, 0), new Point(513, 329, 0), new Point(55, 192, 0));
		d.execute(model);
		JointExpressionCommand jc = new JointExpressionCommand("A0", JVAR.THETA, new FakeExpressionLiteral(0.0174532925));
		jc.execute(model);
		model.setGround("Ground");

		// List<LoopVariable> loopVars = new ArrayList<LoopVariable>();
		// loopVars.add(new LoopVariable("A0", JVAR.THETA, 1*(Math.PI/180)));

		ch.compile();
		assertTrue(ch.verify());
		ch.run(100, 10);
	}
}
