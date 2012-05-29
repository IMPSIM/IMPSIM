/**
 * PluginController.java
 * 5/10/12
 */
package impplugin;

import imp.core.graphics.AbstractModelView;
import imp.core.graphics.ModelView;
import imp.core.structures.Point;
import impplugin.editors.CodeGenerator;
import impplugin.objects.Bodies;
import impplugin.objects.Joints;
import impplugin.views.CanvasComposite;
import impplugin.views.ObjectComposite;
import impplugin.views.PropertiesComposite;
import impplugin.views.PropertiesComposite.GUIState;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLProfile;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IWorkspace;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.FileLocator;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.Platform;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.CoolBar;
import org.eclipse.swt.widgets.CoolItem;
import org.eclipse.swt.widgets.ToolBar;
import org.eclipse.swt.widgets.ToolItem;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PlatformUI;

/**
 * This is the class that controls all aspects of the plugin. When any event happens this class handles the calls;
 * making all the decisions.
 * 
 * Stereotypes: Singleton - This class is a singleton because there is no way to call this class from each composite
 * that resides in the plugin. Using the stereotype of a Singleton this class can then be referenced statically and no
 * instance of this needs to be passed through to the composite classes. In addition, there really only should be one
 * instance of this class. There is no good reason to have multiple instances of this class running.
 * 
 * @author chancea
 * 
 */
public class PluginController {

	/**
	 * The ModelView canvas that will be used to display models
	 */
	private PluginModelView modelView;

	/**
	 * The current list of open files the user is editing
	 */
	private List<IFile> openFiles;

	/**
	 * The currently selected file that the user is editing
	 */
	private IFile file;

	/**
	 * This is the list of joints inside of the current design.
	 * 
	 * TODO: Merge both List<Bodies> and List<Joints> into the Storage class
	 */
	private List<Joints> joints;

	/**
	 * This is the list of bodies inside of the current design.
	 * 
	 * TODO: Merge both List<Bodies> and List<Joints> into the Storage class
	 */
	private List<Bodies> bodies;

	/**
	 * This is the instance of the plugin that will always be used. No other instances will be created. (Part of the
	 * singleton stereotype)
	 */
	private static PluginController instance;

	/**
	 * This is the reference to the properties composite. The controller will take all event calls and make all
	 * decisions regarding this composite.
	 */
	private PropertiesComposite properties;

	/**
	 * This is the reference to the object composite. The controller will take all event calls and make all decisions
	 * regarding this composite.
	 */
	private ObjectComposite objects;

	/**
	 * This is the reference to the canvas composite. The controller will take all event calls and make all decisions
	 * regarding this composite.
	 */
	private CanvasComposite canvas;

	/**
	 * Variable to denote if a body item is selected in the Object Composite
	 */
	private boolean bodySelected;

	/**
	 * Variable to denote if the body header is selected in the Object Composite
	 */
	private boolean bodyHeaderSelected;

	/**
	 * Variable to denote if a joint item is selected in the Object Composite
	 */
	private boolean jointSelected;

	/**
	 * Variable to denote if the joint header is selected in the Object Composite
	 */
	private boolean jointHeaderSelected;

	/**
	 * The current selected body from the object composite
	 */
	private Bodies currentBody;

	/**
	 * The current selected joint from the object composite
	 */
	private Joints currentJoint;

	/**
	 * Private constructor to make this class unable to be instantiated from other classes (Part of the Singleton
	 * stereotype)
	 */
	private PluginController() {
		bodies = new ArrayList<Bodies>();
		joints = new ArrayList<Joints>();
		bodySelected = false;
		jointSelected = false;
		openFiles = new ArrayList<IFile>();
		System.err.println(System.getProperty("java.library.path"));
		modelView = new PluginModelView(60, new GLCapabilities(GLProfile.getDefault()));
		//modelView = new ModelView();
	}

	/**
	 * Adds an iFIle to a list of open iFiles
	 * 
	 * @param iFile - the file to add to the list
	 */
	public void addIFile(IFile iFile) {
		openFiles.add(iFile);

		if (canvas == null) {
			return;
		}

		canvas.addFileItem(iFile.getProject().getName() + "/" + iFile.getName());
		canvas.setFileItem(openFiles.indexOf(iFile));
	}

