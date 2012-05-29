/**
 * PropertiesComposite.java
 * 4/29/12
 */
package impplugin.views;

import imp.core.structures.Point;
import impplugin.PluginController;
import impplugin.objects.Bodies;
import impplugin.objects.Joints;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.ControlEvent;
import org.eclipse.swt.events.ControlListener;
import org.eclipse.swt.events.KeyEvent;
import org.eclipse.swt.events.KeyListener;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Widget;

/**
 * This is the composite class to hold the properties of a joint or a body. This class is intended to be handed off to a
 * parent composite.
 * 
 * @author chancea
 * 
 *         More detail about Composites at: http://www.eclipse.org/swt/widgets/
 */
public class PropertiesComposite extends Composite {

	/**
	 * The KeyListener to listen for the return key and press the complete button.
	 */
	private KeyListener keyListener;

	/**
	 * The key code for the return key
	 */
	private static final int RETURN_KEY_CODE = 13;

	/**
	 * The Space between different fields/forms
	 */
	private static final int FORM_SPACE = 15;

	/**
	 * The space between the Label of a field and the field the label is representing
	 */
	private static final int LABEL_SPACE = 10;

	/**
	 * The indent from the left of the composite for all components
	 */
	private static final int LEFT_INDENT = 10;

	/**
	 * The indent from the top of the composite for all components
	 */
	private static final int TOP_INDENT = 10;

	/**
	 * The length of text fields
	 */
	private static final int TXT_FIELD_LENGTH = 130;

	/**
	 * The Text field for the name of the joint
	 */
	private Text txtName;

	/**
	 * The data composite representing the origin
	 */
	private DataComposite dcOrigin;

	/**
	 * The Combo box to hold the first body the joint is connected to
	 */
	private Combo cmbBody1;

	/**
	 * The Combo box to hold the second body the joint is connected to
	 */
	private Combo cmbBody2;

	/**
	 * The combo box to hold the type of the joint
	 */
	private Combo cmbJType;

	/**
	 * The Label to represent the title of the currently selected object (Joint or Body);
	 */
	private Label lblTitle;

	/**
	 * The label for the name
	 */
	private Label lblName;

	/**
	 * The label for the first body connected
	 */
	private Label lblBody1;

	/**
	 * The label for the second body connected
	 */
	private Label lblBody2;

	/**
	 * The label for the Joint type
	 */
	private Label lblJType;

	/**
	 * The button for the
	 */
	private Button btnComplete;

	/**
	 * The current state of this GUI
	 */
	private GUIState currentState;

	/**
	 * The map to denote the required fields and if they are completed or not
	 */
	private Map<Widget, Boolean> requiredFields;

	/**
	 * The boolean representing if the bodies are being updated by the plugin
	 * 
	 * This is so the event handler doesnt fire for when the plugin updates the bodies and only when the user selects
	 * one
	 */
	private boolean updatingBodies;

	/**
	 * The active data composite fields representing the extra joint data needed for the currently selected joint type
	 */
	private DataComposite[] activeCompositeFields;

	/**
	 * @author chancea The possible states of this GUI
	 */
	public enum GUIState {
		STATE_NONE, STATE_JOINT_ADD, STATE_JOINT_VIEW, STATE_BODY_ADD, STATE_BODY_VIEW;
	}

	/**
	 * Constructor - Takes in a parent and a style as all composites. Creates all GUI fields and initially makes
	 * everything not visible. The Controller will determine which state this composite should be in and depending on
	 * the state is when certain fields will be shown/hidden.
	 * 
	 * @param parent - The composite that this class will be contained within.
	 * @param style - Not used in this composite
	 */
	public PropertiesComposite(Composite parent, int style) {
		super(parent, style);

		keyListener = new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				if (e.keyCode == RETURN_KEY_CODE && checkRequiredFields()) {
					btnCompleteClick();
				}
			}

