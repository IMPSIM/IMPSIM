package imp.core.graphics;

import imp.core.commands.encapsulation.CommandHolder;
import imp.core.commands.encapsulation.JointHolder;
import imp.core.commands.encapsulation.LoopHolder;
import imp.core.commands.encapsulation.PropertyManager;
import imp.core.exceptions.BodyNotFoundException;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.LoopException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.parser.OBJFileFormatException;
import imp.core.observer.NotificationType;
import imp.core.parser.OBJToImpParser;
import imp.core.structures.Point;
import imp.core.structures.PositionMatrix;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import javax.media.opengl.GL3;

/**
 * This class handles the different model objects to display from the command holder
 * 
 * @author kreierj
 * @version 1, 3/20/2012
 * @edit kuszewski added catch block in handleLoopInitialization() for nullParamterException and
 *       OBJFileFormatExceptions.
 */
public class ModelDataSource extends AbstractDataSource {

	/**
	 * Synchronization tool
	 */
	public Object lock = new String("lock");

	/**
	 * Loop data
	 */
	public List<LoopHolder> data = null;

	/**
	 * CommandHolder object
	 */
	public CommandHolder commandHolder;

	/**
	 * Indicates if the loop has changed since the last update
	 */
	protected boolean hasChanged;

	/**
	 * Reference to the camera object
	 */
	private final Camera camera;

	/**
	 * Instantiates a new ModelDataSource using the specified CommandHolder
	 * 
	 * @param ch the command holder
	 * @param Camera the camera it will be drawing on
	 */
	public ModelDataSource(CommandHolder ch, Camera camera) {
		commandHolder = ch;
		ch.addObserver(this);
		hasChanged = true;
		this.camera = camera;
	}

	protected void refreshJoints(GL3 gl) {

		// if the command holder has changed
		if (hasChanged) {
			// get the loops from the command holder
			data = commandHolder.getLoops();

			// if there are no objects yet
			if (this.getObjects().size() == 0) { // initialize everything
				initializeObjects(gl);
			} else { // updating everything
				updateObjects(gl);
			}
		}

	}

	/**
	 * Initializes all the objects and puts them on the GPU
	 * 
	 * @param gl
	 */
	private void initializeObjects(GL3 gl) {
		// for each loop
		for (int i = 0; i < data.size(); i++) {

			handleLoopInitialization(i, gl);
		}
		initializeCamera();
	}

	/**
	 * Updates the objects it is maintaining
	 * 
	 * @param gl
	 */
	private void updateObjects(GL3 gl) {
		// for each loop
		for (int i = 0; i < data.size(); i++) {

			// get the joint list
			List<JointHolder> joints = data.get(i).getJoints();

			// for each joint
			for (int j = 0; j < joints.size(); j++) {
				JointHolder joint = joints.get(j);
				// get the joint's name
				String name = joint.getName();

				// get the joint's rotation (after matrix)
				PositionMatrix matrix = joint.getAfterPositionMatrix();
				double[] temp = matrix.getJamaMatrix().getColumnPackedCopy();
				List<Float> rotationData = new ArrayList<Float>();
				for (int k = 0; k < temp.length; k++) {
					rotationData.add((float) temp[k]);
				}

				// get the object
				AbstractGLObject object = this.getObject(name + i);
				if (object != null) {
					// update the object
					object.updateData(gl, rotationData, AbstractGLObject.DATA_TYPE.ORIENTATION_DATA);

					// if it is a loop object (i.e. no model)
					if (object instanceof LoopObject) {
						List<Float> vertices = new ArrayList<Float>();

						// first point
						vertices.add((float) joint.getPosition().getX());
						vertices.add((float) joint.getPosition().getY());
						vertices.add((float) joint.getPosition().getZ());
						vertices.add(1.0f);

						joint = joints.get(j + 1);

						// second point
						vertices.add((float) joint.getPosition().getX());
						vertices.add((float) joint.getPosition().getY());
						vertices.add((float) joint.getPosition().getZ());
						vertices.add(1.0f);

						// update the object
						object.updateData(gl, vertices, AbstractGLObject.DATA_TYPE.VERTEX_DATA);
					}

					// remove the old object from the list
					this.removeObject(object.getName());

					// put the new object back in the list
					this.putObject(object);
				}

				// update any object axis
				object = this.getObject(name + i + "_axis");
				if (object != null) {
					String tempString = commandHolder.getPropertyManager().getStringProperty(name, "SHOW_AXIS");
					if (tempString.equalsIgnoreCase("after")) {
						object.updateData(gl, rotationData, AbstractGLObject.DATA_TYPE.ORIENTATION_DATA);
						this.removeObject(object.getName());
						this.putObject(object);
					} else {
						matrix = joint.getBeforePositionMatrix();
						temp = matrix.getJamaMatrix().getColumnPackedCopy();
						rotationData = new ArrayList<Float>();
						for (int k = 0; k < temp.length; k++) {
							rotationData.add((float) temp[k]);
						}
						object.updateData(gl, rotationData, AbstractGLObject.DATA_TYPE.ORIENTATION_DATA);
						this.removeObject(object.getName());
						this.putObject(object);
					}
				}
			}

		}
	}

