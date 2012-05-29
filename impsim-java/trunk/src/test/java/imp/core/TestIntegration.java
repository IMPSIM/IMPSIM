package imp.core;

import imp.core.commands.encapsulation.CommandHolder;
import imp.core.model.Model;
import imp.core.parser.ErrorLog.ErrorContainer;
import imp.core.parser.ParserData;
import imp.core.parser.SimpleParser;

import org.junit.Ignore;
import org.junit.Test;

public class TestIntegration {

	@Test
	public void testIntegration() throws Exception {

		Model model = new Model();
		CommandHolder ch = new CommandHolder(model);

		// @formatter:off
		String impCommands = 
				"ZPIN J1 FRAME A 0,0,0 10,0,0 10,0,0;" +
				"ZPIN J2 A B 0,10,0 10,10,0 10,10,0;" +
				"ZPIN J3 B C 10,10,0 20,10,0 20,10,0;" +
				"ZPIN J4 C FRAME 10,0,0 20,0,0 20,0,0;" +

				"GROUND = FRAME;" +

				"J1.Theta = ticks() * 0.0174532925;" +
				"J2.Theta = ticks() * -0.0174532925;";
		// @formatter:on

		ParserData parserData = SimpleParser.parse(impCommands);

		if (parserData.hasErrors()) {
			System.out.println("Errors!");

			for (ErrorContainer ec : parserData.errorLog) {
				System.out.println(ec);
			}

			System.exit(1);
		}

		ch.addCommands(parserData.commands);
		ch.executeCommands();
		ch.compile();
		ch.verifyOrFail();
		ch.run(10, 100);
	}
}
