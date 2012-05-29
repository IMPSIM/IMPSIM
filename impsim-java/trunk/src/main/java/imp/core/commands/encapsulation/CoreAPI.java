/**
 * ModelInterface.java
 * April 27, 2012
 */
package imp.core.commands.encapsulation;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import imp.core.commands.DynamicJointBuilder;
import imp.core.commands.JointArgumentInfo;
import imp.core.commands.JointBuilder;
import imp.core.exceptions.NonExistentJointEntry;
import imp.core.exceptions.expressions.FunctionAlreadyExists;
import imp.core.model.Model;
import imp.core.model.elements.Body;
import imp.core.model.elements.Joint;
import imp.core.parser.ParserData;
import imp.core.parser.SimpleParser;
import imp.core.parser.ErrorLog.ErrorContainer;

/**
 * Class to Interface the core with the Plugin
 * @author ebertb
 * @version 1.0
 */
public class CoreAPI {
	
	
	protected CommandHolder ch;
	protected Model model;
	
	/**
	 * Constructor for the interface
	 */
	public CoreAPI(){
		model = new Model();
	}
	
	/**
	 * This method returns the command holder that the interface uses
	 * @return CommandHolder so the plugin can talk to the graphics
	 */
	public CommandHolder getCommandHolder(){
		return ch;
	}
	
	/**
	 * Runs the filename passed through the parser.
	 * @param name
	 */
	public void runImpFile(String filePath){
		model = new Model();
		
		ch = null;
		try {
			ch = new CommandHolder(model);
		}catch (FunctionAlreadyExists e){
			e.printStackTrace();
		}
		
		// load the commands
				String impCommands = null;
				try {
					impCommands = org.apache.commons.io.FileUtils.readFileToString(new File(filePath));
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
	}
	
	
	/**
	 * Gets a list of Bodies back from the model
	 * @return a list of Body names
	 */
	public List<String> getBodies(){
		List<String> retval = new ArrayList<String>();
		for(Body bd: model.getBodyStructure()){
			retval.add(bd.getName());
		}
		return retval;
	}
	
	
	/**
	 * Gets the two bodies that go with the joint
	 * @param JointName joint that you want the body names from
	 * @return a list of Body names
	 */
	public List<String> getBodies(String JointName){
		List<String> retval = new ArrayList<String>();
		
		Joint requiredJoint = model.getJoint(JointName);
		
		retval.add(requiredJoint.getBodyAfter().getName());
		retval.add(requiredJoint.getBodyBefore().getName());
		
		return retval;
	}
	
	/**
	 * Gets a List of Joints back from the model
	 * @return a list of Joint Names
	 */
	public List<String> getJoints(){
		List<String> retval = new ArrayList<String>();
		for(Joint jt: model.getJointStructure()){
			retval.add(jt.getName());
		}
		return retval;
		
	}
	
	/**
	 * Returns the Origin point of the passed in joint
	 * @param JointName
	 * @return
	 * @Todo
	 */
	public List<String> getOriginPoint(String JointName){
		List<String> retval = new ArrayList<String>();
	//	Joint requiredJoint = model.getJoint(JointName);
		
		
		return retval;
		
	}
	
	/**
	 * Returns the Half plane of the Joint
	 * @param JointName
	 * @return
	 * @Todo
	 */
	public List<String> getHalfPlane(String JointName){
		List<String> retval = new ArrayList<String>();
		return retval;
		
	}
	
	/**
	 * Returns the Common Axis of the Joint
	 * @param JointName
	 * @return
	 * @Todo
	 */
	public List<String> getCommonAxis(String JointName){
		List<String> retval = new ArrayList<String>();
		return retval;
	}
	
	
	
	/**
	 * Method to see what type of joints are implemented in the IMP Core
	 * @return String array of the type of joints implemented
	 */
	public static String[] getJointsImplemented() {
		List<String> list = new ArrayList<String>();
		Collection<JointBuilder> joints = DynamicJointBuilder.getAllBuilders();
		for (JointBuilder j : joints) {
			list.add(j.name);
		}
		String[] retval = new String[list.size()];
		for (int i = 0; i < retval.length; i++) {
			retval[i] = list.get(i);
		}
		return retval;
	}
	
	
	/**
	 * Method to return data types the joints use
	 * @param type Type of Joint
	 * @return String array of all data parameters
	 */
	public static String[] getDataFields(String type) {
		String[] retval = null;
		List<JointArgumentInfo> list = null;
		try {
			list = DynamicJointBuilder.getJointBuilder(type).getArguments();
		} catch (NonExistentJointEntry e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		List<String> realArguments = new ArrayList<String>();
		for (int x = 0; x < list.size(); x++) {
			String name = list.get(x).name.toLowerCase();
			if ((!(name.contains("name"))) && (!(name.contains("origin")))) {
				realArguments.add(list.get(x).name);
			}
		}
		retval = new String[realArguments.size()];
		for (int i = 0; i < realArguments.size(); i++) {
			retval[i] = realArguments.get(i);
		}
		return retval;
	}
	
	
}
