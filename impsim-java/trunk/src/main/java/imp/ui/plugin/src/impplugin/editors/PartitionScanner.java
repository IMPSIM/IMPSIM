package impplugin.editors;

import org.eclipse.jface.text.rules.*;

/**
 * 
 * @author zastrowm
 *
 */
public class PartitionScanner extends RuleBasedPartitionScanner {
	public final static String IMP_COMMENT = "__xml_comment";
	public final static String IMP_TAG = "__xml_tag";

	public PartitionScanner() {

		IToken commentToken = new Token(IMP_COMMENT);
		IToken tag = new Token(IMP_TAG);

		IPredicateRule[] rules = new IPredicateRule[2];

		rules[0] = new SingleLineRule("##", "\n", commentToken);
		rules[1] = new TagRule(tag);		//kept in so I can analyze what's going on
		//TODO: figure out what's going on 

		setPredicateRules(rules);
	}
}
