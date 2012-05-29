/**
 *	ParserData.java part of IMP
 *	May 8, 2011
 */
package imp.core.parser;

import imp.core.commands.Command;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.antlr.runtime.Token;

// TODO: Auto-generated Javadoc
/**
 * Class to contain all the data returned by the parser.
 * 
 * @author zastrowm
 * @version 2.0
 */
public class ParserData {

	/** The error log. */
	public final ErrorLog errorLog = new ErrorLog();

	/** The commands. */
	public final List<Command> commands = new ArrayList<Command>();

	/** The debug info. */
	public final HashMap<Command, Location> debugInfo = new HashMap<Command, Location>();

	/**
	 * Adds a command to the Parser data, saving the debug info as well
	 * 
	 * @param command the command the command to add
	 * @param start the start token from the parser
	 * @param end the end token from the parser
	 */
	public void add(Command command, Token start, Token end) {
		commands.add(command);
		debugInfo.put(command, new Location(start, end));
	}

	/**
	 * Lookup the location where a command is created
	 * 
	 * @param command the command the look up
	 * @return the location of the command in source code, or null if the command does not exist
	 */
	public Location lookup(Command command) {
		if (this.debugInfo.containsKey(command)) {
			return (debugInfo.get(command));
		} else {
			return null;
		}
	}

	/**
	 * Return true if there were any errors
	 * 
	 * @return true if there are errors
	 */
	public boolean hasErrors() {
		return !this.errorLog.errors.isEmpty();
	}

	/**
	 * The location of a command in the parser
	 */
	public static class Location {

		/**
		 * The token to start this location at.
		 */
		public final Token start;

		/**
		 * The token to end this location at.
		 */
		public final Token end;

		/**
		 * Instantiates a new location.
		 * 
		 * @param start the start token
		 * @param end the end the end token
		 */
		public Location(Token start, Token end) {
			this.start = start;
			this.end = end;
		}

	}

}
