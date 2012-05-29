package impplugin.Perspectives;

import org.eclipse.ui.IFolderLayout;
import org.eclipse.ui.IPageLayout;
import org.eclipse.ui.IPerspectiveFactory;

/**
 * This is the IMP perspective that combines different type of
 * views related to the Imp plug-in into one perspective/view
 * @author ebertb
 *
 */
public class IMPPerspective implements IPerspectiveFactory {

	
	@Override
	/**
	 * Creates the layout that the perspective uses to
	 * arrange the views
	 */
	public void createInitialLayout(IPageLayout layout) {
		defineActions(layout);
		defineLayout(layout);

	}

	/**
	 * Defines the actions that the perspective will show
	 * @param layout
	 */
	public void defineActions(IPageLayout layout){
		//Add "new wizards"
		layout.addNewWizardShortcut("impplugin.projectWizard.impplugin.projectWizard.ImpProjectNewImpFile");
		layout.addNewWizardShortcut("IMPPlugIn.ProjectWizard");

		//Add "show views"
		layout.addShowViewShortcut(IPageLayout.ID_PROJECT_EXPLORER);
		layout.addShowViewShortcut(IPageLayout.ID_EDITOR_AREA);
		layout.addShowViewShortcut(IPageLayout.ID_PROBLEM_VIEW);
		layout.addShowViewShortcut("IMPPlugIn.CanvasView");
		layout.addShowViewShortcut("IMPPlugIn.OjbectView");
	}

	/**
	 * Adds the views to the perspective in the layout defined
	 * @param layout
	 */
	public void defineLayout(IPageLayout layout){
		String editorArea = layout.getEditorArea();

		IFolderLayout left = layout.createFolder("left", IPageLayout.LEFT, (float) 0.10, editorArea);

		left.addView(IPageLayout.ID_PROJECT_EXPLORER);
		
		IFolderLayout right = layout.createFolder("right", IPageLayout.RIGHT, (float) 0.70, editorArea);
		
		right.addView("IMPPlugIn.OjbectView");
		
		IFolderLayout top = layout.createFolder("top", IPageLayout.TOP, (float) 0.5, editorArea);
		
		top.addView("IMPPlugIn.CanvasView");
		
		IFolderLayout bottom = layout.createFolder("bottom", IPageLayout.BOTTOM, (float) 0.60, editorArea);
		
		bottom.addView(IPageLayout.ID_PROBLEM_VIEW);
	}
}