	/**
	 * When the canvas composite is created it will call this method to denote what canvas composite this controller
	 * will be controlling.
	 * 
	 * @param canvas - the Canvas composite
	 */
	public void setCanvas(CanvasComposite canvas) {
		this.canvas = canvas;
		for (IFile file : openFiles) {
			canvas.addFileItem(file.getProject().getName() + "/" + file.getName());
		}
		canvas.setFileItem(openFiles.indexOf(file));
	}

	/**
	 * Removes the given iFile from the list of open iFiles. This should be called when the user closes an imp editor
	 * view.
	 * 
	 * @param iFile - the file to remove from the list
	 */
	public void removeIFile(IFile iFile) {
		openFiles.remove(iFile);
	}

	/**
	 * 
	 * @param filePath
	 */
	public void setIFile(String filePath) {
		for (IFile file : openFiles) {
			String pathWithName = file.getProject().getName() + "/" + file.getName();
			if (pathWithName.equals(filePath)) {
				this.file = file;
				canvas.setAddbodiesEnabled(true);
				return;
			}
		}
	}

	/**
	 * Sets the current IFile to load and write to. This method will invoke the loadIFile() to load the data already
	 * previously in the file.
	 * 
	 * @param iFile
	 */
	public void setIFile(IFile iFile) {
		canvas.setAddbodiesEnabled(true);
		file = iFile;
		loadIFile(iFile);
	}

	/**
	 * TODO
	 * 
	 * @param file
	 */
	public void loadIFile(IFile file) {

	}

	/**
	 * For the Object composite, determines if the currently selected item in the object tree is a body item
	 * 
	 * @return - True if the currently selected item is a body item (the body header is not considered a body item, use
	 *         isBodyHeaderSelected() to get a reference for the header)
	 */
	public boolean isBodySelected() {
		return bodySelected;
	}

	/**
	 * For the Object composite, determines if the currently selected item in the object tree is a joint item
	 * 
	 * @return - True if the currently selected item is a joint item (the joint header is not considered a joint item,
	 *         use isjointHeaderSelected() to get a reference for the header)
	 */
	public boolean isJointSelected() {
		return jointSelected;
	}

	/**
	 * For the Object composite, determines if the currently selected item in the object tree is the joint header item
	 * 
	 * @return - True if the currently selected item is the joint header (the joint header is not considered a joint
	 *         item, use isjointSelected() to get a reference for a joint)
	 */
	public boolean isJointHeaderSelected() {
		return jointHeaderSelected;
	}

	/**
	 * For the Object composite, determines if the currently selected item in the object tree is the body header item
	 * 
	 * @return - True if the currently selected item is the body header (the body header is not considered a body item,
	 *         use isBodySelected() to get a reference for a body)
	 */
	public boolean isBodyHeaderSelected() {
		return bodyHeaderSelected;
	}

	/**
	 * This is the method to initialize the instance of the controller. If the controller has already previously been
	 * initialize then instance is returned. (Part of the Singleton stereotype)
	 * 
	 * @return
	 */
	public synchronized static PluginController getInstance() {
		if (instance == null) {
			instance = new PluginController();
		}
		return instance;
	}

	/**
	 * When the properties composite is created it will call this method to denote what properties composite this
	 * controller will be controlling.
	 * 
	 * @param properties - the Properties composite
	 */
	public void setProperties(PropertiesComposite properties) {
		this.properties = properties;
	}

	/**
	 * When the object composite is created it will call this method to denote what object composite this controller
	 * will be controlling.
	 * 
	 * @param objects - the Object composite
	 */
	public void setObjects(ObjectComposite objects) {
		this.objects = objects;
	}

	/**
	 * The event handler method to handle when the user clicks on the add joint button
	 * 
	 * @param name
	 */
	public void addJoint(String name, Bodies body1, Bodies body2, String jointType, Point[] dataPoints, Point origin) {
		for (int i = 0; i < joints.size(); i++) {
			if (joints.get(i).getName().equals(name)) {
				MessageDialog.openError(properties.getShell(), "Cannot add Joint", "A joint with that name already exists");
				return;
			}
		}
		Joints j = new Joints(name, body1, body2, jointType, dataPoints, origin);
		this.joints.add(j);
		this.objects.addJoint(name);

		CodeGenerator.outputJoint(j, this.file);
	}

