/**
 * CommandHolder.java
 * May 15, 2011
 */
package imp.core.commands.encapsulation;

import imp.core.commands.Command;
import imp.core.exceptions.BodyNotFoundException;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.IMPIllegalStateException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.LoopException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.WrappedException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.exceptions.expressions.MethodReturnValue;
import imp.core.expressions.FunctionLibrary;
import imp.core.expressions.attributes.Function;
import imp.core.model.Model;
import imp.core.model.loop.Loop;
import imp.core.observer.AbstractMultiSubject;
import imp.core.observer.NotificationType;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Class for holding the commands to be executed on the model
 * 
 * @author hellmerj
 * @version 1.0
 * @edit kuszewskij Added functionality to pause and resume the model.
 */
public class CommandHolder extends AbstractMultiSubject implements FunctionLibrary {

	private final Queue<Command> commands; // list of commands to be executed on the model
	private final Queue<Command> executedCommands; // list of commands that have already been executed on the model
	private Model model;
	private Thread modelRunningThread;// This is the thread that will run the model.

	private int ticks = 0;

	private runningState currentState = runningState.BEFORE_START;// the current state of the CommandHolder.

	private boolean terminate = false;// this is used to terminate the thread safely instead of using the depreciated
										// stop method.

	/** The property manager. */
	private PropertyManager propertyManager;

	/**
	 * Gets the property manager.
	 * 
	 * @return the propertyManager
	 */
	public PropertyManager getPropertyManager() {

		if (propertyManager == null) {
			propertyManager = new PropertyManager(model.properties);
		}

		return propertyManager;
	}

	//@formatter:off
	/**
	 * 
	 * Definitions for the state of the command holder with respect to it running.
	 * DONE = The CommandHolder has finished Running.
	 * PAUSED = The CommandHolder is in a paused state. The model is not being updated and the tick count is not being incremented.
	 * RUNNING = The CommandHolder is updating the model and updating the tick count.
	 * BEFORE_START = The CommandHolder has not been given the call run yet and is in its initial state.
	 * 
	 * Valid transitions: 
	 * BEFORE_START -> RUNNING
	 * RUNNING -> PAUSED
	 * RUNNING -> DONE
	 * PAUSED -> RUNNING
	 *  
	 * @author kuszewskij
	 * 
	 */
	//@formatter:on 
	public static enum runningState {
		DONE, PAUSED, RUNNING, BEFORE_START
	}

	/**
	 * This is the CommandHolder constructor. It creates a new CommandHolder object and initializes the class
	 * attributes.
	 * 
	 * @param model The model the commands will be executed on
	 * @throws FunctionAlreadyExists Thrown when an equivalent function already exists in this holder.
	 */
	public CommandHolder(Model model) throws FunctionAlreadyExists {
		// check if model passed is null
		NullParameterException.check(model, "model", 0);

		this.commands = new LinkedList<Command>();
		this.executedCommands = new LinkedList<Command>();
		this.model = model;

		model.functionManager.addCoreFunctions();
		model.functionManager.addFunctions(this);
	}

	/*
	 * (non-Javadoc)
	 * @see imp.expressions.FunctionLibrary#initialize(imp.model.Model)
	 */
	@Override
	public void initialize(Model model) {
		// TODO Auto-generated method stub

	}

	/**
	 * This is the addCommand method. It is responsible for adding a command to the end of the list of commands being
	 * held for execution on the model.
	 * 
	 * @param cmd The command being added to the holder
	 */
	public void addCommand(Command cmd) {

		// perform null check
		NullParameterException.check(cmd, "command", 0);

		this.commands.offer(cmd);
	}

	/**
	 * This is the clearModel method. It is responsible for resetting the model to its initial state.
	 */
	public void clearModel() {
		this.model = new Model(this.model.getPrintStream());
	}

