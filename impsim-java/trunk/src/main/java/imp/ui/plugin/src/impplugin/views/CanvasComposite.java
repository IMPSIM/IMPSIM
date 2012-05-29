/**
 * CanvasCoposite.java
 * 4/29/12
 */
package impplugin.views;

import imp.core.graphics.AbstractModelView;
import imp.core.graphics.ModelView;
import impplugin.Activator;
import impplugin.PluginController;
import impplugin.PluginModelView;
import impplugin.objects.Joints;

import java.awt.Frame;

import org.eclipse.jface.resource.ImageRegistry;
import org.eclipse.swt.SWT;
import org.eclipse.swt.awt.SWT_AWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.CoolBar;
import org.eclipse.swt.widgets.CoolItem;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.MenuItem;
import org.eclipse.swt.widgets.ToolBar;
import org.eclipse.swt.widgets.ToolItem;
import org.eclipse.ui.plugin.AbstractUIPlugin;

/**
 * This is the composite class to hold the coolbar and canvas that are used by the user. The coolbar will hold the
 * actions able to be performed on the canvas and the canvas shows the actual IMP model.
 * 
 * @author chancea
 * 
 *         More detail about Composites at: http://www.eclipse.org/swt/widgets/
 */
public class CanvasComposite extends Composite {

	/**
	 * This is the Canvas object that will become the IMP Canvas
	 */
	private Canvas canvas;

	/**
	 * This is the Cool Bar that will contain all of the menu commands (run, stop, pause, etc)
	 */
	private CoolBar menuBar;

	/**
	 * The ToolItem button for adding joints
	 */
	private ToolItem joint;

	/**
	 * The ToolItem button for adding bodies
	 */
	private ToolItem body;

	/**
	 * The Combo item to hold the list of currently active imp files the user has open
	 */
	private Combo fileList;

	/**
	 * Constructor from composites, taking in a parent composite and a style. Initializes the canvas and menu bar.
	 * 
	 * @param parent - the parent this composite will be contained in
	 * @param style - no styles are supported in this composite
	 */
	public CanvasComposite(Composite parent, int style) {
		super(parent, style);

		this.setLayout(new FormLayout());

		canvas = new Canvas(this, SWT.EMBEDDED);

		menuBar = new CoolBar(this, SWT.BORDER);

		int height = 20;
		menuBar.setBounds(0, 0, this.getBounds().width, height);
		canvas.setBounds(0, height, this.getBounds().width, parent.getBounds().height);

		Frame f = SWT_AWT.new_Frame(canvas);
		

		f.setBackground(java.awt.Color.black);

		try {
			// TODO add the model view to the canvas
			AbstractModelView mv = PluginController.getInstance().getModelView();
			f.add(mv.getGLCanvas());
		} catch (Exception e) {
		}

		FormData canvasData = new FormData();
		canvasData.right = new FormAttachment(100);
		canvasData.left = new FormAttachment(0, 0);
		canvasData.bottom = new FormAttachment(100);
		canvasData.top = new FormAttachment(menuBar);
		canvas.setLayoutData(canvasData);

		FormData menuData = new FormData();
		menuData.right = new FormAttachment(100, 0);
		menuData.left = new FormAttachment(0, 0);
		menuData.top = new FormAttachment(0, 0);

		menuBar.setLayoutData(menuData);

		// grab the image icons from the registry
		AbstractUIPlugin plugin = Activator.getDefault();
		ImageRegistry imageRegistry = plugin.getImageRegistry();
		Image stop = imageRegistry.get("IMG_STOP");
		Image pause = imageRegistry.get("IMG_PAUSE");
		Image run = imageRegistry.get("IMG_RUN");

		PluginController.createItem(menuBar, new Image[] { run, stop, pause });
		createMenuBar();
		addJointItems(joint, Joints.JOINT_TYPES);
		PluginController.getInstance().setCanvas(this);
	}

