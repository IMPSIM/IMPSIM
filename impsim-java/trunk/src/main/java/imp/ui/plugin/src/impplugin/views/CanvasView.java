/**
 * CanvasView.java
 * 4/29/12
 */
package impplugin.views;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.ViewPart;

/**
 * This is the canvas view that extends ViewPart.
 * The canvas view creates the CanvasComposite and hands it
 * off to the parent composite the plugin gave this class.
 * @author chancea
 *
 */
public class CanvasView extends ViewPart {

	
	@Override
	public void createPartControl(Composite parent) {
		
		//Create the new CanvasComposite and
		//hand it off to the parent
		new CanvasComposite(parent,SWT.NONE);
	 }

	@Override
	public void setFocus() {
		// TODO Auto-generated method stub
		
	}
}