	/**
	 * The event handler method to handle when the user clicks on the add joint button
	 */
	public void addJoint() {
		this.properties.changeState(GUIState.STATE_JOINT_ADD);
	}

	/**
	 * The event handler method to handle when the user clicks on a specific joint to add (they clicked on the joint
	 * drop down menu and selected a type, that type name is passed in)
	 * 
	 * @param jType - The type of joint the user selected to add
	 */
	public void addJoint(String jType) {
		addJoint();
		this.properties.setJType(jType);
	}

	/**
	 * The event handler method to handle the adding of a body. This event finalizes and actually will add the body to
	 * the list of bodies.
	 * 
	 * @param name
	 */
	public void addBody(String name) {
		for (int i = 0; i < bodies.size(); i++) {
			if (bodies.get(i).getName().equals(name)) {
				MessageDialog.openError(properties.getShell(), "Cannot add Body", "A body with that name already exists");
				return;
			}
		}
		this.bodies.add(new Bodies(name));
		if (bodies.size() >= 2) {
			objects.setAddJointsEnabled(true);
			canvas.setAddJointsEnabled(true);
		}
		this.objects.addBody(name);
		this.properties.updateBodies();
	}

	/**
	 * The event handler method to handle when the user clicks on the add body button
	 */
	public void addBody() {
		this.properties.changeState(GUIState.STATE_BODY_ADD);
	}

	/**
	 * Updates the currently selected body in the object composite tree to the new body name given as long as the new
	 * name does not conflict with any other names already added to the tree
	 * 
	 * @param name - the new name to call the body
	 */
	public void updateCurrentBody(String name) {
		for (int i = 0; i < bodies.size(); i++) {
			if (bodies.get(i).getName().equals(name)) {
				MessageDialog.openError(properties.getShell(), "Cannot update Body", "A body with that name already exists");
				return;
			}
		}
		currentBody.setName(name);
		objects.updateCurrentTreeItem(name);
		properties.updateBodies();
	}

	/**
	 * The event handler method for when the user selects the body header from the tree
	 */
	public void bodyHeaderSelected() {
		jointSelected = false;
		bodySelected = false;
		jointHeaderSelected = false;
		bodyHeaderSelected = true;
	}

	/**
	 * The event handler method to just denote the user selected a body from the tree (i.e. they right clicked and want
	 * to just show the context menu)
	 */
	public void bodySelected() {
		jointSelected = false;
		bodySelected = true;
	}

	/**
	 * The event handler method for when a user selected and wants to edit a body from the tree (i.e. they left clicked
	 * and want to load/edit the body)
	 * 
	 * @param name - the name of the body they want to edit
	 */
	public void bodySelected(String name) {
		bodySelected();
		for (int i = 0; i < bodies.size(); i++) {
			if (bodies.get(i).getName().equals(name)) {
				this.currentBody = bodies.get(i);
				break;
			}
		}
		this.properties.changeState(GUIState.STATE_BODY_VIEW);
		this.properties.setName(name);
	}

	/**
	 * Gets the data fields for the specific joint type
	 * 
	 * TODO: Change this so it can return something that will denote if the data field is a Point or a Double in
	 * addition to the name.
	 * 
	 * @param jointType - The type of joint to get the fields for (i.e. ZPin)
	 * @return - The list of data fields
	 */
	public String[] getJointDataFields(String jointType) {
		return PluginJointsLoader.getDataFields(jointType);
	}

	/**
	 * The event handler method to just denote the user selected a joint from the tree (i.e. they right clicked and want
	 * to just show the context menu)
	 */
	public void jointSelected() {
		jointSelected = true;
		bodySelected = false;
	}

