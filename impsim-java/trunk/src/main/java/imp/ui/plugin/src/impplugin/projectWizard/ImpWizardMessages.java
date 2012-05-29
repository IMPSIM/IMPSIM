package impplugin.projectWizard;

import org.eclipse.osgi.util.NLS;


/**
 * This class externalizes the strings in the wizards.
 * @author ebertb
 *
 */
public class ImpWizardMessages extends NLS {
	private static final String BUNDLE_NAME = "impplugin.projectWizard.messages"; //$NON-NLS-1$
	public static String NewImpProject_Create_new_Imp_Project;
	public static String NewImpProject_New_Imp_Project;
	public static String NewImpFile_New_Imp_File;
	public static String NewImpFile_Create_new_Imp_File;
	public static String NewImpFile_New_Imp_File_Initial_Content;
	
	
	static {
		// initialize resource bundle
		NLS.initializeMessages(BUNDLE_NAME, ImpWizardMessages.class);
	}

	private ImpWizardMessages() {
	}
}
