package imp.core.graphics;


import java.awt.event.KeyListener;

import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import java.awt.event.MouseWheelListener;

import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLProfile;
import javax.media.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.FPSAnimator;

/**
 * Abstract class which defines how a GLCanvas can be used to view a set of GLObjects
 * @author kreierj
 * @edit moved the math for controlling the camera to the camera.
 * @version 1
 */
public abstract class AbstractModelView extends AbstractGraphics implements MouseWheelListener, MouseMotionListener, MouseListener, KeyListener{



	/**
	 * Canvas which will be displayed to the screen
	 */
	private GLCanvas canvas;

	/**
	 * Animator for the GLCanvas
	 */
	private FPSAnimator animator;

	/**
	 * Convenience constructors
	 */
	public AbstractModelView(){
		this(60, new GLCapabilities(GLProfile.getDefault()));
	}

	/**
	 * Constructor
	 * @param fps Target frames per second for the canvas
	 * @param caps Capabilities of the canvas
	 */
	public AbstractModelView(int fps, GLCapabilities caps){
		super();

		//create the canvas
		canvas = new GLCanvas(caps);

		//add all the listeners to the canvas
		canvas.addMouseWheelListener(this);
		canvas.addMouseMotionListener(this);
		canvas.addMouseListener(this);
		canvas.addKeyListener(this);

		canvas.addGLEventListener(this); //implemented in extended class

		animator = new FPSAnimator(canvas, fps);
	}

	/**
	 * Returns the GLCanvas
	 * @return
	 */
	public GLCanvas getGLCanvas(){
		return canvas;
	}

	/**
	 * Returns the GL Object at screen position x,y
	 * @param x coordinate
	 * @param y coordinate
	 * @return Closest object at position (x,y)
	 */
	//TODO: I will deal with this method once I complete my other tasks, probably will not be completed within the scope of refactoring --Justin
	public AbstractGLObject getGLObject(float x, float y){
		//get list of objects being drawn
		//draw orthogonal ray into viewport at x,y
		//return closest colliding object
		return null;
	}

	/**
	 * Moves the camera backward along the view vector
	 * @param
	 */
	public void moveBackward(float dist){
		Vec3 pos = this.getCamera().getPosition();//get the cameras current position
		Vec3 direction = this.getCamera().getDirection();//see what direction its facing
		direction = direction.normalize().multiply(-dist);//create a vector that is in the direction the camera is facing, but with negative magnitude equal to the specified value.
		pos = pos.plus(direction);//add the movement vector to the current position.
		this.getCamera().setPosition(pos);
	}
	
	/**
	 * Moves the camera smoothly in the up direction by the given speed.
	 * @param speed the speed to move the camera by.
	 */
	public void moveSmoothBackward(float speed){
		this.getCamera().moveBackwards(speed);
	}
	
	/**
	 * causes the camera to stop moving up.
	 */
	public void stopSmoothBackwardMovement(){
		this.getCamera().stopBackwards();
	}
	

	/**
	 * Moves the camera forward along the view vector
	 * @param dist
	 */
	public void moveForward(float dist){
		Vec3 pos = this.getCamera().getPosition();//get the cameras current position
		Vec3 direction = this.getCamera().getDirection();//see what direction its facing
		direction = direction.normalize().multiply(dist);//create a vector that is in the direction the camera is facing with a magnitude equal to the specified value.
		pos = pos.plus(direction);//add the movement vector to the current position.
		this.getCamera().setPosition(pos);
	}
	
	/**
	 * Moves the camera smoothly in the up direction by the given speed.
	 * @param speed the speed to move the camera by.
	 */
	public void moveSmoothForward(float speed){
		this.getCamera().moveForward(speed);
	}
	
	/**
	 * causes the camera to stop moving up.
	 */
	public void stopSmoothForwardMovement(){
		this.getCamera().stopForward();
	}
	

	/**
	 * Moves the camera left along the left vector
	 * @param dist
	 */
	public void moveLeft(float dist){
		Vec3 pos = this.getCamera().getPosition();//get the cameras current position
		Vec3 direction = this.getCamera().getDirection();//see what direction its facing
		Vec3 leftDir = direction.cross(this.getCamera().getUpVector());//get the x axis relative to the camera
		leftDir = leftDir.normalize().multiply(-dist);//create a vector that is in the direction the camera is facing with a magnitude equal to the specified value.
		pos = pos.plus(leftDir);//add the movement vector to the current position.
		this.getCamera().setPosition(pos);
	}
	
	/**
	 * Moves the camera smoothly in the up direction by the given speed.
	 * @param speed the speed to move the camera by.
	 */
	public void moveSmoothLeft(float speed){
		this.getCamera().moveLeft(speed);
	}
	