	/**
	 * This is the executeCommands method. It is responsible for invoking the execution of the commands in the holder
	 * list.
	 * 
	 * @throws IMPException Thrown if a command being executor encounters an error.
	 * 
	 */
	public void executeCommands() throws IMPException {
		Command cmd;

		while (this.commands.size() > 0) {
			cmd = this.commands.poll();
			cmd.execute(this.model);
			this.executedCommands.offer(cmd);
		}
	}

	/**
	 * This is the getCommands method. It is a getter method for the commands list, responsible for returning a copy of
	 * the holder's command list.
	 * 
	 * @return The queue of commands in the holder
	 */
	public Queue<Command> getCommands() {
		return this.commands;
	}

	/**
	 * This is the getExecutedCommands method. It is a getter method for the executed commands list, responsible for
	 * returning a copy of the holder's executed command list.
	 * 
	 * @return The queue of executed commands in the holder
	 */
	public Queue<Command> getExecutedCommands() {
		return this.executedCommands;
	}

	/**
	 * This is the remove method. It is responsible for removing a command from the holder command list.
	 * 
	 * @param cmd The command being removed from the holder
	 * @throws InvalidParameterException
	 */
	public void removeCommand(Command cmd) throws InvalidParameterException {

		// perform null check
		NullParameterException.check(cmd, "command", 0);

		if (!(commands.contains(cmd))) {
			throw new InvalidParameterException("The command to be removed is not contained in the holder", 0);
		}

		this.commands.remove(cmd);
	}

	/**
	 * This is the verify method. It is responsible for calling the model's loop finding algorithm.
	 * 
	 * @return true if loops are valid, false otherwise
	 * @throws LoopException Thrown if loop finding encounters errors.
	 * @throws BodyNotFoundException Thrown if a body was not found in the loop.
	 */
	public boolean verify() throws BodyNotFoundException {
		try {
			this.model.findKinematicLoops();
			return true;
		} catch (LoopException e) {
			return false;
		}
	}

	/**
	 * Attempt to verify the model and if it cannot, throw an exception
	 * 
	 * @throws LoopException Thrown if loop finding encounters errors.
	 * @throws BodyNotFoundException Thrown if a body was not found in the loop.
	 */
	public void verifyOrFail() throws LoopException, BodyNotFoundException {
		if (!verify()) {
			throw new LoopException("Could not successfully verify");
		}
	}

	/**
	 * Compile (verify & executeCommands) the model
	 * 
	 * @throws IMPException if any of the commands throw an exception
	 */
	public void compile() throws IMPException {
		this.notifyObservers(NotificationType.modelBeforeCompile);
		executeCommands();
		verify();
		this.notifyObservers(NotificationType.modelAfterCompile);
	}

	/**
	 * Run the model with a time increment as the time step.
	 * 
	 * @param timeStep the time increment.
	 * @throws LoopException Thrown if loop finding encounters an error.
	 */
	public void runIndefinitely(int timeStep) {

		final int timeBetweenSteps = timeStep;

		modelRunningThread = new Thread(new Runnable() {
			@Override
			public void run() {
				notifyObservers(NotificationType.modelBeginRun);
				currentState = runningState.RUNNING;
				while (terminate == false) {
					try {
						model.tick();
						++ticks;

						notifyObservers(NotificationType.modelTick);

						Thread.sleep(timeBetweenSteps);
						while (currentState == runningState.PAUSED && terminate == false) {
							synchronized (modelRunningThread) {
								modelRunningThread.wait();// block this thread until the resume method is called.
							}
						}
					} catch (InterruptedException e) {
						// this is expected to be thrown when the thread is resumed.

					} catch (WrappedException e1) {
						e1.printStackTrace();
					} catch (MethodReturnValue e1) {
						e1.printStackTrace();
					} catch (LoopException e1) {
						e1.printStackTrace();
					}
				}
			}

		});
		if (currentState == runningState.BEFORE_START) {// It only makes sense to run the commandHolder once.
			modelRunningThread.start();// start the running.
		} else {
			String message = "The CommandHolder's method runIndefinitely was called but it is still running.";
			if (currentState == runningState.DONE) {// change the error message if it is si done running.
				message = "The CommandHolder's method runIndefinitely was called, but it has already been run and has finished.";
			}
			throw new IMPIllegalStateException(message);
		}
	}

