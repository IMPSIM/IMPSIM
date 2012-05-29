/**
 * Model.java
 * January 22, 2011
 */

package imp.core.model;

import imp.core.exceptions.BodyNotFoundException;
import imp.core.exceptions.InvalidDatatypeException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.LoopException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.exceptions.WrappedException;
import imp.core.exceptions.expressions.MethodReturnValue;
import imp.core.expressions.Expression;
import imp.core.expressions.FunctionManager;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.model.loop.Loop;
import imp.core.model.loop.LoopCloser;
import imp.core.model.loop.LoopFinder;
import imp.core.model.loop.LoopVariable;
import imp.core.observer.AbstractSubject;
import imp.core.observer.NotificationType;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Represents an IMP model.
 * 
 * @version 1.23
 */
public class Model extends AbstractSubject {

	/**
	 * these are package visible so that LoopFinder can find it
	 */

	/**
	 * The collection of bodies contained in this model.
	 */
	private ElementMap<Body> bodies;

	/**
	 * The collection of joints contained in this model.
	 */
	private ElementMap<Joint> joints;

	/**
	 * The collection of loops found in this model.
	 */
	private List<Loop> loops;

	/**
	 * The default print stream for messages.
	 */
	private PrintStream ps = System.out;

	/**
	 * The body which represents the ground.
	 */
	private Body ground;

	/**
	 * hold all the properties of the model
	 */
	final public ModelPropertyManager properties = new ModelPropertyManager();

	/**
	 * hold all the functions in the model
	 */
	final public FunctionManager functionManager = new FunctionManager();

	/**
	 * hold all the variables/expressions in the model
	 */
	final public VariableManager variableManager = new VariableManager();

	/**
	 * Hold all the variables/expressions in the model
	 */
	final public JointExpressionManager jointExpressionManager = new JointExpressionManager();

	/**
	 * The list of expressions for this model.
	 */
	final public List<Expression> expressions = new ArrayList<Expression>();

	/**
	 * Represents an IMP model.
	 */
	public Model() {
		Set<String> names = new HashSet<String>();
		this.bodies = new ElementMap<Body>(names);
		this.joints = new ElementMap<Joint>(names);
	}

	/**
	 * Creates a model with a print stream besides the default.
	 * 
	 * @param psr The printStream to be utilized.
	 */
	public Model(PrintStream psr) {
		this();
		if (psr == null) {
			// DO NOTHING
			// model printstream defaults to System.out
		} else {
			this.ps = psr;
		}
	}

	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------
	// Methods adding elements to the model
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	/**
	 * Locate the Body with the given name within the model and return it. -- OR -- If no Body is found with the given
	 * name, create it and add it to the model.
	 * 
	 * 
	 * @param bodyName Name of the Body.
	 * 
	 * @return The Body object with the specified name.
	 * @throws NameConflictException Thrown if this method attempts to add a body that already exists.
	 * @throws NullParameterException If the body name is null.
	 * @throws InvalidParameterException thrown if the body name is empty.
	 */
	// OPTIMIZE this code may need to be revised
	public Body addBody(String bodyName) throws NameConflictException, NullParameterException, InvalidParameterException {

		if (bodyName == null) { // null parameter check
			throw new NullParameterException("Body name cannot be null", 0);
		}

		Body returnVal = this.getBody(bodyName);
		if (returnVal == null) {
			returnVal = new Body(bodyName);
			this.bodies.put(returnVal);
		}
		return returnVal;
	}

