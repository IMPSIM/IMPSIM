package imp.core.graphics;

import imp.core.commands.encapsulation.CommandHolder;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.ShaderException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.model.Model;
import imp.core.parser.ErrorLog.ErrorContainer;
import imp.core.parser.ParserData;
import imp.core.parser.SimpleParser;

import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.io.File;
import java.io.IOException;
import java.nio.charset.CharacterCodingException;

import javax.swing.JFrame;

/**
 * Rough implementation of AbstractModelView to be used as an example for future implementations
 * 
 * See RunImp1() for comments on usage
 * 
 * @author kreierj
 * 
 */
public class ModelView extends AbstractModelView {

	/**
	 * TODO: Comment all these methods -Austin This is a prototype class, if you really want them commented I can but
	 * for now its just for demonstration Also I'm lazy - Justin
	 */
	private CommandHolder ch;

	public static void main(String[] args) {
		ModelView model = new ModelView();
		model.init();
		model.startGraphics(); // begin graphics rendering
	}

	public ModelView() {
		super();

	}

	public void init() {
		JFrame frame = new JFrame();
		frame.getContentPane().add(this.getGLCanvas()); // add the GL Canvas maintained by the AbstractModelView to the
														// frame

		// TODO: PLUGIN TEAM, THE FOLLOWING SET OF CODE IS IMPORTANT TO THE CORRECT FUNCTIONING OF THE ABSTRACT GRAPHICS
		// CLASS
		// IT MUST BE PERIODICALLY CHECKED IN ORDER TO PROPERLY RECIEVE EXCEPTIONS FROM THE GRAPHICS CODE
		if (AbstractGraphics.hasExceptions()) {

			try {
				AbstractGraphics.throwExceptions();
			} catch (ShaderException e) {
				e.printStackTrace();
			} catch (CharacterCodingException e) {
				e.printStackTrace();
			}

		}

		frame.setSize(600, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

	/**
	 * Used by the KeyListener.
	 */
	private int lastY = 0;

	private int lastX;

	/**
	 * Determines how many degrees to rotate per distance dragged.
	 */
	private final double degreesPerPixle = .03;

	/**
	 * Determines how far to move the camera.
	 */
	private final float moveDistance = .3f;

	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		// TODO Auto-generated method stub

	}

	private final int tollerance = 0;

	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
		int newY = e.getY();
		int difference = newY - lastY;
		if (difference > tollerance) {
			this.rotateDown((float) (degreesPerPixle));
			// System.out.println("Rotating down");
		}
		if (difference < tollerance) {
			this.rotateUp((float) (degreesPerPixle));
			// System.out.println("Rotating up");
		}
		lastY = newY;

		int newX = e.getX();
		int xDiff = newX - lastX;
		lastX = newX;
		if (xDiff > tollerance) {

			this.rotateRight((float) (degreesPerPixle));
			// System.out.println("Rotating right");

		}
		if (xDiff < tollerance) {

			this.rotateLeft((float) (degreesPerPixle));
			// System.out.println("Rotating Left");
		}
	}

	// {{ Mouse Stuff

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

	// }}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub

		if (e.getKeyCode() == 32) {
		}
	}

	@Override
	public void keyPressed(final KeyEvent e) {
		// TODO Auto-generated method stub
		switch (e.getKeyCode()) {
		case 65:// a
			this.moveSmoothLeft(moveDistance);
			break;
		case 68:// d
			this.moveSmoothRight(moveDistance);
			break;
		case 83:// s
			this.moveSmoothBackward(moveDistance);
			break;
		case 87:// w
			this.moveSmoothForward(moveDistance);
			break;
		case 82:// r
			this.moveSmoothUp(moveDistance);
			break;
		case 70:// f
			this.moveSmoothDown(moveDistance);
			break;
		case 88:
			this.rollCounterClockwise(.1f);
			break;
		case 90:
			this.rollClockwise(.1f);
			break;
		case 80:// p pause
			System.out.println("Pause was pressed");
			ch.pause();

			break;
		case 79:// o
			ch.resume();
			break;
		case KeyEvent.VK_1:
		case KeyEvent.VK_2:
		case KeyEvent.VK_3:
		case KeyEvent.VK_4:
		case KeyEvent.VK_5:
		case KeyEvent.VK_6:
			new Thread(new Runnable() {

				@Override
				public void run() {
					// get offset on which key (1-6 was pressed)
					int num = e.getKeyCode() - KeyEvent.VK_1 + 1;
					runImp(num);
				}

			}).start();
		}

	}

	@Override
	public void keyReleased(KeyEvent e) {
		switch (e.getKeyCode()) {
		case 65:// a
			this.stopSmoothLeftMovement();
			break;
		case 68:// d
			this.stopSmoothRightMovement();
			break;
		case 83:// s
			this.stopSmoothBackwardMovement();
			break;
		case 87:// w
			this.stopSmoothForwardMovement();
			break;
		case 82:// r
			this.stopSmoothUpMovement();
			break;
		case 70:// f
			this.stopSmoothDownMovement();
			break;
		}
	}

	/**
	 * Run a specific model of imp
	 * 
	 * @param index the index of the model to run, 1 based
	 */
	public void runImp(int index) {
		// // TODO fix model 3 (can comment out the following to see what it should look like
		// if (index == 3) {
		// try {
		// runImp3();
		// } catch (IMPException e) {
		// // TODO Auto-generated catch block
		// e.printStackTrace();
		// }
		// } else {
		runImpFile(index + ".imp");
		// }
	}

	/**
	 * Run an imp model(s) from a file
	 * 
	 * @param name the name file located at src/main/java/imp/core/graphics/
	 */
	public void runImpFile(String name) {
		Model model = new Model();
		stopGraphics(); // pause the graphics during the update (unnecessary but prevents tearing)

		ch = null;
		try {
			ch = new CommandHolder(model);
		} catch (FunctionAlreadyExists e) {
			e.printStackTrace();
		}

		// load the commands
		String impCommands = null;
		try {
			impCommands = org.apache.commons.io.FileUtils.readFileToString(new File("src/main/java/imp/core/graphics/" + name));
		} catch (IOException e1) {
			impCommands = "";
		}

		ParserData parserData = SimpleParser.parse(impCommands);

		// check for errors, fail if we have any
		if (parserData.hasErrors()) {
			System.out.println("Errors!");

			for (ErrorContainer ec : parserData.errorLog) {
				System.out.println(ec);
			}

			System.exit(1);
		}

		// let's make the model
		ch.addCommands(parserData.commands);

		ModelDataSource source = new ModelDataSource(ch, this.getCamera());
		source.startModel(10);
		setGraphicsDataSource(source);

		// and then show the model
		startGraphics();

	}

	public void runImp3() throws IMPException {
		// TODO Re-Translate Model # 3

		// Model model = new Model();
		// stopGraphics();
		//
		// CommandHolder ch = null;
		//
		// try {
		// ch = new CommandHolder(model);
		//
		// } catch (FunctionAlreadyExists e) {
		// e.printStackTrace();
		// }
		//
		// model.addJoint(new Revolute("A0"), "Ground", "2");
		// model.addJoint(new Revolute("A"), "2", "3");
		// model.addJoint(new Revolute("C"), "2", "5");
		// model.addJoint(new Revolute("B0"), "Ground", "4");
		// model.addJoint(new Revolute("B"), "4", "3");
		// model.addJoint(new Revolute("E"), "4", "6");
		// model.addJoint(new Revolute("D"), "6", "5");
		// DataZPinCommand a0 = new DataZPinCommand(new Point(4.1, 2.7, 0), new Point(5.0, 2.7, 0), new Point(8.1, 13.2,
		// 0), "A0");
		// a0.execute(model);
		// DataZPinCommand a = new DataZPinCommand(new Point(8.1, 13.2, 0), new Point(4.1, 2.7, 0), new Point(38.1,
		// 28.3, 0), "A");
		// a.execute(model);
		// DataZPinCommand c = new DataZPinCommand(new Point(5.5, 19.2, 0), new Point(8.1, 13.2, 0), new Point(27.8,
		// 41.4, 0), "C");
		// c.execute(model);
		// DataZPinCommand b0 = new DataZPinCommand(new Point(37.4, 8.5, 0), new Point(47.4, 8.5, 0), new Point(38.1,
		// 28.3, 0), "B0");
		// b0.execute(model);
		// DataZPinCommand b = new DataZPinCommand(new Point(38.1, 28.3, 0), new Point(37.4, 8.5, 0), new Point(8.1,
		// 13.2, 0), "B");
		// b.execute(model);
		// DataZPinCommand e = new DataZPinCommand(new Point(51.3, 32.9, 0), new Point(38.1, 28.3, 0), new Point(27.8,
		// 41.4, 0), "E");
		// e.execute(model);
		// DataZPinCommand d = new DataZPinCommand(new Point(27.8, 41.4, 0), new Point(51.3, 32.9, 0), new Point(5.5,
		// 19.2, 0), "D");
		// d.execute(model);
		// JointExpressionCommand jc = new JointExpressionCommand("A0", JVAR.THETA, new
		// imp.core.commands.expressions.Function("", "*",
		// new imp.core.commands.expressions.Function("", "ticks"), new FakeExpressionLiteral(-0.0174532925)));
		// jc.execute(model);
		// model.setGround("Ground");
		//
		// ch.executeCommands();
		//
		// ch.compile();
		// ch.verifyOrFail();
		//
		// this.getCamera().setPosition(new Vec3(20, 0, 100));
		// this.getCamera().setDirection(new Vec3(0, 0, -1));
		// this.getCamera().setUpVector(new Vec3(0, 1, 0));
		//
		// AbstractDataSource source = new ModelDataSource(ch, this.getCamera());
		// setGraphicsDataSource(source);
		// startGraphics();
		//
		// ch.run(10, 2000);
	}

}
