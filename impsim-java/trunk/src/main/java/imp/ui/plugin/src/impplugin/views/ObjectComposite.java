package impplugin.views;

import impplugin.PluginController;
import impplugin.objects.Joints;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.MenuItem;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;

/**
 * This class is a representation of the composite class.
 * This composite holds a tree list of Joints and Bodies
 * that have been added to the plugin.
 * @author chancea
 * 
 * More detail about Composites at: http://www.eclipse.org/swt/widgets/
 */
public class ObjectComposite extends Composite{
		
	/**
	 * The is the top level tree that holds
	 * all the joints
	 */
	private Tree jointTree;
	
	/**
	 * The is the top level tree that holds
	 * all the bodies
	 */
	private Tree bodyTree;
	
	/**
	 * This is the tree item that represents
	 * the collection of joints
	 */
	private TreeItem jointItems;
	
	/**
	 * This is the tree item that represents
	 * the collection of bodies
	 */
	private TreeItem bodyItems;
	
	/**
	 * The right click menu for the Joint Header tree
	 */
	private Menu jointRightClickHeaderMenu;
	
	/**
	 * The right click menu for the Body Header tree
	 */
	private Menu bodyRightClickHeaderMenu;
	
	/**
	 * A menu that contains the delete option
	 */
	private Menu deleteMenu;
	
	/**
	 * a boolean to denote the joint tree's current
	 * expanded state
	 */
	private boolean jointTreeExpanded;
	
	/**
	 * the currently selected tree item
	 */
	private TreeItem currentItem;
	
	/**
	 * Data used for event calls
	/************************************************************/
	private static final String JOINT_HEADER_DATA = "JOINT_HEADER";
	private static final String BODY_HEADER_DATA = "BODY_HEADER";
	private static final String JOINT_ITEM_DATA = "JOINT_ITEM";
	private static final String BODY_ITEM_DATA = "BODY_ITEM";
	/************************************************************/
	
	/**
	 * The integer value for a mouse right click
	 */
	private static final int BTN_RIGHT_CLICK = 3;
	
