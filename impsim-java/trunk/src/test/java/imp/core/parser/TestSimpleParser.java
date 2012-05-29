package imp.core.parser;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import imp.core.commands.Command;
import imp.core.commands.GroundCommand;
import imp.core.commands.JointExpressionCommand;
import imp.core.commands.ModelCommand;
import imp.core.commands.PropertyAssignmentCommand;
import imp.core.commands.expressions.FakeExpressionLiteral;
import imp.core.exceptions.InvalidParameterException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.SelfLoopException;
import imp.core.model.elements.Joint.JVAR;
import imp.core.parser.ErrorLog.ErrorContainer;
import imp.core.structures.Point;

import org.junit.Before;
import org.junit.Test;

/**
 * Test the Parser
 * 
 * @author zastrowm
 * @edit ebertb
 */
@SuppressWarnings("javadoc")
public class TestSimpleParser {

	// variables for testing that the parser actually does what it's supposed to
	private Command expectedCommands[];
	private String codeToRun;

	@Before
	public void setUp() throws NullParameterException, InvalidParameterException, SelfLoopException {
		// These are all of the commands created manually

		// Making the points here so that the lines don't become overly long
		// @formatter:off

		Point p1 = new Point(-2.0, 2.5, 0.0),
					 p2 = new Point(-20.0, 3.5, 0.0),
					 p3 = new Point(0.0, 2.5, 0.5),
					 p4 = new Point(-3.0, 2.5, 1.0);

		this.expectedCommands = new Command[] {
				new GroundCommand("NEWGROUND"),
				new imp.core.commands.joints.CylinderCommand("NCYLINDER", "BODY1", "BODY2", p1, p2, p3),
				new imp.core.commands.joints.RevoluteCommand("PIN", "LINK1", "LINK2", p1, p2, p3, p4),
				imp.core.commands.joints.RevoluteCommand.CreateXPin("PINX", "LNK1", "LNK2", p1, p2, p3),
				imp.core.commands.joints.RevoluteCommand.CreateYPin("PINY", "LNK1", "LNK2", p1, p2, p3),
				imp.core.commands.joints.RevoluteCommand.CreateZPin("PINZ", "LNK1", "LNK2", p1, p2, p3),
				new imp.core.commands.joints.PrismCommand("SLIP", "LNK1", "LNK2", p1, p2, p3),
				imp.core.commands.joints.PrismCommand.CreateXSlide("SLIDE", "LINK1", "LINK2", p1),
				imp.core.commands.joints.PrismCommand.CreateYSlide("SLIDE", "LINK1", "LINK2", p1),
				imp.core.commands.joints.PrismCommand.CreateZSlide("SLIDE", "LINK1", "LINK2", p1),
				new JointExpressionCommand("SLIPZ", JVAR.XDISPLACEMENT, new FakeExpressionLiteral(1.0)),
				new PropertyAssignmentCommand("SLIP", "TEST", new FakeExpressionLiteral(1.0)),
				new ModelCommand("MYMODEL")
		};

		// The same above commands in IMP code
		this.codeToRun = ""
				+ "GROUND = NEWGROUND;"
				+ "Cylinder NCYLINDER BODY1 BODY2 -2.0,2.5,0.0 -20.0,3.5,0.0 0.0,2.5,0.5;"
				+ "Revolute PIN LINK1 LINK2 -2.0,2.5,0.0 -20.0,3.5,0.0 0.0,2.5,0.5 -3.0,2.5,1.0;"
				+ "XPin PINX LNK1 LNK2 -2.0,2.5,0.0 -20.0,3.5,0.0 0.0,2.5,0.5;"
				+ "YPin PINY LNK1 LNK2 -2.0,2.5,0.0 -20.0,3.5,0.0 0.0,2.5,0.5;"
				+ "ZPin PINZ LNK1 LNK2 -2.0,2.5,0.0 -20.0,3.5,0.0 0.0,2.5,0.5;"
				+ "Prism SLIP LNK1 LNK2 -2.0,2.5,0.0 -20.0,3.5,0.0 0.0,2.5,0.5;"
				+ "XSLIDE SLIDE LINK1 LINK2 -2.0,2.5,0.0;"
				+ "YSLIDE SLIDE LINK1 LINK2 -2.0,2.5,0.0;"
				+ "ZSLIDE SLIDE LINK1 LINK2 -2.0,2.5,0.0;"
				+ "SLIPZ.XDISPLACEMENT = 1.0;"
				+ "SLIP[TEST] = 1.0;"
				+ "Model MYMODEL;"
				;
			}

