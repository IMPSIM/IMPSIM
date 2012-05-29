package imp.core.commands.encapsulation;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import imp.core.commands.Command;
import imp.core.commands.GroundCommand;
import imp.core.commands.definition.CylinderCommand;
import imp.core.commands.definition.ScrewCommand;
import imp.core.exceptions.IMPException;
import imp.core.exceptions.IMPIllegalStateException;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.JointNotFoundException;
import imp.core.exceptions.LoopException;
import imp.core.exceptions.NameConflictException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.model.Model;
import imp.core.model.joints.Cylinder;
import imp.core.parser.ParserData;
import imp.core.parser.SimpleParser;

import java.util.ArrayList;
import java.util.List;

import junit.framework.Assert;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * @author dykstran
 * @version 2.0
 * @edit 3/31/2012 kuszewski - added test cases for the new pause and resume functions in the command holder.
 */
@SuppressWarnings("javadoc")
public class TestCommandHolder {

	/**
	 * The type of exception expected during testing.
	 */
	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#CommandHolder(imp.core.model.Model)}.
	 * 
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testCommandHolder() throws FunctionAlreadyExists {

		Model testModel = new Model();

		// sunny-day constructor
		new CommandHolder(testModel);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#CommandHolder(imp.core.model.Model)}.
	 * 
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testCommandHolderNullParam() throws FunctionAlreadyExists {

		// null parameter passed to constructor
		thrown.expect(NullParameterException.class);
		new CommandHolder(null);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#addCommand(imp.core.commands.Command)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testAddCommand() throws NullParameterException, SelfLoopException, FunctionAlreadyExists {

		// create command and holder
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		CommandHolder ch = new CommandHolder(new Model());

		// add command to holder
		ch.addCommand(cc);

		// check that command is contained in holder
		assertTrue(ch.getCommands().contains(cc));
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#addCommand(imp.core.commands.Command)}.
	 * 
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testAddCommandNullParam() throws FunctionAlreadyExists {

		CommandHolder test = new CommandHolder(new Model());

		// add null command should fail
		thrown.expect(NullParameterException.class);
		test.addCommand(null);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#addCommands(java.util.List)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testAddCommands() throws NullParameterException, SelfLoopException, FunctionAlreadyExists {

		// list for commands
		List<Command> cmdList = new ArrayList<Command>();

		// commands
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		ScrewCommand sc = new ScrewCommand("ScrewBody1", "ScrewBody2", "ScrewJoint");

		// add commands to list
		cmdList.add(cc);
		cmdList.add(sc);

		// holder
		CommandHolder test = new CommandHolder(new Model());

		// add list of commands to holder
		test.addCommands(cmdList);

		// check that all commands in list were added to holder
		assertTrue(test.getCommands().containsAll(cmdList));
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#addCommands(java.util.List)}.
	 * 
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testAddCommandsNullParam() throws FunctionAlreadyExists {

		// test holder
		CommandHolder test = new CommandHolder(new Model());

		// try adding null list of commands
		thrown.expect(NullParameterException.class);
		test.addCommands(null);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#clearModel()}.
	 * 
	 * @throws InvalidParameterException
	 * @throws JointNotFoundException
	 * @throws NameConflictException
	 * @throws FunctionAlreadyExists
	 */
	@Test
	public void testClearModel() throws NullParameterException, SelfLoopException, NameConflictException, JointNotFoundException, InvalidParameterException,
			FunctionAlreadyExists {

		Model testModel = new Model();

		// add bodies and joints to model
		testModel.addBody("body1");
		testModel.addJoint(new Cylinder("TestJoint"), "bodyNameAfter", "bodyNameBefore");

		// create commandHolder with populated model
		CommandHolder ch = new CommandHolder(testModel);

		// clear the model
		ch.clearModel();

		// check that no bodies or joints remain
		assertEquals(ch.getModel().countBodies(), 0);
		assertEquals(ch.getModel().countJoints(), 0);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#executeCommands()}.
	 * 
	 * @throws NullParameterException
	 * @throws IMPException
	 */
	@Test
	public void testExecuteCommands() throws NullParameterException, IMPException {

		// create command and holder
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		CommandHolder ch = new CommandHolder(new Model());

		// add command to holder
		ch.addCommand(cc);

		ch.executeCommands();

		// check that command is moved to executed list
		assertFalse(ch.getCommands().contains(cc));
		assertTrue(ch.getExecutedCommands().contains(cc));

		// check that bodies and joints are created
		assertTrue(ch.getModel().countBodies() > 0);
		assertTrue(ch.getModel().countJoints() > 0);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#removeCommand(imp.core.commands.Command)}.
	 * 
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 * @throws FunctionAlreadyExists
	 * @throws InvalidParameterException
	 */
	@Test
	public void testRemoveCommand() throws NullParameterException, SelfLoopException, FunctionAlreadyExists, InvalidParameterException {

		// create command and holder
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		CommandHolder ch = new CommandHolder(new Model());

		// add command to holder
		ch.addCommand(cc);

		// check that command is contained in holder
		assertTrue(ch.getCommands().contains(cc));

		// remove command from holder
		ch.removeCommand(cc);

		// check that command is removed from holder
		assertFalse(ch.getCommands().contains(cc));
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#removeCommand(Command)}.
	 * 
	 * @throws FunctionAlreadyExists
	 * @throws InvalidParameterException
	 */
	@Test
	public void testRemoveCommandNullParam() throws FunctionAlreadyExists, InvalidParameterException {

		// create holder
		CommandHolder ch = new CommandHolder(new Model());

		// attempt to remove null command
		thrown.expect(NullParameterException.class);
		ch.removeCommand(null);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#removeCommand(Command)}.
	 * 
	 * @throws FunctionAlreadyExists
	 * @throws SelfLoopException
	 * @throws NullParameterException
	 * @throws InvalidParameterException
	 */
	@Test
	public void testRemoveCommandNonExistentCommand() throws FunctionAlreadyExists, NullParameterException, SelfLoopException, InvalidParameterException {

		// create command and holder
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		CommandHolder ch = new CommandHolder(new Model());

		// attempt to remove command that was not first added
		thrown.expect(InvalidParameterException.class);
		ch.removeCommand(cc);
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#verify()}.
	 * 
	 * @throws NullParameterException
	 * @throws IMPException
	 */
	@Test(timeout = 100)
	public void testVerify() throws NullParameterException, IMPException {

		// create holder
		CommandHolder ch = new CommandHolder(new Model());
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		GroundCommand gc = new GroundCommand("body1");

		ch.addCommand(cc);
		ch.addCommand(gc);

		ch.executeCommands();

		// thrown.expect(LoopException.class);
		assertFalse(ch.verify());
	}

	/**
	 * Test method for {@link imp.core.commands.encapsulation.CommandHolder#verifyOrFail()};
	 * 
	 * @throws NullParameterException
	 * @throws IMPException
	 */
	@Test(timeout = 100)
	public void testVerifyOrFail() throws NullParameterException, IMPException {

		// create holder
		CommandHolder ch = new CommandHolder(new Model());
		CylinderCommand cc = new CylinderCommand("body1", "body2", "joint");
		GroundCommand gc = new GroundCommand("body1");

		ch.addCommand(cc);
		ch.addCommand(gc);

		ch.executeCommands();

		// no loops should be found
		thrown.expect(LoopException.class);
		ch.verifyOrFail();
	}

	/**
	 * Test calling the pause method when the commandHolder is running.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testPauseValidModelRunning() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(10, 10000);// start it
		Thread.sleep(100);// give it a few moments to finish compiling.
		ch.pause();// pause it

		Thread.sleep(1000);// The thread may not pause this instant so give it a few chances to pause

		double ticks = ch.getTicks();
		Thread.sleep(100);// sleep for a few time steps to give the command holder a few chances to tick if it actually
							// isnt paused.

		assertEquals(ticks, ch.getTicks(), .1);// the commandHolder should not have ticked after 50 ms.
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.PAUSED);// should be paused

		ch.terminateThread();
	}

	/**
	 * Test calling the pause method when the commandHolder is already paused.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testPauseAlreadyPaused() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(10, 10000);// start it
		Thread.sleep(100);// give it a few moments to finish compiling.
		ch.pause();// pause it
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.PAUSED);// should be paused
		ch.pause();// pause it again.
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.PAUSED);// should be paused still after
																						// calling pause again.

		ch.terminateThread();
	}

	/**
	 * Test calling the pause method when the commandHolder is finished running.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testPauseFinishedRunning() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(1, 1);// start it
		Thread.sleep(100);// give it a few moments to finish compiling and finish running.
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.DONE);// should be done running.
		ch.pause();// try to pause it
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.DONE);// should still be done running.

		ch.terminateThread();
	}

	/**
	 * Test calling the resume method when the commandHolder is running.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testResumeValidModelRunning() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(10, 1000);// start it
		Thread.sleep(100);// give it a few moments to finish compiling.
		ch.resume();// try to resume it
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.RUNNING);// should still be running.

		ch.terminateThread();
	}

	/**
	 * Test calling the resume method when the commandHolder is paused.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testResumePaused() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(10, 1000);// start it
		Thread.sleep(100);// give it a few moments to finish compiling and finish running.
		ch.pause();// try to pause it
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.PAUSED);// should be paused

		ch.resume();// start it up again
		Thread.sleep(50);// let it advance a few ticks

		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.RUNNING);

		ch.terminateThread();
	}

	/**
	 * Test calling the resume method when the commandHolder is done running.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testResumeDoneRunning() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(1, 1);// start it
		Thread.sleep(100);// give it a few moments to finish compiling and finish running.
		ch.resume();// try to resume it
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.DONE);

		ch.terminateThread();
	}

	/**
	 * Test calling the run method when the commandHolder is running.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testRunningAlreadyRunning() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(10, 1000);// start it
		Thread.sleep(100);// give it a few moments to finish compiling and finish running.

		thrown.expect(IMPIllegalStateException.class);// the model is still running so an exception should be thrown
		ch.run(10, 100);

		ch.terminateThread();
	}

	/**
	 * Test calling the run method when the commandHolder is paused.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testRunningPaused() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(10, 100);// start it
		Thread.sleep(100);// give it a few moments to finish compiling and finish running.
		ch.pause();// pause it for the test
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.PAUSED);// should be paused

		thrown.expect(IMPIllegalStateException.class);// the model is still paused but not yet finished so an exception
														// should be thrown
		ch.run(10, 100);

		ch.terminateThread();
	}

	/**
	 * Test calling the runIndefinitely method.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testRunningIndefinitely() throws IMPException, InterruptedException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.runIndefinitely(10);// Have it run forever, well atleast until the end of the test.

		double ticks = ch.getTicks();

		Thread.sleep(200);// run a bit to make sure it hasn't stopped running.
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.RUNNING);

		assertTrue(ticks < ch.getTicks());

		ch.terminateThread();
	}

	/**
	 * Test calling the runIndefinitely method when the commandHolder is already running.
	 * 
	 * @throws IMPException
	 * @throws InterruptedException
	 */
	@Test
	public void testRunningAlreadyDoneRunning() throws InterruptedException, IMPException {
		CommandHolder ch = setUpCommandHolder();// get a command holder ready to be run
		ch.run(1, 0);// start it
		Thread.sleep(100);// give it a few moments to finish compiling and finish running.
		assertEquals(ch.getCurrentRunningState(), CommandHolder.runningState.DONE);// should be done
		thrown.expect(IMPIllegalStateException.class);// the model is finished so an exception should be thrown becasue
														// it has already been run.
		ch.run(10, 100);

		ch.terminateThread();
	}

	/**
	 * Helper method for some test cases that need a model ready to be run.
	 * 
	 * @return
	 * @throws IMPException
	 */
	private CommandHolder setUpCommandHolder() throws IMPException {

		Model model = new Model();
		// @formatter:off
		String impCommands =
				"ZPIN J1 FRAME A 0,0,0 2,0,0 2,0,1;\r\n" + 
				"ZPIN J2 A B 0,1,0 1,1,0 1,1,1;\r\n" + 
				"ZPIN J3 B C 1,1,0 2,1,0 2,1,1;\r\n" + 
				"ZPIN J4 C FRAME 1,0,0 2,0,0 2,0,1;\r\n" + 
				"GROUND = FRAME;\r\n" + 
				"J1.Theta = ticks() * 0.0174532925;\r\n" + 
				"J2.Theta = ticks() * -0.0174532925;\r\n" + 
				"\r\n" + 
				"";
		// @formatter:on
		ParserData parserData = SimpleParser.parse(impCommands);

		if (parserData.hasErrors()) {

		}
		Assert.assertFalse(parserData.hasErrors());

		CommandHolder ch = null;
		ch = new CommandHolder(model);
		ch.addCommands(parserData.commands);
		ch.executeCommands();
		ch.compile();
		ch.verifyOrFail();

		return ch;
	}

}
