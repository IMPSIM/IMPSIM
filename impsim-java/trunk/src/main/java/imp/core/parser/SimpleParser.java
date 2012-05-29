/**
 * SimpleParser.java
 * May 12, 2011
 */
package imp.core.parser;

import imp.core.exceptions.NullParameterException;
import imp.core.parser.impLexer;
import imp.core.parser.impParser;
import imp.core.parser.impParser.commands_return;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CharStream;
import org.antlr.runtime.CommonTokenStream;
import org.antlr.runtime.RecognitionException;
import org.antlr.runtime.Token;
import org.antlr.runtime.TokenStream;
import org.antlr.runtime.tree.CommonTree;
import org.antlr.runtime.tree.CommonTreeAdaptor;

/**
 * Class to parse the IMP language into IMP Commands.
 * 
 * @author zastrowm
 * @review edmissonj
 * @edit dykstran Updated JavaDoc
 * @edit zastrowm converted to static class, updated with new Parsing Method
 * @version 1.1
 * 
 */
public class SimpleParser {

	
	/**
	 * No one can create!
	 */
	private SimpleParser() {
		
	}

	/**
	 * Parse all of the IMPCommands in a string.
	 * 
	 * @param strCommands The commands to parse.
	 * @return A list of commands that have been parsed.
	 */
	public static ParserData parse(String strCommands) {
		//strCommands = strCommands.toUpperCase() + "\r\n";
		strCommands = convertToCommonCase(strCommands) + "\r\n";

		// set up the lexer/parser to accept strings:
		CharStream characterStream = new ANTLRStringStream(strCommands);
		impLexer lexer = new impLexer(characterStream);
		TokenStream tokenStream = new CommonTokenStream(lexer);
		impParser parser = new impParser(tokenStream);

		// actually try to parse the text:
		try {
			parser.setTreeAdaptor(adaptor);
			commands_return ret = parser.commands();
			return ret.value;
			
		} catch (RecognitionException e) {
			e.printStackTrace();
			return null;
		}
		
	}

	/**
	 * Parse a file containing IMP Commands.
	 * 
	 * @param file The file to parse.
	 * @return A list of commands that have been parsed.
	 * @throws FileNotFoundException Thrown if the file cannot be found.
	 */
	public static ParserData parseFile(File file) throws FileNotFoundException {
		String contents = "";

		Scanner reader = new Scanner(file);
		while (reader.hasNextLine()) {
			contents += reader.nextLine() + "\r\n";
		}

		return parse(contents);
	}

	/**
	 * Parse a file containing IMP Commands.
	 * 
	 * @param filename The name of the file to parse
	 * @return A list of commands that have been parsed
	 * @throws FileNotFoundException Thrown if the file cannot be found.
	 * @note This is a convenience method alternative to parseFile(File).
	 */
	public static ParserData parseFile(String filename) throws FileNotFoundException {
		return parseFile(new File(filename));
	}


	/**
	 * Convert text to upper case, except for quoted strings. For example, it will convert ABCdef"gHiJk"LMnop to
	 * ABCDEF"gHiJk"LMNOP
	 * 
	 * @param text The text to convert.
	 * @return The text in upper case, except for quoted strings.
	 */
	/*package*/ static String convertToCommonCase(String text) {

		NullParameterException.check(text, "text", 0);

		StringBuffer newText = new StringBuffer(text.length() + 1);

		/*
		 * Regular expression to look for the end of a string. Characters such as newlines and quotations are escaped
		 * with a preceding `, otherwise it looks for the end quotation
		 */
		Pattern regexEndOfString = Pattern.compile("(([^\\`\\\"])|(`.))*");

		int indexStart = 0;
		int indexEnd = 0;

		/*
		 * This loop goes through the string looking for quotes (ie strings), so that it doesn't uppercase the strings.
		 * Everything else is turned into uppercase
		 */
		while ((indexEnd = text.indexOf("\"", indexStart)) > 0) {
			newText.append(text.substring(indexStart, indexEnd).toUpperCase());

			// move past the quotation marK:
			indexStart = indexEnd + 1;

			// look for the end of the string
			Matcher matches = regexEndOfString.matcher(text.substring(indexStart));

			// if we don't find a match, leave the loop
			if (!matches.find()) {
				break;
			}

			// add the end quote to the string
			newText.append('"');

			// get the offset for .substring()
			indexEnd = indexStart + matches.group(0).length();
			newText.append(text.substring(indexStart, indexEnd));

			// get past the quotation
			indexStart = indexEnd + 1;

			// we should only append a quote if there is a quote coming up
			if (text.indexOf("\"", indexStart - 1) > 0) {
				newText.append('"');
			}
			// add the end quote

		}

		// add whatever part of the string is remaining
		if (indexStart >= 0 && indexStart < text.length()) {

			newText.append(text.substring(indexStart).toUpperCase());
		}

		return newText.toString();

	}

	/**
	 * Adapter for parsing.
	 */
	static final CommonTreeAdaptor adaptor = new CommonTreeAdaptor() {
		@Override
		public Object create(Token payload) {
			return new CommonTree(payload);
		}
	};

}
