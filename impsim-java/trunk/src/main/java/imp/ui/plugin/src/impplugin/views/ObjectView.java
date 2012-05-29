/**
 * ObjectView.java
 * 4/29/12
 */
package impplugin.views;

import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.ViewPart;

/**
 * The view in the plugin to show the 
 * Object composite and the Properties composite
 * @author chancea
 * 
 */
public class ObjectView extends ViewPart {

	/**
	 * The percent of the view the object composite view will take up.
	 * 
	 * The Properties composite view will then take up (100 - OBJECT_COMPOSTE_WIDTH_PERCENT)
	 */
	private static final int OBJECT_COMPOSITE_WIDTH_PERCENT = 35;
	
	@Override
	public void createPartControl(Composite parent) {
		
		parent.setLayout(new FormLayout());
		
		ObjectComposite oc = new ObjectComposite(parent, 0);
		FormData fd_oc = new FormData();
		fd_oc.right = new FormAttachment(OBJECT_COMPOSITE_WIDTH_PERCENT,0);
		fd_oc.left = new FormAttachment(0,0);
		fd_oc.top = new FormAttachment(0,0);
		fd_oc.bottom = new FormAttachment(100,0);
		
		oc.setLayoutData(fd_oc);
		
		PropertiesComposite pc = new PropertiesComposite(parent, 0);
		FormData fd_pc = new FormData();
		fd_pc.left = new FormAttachment(OBJECT_COMPOSITE_WIDTH_PERCENT,0);
		fd_pc.right = new FormAttachment(100,0);
		fd_oc.top = new FormAttachment(0,0);
		fd_oc.bottom = new FormAttachment(100,0);
		
		pc.setLayoutData(fd_pc);
		
	}

	@Override
	public void setFocus() {
		// TODO Auto-generated method stub
	}
}