			@Override
			public void keyReleased(KeyEvent e) {
				// TODO Auto-generated method stub

			}

		};
		// create a new FormLayout
		setLayout(new FormLayout());

		// The plugin controller needs to know the instance
		// of the properties composite.
		PluginController.getInstance().setProperties(this);

		lblTitle = new Label(this, SWT.NONE);
		lblTitle.setText("Add Joint");
		FormData fd_lblTitle = new FormData();
		fd_lblTitle.top = new FormAttachment(0, TOP_INDENT);
		fd_lblTitle.left = new FormAttachment(0, LEFT_INDENT);
		lblTitle.setLayoutData(fd_lblTitle);
		lblTitle.setFont(new Font(this.getDisplay(), "Courier New", 20, SWT.BOLD));

		{ // Create fields for the Name
			lblName = new Label(this, SWT.NONE);
			lblName.setText("Name");
			FormData fd_lblName = new FormData();
			fd_lblName.top = new FormAttachment(lblTitle, LABEL_SPACE, SWT.BOTTOM);
			fd_lblName.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			lblName.setLayoutData(fd_lblName);

			txtName = new Text(this, SWT.BORDER);
			FormData fd_txtName = new FormData();
			fd_txtName.right = new FormAttachment(lblTitle, 0, SWT.RIGHT);
			fd_txtName.left = new FormAttachment(lblName, 0, SWT.LEFT);
			fd_txtName.top = new FormAttachment(lblName, LABEL_SPACE, SWT.BOTTOM);
			txtName.setLayoutData(fd_txtName);
			txtName.addKeyListener(keyListener);
			addRequiredField(txtName);
		}
		{
			dcOrigin = new DataComposite("Origin", this, SWT.NONE);
			FormData dc_fd = new FormData();
			dc_fd.top = new FormAttachment(txtName, FORM_SPACE, SWT.BOTTOM);
			dc_fd.left = new FormAttachment(0, LEFT_INDENT);
			dc_fd.right = new FormAttachment(lblTitle, 0, SWT.RIGHT);
			dcOrigin.setLayoutData(dc_fd);
			dcOrigin.setVisible(true);
		}
		{ // Body fields
			lblBody1 = new Label(this, SWT.NONE);
			lblBody1.setText("Body 1");
			FormData fd_lblBody1 = new FormData();
			fd_lblBody1.top = new FormAttachment(dcOrigin, FORM_SPACE, SWT.BOTTOM);
			fd_lblBody1.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			lblBody1.setLayoutData(fd_lblBody1);

			cmbBody1 = new Combo(this, SWT.DROP_DOWN);
			FormData fd_cmbBody1 = new FormData();
			fd_cmbBody1.top = new FormAttachment(lblBody1, LABEL_SPACE, SWT.BOTTOM);
			fd_cmbBody1.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			fd_cmbBody1.right = new FormAttachment(0, 90);
			cmbBody1.setLayoutData(fd_cmbBody1);
			cmbBody1.addKeyListener(keyListener);

			lblBody2 = new Label(this, SWT.NONE);
			lblBody2.setText("Body 2");
			FormData fd_lblBody2 = new FormData();
			fd_lblBody2.top = new FormAttachment(cmbBody1, FORM_SPACE, SWT.BOTTOM);
			fd_lblBody2.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			lblBody2.setLayoutData(fd_lblBody2);

			cmbBody2 = new Combo(this, SWT.DROP_DOWN);
			FormData fd_cmbBody2 = new FormData();
			fd_cmbBody2.top = new FormAttachment(lblBody2, LABEL_SPACE, SWT.BOTTOM);
			fd_cmbBody2.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			fd_cmbBody2.right = new FormAttachment(0, 90);
			cmbBody2.setLayoutData(fd_cmbBody2);
			cmbBody2.addKeyListener(keyListener);
		}

		{ // Joint Type fields
			lblJType = new Label(this, SWT.NONE);
			FormData fd_lblJType = new FormData();
			fd_lblJType.top = new FormAttachment(cmbBody2, FORM_SPACE, SWT.BOTTOM);
			fd_lblJType.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			lblJType.setText("Joint Type");
			lblJType.setLayoutData(fd_lblJType);

			cmbJType = new Combo(this, SWT.DROP_DOWN);
			FormData fd_cmbJType = new FormData();
			fd_cmbJType.top = new FormAttachment(lblJType, LABEL_SPACE, SWT.BOTTOM);
			fd_cmbJType.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			fd_cmbJType.right = new FormAttachment(lblTitle, 0, SWT.RIGHT);
			cmbJType.setLayoutData(fd_cmbJType);
			cmbJType.setItems(Joints.JOINT_TYPES);
			cmbJType.addKeyListener(keyListener);
			cmbJType.addSelectionListener(new SelectionListener() {

				@Override
				public void widgetSelected(SelectionEvent e) {
					updateDataFields(PluginController.getInstance().getJointDataFields(cmbJType.getText()));
					pack();
				}

				@Override
				public void widgetDefaultSelected(SelectionEvent e) {
					// TODO Auto-generated method stub

				}

			});

		}

		btnComplete = new Button(this, SWT.PUSH);

		btnComplete.addSelectionListener(new SelectionListener() {

			@Override
			public void widgetSelected(SelectionEvent e) {
				btnCompleteClick();
			}

			@Override
			public void widgetDefaultSelected(SelectionEvent e) {
				// not implemented
			}

		});
		changeState(GUIState.STATE_NONE);
		pack();
	}

	/**
	 * Will update the body combo boxes to all current bodies held by the controller
	 */
	public void updateBodies() {
		List<Bodies> listBodies = PluginController.getInstance().getBodies();
		String[] bodies = new String[listBodies.size()];
		for (int i = 0; i < listBodies.size(); i++) {
			bodies[i] = listBodies.get(i).getName();
		}
		updatingBodies = true;
		this.cmbBody1.setItems(bodies);
		this.cmbBody2.setItems(bodies);
		updatingBodies = false;
	}

	/**
	 * Takes a widget and adds it to the Map of required fields
	 * 
	 * @param w - the widget to add to the Map
	 */
	private void addRequiredField(Widget w) {
		synchronized (this) {
			if (requiredFields == null) {
				requiredFields = new HashMap<Widget, Boolean>();
			}
		}
		if (!requiredFields.containsKey(w)) {
			requiredFields.put(w, false);
		}
	}

	/**
	 * Removes a widget from the required fields map
	 * 
	 * @param w - the widget to remove from the map
	 */
	public void removeRequiredField(Widget w) {
		if (requiredFields != null) {
			requiredFields.remove(w);
		}
		// System.out.println("Cannot remove null");
	}

	/**
	 * Removes a widget from the required fields map
	 * 
	 * @param w - the widget to remove from the map
	 */
	public void removeRequiredField(DataComposite dc) {
		if (requiredFields != null) {
			requiredFields.remove(dc.txtX);
			requiredFields.remove(dc.txtY);
			requiredFields.remove(dc.txtZ);
		}
		// System.out.println("Cannot remove null");
	}

	/**
	 * Adds a required Text field to the required fields Map and creates a listener to denote when the field is
	 * complete.
	 * 
	 * Adding a required field means that Widget must be filled in (complete) in order for the complete button to be
	 * activated.
	 * 
	 * @param t - The Text field to add in
	 */
	public void addRequiredField(final Text t) {
		addRequiredField((Widget) t);
		t.addModifyListener(new ModifyListener() {

			@Override
			public void modifyText(ModifyEvent e) {

				requiredFields.put(t, t.getText().length() > 0);
				// System.out.println(t.getText());
				btnComplete.setEnabled(checkRequiredFields());
			}

		});
	}

	/**
	 * Adds a required Combo field to the required fields Map and creates a listener to denote when the field is
	 * complete.
	 * 
	 * Adding a required field means that Widget must be filled in (complete) in order for the complete button to be
	 * activated.
	 * 
	 * @param c - The Combo field to add in
	 */
	public void addRequiredField(final Combo c) {
		addRequiredField((Widget) c);
		c.addModifyListener(new ModifyListener() {

			@Override
			public void modifyText(ModifyEvent e) {
				if (updatingBodies) {
					return;
				}

				requiredFields.put(c, c.getText().length() > 0);
				// System.out.println(c.getText());
				btnComplete.setEnabled(checkRequiredFields());
			}
		});
	}

	/**
	 * Adds a required DataComposite field to the required fields Map and creates a listener to denote when the field is
	 * complete.
	 * 
	 * Adding a required field means that Widget must be filled in (complete) in order for the complete button to be
	 * activated.
	 * 
	 * @param dc - The DataComposite field to add in
	 */
	public void addRequiredField(final DataComposite dc) {
		addRequiredField(dc.txtX);
		addRequiredField(dc.txtY);
		addRequiredField(dc.txtZ);
	}

	/**
	 * Checks all required fields currently added into the requiredFields Map to see if they are either all filled in
	 * (complete).
	 * 
	 * @return - True if ALL fields are complete, False if one or more fields still need completing
	 */
	private boolean checkRequiredFields() {
		boolean retval = true;
		Set<Widget> set = requiredFields.keySet();
		// System.out.println("----------------");
		// System.out.println(set.size());
		for (Widget w : set) {

			if (!requiredFields.get(w)) {
				// System.out.println("Widget " + w + " data " + w.getData());
				retval = false;
				break;
			}
		}
		// System.out.println("----------------");
		return retval;
	}

	/**
	 * Changes the current GUI state
	 * 
	 * See the enum GUIState for a list of all possible states
	 * 
	 * @param state
	 */
	public void changeState(GUIState state) {
		if (currentState != state) {
			txtName.setText("");
		}
		switch (state) {
		case STATE_NONE:

			setAllComponentsVisible(false);

			break;
		case STATE_JOINT_ADD:

			setAllComponentsVisible(true);
			lblTitle.setText("Add Joint");
			btnComplete.setText("Add Joint");
			txtName.setFocus();
			break;
		case STATE_JOINT_VIEW:

			setAllComponentsVisible(true);
			lblTitle.setText("Edit Joint");
			btnComplete.setText("Save Joint");
			break;
		case STATE_BODY_ADD:

			setAllComponentsVisible(false);
			lblTitle.setVisible(true);
			lblName.setVisible(true);
			txtName.setVisible(true);
			lblTitle.setText("Add Body");

			btnComplete.setVisible(true);
			btnComplete.setText("Add Body");
			txtName.setFocus();
			break;
		case STATE_BODY_VIEW:
			setAllComponentsVisible(false);
			lblTitle.setVisible(true);
			lblName.setVisible(true);
			txtName.setVisible(true);
			lblTitle.setText("Edit Body");

			btnComplete.setVisible(true);
			btnComplete.setText("Save Body");
			txtName.setFocus();
			break;
		}
		setBtnCompleteState(state);
		currentState = state;
	}

	/**
	 * Sets the state of the complete button to the state given
	 * 
	 * See the enum GUIState for a list of all possible states
	 * 
	 * @param state
	 */
	private void setBtnCompleteState(GUIState state) {
		FormData fd_btnComplete = new FormData();
		switch (state) {
		case STATE_JOINT_ADD:
		case STATE_JOINT_VIEW:

			addRequiredField(dcOrigin);

			addRequiredField(cmbBody1);
			addRequiredField(cmbBody2);

			addRequiredField(cmbJType);

			if (activeCompositeFields != null && activeCompositeFields.length > 0) {
				fd_btnComplete.top = new FormAttachment(activeCompositeFields[activeCompositeFields.length - 1], FORM_SPACE, SWT.BOTTOM);
			} else {
				fd_btnComplete.top = new FormAttachment(cmbJType, FORM_SPACE, SWT.BOTTOM);
			}
			fd_btnComplete.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			fd_btnComplete.right = new FormAttachment(txtName, 0, SWT.RIGHT);
			btnComplete.setEnabled(checkRequiredFields());
			break;

		case STATE_BODY_ADD:
		case STATE_BODY_VIEW:

			removeRequiredField(dcOrigin);

			removeRequiredField(cmbBody1);
			removeRequiredField(cmbBody2);

			removeRequiredField(cmbJType);

			fd_btnComplete.top = new FormAttachment(txtName, FORM_SPACE, SWT.BOTTOM);
			fd_btnComplete.left = new FormAttachment(lblTitle, 0, SWT.LEFT);
			fd_btnComplete.right = new FormAttachment(txtName, 0, SWT.RIGHT);
			btnComplete.setEnabled(checkRequiredFields());
			break;
		}

		btnComplete.setLayoutData(fd_btnComplete);
		this.layout();

	}

	/**
	 * The event method for when the Complete button is clicked
	 */
	private void btnCompleteClick() {

		PluginController controller = PluginController.getInstance();

		switch (currentState) {
		case STATE_NONE:
			// cannot occur
		case STATE_JOINT_ADD:
			Bodies body1;
			Bodies body2;
			try {
				body1 = controller.getBodies().get(cmbBody1.getSelectionIndex());
				body2 = controller.getBodies().get(cmbBody2.getSelectionIndex());
			} catch (ArrayIndexOutOfBoundsException e) {
				MessageDialog.openWarning(this.getShell(), "Warning", "Both bodies must be selected");
				return;
			}
			String warnings = "The following warnings must be dealt with:\n";
			boolean warning = false;
			if (!dcOrigin.isComplete()) {
				warnings += "\tOrigin must be complete with only numbers\n";
				warning = true;
			}
			if (activeCompositeFields != null) {
				for (DataComposite dc : activeCompositeFields) {
					if (!dc.isComplete()) {
						warnings += "\t" + dc.getName() + " must be complete with only numbers\n";
						warning = true;
					}
				}
			}
			if (warning) {
				MessageDialog.openWarning(this.getShell(), "Warnings", warnings);
				return;
			}
			int length = 0;
			if (activeCompositeFields != null) {
				length += activeCompositeFields.length;
			}
			Point[] dataPoints = new Point[length];
			for (int i = 0; i < dataPoints.length; i++) {
				dataPoints[i] = activeCompositeFields[i].getPoint();
			}
			controller.addJoint(txtName.getText(), body1, body2, cmbJType.getText(), dataPoints, dcOrigin.getPoint());
			break;
		case STATE_JOINT_VIEW:

			break;
		case STATE_BODY_ADD:
			controller.addBody(txtName.getText());
			break;
		case STATE_BODY_VIEW:
			controller.updateCurrentBody(this.txtName.getText());
			break;
		}

	}

	/**
	 * Sets the visibility of all components
	 * 
	 * @param flag - the boolean to denote if the components are visible or not
	 */
	private void setAllComponentsVisible(boolean flag) {
		lblTitle.setVisible(flag);
		lblName.setVisible(flag);
		txtName.setVisible(flag);
		dcOrigin.setVisible(flag);
		lblBody1.setVisible(flag);
		lblBody2.setVisible(flag);
		cmbBody1.setVisible(flag);
		cmbBody2.setVisible(flag);
		lblJType.setVisible(flag);
		cmbJType.setVisible(flag);
		btnComplete.setVisible(flag);
		if (activeCompositeFields != null) {
			for (int i = 0; i < activeCompositeFields.length; i++) {
				activeCompositeFields[i].setVisible(flag);
			}
		}
	}

	/**
	 * Sets the value of the three text's that denote the origin value to the given x,y,z parameters
	 * 
	 * @param x - the x value of the origin
	 * @param y - the y value of the origin
	 * @param z - the z value of the origin
	 */
	public void setOrigin(double x, double y, double z) {
		dcOrigin.setPoint(x, y, z);
	}

	/**
	 * Sets the currently displayed origin
	 * 
	 * @param p
	 */
	public void setOrigin(Point p) {
		dcOrigin.setPoint(p.getX(), p.getY(), p.getZ());
	}

	/**
	 * Sets the name text that resides in the name box
	 * 
	 * @param name
	 */
	public void setName(String name) {
		this.txtName.setText(name);
	}

	/**
	 * 
	 * @param jType
	 */
	public void setJType(String jType) {
		this.cmbJType.select(cmbJType.indexOf(jType));
		updateDataFields(PluginController.getInstance().getJointDataFields(cmbJType.getText()));
	}

	public void setBody1(String b1Name) {
		this.cmbBody1.select(cmbBody1.indexOf(b1Name));
	}

	public void setBody2(String b2Name) {
		this.cmbBody2.select(cmbBody2.indexOf(b2Name));
	}

	public void setDataPoints(Point[] dataPoints) {
		if (activeCompositeFields != null) {
			for (int i = 0; i < activeCompositeFields.length; i++) {
				activeCompositeFields[i].setPoint(dataPoints[i].getX(), dataPoints[i].getY(), dataPoints[i].getZ());
			}
		}
	}

	/**
	 * 
	 * @return
	 */
	public Point getOriginPoint() {
		return dcOrigin.getPoint();
	}

	/**
	 * 
	 * @param fields
	 */
	private void updateDataFields(String[] fields) {
		if (activeCompositeFields != null) {
			for (int i = 0; i < activeCompositeFields.length; i++) {
				removeRequiredField(activeCompositeFields[i]);
				activeCompositeFields[i].dispose();
			}
		}
		activeCompositeFields = new DataComposite[fields.length];
		for (int i = 0; i < fields.length; i++) {
			activeCompositeFields[i] = new DataComposite(fields[i], this, SWT.NONE);
			addRequiredField(activeCompositeFields[i]);
			FormData fd = new FormData();
			if (i == 0) {
				fd.top = new FormAttachment(cmbJType, FORM_SPACE, SWT.BOTTOM);
			} else {
				fd.top = new FormAttachment(activeCompositeFields[i - 1], FORM_SPACE, SWT.BOTTOM);
			}
			fd.left = new FormAttachment(0, LEFT_INDENT);
			fd.right = new FormAttachment(lblTitle, 0, SWT.RIGHT);
			activeCompositeFields[i].setLayoutData(fd);
		}
		setBtnCompleteState(currentState);
		this.redraw();
		this.update();
		this.layout(true);
		this.redraw();
		layout();
	}

	/**
	 * Data composite class Representing a composite that contains input fields for users to enter in Point data.
	 * 
	 * @author chancea
	 * 
	 */
	private class DataComposite extends Composite {

		/**
		 * The group composite to hold all of the data. The group composite also displays the name of this composite.
		 */
		private Group group;

		/**
		 * The Three texts denoting the x, y, and z points for the user to input values into
		 */
		/**************************************************/
		private Text txtX;
		private Text txtY;
		private Text txtZ;
		/**************************************************/

		/**
		 * The Three labels denoting the x, y, and z points
		 */
		/**************************************************/
		private Label lblX;
		private Label lblY;
		private Label lblZ;

		/**************************************************/

		/**
		 * Constructor - takes in a display name that will be shown above the fields, and a parent and style as all
		 * composites.
		 * 
		 * @param displayName - The name to be displayed above the fields
		 * @param parent - The composite that this class will be contained within.
		 * @param style - Not used in this composite
		 */
		public DataComposite(String displayName, Composite parent, int style) {
			super(parent, style);
			this.setSize(250, 100);
			this.setLayout(new FormLayout());

			{ // Labels
				// Create the label for the x text
				lblX = new Label(this, SWT.NONE);
				FormData fd_lblX = new FormData();
				fd_lblX.top = new FormAttachment(0, TOP_INDENT + LABEL_SPACE);
				fd_lblX.left = new FormAttachment(0, TXT_FIELD_LENGTH / 6);
				lblX.setText("x");
				lblX.setLayoutData(fd_lblX);

				// Create the label for the y text
				lblY = new Label(this, SWT.NONE);
				FormData fd_lblY = new FormData();
				fd_lblY.top = new FormAttachment(lblX, 0, SWT.TOP);
				fd_lblY.left = new FormAttachment(lblX, TXT_FIELD_LENGTH / 3, SWT.LEFT);
				lblY.setText("y");
				lblY.setLayoutData(fd_lblY);

				// Create the label for the z text
				lblZ = new Label(this, SWT.NONE);
				FormData fd_lblZ = new FormData();
				fd_lblZ.top = new FormAttachment(lblX, 0, SWT.TOP);
				fd_lblZ.left = new FormAttachment(lblY, TXT_FIELD_LENGTH / 3, SWT.LEFT);
				lblZ.setText("z");
				lblZ.setLayoutData(fd_lblZ);
			}
			{ // Text Boxes
				// Create the x text
				txtX = new Text(this, SWT.BORDER);
				FormData fd_txtX = new FormData();
				fd_txtX.top = new FormAttachment(lblX, LABEL_SPACE / 2, SWT.BOTTOM);
				fd_txtX.right = new FormAttachment(0, TXT_FIELD_LENGTH / 3);
				fd_txtX.left = new FormAttachment(txtX, LABEL_SPACE, SWT.LEFT);
				txtX.setLayoutData(fd_txtX);
				txtX.addKeyListener(keyListener);

				// Create the y text
				txtY = new Text(this, SWT.BORDER);
				FormData fd_txtY = new FormData();
				fd_txtY.top = new FormAttachment(txtX, 0, SWT.TOP);
				fd_txtY.right = new FormAttachment(txtX, TXT_FIELD_LENGTH / 3, SWT.RIGHT);
				fd_txtY.left = new FormAttachment(txtX, LABEL_SPACE, SWT.RIGHT);
				txtY.setLayoutData(fd_txtY);
				txtY.addKeyListener(keyListener);

				// Create the z text
				txtZ = new Text(this, SWT.BORDER);
				FormData fd_txtZ = new FormData();
				fd_txtZ.top = new FormAttachment(txtX, 0, SWT.TOP);
				fd_txtZ.right = new FormAttachment(txtY, TXT_FIELD_LENGTH / 3, SWT.RIGHT);
				fd_txtZ.left = new FormAttachment(txtY, LABEL_SPACE, SWT.RIGHT);
				txtZ.setLayoutData(fd_txtZ);
				txtZ.addKeyListener(keyListener);
			}

			group = new Group(this, SWT.SHADOW_ETCHED_IN);
			group.setText(displayName);
			FormData group_fd = new FormData();
			group_fd.top = new FormAttachment(0);
			group_fd.left = new FormAttachment(0);
			group_fd.right = new FormAttachment(100);
			group_fd.bottom = new FormAttachment(100, 0);

			group.setLayoutData(group_fd);
		}

		/**
		 * Gets the Point class version of the data composite
		 * 
		 * @return - The created Point class containing the inputed values
		 */
		public Point getPoint() {
			return new Point(Double.parseDouble(txtX.getText()), Double.parseDouble(txtY.getText()), Double.parseDouble(txtZ.getText()));
		}

		/**
		 * Gets the name of this DataComposite
		 * 
		 * @return - The name associated with the group box of this data composite
		 */
		public String getName() {
			return group.getText();
		}

		/**
		 * Sets the point of the data composite
		 * 
		 * @param x - The x value
		 * @param y - The y value
		 * @param z - The z value
		 */
		public void setPoint(double x, double y, double z) {
			txtX.setText("" + x);
			txtY.setText("" + y);
			txtZ.setText("" + z);
		}

		/**
		 * Checks to see if there are inputed values and if they are only numbers.
		 * 
		 * @return - True if the inputed values are numbers
		 */
		public boolean isComplete() {
			boolean retval = true;
			String x = txtX.getText();
			String y = txtY.getText();
			String z = txtZ.getText();
			try {
				Double.parseDouble(x);
				Double.parseDouble(y);
				Double.parseDouble(z);
			} catch (NumberFormatException e) {
				retval = false;
			}
			return retval;
		}

	}
}
