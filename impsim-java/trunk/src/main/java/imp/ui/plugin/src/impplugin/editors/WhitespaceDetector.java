package impplugin.editors;

import org.eclipse.jface.text.rules.IWhitespaceDetector;

/**
 * Class to define what white space is
 * @author zastrowm
 *
 */
public class WhitespaceDetector implements IWhitespaceDetector {

	@Override
	public boolean isWhitespace(char c) {
		return (c == ' ' || c == '\t');
	}
}