	/**
	 * Add a joint of a specific type and perhaps bodies to the model.
	 * 
	 * @param theJoint The joint to add.
	 * @param bodyNameAfter Name of the body following the joint.
	 * @param bodyNameBefore Name of the body preceding the joint.
	 * @throws SelfLoopException Thrown if the joint attempts to connect a body to itself.
	 * @throws NameConflictException Thrown if a joint of this name already exists.
	 * @throws NullParameterException thrown if any parameters are null.
	 * @throws JointNotFoundException Thrown if a joint is removed but cannot be found.
	 * @throws InvalidParameterException thrown if the body names are empty.
	 */
	public void addJoint(Joint theJoint, String bodyNameAfter, String bodyNameBefore) throws SelfLoopException, NameConflictException, NullParameterException,
			JointNotFoundException, InvalidParameterException {

		NullParameterException.check(theJoint, "theJoint", 0);
		NullParameterException.check(bodyNameAfter, "bodyNameAfter", 1);
		NullParameterException.check(bodyNameBefore, "bodyNameBefore", 2);

		// Check for a self loop.
		if (bodyNameAfter.compareToIgnoreCase(bodyNameBefore) == 0) {
			throw new SelfLoopException("A joint cannot connect a body to itself.");
		}

		// Delete any previous joint with the same name.
		if (this.joints.contains(theJoint.getName())) {
			this.removeJoint(theJoint.getName());
			this.ps.printf("*** The former joint '%s' is replaced. ***", theJoint.getName());
		}

		// check if both bodies are already contained in the model
		if (this.bodies.contains(bodyNameBefore) && this.bodies.contains(bodyNameAfter)) {
			// temp variable for name of body before and after each joint
			String nameBef = "";
			String nameAft = "";
			for (Joint jnt : this.joints) { // iterate through model joints
				// get name of body before and after joint
				nameBef = jnt.getBodyBefore().getName();
				nameAft = jnt.getBodyAfter().getName();
				// check if bodies of joint match bodies of new joint (in any order), creating rigid joint
				if ((nameBef.equals(bodyNameBefore) && nameAft.equals(bodyNameAfter)) || (nameBef.equals(bodyNameAfter) && nameAft.equals(bodyNameBefore))) {
					throw new SelfLoopException("Two different joints cannot connect the same two bodies");
				}
			}
		}

		// Locate or form the body records.
		Body theBodyAfter = this.addBody(bodyNameAfter);
		Body theBodyBefore = this.addBody(bodyNameBefore);

		// Connect the joint to the bodies on either side via Axis objects
		Axis theAxisAfter = new Axis(theJoint, theBodyAfter);
		Axis theAxisBefore = new Axis(theJoint, theBodyBefore);
		theJoint.setAxisAfter(theAxisAfter);
		theJoint.setAxisBefore(theAxisBefore);
		theBodyAfter.addAxis(theAxisAfter);
		theBodyBefore.addAxis(theAxisBefore);

		// Add the new joint to the model
		this.joints.put(theJoint);
	}

	/**
	 * Closes the loops in this model for the given joint.
	 * 
	 * @param vars the loop variables used for loop closure.
	 * 
	 * @throws LoopException thrown if an error is encountered during loop closure.
	 */
	public void closeLoops(List<LoopVariable> vars) throws LoopException {

		LoopCloser lc = new LoopCloser();

		loops = lc.closeLoop(vars, loops);

		this.notifyObservers(NotificationType.position);
	}

	/**
	 * Determines if a certain element of a specific type exists in the model.
	 * 
	 * @param name The name of the element being searched for.
	 * @param classType The class type of the element being searched for.
	 * @return returns True if it exists, false otherwise.
	 * @throws InvalidDatatypeException Thrown if the object is of the wrong class.
	 */
	public boolean contains(String name, Object classType) throws InvalidDatatypeException {
		boolean retVal = false;
		boolean body = false;
		boolean joint = false;

		body = this.bodies.contains(name);
		joint = this.joints.contains(name);

		// determines if the returned value is the correct type of element
		if (body) {
			if (classType.equals(this.getBody(name).getClass())) {
				retVal = true;
			} else {
				throw new InvalidDatatypeException("you were looking for a joint, but a body was found");
			}
		} else if (joint) {
			if (classType.equals(this.getJoint(name).getClass())) {
				retVal = true;
			} else {
				throw new InvalidDatatypeException("you were looking for a body, but a joint was found");
			}
		}
		return retVal;
	}

	/**
	 * Get the number of bodies in this model.
	 * 
	 * @return The number of bodies in this model.
	 */
	public int countBodies() {
		return this.bodies.size();
	}

	/**
	 * Get the number of joints in this model.
	 * 
	 * @return The number of joints in this model.
	 */
	public int countJoints() {
		return this.joints.size();
	}

	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------
	// Methods getting elements from the model
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	/**
	 * This method finds all kinematic loops for the current model.
	 * 
	 * @return A list of loop objects.
	 * @throws LoopException thrown if an error is encountered during loop finding.
	 * @throws BodyNotFoundException Thrown when a body is not found.
	 */
	public List<Loop> findKinematicLoops() throws LoopException, BodyNotFoundException {
		LoopFinder lf = new LoopFinder(this);
		this.loops = lf.findKinematicLoops();
		return this.loops;
	}