	/**
	 * Run the model with a time increment as the time step.
	 * 
	 * @param timeStep the time increment.
	 * @param maxSteps the number of time steps to run.
	 */
	public void run(int timeStep, int maxSteps) {

		final int timeBetweenSteps = timeStep;
		final int maxNumberOfSteps = maxSteps;

		modelRunningThread = new Thread(new Runnable() {

			@Override
			public void run() {
				notifyObservers(NotificationType.modelBeginRun);
				currentState = runningState.RUNNING;
				for (ticks = 0; ticks < maxNumberOfSteps; ticks++) {
					try {
						model.tick();
						ticks++;
						notifyObservers(NotificationType.modelTick);
						Thread.sleep(timeBetweenSteps);
						while (currentState == runningState.PAUSED && terminate == false) {
							synchronized (modelRunningThread) {
								modelRunningThread.wait();// block this thread until the resume method is called.
							}
						}

						if (terminate) {
							break;// stop the thread. the loop will exit now.
						}
					} catch (InterruptedException e) {
						// This exception is expected to be thrown when the model is resumed.
					} catch (WrappedException e1) {
						e1.printStackTrace();
					} catch (MethodReturnValue e1) {
						e1.printStackTrace();
					} catch (LoopException e1) {
						e1.printStackTrace();
					}
				}
				currentState = runningState.DONE;
				notifyObservers(NotificationType.modelEndRun);
			}

		});

		if (currentState == runningState.BEFORE_START) {// It only makes sense to run the commandHolder once.
			modelRunningThread.start();// start the running.
			currentState = runningState.BEFORE_START;
		} else {
			String message = "The CommandHolder's method run was called but it is still running.";
			if (currentState == runningState.DONE) {// change the error message if it is si done running.
				message = "The CommandHolder's method run was called, but it has already been run and has finished.";
			}
			throw new IMPIllegalStateException(message);
		}
	}

	/**
	 * Calling this method will terminate the thread that is used to run the model.
	 */
	public void terminateThread() {
		if (modelRunningThread != null) {
			terminate = true;
		}
	}

	/**
	 * Returns the current state of the command holder with respect to it running.
	 * 
	 * @return the current state.
	 */
	public runningState getCurrentRunningState() {
		return currentState;
	}

	/**
	 * Pause the model if it is running. Otherwise calling this method will have no effect.
	 */
	/**
	 * Pause the model if it is running. Otherwise calling this method will have no effect.
	 */
	public void pause() {
		if (currentState == runningState.RUNNING) {// can't pause a model unless it is running.
			this.currentState = runningState.PAUSED;
		}
	}

	/**
	 * Resume the model if it was paused. Otherwise this method will have no effect.
	 */
	public void resume() {
		if (currentState == runningState.PAUSED) {// can't resume a model that is not paused
			this.currentState = runningState.RUNNING;
			synchronized (modelRunningThread) {
				modelRunningThread.notify();
			}
		}
	}

	/**
	 * Gets the ticks.
	 * 
	 * @return the ticks
	 */
	@Function("ticks")
	public double getTicks() {
		return ticks;
	}

	/**
	 * Gets the loops.
	 * 
	 * @return the loops
	 */
	public List<LoopHolder> getLoops() {

		List<LoopHolder> loops = new LinkedList<LoopHolder>();

		for (Loop l : this.model.getLoops()) {
			loops.add(new LoopHolder(l));
		}

		return loops;
	}

	/**
	 * Adds the commands.
	 * 
	 * @param cmds the cmds to add
	 */
	public void addCommands(List<Command> cmds) {

		// perform null check
		NullParameterException.check(cmds, "commands", 0);

		for (Command c : cmds) {
			addCommand(c);
		}

	}

	/**
	 * Get the model.
	 * 
	 * @return the model
	 */
	public Model getModel() {
		return this.model;
	}

}
