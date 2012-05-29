grammar imp;

options {
	language = Java;
	output = AST;
}

tokens {
	NSET;
	T_STATEMENT;
	T_JOINTDECLERATION;
	T_PROPERTYASS;
	T_ASSIGNMENT;
	T_LITNUM;
	T_LITSTR;
	T_FUNCCALL;
	T_NAMESPACE;
	T_EXPRESSION; 
	T_LITERAL;
	T_VAR;
}

@header { 
	package imp.core.parser;

	import java.util.LinkedList;
	import java.util.ArrayList;

	import imp.core.commands.*;
	import imp.core.commands.data.*;
	import imp.core.commands.definition.*;
	import imp.core.structures.*;
	import imp.core.commands.expressions.*;
	import imp.core.parser.*;
	import imp.core.exceptions.*;
	import org.antlr.tool.Message;
	import imp.core.model.elements.Joint.JVAR;
	import org.apache.commons.lang3.ArrayUtils;
}

@lexer::header { 
  package imp.core.parser;
}

@members
{
	public ParserData parserData = new ParserData();

	public ErrorLog errors = parserData.errorLog;  
    
    public void displayRecognitionError(String[] tokenNames, RecognitionException e) {
    	errors.add(new ParserRecognitionError(tokenNames,e), e.token);
    }
    
}

/* Basic stuff & literals */

name returns [String value]:
	theName=NAME
		{$value = $theName.text;}
	;

numeric_set returns [Point value]:
	(num1=literalNumber ',' num2=literalNumber ',' num3=literalNumber)
		{$value = new Point($num1.value, $num2.value, $num3.value); }
	| NONE
		{$value = new Point(0,0,0); }
	;

literalNumber returns [double value]:
	num=NUMBER
		{ $value = Double.parseDouble($num.text);}
	;

literalString returns [String value]:
	val=STRING
		{ String string = $val.text;  $value = string.substring(1,string.length() - 1); }
	;

literalPoint returns [Point value]:
	LBRAQ point=numeric_set RBRAQ
		{ $value = $point.value; }
	;

literalExpression returns [FakeExpression value]:
	litNum=literalNumber
		{$value = new FakeExpressionLiteral($litNum.value);}
	| litStr=literalString
		{$value = new FakeExpressionLiteral($litStr.value);}
	| litPoint=literalPoint
		{$value = new FakeExpressionLiteral($literalPoint.value);}
	;

expression_primary returns [FakeExpression value]:
	nm=name
		{$value = new Variable($nm.text); }
	| lit=literalExpression
		{$value = $lit.value;}
	| func=expression_function
		{$value = $func.value;}
	|  (LPAREN exp=expression RPAREN)
		{$value = $exp.value;}
	;  

expression_signed returns [FakeExpression value]:
	(type=MINUS | type=PLUS)? exp=expression_primary
		{
			if ($type != null) {
				if ($type.type == PLUS) {
					$value = new Function("","-", $exp.value);
				} else {
					$value = new Function("","+", $exp.value);
				}				
			} else {
				$value = $exp.value;
			} 
		}
	;

/* Expressions */

namespaceQualifier returns [String value]:
	names=(name '~')+
		{$value = $names.text;}
	;

expression_function returns [FakeExpression value]:
		{ LinkedList<FakeExpression> expressions = new LinkedList<FakeExpression>();  }
	ns=namespaceQualifier? nm=name LPAREN (exp=expression { expressions.add($exp.value); } (',' exp=expression { expressions.add($exp.value); })*)? RPAREN
		{	$value = new Function($ns.value != null ? $ns.value : "", $nm.value, expressions);}
	;

expression_power returns [FakeExpression value]:
		{ LinkedList<FakeExpression> expressions = new LinkedList<FakeExpression>();  }
	exp=expression_signed {expressions.add($exp.value);} (( type=POWER ) exp=expression_signed {expressions.add($exp.value);})*
		{$value = Function.convertToBinaryExpression("","^",expressions);}
	;

expression_mult returns [FakeExpression value]:
		{ LinkedList<FakeExpression> expressions = new LinkedList<FakeExpression>();  }
	exp=expression_power {expressions.add($exp.value);}  (( type=TIMES | type=DIVIDE | type=MOD ) exp=expression_power{expressions.add($exp.value);} )*
		{ $value = Function.convertToBinaryExpression("",$type.text,expressions);}
	;

