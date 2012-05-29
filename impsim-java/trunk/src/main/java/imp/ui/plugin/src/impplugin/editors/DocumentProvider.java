package impplugin.editors;

import impplugin.PluginController;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.IDocumentPartitioner;
import org.eclipse.jface.text.rules.FastPartitioner;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.editors.text.FileDocumentProvider;

/**
 * 
 * @author zastrowm
 *
 */
public class DocumentProvider extends FileDocumentProvider {

	protected IDocument createDocument(Object element) throws CoreException {
		IDocument document = super.createDocument(element);
		if (document != null) {
			IDocumentPartitioner partitioner =
				new FastPartitioner(
					new PartitionScanner(),
					new String[] {
						PartitionScanner.IMP_TAG,
						PartitionScanner.IMP_COMMENT });
			partitioner.connect(document);
			document.setDocumentPartitioner(partitioner);
		}
		if (element instanceof IFileEditorInput) { 
			IFile file = ((IFileEditorInput) element).getFile(); 
			PluginController.getInstance().addIFile(file);
		}
		return document;
	}
}