	/**
	 * Gets the body with the specified name.
	 * 
	 * @param bodyName The name of the body to get.
	 * @return The body with the specified name.
	 */
	public Body getBody(String bodyName) {
		return this.bodies.get(bodyName);
	}

	/**
	 * Gets a map of the bodies in this model.
	 * 
	 * @return A map containing all bodies in the model.
	 */
	public ElementMap<Body> getBodyStructure() {
		return new ElementMap<Body>(this.bodies);
	}

	/**
	 * Gets the ground for this model.
	 * 
	 * @return The ground.
	 * @throws BodyNotFoundException Thrown if the ground hasn't been set.
	 */
	public Body getGround() throws BodyNotFoundException {
		if (this.ground == null) {
			throw new BodyNotFoundException("The ground has not yet been set");
		}
		return this.ground;
	}

	/**
	 * Gets the joint with the specified name.
	 * 
	 * @param jointName The name of the joint to get.
	 * @return The joint with the specified name.
	 */
	public Joint getJoint(String jointName) {
		return this.joints.get(jointName);
	}

	/**
	 * Gets a map containing all joints in the model.
	 * 
	 * @return A map containing all joints in the model.
	 */
	public ElementMap<Joint> getJointStructure() {
		ElementMap<Joint> jnts = new ElementMap<Joint>(this.joints);
		return jnts;
	}

	/**
	 * Method for returning the print stream used for displaying messages.
	 * 
	 * @return The print stream utilized by the model.
	 */
	public PrintStream getPrintStream() {
		return this.ps;
	}

	/**
	 * Removes the joint from the model.
	 * 
	 * @param jointName The joint to remove.
	 * @throws JointNotFoundException Thrown if a joint by the specified name cannot be found.
	 */
	public void removeJoint(String jointName) throws JointNotFoundException {
		Joint theJoint = this.joints.remove(jointName);
		if (theJoint != null) {
			// removes the joint's axes from the bodies it links.
			theJoint.getAxisAfter().getBody().removeAxis(theJoint.getAxisAfter());
			theJoint.getAxisBefore().getBody().removeAxis(theJoint.getAxisBefore());
		} else {
			throw new JointNotFoundException("Joint could not be removed as it was not found");
		}
	}

	/**
	 * Method for setting the ground body.
	 * 
	 * @param groundName The name of the body to become the ground body.
	 * @throws BodyNotFoundException thrown if the body does not exist in this model.
	 * @throws InvalidDatatypeException Thrown if the groundName is the name of a joint instead of the name of a body.
	 * @throws NameConflictException Thrown if the body doesn't exist, but something exists with the same name.
	 * @throws NullParameterException Thrown if the name is null.
	 * @throws InvalidParameterException thrown if the ground name is empty.
	 */
	public void setGround(String groundName) throws BodyNotFoundException, InvalidDatatypeException, NameConflictException, NullParameterException,
			InvalidParameterException {
		// checks that the passed in name exists in the model, if not makes one and puts it in the model
		if (!this.contains(groundName, Body.class)) {
			this.addBody(groundName);
		}
		// sets the ground field to the body with the same name
		this.ground = this.getBody(groundName);
	}

	/**
	 * Gets the loops.
	 * 
	 * @return the loops
	 */
	public List<Loop> getLoops() {
		return this.loops;
	}

	/**
	 * Evaluate expressions.
	 * 
	 * @throws WrappedException the wrapped exception
	 * @throws MethodReturnValue the method return value
	 */
	public void evaluateExpressions() throws WrappedException, MethodReturnValue {
		for (Expression exp : expressions) {
			exp.cacheValue();
		}
	}

	/**
	 * Move forward a single tick
	 * 
	 * @throws MethodReturnValue a function expression's method returned the wrong value type.
	 * @throws WrappedException an unknown exception occurred.
	 * @throws LoopException an exception has occurred during loop finding.
	 */
	public void tick() throws WrappedException, MethodReturnValue, LoopException {
		evaluateExpressions();
		List<LoopVariable> loopVars = jointExpressionManager.toLoopVars();
		closeLoops(loopVars);
	}
}