expression returns [FakeExpression value]:
		{ LinkedList<FakeExpression> expressions = new LinkedList<FakeExpression>();  }
	exp=expression_mult {expressions.add($exp.value);}  (( type=PLUS | type=MINUS) exp=expression_mult{expressions.add($exp.value);} )*
		{ $value = Function.convertToBinaryExpression("",$type.text,expressions);}
	;	

/* Assignment */

commandPropertyAssignment returns [Command value]:
	nm=name '[' prop=name ']' EQUALS exp=expression
		{$value=new PropertyAssignmentCommand($nm.value,$prop.value, $exp.value);}
	;

commandVariableAssignment returns [Command value]:
	nm=name EQUALS exp=expression
		{$value = new VariableAssignmentCommand($nm.value, $exp.value); }
	;

commandJointExpression returns [Command value]:
	nm=name '.' type=('XDISPLACEMENT' | 'YDISPLACEMENT' | 'ZDISPLACEMENT' | 'THETA' | 'PHI' | 'PSI') EQUALS exp=expression
		{ $value = new JointExpressionCommand($name.value, JVAR.fromString($type.text), $exp.value);}	
	; 

/* Individual declaration statements */

commandGround returns [Command value]:
	GROUND EQUALS nm=name
		{$value = new GroundCommand($nm.value);}
	;
	
commandJoint returns [Command value]:
	{Object[] datas = new Object[0]; }
	jointType=name jointName=name body1=name body2=name ((data=numeric_set|literalNumber){datas = ArrayUtils.addAll(datas, $data.value);})+
		{
			try { $value= imp.core.commands.DynamicJointBuilder.createInstance($jointType.text, $jointName.text, $body1.text, $body2.text, datas); }
			catch(Exception exc) { errors.add(new WrappedException(exc), $commandJoint.start, $commandJoint.start); }
		}
			
	;

commandModel returns [Command value]:
	'MODEL' modelName=name
		{ $value = new imp.core.commands.ModelCommand($modelName.value); }
	;

command returns [Command value]:
	commandJoint {$value = $commandJoint.value; }
	| commandGround {$value = $commandGround.value; }
	| commandPropertyAssignment {$value = $commandPropertyAssignment.value; }
	| commandVariableAssignment {$value = $commandVariableAssignment.value; }
	| commandJointExpression {$value = $commandJointExpression.value; }
	| commandModel {$value = $commandModel.value; }
	;

commands returns [ParserData value]:
	 (command ';'	{ parserData.add($command.value, $command.start, $command.stop); })+
		{ $value = parserData; }
	;


fragment DIGITS : ('0'..'9')+;
NUMBER : '-' ? DIGITS ('.' DIGITS)? ('E' ('+' | '-') ? DIGITS)?;

PLUS  : '+';
MINUS : '-';
TIMES : '*';
DIVIDE  : '/';
MOD   : '%';
POWER : '^';
LPAREN  : '(';
RPAREN  : ')';
COMMA	: ',';

LBRAQ : '{';
RBRAQ : '}';

EQUALS : '=';
DATA : 'DATA';

POINT :		'POINT';
GRAVITY :	'GRAVITY';
DENSITY :	'DENSITY';
MASS :		'MASS';
INERTIA :	'INERTIA';
SPRING :	'SPRING';
DAMPER :	'DAMPER';
FORCE :		'FORCE';
TORQUE :	'TORQUE';
CONTACT :	'CONTACT';
POSITION :	'POSITION';
VELOCITY :	'VELOCITY';
MOTION :	'MOTION';
IC :		'IC';

GROUND:		'GROUND';

LINK :		'LINK';
NONE :		'NONE';
COLON : 	':';
SEMICOLON :	';';

NAME : FRAG_LETTER (FRAG_LETTER | FRAG_NUMBER) * ;
fragment FRAG_LETTER : ('_' | ('A' .. 'Z'));
fragment FRAG_NUMBER : ('0' .. '9');

STRING : '"' (~('`'|'\n'|'\r'|'"')|('`' ('n' | 'r' | '"' | '`')))* '"';

// ignore white space - gonna have to tackle the continuation character $
WS : (' ' | '\t' | '\r' |  '\n') {$channel = HIDDEN;};

// #this is a comment
COMMENT : ('#' (~'\n')*) {$channel = HIDDEN;};