	// @formatter:on

	/**
	 * Test the command parser
	 */
	@Test
	public void testCommandParser() {

		// parse the actual commands
		ParserData parserData = SimpleParser.parse(this.codeToRun);

		// make sure that the sizes of both are the same
		assertEquals(this.expectedCommands.length, parserData.commands.size());

		// If there is a single error, the test failed (i.e. there should be none!)
		// Note however, that we shouldn't get here because if there was an error,
		// that indicates that the command that was supposed to be parsed, was not
		// and thus the lengths above should not match
		for (ErrorContainer ec : parserData.errorLog) {
			System.out.println(ec);
			fail("Errors were encountered while parsing");
		}

		// Verify that every command we parsed is exactly what we expected
		for (int i = 0; i < this.expectedCommands.length; ++i) {
			assertEquals(this.expectedCommands[i], parserData.commands.get(i));
		}
	}

	/**
	 * Test single character variable name
	 */
	@Test
	public void testSingleCharacterVariable() {
		SimpleParser.parse("REVOLUTE (L, L2) = PIN");
	}

	@Test
	public void testModel1() {
		// the following model code should parse without error (do not change the model it is valid)
		//@formatter:off
		codeToRun = "\r\n" + 
				"ZPIN J1 FRAME A 0,0,0 2,0,0 2,0,0;\r\n" + 
				"ZPIN J2 A B 0,1,0 1,1,0 1,1,0;\r\n" + 
				"ZPIN J3 B C 1,1,0 2,1,0 2,1,0;\r\n" + 
				"ZPIN J4 C FRAME 1,0,0 2,0,0 2,0,0;\r\n" + 
				"GROUND = FRAME;\r\n" + 
				"J1.Theta = ticks() * 0.0174532925;\r\n" + 
				"J2.Theta = ticks() * -0.0174532925;\r\n" + 
				"\r\n" + 
				"\r\n" + 
				"CAMERA[UP] = {0,1,0};\r\n" + 
				"CAMERA[LOCATION] = {0,0,10};\r\n" + 
				"CAMERA[DIRECTION] = {0,0,-1};\n";
		//@formatter:on

		ParserData parserData = SimpleParser.parse(this.codeToRun);
		if (parserData.hasErrors()) {
			fail("The parser had errors");
		}
	}

	@Test
	public void testModel2() {
		// the following model code should parse without error (do not change the model it is valid)
		//@formatter:off
		codeToRun = "ZPIN J1 FRAME A 0,0,0 2,0,0 2,0,0;\r\n" + 
				"ZPIN J2 A B 0,1,0 2,0,0 0,-2,0;\r\n" + 
				"ZPIN J3 B C 1,1,0 -2,0,0 0,1,0;\r\n" + 
				"ZPIN J4 C FRAME 1,0,0 0,1,0 2,0,0;\r\n" + 
				"GROUND = FRAME;\r\n" + 
				"J1.Theta = ticks() * 0.0174532925;\r\n" + 
				"J2.Theta = ticks() * -0.0174532925;\r\n" + 
				"\r\n" + 
				"#sets J1 to be drawn using the model on the file system\r\n" + 
				"J1[OBJ_FILE] = \"resources/models/4-bar.obj\"; \r\n" + 
				"#sets J1 to be drawn using the model on the file system\r\n" + 
				"J2[OBJ_FILE] = \"resources/models/4-bar.obj\"; \r\n" + 
				"#sets J3 to not be drawn\r\n" + 
				"J3[OBJ_FILE] = \"resources/models/4-bar.obj\";\r\n" + 
				"\r\n" + 
				"CAMERA[UP] = {0,1,0};\r\n" + 
				"CAMERA[LOCATION] = {0,0,10};\r\n" + 
				"CAMERA[DIRECTION] = {0,0,-1};\n";
		//@formatter:on

		ParserData parserData = SimpleParser.parse(this.codeToRun);
		if (parserData.hasErrors()) {
			fail("The parser had errors");
		}
	}
	