	/**
	 * The event handler method for when a user selected and wants to edit a joint from the tree (i.e. they left clicked
	 * and want to load/edit the joint)
	 * 
	 * @param name - the name of the joint they want to edit
	 */
	public void jointSelected(String name) {
		jointSelected();
		for (int i = 0; i < joints.size(); i++) {
			if (joints.get(i).getName().equals(name)) {
				this.currentJoint = joints.get(i);
				break;
			}
		}
		this.properties.changeState(GUIState.STATE_JOINT_VIEW);
		this.properties.setName(name);
		this.properties.setOrigin(currentJoint.getOrigin());
		this.properties.setBody1(currentJoint.getBody1().getName());
		this.properties.setBody2(currentJoint.getBody2().getName());
		this.properties.setJType(currentJoint.getType());
		this.properties.setDataPoints(currentJoint.getDataPoints());
	}

	/**
	 * The event handler method to handle when the user selects a joint from the tree
	 */
	public void jointHeaderSelected() {
		jointSelected = false;
		bodySelected = false;
		jointHeaderSelected = true;
		bodyHeaderSelected = false;
	}

	/**
	 * Create a CoolItem that holds a toolbar containing tool items of the images
	 * 
	 * @param coolBar - The cool bar the cool item will be added to
	 * @param images - The images that will be used in the cool item
	 * @return - the created cool item
	 */
	public static CoolItem createItem(final CoolBar coolBar, Image[] images) {

		// create a flat toolbar with the coolbar as its parent
		ToolBar toolBar = new ToolBar(coolBar, SWT.FLAT);

		// for each image given add a new tool item
		int count = images.length;
		for (int i = 0; i < count; i++) {
			ToolItem item = new ToolItem(toolBar, SWT.PUSH);
			item.setToolTipText(images[i].toString());
			item.setImage(images[i]);

			// TEMP: Add selection listener to each too item with
			// a popup menu of their index
			// TODO: change this method so that real selection listeners
			// are listening to the buttons
			final int index = i;
			if(index == 0)
			{
				item.addSelectionListener(new SelectionListener() {
	
					@Override
					public void widgetSelected(SelectionEvent e) {
						//get object which represents the workspace  
						IWorkspace workspace = ResourcesPlugin.getWorkspace();  
						  
						//get location of workspace (java.io.File)  
						File workspaceDirectory = workspace.getRoot().getLocation().toFile();
								
						PluginController instance = PluginController.getInstance();
						IPath p = instance.file.getFullPath();
						File f = p.toFile();						
						
						instance.modelView.runImpFile(workspaceDirectory.getAbsolutePath() + f.toString());
					}
	
					@Override
					public void widgetDefaultSelected(SelectionEvent e) {
						MessageDialog.openInformation(coolBar.getShell(), "View", "Default " + index);
					}
	
				});
			}
		}
		toolBar.pack();

		// set the size
		org.eclipse.swt.graphics.Point size = toolBar.getSize();
		CoolItem item = new CoolItem(coolBar, SWT.NONE);
		item.setControl(toolBar);
		org.eclipse.swt.graphics.Point preferred = item.computeSize(size.x, size.y);
		item.setPreferredSize(preferred);
		return item;
	}

	/**
	 * Gets the list of joints currently added to the model
	 * 
	 * @return - the list of joints
	 */
	public List<Joints> getJoints() {
		return joints;
	}

	/**
	 * Gets the list of bodies currently added to the model
	 * 
	 * @return - the list of bodies
	 */
	public List<Bodies> getBodies() {
		return bodies;
	}

	/**
	 * Inside this plugin calling files with a local path is not really possible, because the code is run within the
	 * workspace of the eclipse this plugin resides in. This method will translate any local path to the absolute path
	 * of the residing eclipse allowing the access of local files.
	 * 
	 * @param localPath - The local path inside this project
	 * @return - The absolute path in the residing eclipse
	 */
	public static String localToPluginFilePath(String localPath) {
		URL url = Platform.getBundle(Activator.PLUGIN_ID).getEntry(localPath);
		String pluginPath = null;
		try {
			pluginPath = FileLocator.toFileURL(url).getPath();
		} catch (IOException e3) {
			// TODO Auto-generated catch block
			e3.printStackTrace();
		}

		return pluginPath;
	}

	public AbstractModelView getModelView() {
		return modelView;
	}
}