	/**
	 * causes the camera to stop moving up.
	 */
	public void stopSmoothLeftMovement(){
		this.getCamera().stopLeft();
	}
	

	/**
	 * Moves the camera right along the left vector
	 * @param dist
	 */
	public void moveRight(float dist){
		Vec3 pos = getCamera().getPosition();//get the cameras current position
		Vec3 direction = getCamera().getDirection();//see what direction its facing
		Vec3 rightDir = direction.cross(getCamera().getUpVector());//get the x axis direction relative to the camera
		rightDir = rightDir.normalize().multiply(dist);//create a vector that is in the direction the camera is facing with a magnitude equal to the specified value.
		pos = pos.plus(rightDir);//add the movement vector to the current position.
		this.getCamera().setPosition(pos);
	}
	
	/**
	 * Moves the camera smoothly in the Right direction by the given speed.
	 * @param speed the speed to move the camera by.
	 */
	public void moveSmoothRight(float speed){
		this.getCamera().moveRight(speed);
	}
	
	/**
	 * causes the camera to stop moving Right.
	 */
	public void stopSmoothRightMovement(){
		this.getCamera().stopRight();
	}

	/**
	 * Moves the camera up along the up vector
	 * @param dist
	 */
	public void moveUp(float dist){
		Vec3 pos = this.getCamera().getPosition();//get the cameras current position
		pos = pos.plus(this.getCamera().getUpVector().normalize().multiply(dist));//add the movement vector to the current position.
		this.getCamera().setPosition(pos);
	}
	
	/**
	 * Moves the camera smoothly in the up direction by the given speed.
	 * @param speed the speed to move the camera by.
	 */
	public void moveSmoothUp(float speed){
		this.getCamera().moveUp(speed);
	}
	
	/**
	 * causes the camera to stop moving up.
	 */
	public void stopSmoothUpMovement(){
		this.getCamera().stopUp();
	}
	
	/**
	 * Moves the camera down along the up vector
	 * @param dist
	 */
	public void moveDown(float dist){
		Vec3 pos = this.getCamera().getPosition();//get the cameras current position
		pos = pos.plus(this.getCamera().getUpVector().normalize().multiply(-dist));//add the movement vector to the current position.
		this.getCamera().setPosition(pos);
	}
	
	/**
	 * Moves the camera smoothly in the down direction by the given speed.
	 * @param speed the speed to move the camera by.
	 */
	public void moveSmoothDown(float speed){
		this.getCamera().moveDown(speed);
	}
	
	/**
	 * causes the camera to stop moving down.
	 */
	public void stopSmoothDownMovement(){
		this.getCamera().stopDown();
	}

	/**
	 * This method will cause the camera to roll clockwise relative to where it is facing.
	 * @param degs
	 */
	public void rollClockwise(float degs){
		this.getCamera().rotateAboutArbitraryAxis(this.getCamera().getDirection(), degs*-1f);
	}
	
	/**
	 * This method will cause the camera to roll counter-clockwise relative to where its facing.
	 * @param degs
	 */
	public void rollCounterClockwise(float degs){
		this.getCamera().rotateAboutArbitraryAxis(this.getCamera().getDirection(),degs);
	}

	/**
	 * This will rotate the camera down.
	 * @param degrees the degrees to rotate by.
	 */
	public void rotateDown(float degrees){
		Vec3 axis = this.getCamera().getDirection().cross(this.getCamera().getUpVector());
		this.getCamera().rotateAboutArbitraryAxis(axis,degrees);
	}

	/**
	 * This will rotate the camera up.
	 * @param degrees the degrees to rotate by.
	 */
	public void rotateUp(float degrees){
		Vec3 axis = this.getCamera().getDirection().cross(this.getCamera().getUpVector());
		this.getCamera().rotateAboutArbitraryAxis(axis,-1*degrees);
	}
	
	/**
	 * This will rotate the camera left.
	 * @param degrees the degrees to rotate by.
	 */
	public void rotateLeft(float degrees){
		Vec3 axis = this.getCamera().getUpVector();
		this.getCamera().rotateAboutArbitraryAxis(axis,-1f*degrees);
	}
	
	/**
	 * This will rotate the camera right.
	 * @param degrees the degrees to rotate by.
	 */
	public void rotateRight(float degrees){
		Vec3 axis = this.getCamera().getUpVector();
		this.getCamera().rotateAboutArbitraryAxis(axis,degrees);
	}

	/**
	 * Starts the graphics rendering
	 * @return
	 */
	public void startGraphics(){
		animator.start();
	}

	/**
	 * Stops the graphics from being rendered
	 * @return 
	 */
	public void stopGraphics(){
		animator.stop();
	}
}
