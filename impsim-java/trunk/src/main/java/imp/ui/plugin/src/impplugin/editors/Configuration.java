package impplugin.editors;

import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.TextAttribute;
import org.eclipse.jface.text.presentation.IPresentationReconciler;
import org.eclipse.jface.text.presentation.PresentationReconciler;
import org.eclipse.jface.text.rules.DefaultDamagerRepairer;
import org.eclipse.jface.text.rules.Token;
import org.eclipse.jface.text.source.ISourceViewer;
import org.eclipse.jface.text.source.SourceViewerConfiguration;

/**
 * 
 * @author zastrowm
 *
 */
public class Configuration extends SourceViewerConfiguration {
	
	private TagScanner tagScanner;
	private Scanner scanner;
	private ColorManager colorManager;

	public Configuration(ColorManager colorManager) {
		this.colorManager = colorManager;
	}
	@Override
	public String[] getConfiguredContentTypes(ISourceViewer sourceViewer) {
		return new String[] {
			IDocument.DEFAULT_CONTENT_TYPE,
			PartitionScanner.IMP_COMMENT,
			PartitionScanner.IMP_TAG };
	}


	protected Scanner getXMLScanner() {
		if (scanner == null) {
			scanner = new Scanner(colorManager);
			scanner.setDefaultReturnToken(
				new Token(
					new TextAttribute(
						colorManager.getColor(ColorConstants.DEFAULT))));
		}
		return scanner;
	}
	protected TagScanner getXMLTagScanner() {
		if (tagScanner == null) {
			tagScanner = new TagScanner(colorManager);
			tagScanner.setDefaultReturnToken(
				new Token(
					new TextAttribute(
						colorManager.getColor(ColorConstants.KEYWORD))));
		}
		return tagScanner;
	}

	@Override
	public IPresentationReconciler getPresentationReconciler(ISourceViewer sourceViewer) {
		PresentationReconciler reconciler = new PresentationReconciler();

		DefaultDamagerRepairer dr =
			new DefaultDamagerRepairer(getXMLTagScanner());
		reconciler.setDamager(dr, PartitionScanner.IMP_TAG);
		reconciler.setRepairer(dr, PartitionScanner.IMP_TAG);

		dr = new DefaultDamagerRepairer(getXMLScanner());
		reconciler.setDamager(dr, IDocument.DEFAULT_CONTENT_TYPE);
		reconciler.setRepairer(dr, IDocument.DEFAULT_CONTENT_TYPE);

		NonRuleBasedDamagerRepairer ndr =
			new NonRuleBasedDamagerRepairer(
				new TextAttribute(
					colorManager.getColor(ColorConstants.COMMENT)));
		reconciler.setDamager(ndr, PartitionScanner.IMP_COMMENT);
		reconciler.setRepairer(ndr, PartitionScanner.IMP_COMMENT);

		return reconciler;
	}

}