	@Test
	public void testModel3(){
		//This Model should run fine.  Even if it looks all messed up.  (Don't Change it)
		//@formatter:off
		codeToRun = "MODEL M4;\r\n" +

		
		"XSLIDE P Three G 4,0,0;\r\n" +
		"GROUND = G;\r\n" +
		"#This sets up the camera so the view is correct\r\n" +
		"CAMERA[UP] = {0,1,0};\r\n" +
		"CAMERA[LOCATION] = {0,0,40};\r\n" +
		"\r\n" +
		"R1.Theta = ticks() * -0.0174532925;\r\n" +
		"\r\n" +
		"CAMERA[DIRECTION] = {0,0,-1};\n" +
		"ZPIN R1 G One 0,0,0 10,0,0 0,3,0;\r\n" +
		"ZPIN R2 One Two 0,3,0 0,0,0 4,0,0;\r\n" +
		"ZPIN R3 Two Three 4,0,0 0,3,0 10,0,0;\r\n";
		//@formatter:on		
		
		ParserData parserData = SimpleParser.parse(this.codeToRun);
		if (parserData.hasErrors()) {
			fail("The parser had errors");
		}
	}
	
	@Test
	public void testModel4(){
		
		//@formatter:off
		codeToRun = "MODEL M5;\r\n" +
		"\r\n" +
		"ZPIN A _ground AB 0,0,0 10,0,0 10,5,0;\r\n" +
		"ZPIN B AB BD 10,5,0 0,0,0 7,12.5,0;\r\n" +
		"ZPIN D2 BD DD 0,30,0 10,5,0 0,40,0;\r\n" +
		"YSLIDE D DD _ground 0,30,0;\r\n" +
		"ZPIN F _ground FE -20,20,0 -10,20,0 -8,24,0;\r\n" +
		"ZPIN E FE HE -8,24,0 -20,20,0 -14,8,0;\r\n" +
		"ZPIN H HE FH -14,8,0 -8,24,0 -20,20,0;\r\n" +
		"ZPIN F2 FH _ground -20,20,0 -14,8,0 -10,20,0;\r\n" +
		"ZPIN H2 HE HI -14,8,0 -8,24,0 7,12.5,0;\r\n" +
		"ZPIN I HI BD 7,12.5,0 -14,8,0 0,30,0;\r\n" +
		"ZPIN G2 ED GG 0,36,0 -8,24,0 0,50,0;\r\n" +
		"ZPIN E2 FE ED -8,24,0 0,36,0 -20,20,0;\r\n" +
		"YSLIDE G GG _ground 0,36,0;\r\n" +
		"\r\n" +
		"GROUND = _ground;\r\n" +
		"\r\n" +
		"A.Theta = ticks() * -0.0174532925;\r\n" +
		"\r\n" +
		"CAMERA[UP] = {0,1,0};\r\n" +
		"CAMERA[LOCATION] = {-10,0,100};\r\n" +
		"CAMERA[DIRECTION] = {0,0,-1};\r\n";
		//@formatter:on
	
	ParserData parserData = SimpleParser.parse(this.codeToRun);
	if (parserData.hasErrors()) {
		fail("The parser had errors");
	}
	}
}
