package impplugin;

import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.CharacterCodingException;

import javax.media.opengl.GLCapabilities;

import imp.core.commands.encapsulation.CommandHolder;
import imp.core.exceptions.ShaderException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.graphics.AbstractGraphics;
import imp.core.graphics.AbstractModelView;
import imp.core.graphics.ModelDataSource;
import imp.core.graphics.Vec3;
import imp.core.model.Model;
import imp.core.parser.ErrorLog.ErrorContainer;
import imp.core.parser.ParserData;
import imp.core.parser.SimpleParser;

/*
 * USAGE NOTES:
 * 
 * How to embed the GLCanvas within a frame/panel:
 * 1. Create the container
 * 2. Call getGLCanvas() to access the underlying GLCanvas
 * 3. Add the canvas to the content pane as though it were a component
 * 
 * 
 * How to have a model displayed within the PluginModelView's GLCanvas:
 * 1. Create a new command holder
 * 2. Add all commands to the command holder
 * 3. Create a new ModelDataSource with the command holder
 * 4. Set the graphicsDataSource to the ModelDataSource
 * 5. Provide camera vectors to a position that will allow the model to be visible
 * 6. Call startGraphics()
 * 7. Call startModel() from the ModelDataSource
 * 
 * The pauseModel(), resumeModel(), and stopModel() commands from the ModelDataSource can be used to
 * pause, resume, and stop the model respectively. If a model is stopped, the commands must be re-added to
 * the command holder
 */

/**
 * This class is an extension of AbstractModelView to allow the plugin to have access to abstracted GL commands. It also
 * provides a way to access the GL canvas which can be embedded within a Swing component.
 * 
 * @author kreierj
 * 
 *         Several sections of code based on implemented by Jake Kuszewski
 * 
 */
public class PluginModelView extends AbstractModelView {

	private CommandHolder ch;
	
	/**
	 * Constructor which instantiates a PluginModelView
	 * 
	 * @param fps The wanted fps to animate at
	 * @param capabilities The GL Capabilities the canvas will run with
	 */
	public PluginModelView(int fps, GLCapabilities capabilities) {
		super(fps, capabilities);
	}

	/**
	 * Constructor which will create a model view using default GL Capabilities at 60 fps
	 */
	public PluginModelView() {
		super();
	}

	/**
	 * Throws all concealed exceptions originated within openGL method calls
	 * 
	 * @throws ShaderException Indicates there was a problem with shader initialization
	 * @throws CharacterCodingException Indicates there was a problem with character encoding
	 */
	public void throwGLExceptions() throws ShaderException, CharacterCodingException {
		if (AbstractGraphics.hasExceptions()) {
			AbstractGraphics.throwExceptions();
		}
	}

	/**
	 * Helper method which sets up the camera so that it will look at the correct location
	 */
	public void setCamera(Vec3 position, Vec3 direction, Vec3 up) {
		getCamera().setPosition(position);
		getCamera().setDirection(direction);
		getCamera().setUpVector(up);
	}

	// Mouse Wheel Listener
	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		// unused
	}

	/**
	 * Last y value recorded
	 */
	private int lastY = 0;

	/**
	 * Last x value recorded
	 */
	private int lastX = 0;

	/**
	 * Determines rotation angle
	 */
	private static float DEGREES_TO_ROTATE = 0.03f;

	/**
	 * Determines movement speed
	 */
	private static float MOVE_DISTANCE = 0.3f;

	/**
	 * Amount the mouse must move before it detects rotation
	 */
	private static int TOLERANCE = 0;

	// Mouse Listener
	@Override
	public void mouseDragged(MouseEvent e) {

		// Handle Y difference
		int newY = e.getY();
		int difference = newY - lastY;
		if (difference > TOLERANCE) {
			rotateDown(DEGREES_TO_ROTATE);
		} else if (difference < TOLERANCE) {
			rotateUp(DEGREES_TO_ROTATE);
		}
		lastY = newY;

		// Handle X Difference
		int newX = e.getX();
		difference = newX - lastX;
		if (difference > TOLERANCE) {
			rotateRight(DEGREES_TO_ROTATE);
		} else if (difference < TOLERANCE) {
			rotateLeft(DEGREES_TO_ROTATE);
		}

	}

	@Override
	public void mouseMoved(MouseEvent e) {
		// unused
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// unused
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// unused
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// unused
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// unused
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// unused
	}

	// KeyListener
	@Override
	public void keyTyped(KeyEvent e) {
		// unused
	}

	@Override
	public void keyPressed(final KeyEvent e) {
		int code = e.getKeyCode();
		switch (code) {
		case KeyEvent.VK_A:
			moveSmoothLeft(MOVE_DISTANCE); // Standard WASD Movement
			break;
		case KeyEvent.VK_D:
			moveSmoothRight(MOVE_DISTANCE);
			break;
		case KeyEvent.VK_S:
			moveSmoothBackward(MOVE_DISTANCE);
			break;
		case KeyEvent.VK_W:
			moveSmoothForward(MOVE_DISTANCE);
			break;
		case KeyEvent.VK_R:
			moveSmoothUp(MOVE_DISTANCE); // R to move up
			break;
		case KeyEvent.VK_F:
			moveSmoothDown(MOVE_DISTANCE); // F to move down
			break;
		case KeyEvent.VK_Z:
			rollCounterClockwise(0.1f); // Z to rotate left
			break;
		case KeyEvent.VK_X:
			rollClockwise(0.1f); // X to rotate right
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
		// unused
	}
	
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
		//runImpFile(index + ".imp");
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
			//D:/MyDocs/Desktop/MSOE/IMP SDL/physicsengine/trunk/src/main/java/imp/core/graphics/" + 
			impCommands = org.apache.commons.io.FileUtils.readFileToString(new File(name));
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
		}
		
		// let's make the model
		ch.addCommands(parserData.commands);

		ModelDataSource source = new ModelDataSource(ch, this.getCamera());
		source.startModel(10);
		setGraphicsDataSource(source);

		// and then show the model
		startGraphics();

	}

}