	/**
	 * Handles initialization of each loop
	 * 
	 * @param loopNumber The loop number being handled
	 * @param gl The gl3
	 */
	private void handleLoopInitialization(int loopNumber, GL3 gl) {
		System.out.println("Loop " + loopNumber);
		// get the joint list
		List<JointHolder> joints = data.get(loopNumber).getJoints();

		// for each joint
		for (int i = 0; i < joints.size(); i++) {
			JointHolder joint = joints.get(i);

			// get the joint's name
			String name = joint.getName();

			// boolean skipped = false;
			// if there is a model
			if (commandHolder.getPropertyManager().hasProperty(name, "OBJ_FILE")) {

				String graphicsModel = commandHolder.getPropertyManager().getStringProperty(name, "OBJ_FILE");
				if (graphicsModel == null) {
					initializeLoopObject(joints, joint, i, loopNumber, name, gl);
				} else if (graphicsModel.equals("DEFAULT")) { // handle default case
					// use a loop object
					initializeLoopObject(joints, joint, i, loopNumber, name, gl);
				} else if (graphicsModel.equals("NONE")) {
					// OPTIMIZE: should create a blank abstract GL object so empty models aren't being maintained by the
					// GPU
					// handle the case for wanting no object file drawn
					Float[] parsedVertices = new Float[] {};
					Integer[] parsedFaces = new Integer[] {};
					initializeModelObject(joint, i, loopNumber, name, parsedVertices, parsedFaces, gl);
				} else {

					// load and parse the model
					Float[] parsedVertices = null;
					Integer[] parsedFaces = null;

					try {
						OBJToImpParser modelLoader = new OBJToImpParser(graphicsModel);
						parsedVertices = modelLoader.getVertices();
						parsedFaces = modelLoader.getFaces();

						initializeModelObject(joint, i, loopNumber, name, parsedVertices, parsedFaces, gl);

					} catch (NullParameterException e) {
						// TODO: do more than just skip the joint?

						initializeLoopObject(joints, joint, i, loopNumber, name, gl);
						System.out.println("The argument passed was not a OBJ file: " + graphicsModel);

					} catch (FileNotFoundException e) {
						// TODO: do more than just skip the joint?

						initializeLoopObject(joints, joint, i, loopNumber, name, gl);
						System.out.println("File not found: " + graphicsModel);
					} catch (OBJFileFormatException e) {
						// TODO: do more than just skip the joint?

						initializeLoopObject(joints, joint, i, loopNumber, name, gl);
						System.out.println("Invalid formatting for file: " + graphicsModel);
					}

				}
			} else {
				initializeLoopObject(joints, joint, i, loopNumber, name, gl);
			}

			// initialize axes

			String showAxis = commandHolder.getPropertyManager().getStringProperty(name, "SHOW_AXIS");
			if (showAxis != null) {
				if (showAxis.equalsIgnoreCase("before")) {
					initializeAxisObject(joint, i, loopNumber, name, true, gl);
				} else if (showAxis.equalsIgnoreCase("after")) {
					initializeAxisObject(joint, i, loopNumber, name, false, gl);
				}
			}

		}
	}

	/**
	 * Initializes a single loop object
	 * 
	 * @param joints The joints in the loop
	 * @param joint The target joint
	 * @param index The current index of the joint
	 * @param loopNumber The loop number you're on
	 * @param name The joint's name
	 * @param gl The GL3
	 */
	public void initializeLoopObject(List<JointHolder> joints, JointHolder joint, int index, int loopNumber, String name, GL3 gl) {
		// check if there is a next joint
		if (index + 1 < joints.size()) {
			// create new LoopObject
			List<Float> vertices = new ArrayList<Float>();

			// first point
			vertices.add((float) joint.getPosition().getX());
			vertices.add((float) joint.getPosition().getY());
			vertices.add((float) joint.getPosition().getZ());
			vertices.add(1.0f);

			joint = joints.get(index + 1);

			// second point
			vertices.add((float) joint.getPosition().getX());
			vertices.add((float) joint.getPosition().getY());
			vertices.add((float) joint.getPosition().getZ());
			vertices.add(1.0f);

			List<Float> colorData = new ArrayList<Float>();

			// first point
			colorData.add((float) Math.random());
			colorData.add((float) Math.random());
			colorData.add((float) Math.random());
			colorData.add(1.0f);

			// second point
			colorData.add((float) Math.random());
			colorData.add((float) Math.random());
			colorData.add((float) Math.random());
			colorData.add(1.0f);

			System.out.println("Creating model " + name);
			AbstractGLObject model = new LoopObject(name + loopNumber, vertices, colorData);

			// initialize the object
			model.initialize(gl);

			// put the object in the mapping
			this.putObject(model);
		}
	}