	/**
	 * Helper method, just creates the menu bars [joint] and [body] buttons
	 */
	private void createMenuBar() {
		ToolBar toolBar = new ToolBar(menuBar, SWT.FLAT);
		body = new ToolItem(toolBar, SWT.PUSH);
		body.setToolTipText("Add a body");
		body.setText("Body");
		body.addSelectionListener(new SelectionListener() {

			@Override
			public void widgetSelected(SelectionEvent e) {
				PluginController.getInstance().addBody();
			}

			@Override
			public void widgetDefaultSelected(SelectionEvent e) {

			}

		});

		body.setEnabled(false);

		joint = new ToolItem(toolBar, SWT.DROP_DOWN);
		joint.setToolTipText("Add a Joint");
		joint.setText("Joint");
		joint.addSelectionListener(new SelectionListener() {

			@Override
			public void widgetSelected(SelectionEvent event) {
				if (!(event.detail == SWT.ARROW)) {
					PluginController.getInstance().addJoint();
				}
			}

			@Override
			public void widgetDefaultSelected(SelectionEvent e) {

			}

		});

		joint.setEnabled(false);

		ToolItem separator = new ToolItem(toolBar, SWT.SEPARATOR);

		fileList = new Combo(toolBar, SWT.DROP_DOWN | SWT.READ_ONLY);
		fileList.addSelectionListener(new SelectionListener() {

			@Override
			public void widgetSelected(SelectionEvent e) {
				PluginController.getInstance().setIFile(fileList.getText());
			}

			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				// TODO Auto-generated method stub

			}

		});
		fileList.pack();
		fileList.setBounds(105, 5, 100, 15);
		separator.setWidth(fileList.getSize().x);

		toolBar.pack();
		Point size = toolBar.getSize();
		CoolItem item = new CoolItem(menuBar, SWT.NONE);
		item.setControl(toolBar);
		Point preferred = item.computeSize(size.x, size.y);
		item.setPreferredSize(preferred);

	}

	/**
	 * 
	 * @param t
	 * @param items
	 */
	private void addJointItems(ToolItem t, String[] items) {
		JointSelectionListener listenerOne = new JointSelectionListener(t);
		for (int i = 0; i < items.length; i++) {
			listenerOne.add(items[i]);
		}
		t.addSelectionListener(listenerOne);
	}

	/**
	 * Adds a new file to the active files combo (fileList)
	 * 
	 * @param fileName
	 */
	public void addFileItem(String fileName) {
		String[] items = fileList.getItems();
		String[] newItems = new String[items.length + 1];
		for (int i = 0; i < items.length; i++) {
			newItems[i] = items[i];
		}
		newItems[items.length] = fileName;

		fileList.setItems(newItems);
		fileList.pack();
	}

	/**
	 * Sets the selected active file
	 * 
	 * @param index - the index of the currently active file
	 */
	public void setFileItem(int index) {
		fileList.select(index);
		PluginController.getInstance().setIFile(fileList.getText());
		fileList.update();
	}

	/**
	 * This is the selection listener to control the events of the joint tool item
	 * 
	 * @author chancea
	 * 
	 */
	private class JointSelectionListener extends SelectionAdapter {

		/**
		 * The menu that will appear for when the drop down arrow is clicked on joints
		 */
		private Menu menu;

		/**
		 * Constructor takes in a drop down tool item and adds the menu to its drop down event
		 * 
		 * @param dropdown
		 */
		public JointSelectionListener(ToolItem dropdown) {
			menu = new Menu(dropdown.getParent().getShell());
		}

		/**
		 * Adds a menu item to the menu using the name of the string given. In addition, adds the selection event
		 * listener to the created menu item. This event will call the Controller's addJoint method using the selected
		 * text.
		 * 
		 * @param item - the String item name of the menu
		 */
		public void add(String item) {
			MenuItem menuItem = new MenuItem(menu, SWT.NONE);
			menuItem.setText(item);
			// the selection listener for that joint type
			menuItem.addSelectionListener(new SelectionAdapter() {
				@Override
				public void widgetSelected(SelectionEvent event) {
					MenuItem selected = (MenuItem) event.widget;
					PluginController.getInstance().addJoint(selected.getText());
				}
			});
		}

		@Override
		public void widgetSelected(SelectionEvent event) {
			if (event.detail == SWT.ARROW) { // if it was the drop down that was clicked
				ToolItem item = (ToolItem) event.widget;
				Rectangle rect = item.getBounds();
				Point pt = item.getParent().toDisplay(new Point(rect.x, rect.y));
				menu.setLocation(pt.x, pt.y + rect.height);
				menu.setVisible(true);
			}
		}
	}

	/**
	 * Sets if the add joints tool item is enabled
	 * 
	 * @param flag - true to enable, false to disable
	 */
	public void setAddJointsEnabled(boolean flag) {
		this.joint.setEnabled(flag);
	}

	/**
	 * Sets if the add bodies tool item is enabled
	 * 
	 * @param flag - true to enable, false to disable
	 */
	public void setAddbodiesEnabled(boolean flag) {
		this.body.setEnabled(flag);
	}
}
