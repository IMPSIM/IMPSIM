/**
 * PropertiesView.java
 * 4/29/12
 */
package impplugin.views;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.ViewPart;

/**
 * As of right now this class is unused.  If we ever
 * want to separate the object tree composite from the properties composite
 * this class would be used to hold the properties composite.
 * @author chancea
 * 
 */
public class PropertiesView extends ViewPart {

	@Override
	public void createPartControl(Composite parent) {
		
		new PropertiesComposite(parent, SWT.NONE);
		
	}

	@Override
	public void setFocus() {
		// TODO Auto-generated method stub
		
	}
}
