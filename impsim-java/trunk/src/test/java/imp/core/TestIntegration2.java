package imp.core;

import static org.junit.Assert.assertTrue;
import imp.core.commands.JointExpressionCommand;
import imp.core.commands.data.DataXSlideCommand;
import imp.core.commands.data.DataYSlideCommand;
import imp.core.commands.definition.XSlideCommand;
import imp.core.commands.definition.YSlideCommand;
import imp.core.commands.encapsulation.CommandHolder;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.commands.joints.RevoluteCommand;
import imp.core.exceptions.IMPException;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.structures.Point;

import org.junit.Test;

@SuppressWarnings("javadoc")
public class TestIntegration2 {

	@Test
	public void yokeIntegrationRuns() throws IMPException {
		Model model = new Model();
		CommandHolder ch = new CommandHolder(model);

		// ZPIN(ysld,bar)=ry //a pin in the z-axis holding the yslider and the bar together
		// ZPIN(bar,xsld)=rx //a pin in the z-axis holding the bar and the xslider together
		// XSLIDE(xsld,base)=px //a prism in the x-axis holding the xslider and the base together
		// YSLIDE(base,ysld)=py //a prism in the y-axis holding the base and the xslider together
		new XSlideCommand("xsld", "base", "px").execute(model);
		new YSlideCommand("base", "ysld", "py").execute(model);

		// DATA ZPIN(rx) = 3,0,0

		RevoluteCommand.CreateZPin("rx", "bar", "xsld", new Point(3, 0, 0), new Point(4, 0, 0), new Point(3, 1, 0)).execute(model);
		// DATA ZPIN(ry) = 0,3,0
		RevoluteCommand.CreateZPin("ry", "ysld", "bar", new Point(0, 3, 0), new Point(1, 3, 0), new Point(0, 4, 0)).execute(model);
		// DATA YSLIDE(py) = 0,3,0
		new DataYSlideCommand(new Point(0, 3, 0), "py").execute(model);
		// DATA XSLIDE(px) = 3,0,0
		new DataXSlideCommand(new Point(3, 0, 0), "px").execute(model);
		JointExpressionCommand jc = new JointExpressionCommand("px", JVAR.ZDISPLACEMENT, new FakeExpressionLiteral(-0.5));
		jc.execute(model);
		model.setGround("base");
		// List<LoopVariable> loopVars = new ArrayList<LoopVariable>();
		// loopVars.add(new LoopVariable("px", JVAR.ZDISPLACEMENT, .5));

		// loopVars.add(new LoopVariable("py", JVAR.ZDISPLACEMENT, 0)); This is in the yoke.dat, but seems unnecessary

		ch.compile();
		assertTrue(ch.verify());
		ch.run(100, 5);
	}

}
