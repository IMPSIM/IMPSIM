package impplugin.editors;

import org.eclipse.jface.text.TextAttribute;
import org.eclipse.jface.text.rules.EndOfLineRule;
import org.eclipse.jface.text.rules.IRule;
import org.eclipse.jface.text.rules.IWordDetector;
import org.eclipse.jface.text.rules.RuleBasedScanner;
import org.eclipse.jface.text.rules.Token;
import org.eclipse.jface.text.rules.WordRule;
import org.eclipse.swt.SWT;

/**
 * Scanner class - it colors the keywords in the text editor
 * @author zastrowm
 *
 */
public class Scanner extends RuleBasedScanner {

	/**
	 * Constructor.  Sets up all the rules for the editor
	 * @param manager - not sure what this is for, I just use it
	 */
	public Scanner(ColorManager manager) {
		setRules(new IRule[]{
			createKeywordRule(manager),
			createCommentRule(manager)
		});
	}
	
	/**
	 * Create the word that colors keywords
	 * @param manager the manager - not sure what this is for, I just use it like in the SDK
	 * @return the WordRule that we created for keywords
	 */
	private WordRule createKeywordRule(ColorManager manager){
		
		//Uses java style words:
		IWordDetector wordDetector = new IWordDetector() {			
            @Override
			public boolean isWordStart(char c) { 
            	return Character.isJavaIdentifierStart(c); 
            }
            @Override
			public boolean isWordPart(char c) {   
            	return Character.isJavaIdentifierPart(c); 
            };
		};
		
		//make a new word rule which uses java style words, doesn't return a token
		//and is case insensitive
		WordRule keywordRule = new WordRule(wordDetector,Token.UNDEFINED,true);
				
		//All the keywords for the IMP language
		String keywords[] = {
				"DATA" , "REVOLUTE" , "XPIN" , "YPIN" , "ZPIN" , "XSLIDE" , "YSLIDE" ,
				"ZSLIDE" , "PRISM" , "CYLINDER" , "RIGID" , "GEAR" , "RACK" , "SCREW" ,
				"CAM" , "SLOT" , "SPHERE" , "POINT" , "GRAVITY" , "DENSITY" , "MASS" ,
				"INERTIA" , "SPRING" , "DAMPER" , "FORCE" , "TORQUE" , "CONTACT" , "POSITION" ,
				"VELOCITY" , "MOTION" , "IC" , "LINK" , "NONE"
		};
		
		//The color of each keyword
		Token keyword = new Token(new TextAttribute(manager.getColor(ColorConstants.KEYWORD), null, SWT.BOLD));
		
		//add each word to the list of keywords
		for (int i = 0; i < keywords.length; i++){
			keywordRule.addWord(keywords[i],keyword);
		}
		
		return keywordRule;
	}
	
	/**
	 * The method to highlight the comments
	 * @param manager - THe color manager
	 * @return - the rule for what defines a comment
	 */
	private EndOfLineRule createCommentRule(ColorManager manager)
	{
		//Uses java style words:
		Token comment = new Token(new TextAttribute(manager.getColor(ColorConstants.COMMENT)));
		EndOfLineRule commentDetector = new EndOfLineRule("#", comment);
		return commentDetector;
	}
}