	/**
	 * Constructor - Takes in a parent and a style as all composites.
	 * Initializes the object tree and adds in the jointItems and bodyItems
	 * to display "Joints" and "Bodies" all joints and bodies added to this
	 * will then appear under those individual lists.
	 * 
	 * @param parent - The composite that this class will be contained
	 * within.
	 * @param style - Not used in this composite
	 */
	public ObjectComposite(Composite parent, int style) {
		super(parent, style);
		
		//The plugin controller needs to know the instance
		//of the object composite.
		PluginController.getInstance().setObjects(this);
		
		//initialize the joint tree
		jointTree = new Tree(this, SWT.NONE);
		jointTree.setData(JOINT_HEADER_DATA);
		
		//Add the selection listener to the tree.  This
		//listener will hand of the selected joint to
		//the plugin controller and it will decide what to do
		jointTree.addListener(SWT.Selection, new Listener(){

			@Override
			public void handleEvent(Event event) {
				
				TreeItem treeItem = jointTree.getSelection()[0];
				currentItem = treeItem;
				if(treeItem.getData().toString().equals(JOINT_HEADER_DATA))
				{
					PluginController.getInstance().jointHeaderSelected();
				}
				else if(treeItem.getData().toString().equals(JOINT_ITEM_DATA))
				{
					PluginController.getInstance().jointSelected(treeItem.getText());
				}				
				
			}
			
		});
		
		//initialize the body tree
		bodyTree = new Tree(this, SWT.NONE);
		bodyTree.setData(BODY_HEADER_DATA);
		
		//Add the selection listener to the tree.  This
		//listener will hand of the selected body to
		//the plugin controller and it will decide what to do
		bodyTree.addListener(SWT.Selection, new Listener(){

			@Override
			public void handleEvent(Event event) {
				
				TreeItem treeItem = bodyTree.getSelection()[0];
				currentItem = treeItem;
				if(treeItem.getData().toString().equals(BODY_HEADER_DATA))
				{
					PluginController.getInstance().bodyHeaderSelected();
				}
				else if(treeItem.getData().toString().equals(BODY_ITEM_DATA))
				{
					PluginController.getInstance().bodySelected(treeItem.getText());
				}
				
			}
		});
		
		//In the IMP meeting we talked briefly about adding a right-click option
		//to the tree to add joints or bodies.  This is where the code would 
		//be for that implementation: (setUpRightClickMenus AND the listener events below that);
		
		setUpRightClickMenus();
		
		//add a listener for when the joint tree is expanded
		jointTree.addListener(SWT.Expand, new Listener(){

			@Override
			public void handleEvent(Event event) {
				updateTreeLayout(false);
			}
			
		});
		
		//add a listener for when the joint tree is collapsed
		jointTree.addListener(SWT.Collapse, new Listener(){

			@Override
			public void handleEvent(Event event) {
				updateTreeLayout(true);
			}
			
		});
		
		//add a mouse listener for the joint tree
		jointTree.addMouseListener(new MouseListener(){

			//a helper method to get the index of the tree item
			//the user clicked on if the click falls within this 
			//trees bounds
			private int getIndexFromMouseEvent(MouseEvent e)
			{
				int height = jointItems.getBounds().height;
				int index = 0;
				int y = e.y;
				while(y > 0)
				{
					y -= height;
					index++;
				}
				return index;
			}
			
			@Override
			public void mouseDoubleClick(MouseEvent e) {
				//we could possible have an event occur on a double click
				
				if(e.button == BTN_RIGHT_CLICK) //even a double right click
				{
					//TODO: add possible functionality here
				}
				
				if(e.button == 1) //or a double left click
				{
					//TODO: add possible functionality here
				}
				
			}

			@Override
			public void mouseDown(MouseEvent e) {
				//if we want the event to occur on the down press of the click
			
				if(e.button == BTN_RIGHT_CLICK) //if it was a right click
				{
					if(!jointTreeExpanded)
					{
						//if the tree is not expanded we know it was the header
						PluginController.getInstance().jointHeaderSelected();
					}
					else 
					{
						//we get the index of the item the mouse is at
						int index = getIndexFromMouseEvent(e);
						if(index == 1) //if it is at the header
						{
							PluginController.getInstance().jointHeaderSelected();
						}
						else //the user selected an actual joint from the expanded list
						{
							PluginController.getInstance().jointSelected();
						}
					}
				}
			}

			@Override
			public void mouseUp(MouseEvent e) {
				//if we want the event to occur on the release of the click
				//System.out.println(e.data);
				if(e.button == BTN_RIGHT_CLICK) //if it was a right click
				{
					PluginController controller = PluginController.getInstance();
					if(controller.isJointSelected()) //we want to initialize the right click menu for a joint item
					{
						Rectangle rect = jointItems.getBounds();
						Point pt = jointItems.getParent().toDisplay(new Point(rect.x, rect.y));
						int index = getIndexFromMouseEvent(e);
						if(index > jointItems.getItemCount() + 1)
						{
							return;
						}
						int height = jointItems.getBounds().height;
						deleteMenu.setLocation(pt.x, pt.y + height*index);
						deleteMenu.setVisible(true);
					}
					else if(controller.isJointHeaderSelected()) //we want to initialize the right click menu for the joint header
					{
						  Rectangle rect = jointItems.getBounds();
						  Point pt = jointItems.getParent().toDisplay(new Point(rect.x, rect.y));
						  jointRightClickHeaderMenu.setLocation(pt.x, pt.y + rect.height);
						  jointRightClickHeaderMenu.setVisible(true);
					}
				}
				
			}
			
		});
		
		bodyTree.addMouseListener(new MouseListener(){

			//a helper method to get the index of the tree item
			//the user clicked on if the click falls within this 
			//trees bounds
			private int getIndexFromMouseEvent(MouseEvent e)
			{
				int height = bodyItems.getBounds().height;
				int index = 0;
				int y = e.y;
				while(y > 0)
				{
					y -= height;
					index++;
				}
				return index;
			}
			
			@Override
			public void mouseDoubleClick(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseDown(MouseEvent e) {
				//if we want the event to occur on the down press of the click
				
				if(e.button == BTN_RIGHT_CLICK) //if it was a right click
				{
					int index = getIndexFromMouseEvent(e);
					if(index == 1) //if it is in the header
					{
						PluginController.getInstance().bodyHeaderSelected();
					}
					else //the user selected an actual body from the expanded list
					{
						PluginController.getInstance().bodySelected();
					}
					
				}
			}

			@Override
			public void mouseUp(MouseEvent e) {
				
				if(e.button == BTN_RIGHT_CLICK) //if it was a right click
				{
					PluginController controller = PluginController.getInstance();
					if(controller.isBodySelected()) //we want to initialize the right click menu for a body item
					{
						Rectangle rect = bodyItems.getBounds();
						Point pt = bodyItems.getParent().toDisplay(new Point(rect.x, rect.y));
						int height = bodyItems.getBounds().height;
						int index = getIndexFromMouseEvent(e);
						if(index > bodyItems.getItemCount() + 1)
						{
							return;
						}
						deleteMenu.setLocation(pt.x, pt.y + height*index);
						deleteMenu.setVisible(true);
					}
					else if (controller.isBodyHeaderSelected()) //we want to initialize the right click menu for the body header
					{
						Rectangle rect = bodyItems.getBounds();
					    Point pt = bodyItems.getParent().toDisplay(new Point(rect.x, rect.y));
					    bodyRightClickHeaderMenu.setLocation(pt.x, pt.y + rect.height);
					    bodyRightClickHeaderMenu.setVisible(true);
					}
				}
				
			}
			
		});
		
		//Setting the layout of the composite
		setLayout(new FormLayout());		
		
		//Instantiate the jointItems and BodyItems to new TreeItems
		//with the main object tree as their parent and having no style
		jointItems = new TreeItem(jointTree, SWT.NONE);
		jointItems.setData(JOINT_HEADER_DATA);
		
		bodyItems = new TreeItem(bodyTree, SWT.NONE);
		bodyItems.setData(BODY_HEADER_DATA);
		
		//Sets the text of the TreeItems to display "Joints" and "Bodies"
		jointItems.setText("Joints");
		bodyItems.setText("Bodies");
		
		//This is a simple layout making the 
		//object tree start at position 0,0 and span
		//100% of the width and height of the composite
		FormData fd_jointTree = new FormData();
		fd_jointTree.top = new FormAttachment(0, 0);
		fd_jointTree.left = new FormAttachment(0, 0);
		fd_jointTree.bottom = new FormAttachment(0, jointItems.getBounds().height);
		fd_jointTree.right = new FormAttachment(100, 0);
		jointTree.setLayoutData(fd_jointTree);
		
		FormData fd_objectTree = new FormData();
		fd_objectTree.top = new FormAttachment(jointTree, 0, SWT.BOTTOM);
		fd_objectTree.left = new FormAttachment(0, 0);
		fd_objectTree.bottom = new FormAttachment(100, 0);
		fd_objectTree.right = new FormAttachment(100, 0);
		bodyTree.setLayoutData(fd_objectTree);
	}
	
	/**
	 * Layouts the joints tree for either:
	 * 
	 * 	- collapsed (true) - this means the tree will take
	 * 	on the layout of not being expanded, and will
	 * 	only have bounds to show the header of the tree.
	 * 
	 * 	- expanded (false) - this means the tree will take
	 * 	on the layout of being expanded, and will have
	 * 	bounds to show all of the tree items inside of the
	 * 	tree.  Unless the tree items take up more than 50%
	 * 	of the current height of the view.  In that case
	 * 	the lists height will be limited to the first full
	 * 	item before 50%.
	 * @param collasped
	 */
	private void updateTreeLayout(boolean collasped)
	{
		if(collasped)
		{
			jointTreeExpanded = false;
			FormData fd_jointTree = new FormData();
			fd_jointTree.top = new FormAttachment(0, 0);
			fd_jointTree.left = new FormAttachment(0, 0);
			fd_jointTree.bottom = new FormAttachment(0, jointItems.getBounds().height);
			fd_jointTree.right = new FormAttachment(100, 0);
			jointTree.setLayoutData(fd_jointTree);
			ObjectComposite.this.layout();
		}
		else
		{
			jointTreeExpanded = true;
			jointTree.setSize(jointTree.getBounds().width, jointItems.getBounds().height*(jointItems.getItemCount() + 1));
			FormData fd_jointTree = new FormData();
			fd_jointTree.top = new FormAttachment(0, 0);
			fd_jointTree.left = new FormAttachment(0, 0);
			fd_jointTree.bottom = new FormAttachment(0, Math.min(jointTree.getBounds().height, ObjectComposite.this.getBounds().height/2 + ObjectComposite.this.getBounds().height%jointItems.getBounds().height));
			fd_jointTree.right = new FormAttachment(100, 0);
			jointTree.setLayoutData(fd_jointTree);
			ObjectComposite.this.layout();
		}
	}
	
	/**
	 * Sets up the right click menus
	 * 
	 * Because all items within both trees (joints/bodies)
	 * only need to be edited or deleted the right click
	 * menu can be the same for both trees.  This right click
	 * menu only will contain the delete option, because 
	 * regular clicking on an item will initiate edit mode.
	 */
	private void setUpRightClickMenus()
	{
		//initialize the joints right click menu
		jointRightClickHeaderMenu = new Menu(getShell());
		
			//add a menu for adding joints and add all possible joints to that menu
			MenuItem jointsAdd = new MenuItem(jointRightClickHeaderMenu, SWT.CASCADE);
			jointsAdd.setText("Add");
			jointsAdd.setEnabled(false);
			Menu jointsAddMenu = new Menu(jointRightClickHeaderMenu);
			jointsAdd.setMenu(jointsAddMenu);
				String[] joints = Joints.JOINT_TYPES;
				for(int i = 0; i < joints.length; i++)
				{
					MenuItem item = new MenuItem(jointsAddMenu, SWT.NONE);
					item.setText(joints[i]);
					item.addSelectionListener(new SelectionAdapter() {
						@Override
						public void widgetSelected(SelectionEvent event) 
						{
							MenuItem selected = (MenuItem) event.widget;
					    	PluginController.getInstance().addJoint(selected.getText());
						}
					});
				}
			
			//add a menu for sorting, and add the 2 sorting methods to that menu
			MenuItem jointsSort = new MenuItem(jointRightClickHeaderMenu, SWT.CASCADE);
			jointsSort.setText("Sort by");
			Menu jointsSortMenu = new Menu(jointRightClickHeaderMenu);
			jointsSort.setMenu(jointsSortMenu);
			
				MenuItem sortType = new MenuItem(jointsSortMenu, SWT.NONE);
				sortType.setText("Type");
				
				MenuItem nameType = new MenuItem(jointsSortMenu, SWT.NONE);
				nameType.setText("Name");
				
			//An extra field for future possible use
			MenuItem jointsExtra1 = new MenuItem(jointRightClickHeaderMenu, SWT.CASCADE);
			jointsExtra1.setText("Extra Option 1");
			
			//An extra field for future possible use
			MenuItem jointsExtra2 = new MenuItem(jointRightClickHeaderMenu, SWT.CASCADE);
			jointsExtra2.setText("Extra Option 2");
			
		//initialize the delete menu for both joints and bodies
		deleteMenu = new Menu(getShell());
			MenuItem jointsDelete = new MenuItem(deleteMenu, SWT.CASCADE);
			jointsDelete.setText("Delete");
			
		//initialize the body right click menu
		bodyRightClickHeaderMenu = new Menu(getShell());

			//add a menu for adding joints and add all possible joints to that menu
			MenuItem bodyAdd = new MenuItem(bodyRightClickHeaderMenu, SWT.NONE);
			bodyAdd.setText("Add");
			bodyAdd.addSelectionListener(new SelectionListener(){

				@Override
				public void widgetSelected(SelectionEvent event) {
			    	PluginController.getInstance().addBody();
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent event) {
					// TODO Auto-generated method stub
					
				}
				
			});

			//add a menu for sorting, and add the 2 sorting methods to that menu
			MenuItem bodySort = new MenuItem(bodyRightClickHeaderMenu, SWT.CASCADE);
			bodySort.setText("Sort by");
			Menu bodySortMenu = new Menu(bodyRightClickHeaderMenu);
			bodySort.setMenu(bodySortMenu);
			
				MenuItem bodySortType = new MenuItem(bodySortMenu, SWT.NONE);
				bodySortType.setText("Type");
				
				MenuItem bodySortName = new MenuItem(bodySortMenu, SWT.NONE);
				bodySortName.setText("Name");
			
	}
	
	/**
	 * Updates the currently selected tree items
	 * text to the name given
	 * @param name - the name (text) to give the 
	 * currently selected tree item
	 */
	public void updateCurrentTreeItem(String name)
	{
		currentItem.setText(name);
	}
	
	/**
	 * Adds a joint to the tree list, then layouts
	 * the joint tree for the added item
	 * @param joint - the joint to add to the list
	 */
	public void addJoint(String joint)
	{
		TreeItem item = new TreeItem(jointItems, 0);
		item.setData(JOINT_ITEM_DATA);
		item.setText(joint);
		jointItems.setExpanded(true);
		updateTreeLayout(false);
		
		
	}
	
	/**
	 * Adds a body to the tree list.
	 * 
	 * @param body - the body to add to the list
	 */
	public void addBody(String body)
	{
		TreeItem item = new TreeItem(bodyItems, 0);
		item.setData(BODY_ITEM_DATA);
		item.setText(body);
		
		bodyItems.setExpanded(true);
		
	}
	
	/**
	 * Sets the add joints menu to enabled or disabled
	 * @param flag - True to enable, false to disable
	 */
	public void setAddJointsEnabled(boolean flag)
	{
		this.jointRightClickHeaderMenu.getItem(0).setEnabled(flag);
	}
}
