package impplugin.editors;

import impplugin.PluginController;

import org.eclipse.core.resources.IFile;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.editors.text.TextEditor;
import org.eclipse.ui.part.FileEditorInput;

/**
 * 
 * @author zastrowm
 *
 */
public class Editor extends TextEditor {

	private ColorManager colorManager;

	public Editor() {
		super();
		colorManager = new ColorManager();
		setSourceViewerConfiguration(new Configuration(colorManager));
		setDocumentProvider(new DocumentProvider());
		System.out.println(getEditorInput());
		
	}
	public void dispose() {
		colorManager.dispose();
		super.dispose();
	}

}