	/**
	 * Initializes a model object
	 * 
	 * @param joint The target joint
	 * @param index The joint's index
	 * @param loopNumber The loop number you're on
	 * @param name The joint's name
	 * @param parsedVertices The vertices to use
	 * @param parsedFaces The faces to use
	 * @param gl The GL3
	 */
	private void initializeModelObject(JointHolder joint, int index, int loopNumber, String name, Float[] parsedVertices, Integer[] parsedFaces, GL3 gl) {
		// get the joint's rotation (after matrix)
		PositionMatrix matrix = joint.getAfterPositionMatrix();
		double[] temp = matrix.getJamaMatrix().getColumnPackedCopy();
		float[] tempFloats = new float[temp.length];
		for (int k = 0; k < temp.length; k++) {
			tempFloats[k] = (float) temp[k];
		}
		Mat4 rotation = new Mat4(tempFloats);

		// create new GLModelObject
		System.out.println("Creating model " + name);
		AbstractGLObject model = new GLModel(name + loopNumber, parsedVertices, parsedFaces, rotation);
		// initialize the object
		model.initialize(gl);
		// put the object in the mapping
		this.putObject(model);
	}

	/**
	 * Initializes all axis objects
	 * 
	 * @param joint The joint the axis is for
	 * @param index What index we're on
	 * @param loopNumber What loop number we're on
	 * @param name The joint's name
	 * @param before True if the user requested a before axis
	 * @param gl
	 */
	private void initializeAxisObject(JointHolder joint, int index, int loopNumber, String name, boolean before, GL3 gl) {
		PositionMatrix matrix = null;
		if (before) {
			matrix = joint.getBeforePositionMatrix();
		} else {
			matrix = joint.getAfterPositionMatrix();
		}
		double[] temp = matrix.getJamaMatrix().getColumnPackedCopy();
		float[] tempFloats = new float[temp.length];
		for (int k = 0; k < temp.length; k++) {
			tempFloats[k] = (float) temp[k];
		}
		Mat4 rotation = new Mat4(tempFloats);

		// create new AxisObject
		AbstractGLObject axisObject = new AxisObject(name + loopNumber + "_axis", rotation);

		System.out.println("Creating model: " + name + loopNumber + "_axis");
		axisObject.initialize(gl);
		this.putObject(axisObject);
	}

	/**
	 * Initializes camera positions
	 */
	private void initializeCamera() {
		// default positions
		PropertyManager properties = commandHolder.getPropertyManager();

		Point upVector = properties.getPointProperty("CAMERA", "UP", new Point(0, 1, 0));
		Point directionVector = properties.getPointProperty("CAMERA", "DIRECTION", new Point(0, 0, -1));
		Point locationVector = properties.getPointProperty("CAMERA", "LOCATION", new Point(0, 0, 10));

		camera.setUpVector(upVector.toVector3());
		camera.setDirection(directionVector.toVector3());
		camera.setPosition(locationVector.toVector3());
	}

	@Override
	public void execute() {
		// unused

	}

	@Override
	public void update(NotificationType updateType) {
		switch (updateType) {
		// if the model has updated, refresh the joints
		case modelTick:
			synchronized (lock) {
				hasChanged = true;
			}
			break;
		}

	}

	@Override
	public void update(GL3 gl) {
		refreshJoints(gl);

	}

	/**
	 * Compiles, verifies, and starts a model running
	 * 
	 * @param timeStep The time step per tick
	 */
	public void startModel(int timeStep) {

		try {
			commandHolder.compile();
			commandHolder.verifyOrFail();
			commandHolder.runIndefinitely(timeStep);
		} catch (LoopException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (BodyNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IMPException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	/**
	 * Pauses a running model.
	 */
	public void pauseModel() {
		commandHolder.pause();
	}

	/**
	 * Resumes a paused model.
	 */
	public void resumeModel() {
		commandHolder.resume();
	}

	/**
	 * Stops a running model. You will not be able to resume the model if it is stopped this way.
	 */
	public void stopModel() {
		commandHolder.terminateThread();
	}

}
