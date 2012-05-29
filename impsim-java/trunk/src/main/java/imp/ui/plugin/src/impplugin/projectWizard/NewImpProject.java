package impplugin.projectWizard;

import java.net.URI;


import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IConfigurationElement;
import org.eclipse.core.runtime.IExecutableExtension;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.dialogs.WizardNewProjectCreationPage;
import org.eclipse.ui.wizards.newresource.BasicNewProjectResourceWizard;

/**
 * Class creates a wizard for creating a new IMP project
 * @author ebertb
 */
public class NewImpProject extends Wizard implements INewWizard, IExecutableExtension {

	private WizardNewProjectCreationPage _pageOne;
	
	private static final String PAGE_NAME = "New IMP Project Wizard"; //$NON-NLS-1$
	private static final String WIZARD_NAME = "IMP Project"; //$NON-NLS-1$
	private IConfigurationElement _configurationElement;
	
	/**
	 * Constructor for Wizard
	 */
	public NewImpProject() {
		setWindowTitle(WIZARD_NAME);
	}

	@Override
	public void init(IWorkbench workbench, IStructuredSelection selection) {
		// TODO Auto-generated method stub

	}

	/**
	 * Performs final actions when the user clicks finish
	 */
	@Override
	public boolean performFinish() {
		String name = _pageOne.getProjectName();
		URI location = null;
		if(!_pageOne.useDefaults()){
			location = _pageOne.getLocationURI();
			System.err.println("location: " + location.toString());
		}
		
		ImpPluginSupport.createProject(name, location);
		BasicNewProjectResourceWizard.updatePerspective(_configurationElement);
		
		
		return true;
	}
	
	/**
	 * adds a page to the wizard
	 */
	@Override
	public void addPages() {
		super.addPages();
		 
		_pageOne = new WizardNewProjectCreationPage(PAGE_NAME);
		_pageOne.setTitle(ImpWizardMessages.NewImpProject_New_Imp_Project);
		_pageOne.setDescription(ImpWizardMessages.NewImpProject_Create_new_Imp_Project);
		 
	    addPage(_pageOne);
	}

	/**
	 * initializes data to configure 
	 */
	@Override
	public void setInitializationData(IConfigurationElement config,
			String propertyName, Object data) throws CoreException {
		_configurationElement = config;
		
	}

}
