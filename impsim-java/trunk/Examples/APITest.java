package imp;

import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;

import javax.swing.JFrame;

import imp.core.commands.GroundCommand;
import imp.core.commands.JointExpressionCommand;
import imp.core.commands.PropertyAssignmentCommand;
import imp.core.commands.encapsulation.CommandHolder;
import imp.core.commands.expressions.FakeExpression;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.commands.expressions.Function;
import imp.core.commands.joints.RevoluteCommand;
import imp.core.exceptions.BodyNotFoundException;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.LoopException;
import imp.core.exceptions.SelfLoopException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.graphics.AbstractModelView;
import imp.core.graphics.ModelDataSource;
import imp.core.model.Model;
import imp.core.model.elements.Joint.JVAR;
import imp.core.structures.Point;

/**
 * This class demonstrates how to make a model execute and display using the IMP API
 * 
 * Running the program then pressing Space will display the model in the frame.
 * 
 * 
 */
public class APITest extends AbstractModelView{

	/**
	 * IMP API object
	 */
	private CommandHolder ch;

	/**
	 * Main method
	 */
	public static void main(String[] args) {
		APITest model = new APITest();
		model.init();
	}

	/**
	 * Basic initialization of the canvas
	 */
	public void init(){
		//initializes the GL canvas
		JFrame frame = new JFrame();
		frame.getContentPane().add(this.getGLCanvas());

		
		frame.setSize(600, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}


	/**
	 * Creates and executes a model using the IMP API
	 */
	public void runModel(){
		stopGraphics();

		//clear the reference to the current command holder
		ch = null;

		//add commands
		try {

			Model model = new Model();
			ch = new CommandHolder(model);

			//define the mechanism
			ch.addCommand(RevoluteCommand.CreateZPin("J1", "FRAME", "A", new Point(0,0,0), new Point(2,0,0), new Point(2,0,0)));
			ch.addCommand(RevoluteCommand.CreateZPin("J2", "A", "B", new Point(0,1,0), new Point(2,0,0), new Point(0,-2,0)));
			ch.addCommand(RevoluteCommand.CreateZPin("J3", "B", "C", new Point(1,1,0), new Point(-2,0,0), new Point(0,1,0)));
			ch.addCommand(RevoluteCommand.CreateZPin("J4", "C", "FRAME", new Point(1,0,0), new Point(0,1,0), new Point(2,0,0)));

			//sets the ground
			ch.addCommand(new GroundCommand("FRAME"));

			//sets J1 and J2 to rotate 0.02 and -0.02 per tick respectively
			FakeExpression[] expression1 = new FakeExpression[2];
			expression1[0] = new Function("", "TICKS");
			expression1[1] = new FakeExpressionLiteral(0.02);
			ch.addCommand(new JointExpressionCommand("J1", JVAR.THETA, new Function("", "*", expression1)));

			FakeExpression[] expression2 = new FakeExpression[2];
			expression2[0] = new Function("", "TICKS");
			expression2[1] = new FakeExpressionLiteral(-0.02);
			ch.addCommand(new JointExpressionCommand("J2", JVAR.THETA, new Function("", "*", expression2)));
			//end add commands


			ch.compile(); //compile the model
			ch.verifyOrFail(); //check for errors
			ch.runIndefinitely(10); //begin model execution

		} catch (SelfLoopException e){
			e.printStackTrace();
		} catch (FunctionAlreadyExists e) {
			e.printStackTrace();
		} catch (LoopException e) {
			e.printStackTrace();
		} catch (BodyNotFoundException e) {
			e.printStackTrace();
		} catch (IMPException e) {
			e.printStackTrace();
		}
		//Sets command holder to use when drawing to the canvas
		ModelDataSource ds = new ModelDataSource(ch, this.getCamera());
		setGraphicsDataSource(ds);

		//restarts graphics rendering
		startGraphics();

	}


	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub

	}


	/**
	 * Starts the model execution when Spacebar is pressed
	 */
	@Override
	public void keyPressed(KeyEvent e) {
		if (e.getKeyChar() == ' '){
			runModel();
		}

	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub

	}

}
