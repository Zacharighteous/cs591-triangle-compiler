#ifndef _Parser
#define _Parser

#include <cstdio>
#include <vector>
#include "SourcePosition.h"
#include "SourceFile.h"
#include "Token.h"
#include "Scanner.h"
#include "ErrorReporter.h"
#include "import_headers.h"

#include <string>
using namespace std;


class Parser {

  Scanner* lexicalAnalyser;
  ErrorReporter* errorReporter;
  Token* currentToken;
  SourcePosition* previousTokenPosition;

public:
  
  Parser(Scanner* lexer, ErrorReporter* reporter);
  Program* parseProgram();
  
  void start(SourcePosition* position) ;
  void finish(SourcePosition* position);
  void acceptIt();
  bool check(int tokenExpected);


//Below are the methods that throw SyntaxError exception in Java

  void accept (int tokenExpected);
  void syntacticError(string messageTemplate, string tokenQuoted);
  IntegerLiteral* parseIntegerLiteral();
  CharacterLiteral* parseCharacterLiteral();
  StringLiteral* parseStringLiteral();
  Identifier* parseIdentifier();
  Identifier* parsePackageIdentifier(Identifier *I);
  Operator* parseOperator();
  Command* parseCommand();
  Command* parseSingleCommand();
  Expression* parseExpression();
  Expression* parseSecondaryExpression();
  Expression* parsePrimaryExpression();
  RecordAggregate* parseRecordAggregate();
  ArrayAggregate* parseArrayAggregate();
  Vname* parseVname ();
  Vname* parseRestOfVname(Identifier* identifierAST);
  Declaration* parseDeclaration();
  Declaration* parseSingleDeclaration();
  FormalParameterSequence* parseFormalParameterSequence();
  FormalParameterSequence* parseProperFormalParameterSequence();
  FormalParameter* parseFormalParameter();
  ActualParameterSequence* parseActualParameterSequence();
  ActualParameterSequence* parseProperActualParameterSequence();
  ActualParameter* parseActualParameter();
  TypeDenoter* parseTypeDenoter();
  FieldTypeDenoter* parseFieldTypeDenoter();
};

/*######################################################################################################################*/
/*######################################################################################################################*/
/*######################################################################################################################*/

Parser::Parser(Scanner* lexer, ErrorReporter* reporter) {
    lexicalAnalyser = lexer;
    errorReporter = reporter;
    previousTokenPosition = new SourcePosition();
	}

// accept checks whether the current token matches tokenExpected.
// If so, fetches the next token.
// If not, reports a syntactic error.

void Parser::accept (int tokenExpected) {
	if (currentToken->kind == tokenExpected) {
      previousTokenPosition = currentToken->position;
      currentToken = lexicalAnalyser->scan();
    } else {
		syntacticError("\"%\" expected here", Token::spell(tokenExpected));
    }
  }

void Parser::acceptIt() {
    previousTokenPosition = currentToken->position;
    currentToken = lexicalAnalyser->scan();
  }

bool Parser::check(int tokenExpected) {
  return currentToken->kind == tokenExpected;
}

// start records the position of the start of a phrase.
// This is defined to be the position of the first
// character of the first token of the phrase.

void Parser::start(SourcePosition* position) {
    position->start = currentToken->position->start;
  }

// finish records the position of the end of a phrase.
// This is defined to be the position of the last
// character of the last token of the phrase.

void Parser::finish(SourcePosition* position) {
    position->finish = previousTokenPosition->finish;
  }

void Parser::syntacticError(string messageTemplate, string tokenQuoted){
    SourcePosition* pos = currentToken->position;
	errorReporter->reportError(messageTemplate,tokenQuoted,pos);
    exit(1);
  }

///////////////////////////////////////////////////////////////////////////////
//
// PROGRAMS
//
///////////////////////////////////////////////////////////////////////////////

Program* Parser::parseProgram() {

    Program* programAST = NULL;

    previousTokenPosition->start = 0;
    previousTokenPosition->finish = 0;
    currentToken = lexicalAnalyser->scan();

    try {
      Command* cAST = parseCommand();
      programAST = new Program(cAST, previousTokenPosition);
	  if (currentToken->kind != Token::EOT) {
        syntacticError("\"%\" not expected after end of program",currentToken->spelling);
      }

    }
    catch (string s) { return NULL; }
    return programAST;
  }

///////////////////////////////////////////////////////////////////////////////
//
// LITERALS
//
///////////////////////////////////////////////////////////////////////////////

// parseIntegerLiteral parses an integer-literal, and constructs
// a leaf AST to represent it.

IntegerLiteral* Parser::parseIntegerLiteral(){
    IntegerLiteral* IL = NULL;

	if (currentToken->kind == Token::INTLITERAL) {
      previousTokenPosition = currentToken->position;
      string spelling = currentToken->spelling;
      IL = new IntegerLiteral(spelling, previousTokenPosition);
      currentToken = lexicalAnalyser->scan();
    } else {
      IL = NULL;
      syntacticError("integer literal expected here", "");
    }
    return IL;
  }

// parseCharacterLiteral parses a character-literal, and constructs a leaf
// AST to represent it.

CharacterLiteral* Parser::parseCharacterLiteral(){
    CharacterLiteral* CL = NULL;

	if (currentToken->kind == Token::CHARLITERAL) {
      previousTokenPosition = currentToken->position;
      string spelling = currentToken->spelling;
      CL = new CharacterLiteral(spelling, previousTokenPosition);
      currentToken = lexicalAnalyser->scan();
    } else {
      CL = NULL;
      syntacticError("character literal expected here", "");
    }
    return CL;
  }

StringLiteral* Parser::parseStringLiteral()
{
  StringLiteral *SL = NULL;

  if (currentToken->kind == Token::STRINGLITERAL)
  {
    SL = new StringLiteral(currentToken->spelling, currentToken->position);
    currentToken = lexicalAnalyser->scan();
  }
  else
    syntacticError("string literal expected here", "");
  
  return SL;
}

// parseIdentifier parses an identifier, and constructs a leaf AST to
// represent it.

Identifier* Parser::parseIdentifier(){
  Identifier* I = NULL;

	if (currentToken->kind == Token::IDENTIFIER) {
    previousTokenPosition = currentToken->position;
    string spelling = currentToken->spelling;
    I = new Identifier(spelling, previousTokenPosition);
    currentToken = lexicalAnalyser->scan();
    while (check(Token::DOLLAR))
      I = parsePackageIdentifier(I);
  } else {
    I = NULL;
    syntacticError("identifier expected here", "");
  }
  return I;
}

Identifier* Parser::parsePackageIdentifier(Identifier *I)
{
  // Scan next token(after $)
  currentToken = lexicalAnalyser->scan();
  previousTokenPosition = currentToken->position;
  string spelling = currentToken->spelling;
  I = new PackageIdentifier(I, spelling, previousTokenPosition);
  currentToken = lexicalAnalyser->scan();

  return I;
}

// parseOperator parses an operator, and constructs a leaf AST to
// represent it.

Operator* Parser::parseOperator(){
    Operator* O = NULL;

	if (currentToken->kind == Token::OPERATOR) {
    previousTokenPosition = currentToken->position;
    string spelling = currentToken->spelling;
    O = new Operator(spelling, previousTokenPosition);
    currentToken = lexicalAnalyser->scan();
  } else {
    O = NULL;
    syntacticError("operator expected here", "");
  }
  return O;
}

///////////////////////////////////////////////////////////////////////////////
//
// COMMANDS
//
///////////////////////////////////////////////////////////////////////////////

// parseCommand parses the command, and constructs an AST
// to represent its phrase structure.

Command* Parser::parseCommand() {
    Command* commandAST = NULL; // in case there's a syntactic error

    SourcePosition* commandPos = new SourcePosition();

    start(commandPos);
    commandAST = parseSingleCommand();
	while (currentToken->kind == Token::SEMICOLON) {
      acceptIt();
      Command* c2AST = parseSingleCommand();
      finish(commandPos);
      commandAST = new SequentialCommand(commandAST, c2AST, commandPos);
    }
    return commandAST;
  }

Command* Parser::parseSingleCommand() {
  Command* commandAST = NULL; // in case there's a syntactic error
  SourcePosition* commandPos = new SourcePosition();
  start(commandPos);

  switch (currentToken->kind) {

	case Token::IDENTIFIER:
  {
    Identifier* iAST = parseIdentifier();
		if (currentToken->kind == Token::LPAREN) {
      acceptIt();
      ActualParameterSequence* apsAST = parseActualParameterSequence();
      accept(Token::RPAREN);
      finish(commandPos);
      commandAST = new CallCommand(iAST, apsAST, commandPos);
    }
    else {
      Vname* vAST = parseRestOfVname(iAST);
		  accept(Token::BECOMES);
      Expression* eAST = parseExpression();
      finish(commandPos);
      commandAST = new AssignCommand(vAST, eAST, commandPos);
    }
  }
  break;

	case Token::BEGIN:
    acceptIt();
    commandAST = parseCommand();
	  accept(Token::END);
    break;

	case Token::LET:
  {
    acceptIt();
    Declaration* dAST = parseDeclaration();
		accept(Token::IN_IN);
    Command* cAST = parseSingleCommand();
    finish(commandPos);
    commandAST = new LetCommand(dAST, cAST, commandPos);
  }
  break;

	case Token::IF:
  {
    acceptIt();
    Expression* eAST = parseExpression();
		accept(Token::THEN);
    Command* c1AST = parseSingleCommand();
		accept(Token::ELSE);
    Command* c2AST = parseSingleCommand();
    finish(commandPos);
    commandAST = new IfCommand(eAST, c1AST, c2AST, commandPos);
  }
  break;

	case Token::WHILE:
  {
    acceptIt();
    Expression* eAST = parseExpression();
		accept(Token::DO);
    Command* cAST = parseSingleCommand();
    finish(commandPos);
    commandAST = new WhileCommand(eAST, cAST, commandPos);
  }
  break;
  
  case Token::REPEAT:
  {
    acceptIt();
    Command *cAST = parseSingleCommand();
    accept(Token::UNTIL);
    Expression *eAST = parseExpression();
    finish(commandPos);
    commandAST = new RepeatCommand(cAST, eAST, commandPos);
  }
  break;

  case Token::FOR:
  {
    acceptIt();
    Identifier *iAST = parseIdentifier();
    accept(Token::FROM);
    Expression *e1AST = parseExpression();
    ConstDeclaration *dAST = new ConstDeclaration(iAST, e1AST, NULL);
    accept(Token::TO);
    Expression *e2AST = parseExpression();
    accept(Token::DO);
    Command *cAST = parseSingleCommand();
    finish(commandPos);
    commandAST = new ForCommand(dAST, e2AST, cAST, commandPos);
  }
  break;

  case Token::CASE:
  {
    acceptIt();
    Expression *eAST = parseExpression();
    accept(Token::OF);
    std::vector<IntegerLiteral *> iASTs;
    std::vector<Command *> cASTs;
    while (check(Token::INTLITERAL))
    {
      iASTs.push_back(parseIntegerLiteral());
      accept(Token::COLON);
      cASTs.push_back(parseSingleCommand());
      accept(Token::SEMICOLON);
    }
    accept(Token::ELSE);
    accept(Token::COLON);
    Command *elseAST = parseSingleCommand();
    finish(commandPos);
    commandAST = new CaseCommand(eAST, iASTs, cASTs, elseAST, commandPos);
  }
  break;
  
  case Token::SEMICOLON:
	case Token::END:
	case Token::ELSE:
	case Token::IN_IN:
	case Token::EOT:
  finish(commandPos);
  commandAST = new EmptyCommand(commandPos);
  break;

  default:
    syntacticError("\"%\" cannot start a command", currentToken->spelling);
    break;
  }

  return commandAST;
}

///////////////////////////////////////////////////////////////////////////////
//
// EXPRESSIONS
//
///////////////////////////////////////////////////////////////////////////////

Expression* Parser::parseExpression() {
  Expression* expressionAST = NULL; // in case there's a syntactic error

  SourcePosition* expressionPos = new SourcePosition();

  start (expressionPos);

  switch (currentToken->kind) {
    case Token::LET:
    {
      acceptIt();
      Declaration* dAST = parseDeclaration();
      accept(Token::IN_IN);
      Expression* eAST = parseExpression();
      finish(expressionPos);
      expressionAST = new LetExpression(dAST, eAST, expressionPos);
    }
    break;

    case Token::IF:
    {
      acceptIt();
      Expression* e1AST = parseExpression();
      accept(Token::THEN);
      Expression* e2AST = parseExpression();
      accept(Token::ELSE);
      Expression* e3AST = parseExpression();
      finish(expressionPos);
      expressionAST = new IfExpression(e1AST, e2AST, e3AST, expressionPos);
    }
    break;

    default:
      expressionAST = parseSecondaryExpression();
      break;
  }
  return expressionAST;
}

Expression* Parser::parseSecondaryExpression() {
    Expression* expressionAST = NULL; // in case there's a syntactic error

    SourcePosition* expressionPos = new SourcePosition();
    start(expressionPos);

    expressionAST = parsePrimaryExpression();
	while (currentToken->kind == Token::OPERATOR) {
      Operator* opAST = parseOperator();
      Expression* e2AST = parsePrimaryExpression();
      expressionAST = new BinaryExpression (expressionAST, opAST, e2AST,
        expressionPos);
    }
    return expressionAST;
  }

Expression* Parser::parsePrimaryExpression() {
  Expression* expressionAST = NULL; // in case there's a syntactic error

  SourcePosition* expressionPos = new SourcePosition();
  start(expressionPos);

  switch (currentToken->kind) {
  case Token::INTLITERAL:
  {
    IntegerLiteral* ilAST = parseIntegerLiteral();
    finish(expressionPos);
    expressionAST = new IntegerExpression(ilAST, expressionPos);
  }
  break;

  case Token::CHARLITERAL:
  {
    CharacterLiteral* clAST= parseCharacterLiteral();
    finish(expressionPos);
    expressionAST = new CharacterExpression(clAST, expressionPos);
  }
  break;

  case Token::STRINGLITERAL:
  {
    StringLiteral *s1AST = parseStringLiteral();
    finish(expressionPos);
    expressionAST = new StringExpression(s1AST, expressionPos);
  }
  break;

  case Token::LBRACKET:
  {
    acceptIt();
    ArrayAggregate* aaAST = parseArrayAggregate();
    accept(Token::RBRACKET);
    finish(expressionPos);
    expressionAST = new ArrayExpression(aaAST, expressionPos);
  }
  break;

  case Token::LCURLY:
  {
    acceptIt();
    RecordAggregate* raAST = parseRecordAggregate();
    accept(Token::RCURLY);
    finish(expressionPos);
    expressionAST = new RecordExpression(raAST, expressionPos);
  }
  break;

  case Token::IDENTIFIER:
  {
    Identifier* iAST= parseIdentifier();
    if (currentToken->kind == Token::LPAREN) {
      acceptIt();
      ActualParameterSequence* apsAST = parseActualParameterSequence();
      accept(Token::RPAREN);
      finish(expressionPos);
      expressionAST = new CallExpression(iAST, apsAST, expressionPos);
    } else {
      Vname* vAST = parseRestOfVname(iAST);
      finish(expressionPos);
      expressionAST = new VnameExpression(vAST, expressionPos);
    }
  }
  break;

  case Token::PRED:
  {
    acceptIt();
    Expression *eAST = parsePrimaryExpression();
    finish(expressionPos);
    expressionAST = new PredExpression(eAST, expressionPos);
  }
  break;

  case Token::SUCC:
  {
    acceptIt();
    Expression *eAST = parsePrimaryExpression();
    finish(expressionPos);
    expressionAST = new SuccExpression(eAST, expressionPos);
  }
  break;

  case Token::NIL:
  {
    acceptIt();
    finish(expressionPos);
    expressionAST = new NilExpression(expressionPos);
  }
  break;

  case Token::OPERATOR:
  {
    Operator* opAST = parseOperator();
    Expression* eAST = parsePrimaryExpression();
    finish(expressionPos);
    expressionAST = new UnaryExpression(opAST, eAST, expressionPos);
  }
  break;

	case Token::LPAREN:
    acceptIt();
    expressionAST = parseExpression();
    accept(Token::RPAREN);
    break;

  default:
    syntacticError("\"%\" cannot start an expression", currentToken->spelling);
    break;
  }
  return expressionAST;
}

RecordAggregate* Parser::parseRecordAggregate() {
    RecordAggregate* aggregateAST = NULL; // in case there's a syntactic error

    SourcePosition* aggregatePos = new SourcePosition();
    start(aggregatePos);

    Identifier* iAST = parseIdentifier();
	accept(Token::IS);
    Expression* eAST = parseExpression();

	if (currentToken->kind == Token::COMMA) {
      acceptIt();
      RecordAggregate* aAST = parseRecordAggregate();
      finish(aggregatePos);
      aggregateAST = new MultipleRecordAggregate(iAST, eAST, aAST, aggregatePos);
    } else {
      finish(aggregatePos);
      aggregateAST = new SingleRecordAggregate(iAST, eAST, aggregatePos);
    }
    return aggregateAST;
  }

ArrayAggregate* Parser::parseArrayAggregate(){
    ArrayAggregate* aggregateAST = NULL; // in case there's a syntactic error

    SourcePosition* aggregatePos = new SourcePosition();
    start(aggregatePos);

    Expression* eAST = parseExpression();
	if (currentToken->kind == Token::COMMA) {
      acceptIt();
      ArrayAggregate* aAST = parseArrayAggregate();
      finish(aggregatePos);
      aggregateAST = new MultipleArrayAggregate(eAST, aAST, aggregatePos);
    } else {
      finish(aggregatePos);
      aggregateAST = new SingleArrayAggregate(eAST, aggregatePos);
    }
    return aggregateAST;
  }

///////////////////////////////////////////////////////////////////////////////
//
// VALUE-OR-VARIABLE NAMES
//
///////////////////////////////////////////////////////////////////////////////

Vname* Parser::parseVname () {
  Vname* vnameAST = NULL; // in case there's a syntactic error
  Identifier* iAST = parseIdentifier();
  vnameAST = parseRestOfVname(iAST);
  return vnameAST;
}

Vname* Parser::parseRestOfVname(Identifier* identifierAST){
  SourcePosition* vnamePos = new SourcePosition();
  vnamePos = identifierAST->position;
  Vname* vAST = new SimpleVname(identifierAST, vnamePos);

	while (check(Token::DOT) || check(Token::LBRACKET)) {
		if (check(Token::DOT)) {
      acceptIt();
      Identifier* iAST = parseIdentifier();
      vAST = new DotVname(vAST, iAST, vnamePos);
    } else {
      acceptIt();
      Expression* eAST = parseExpression();
		  accept(Token::RBRACKET);
      finish(vnamePos);
      vAST = new SubscriptVname(vAST, eAST, vnamePos);
    }
  }
  return vAST;
}

///////////////////////////////////////////////////////////////////////////////
//
// DECLARATIONS
//
///////////////////////////////////////////////////////////////////////////////

Declaration* Parser::parseDeclaration() {
    Declaration* declarationAST = NULL; // in case there's a syntactic error

    SourcePosition* declarationPos = new SourcePosition();
    start(declarationPos);
    declarationAST = parseSingleDeclaration();
	while (currentToken->kind == Token::SEMICOLON) {
      acceptIt();
      Declaration* d2AST = parseSingleDeclaration();
      finish(declarationPos);
      declarationAST = new SequentialDeclaration(declarationAST, d2AST,
        declarationPos);
    }
    return declarationAST;
  }

Declaration* Parser::parseSingleDeclaration() {
    Declaration* declarationAST = NULL; // in case there's a syntactic error

    SourcePosition* declarationPos = new SourcePosition();
    start(declarationPos);

    switch (currentToken->kind) {

	case Token::CONST:
      {
        acceptIt();
        Identifier* iAST = parseIdentifier();
		accept(Token::IS);
        Expression* eAST = parseExpression();
        finish(declarationPos);
        declarationAST = new ConstDeclaration(iAST, eAST, declarationPos);
      }
      break;

	case Token::VAR:
  {
    acceptIt();
    Identifier* iAST = parseIdentifier();
    if (check(Token::BECOMES))
    {
      acceptIt();
      Expression *eAST = parseExpression();
      finish(declarationPos);
      declarationAST = new VarInitDeclaration(iAST, eAST, declarationPos);
    }
    else
    {
      accept(Token::COLON);
      TypeDenoter* tAST = parseTypeDenoter();
      finish(declarationPos);
      declarationAST = new VarDeclaration(iAST, tAST, declarationPos);
    }
  }
  break;

  case Token::ENUM:
  {
    acceptIt();
    accept(Token::TYPE);
    Identifier *nameAST = parseIdentifier();
    accept(Token::IS);
    accept(Token::LPAREN);
    std::vector<Identifier *> iASTs;
    iASTs.push_back(parseIdentifier());
    while (check(Token::COMMA))
    {
      acceptIt();
      iASTs.push_back(parseIdentifier());
    }
    accept(Token::RPAREN);
    finish(declarationPos);
    declarationAST = new EnumDeclaration(nameAST, iASTs, declarationPos);
  }
  break;

  case Token::REC:
  {
    acceptIt();
    accept(Token::TYPE);
    Identifier *iAST = parseIdentifier();
    accept(Token::IS);
    TypeDenoter *tAST = parseTypeDenoter();
    finish(declarationPos);
    declarationAST = new RecTypeDeclaration(iAST, tAST, declarationPos);
  }
  break;

  case Token::PACKAGE:
  {
    acceptIt();
    Identifier *iAST = parseIdentifier();
    accept(Token::IS);
    Declaration *d1AST = parseDeclaration();
    Declaration *d2AST = NULL;
    if (check(Token::WHERE))
    {
      acceptIt();
      d2AST = parseDeclaration();
    }
    accept(Token::END);
    finish(declarationPos);
    declarationAST = new PackageDeclaration(iAST, d1AST, d2AST, declarationPos);
  }
  break;

	case Token::PROC:
  {
    acceptIt();
    Identifier* iAST = parseIdentifier();
		accept(Token::LPAREN);
    FormalParameterSequence* fpsAST = parseFormalParameterSequence();
		accept(Token::RPAREN);
		accept(Token::IS);
    Command* cAST = parseSingleCommand();
    finish(declarationPos);
    declarationAST = new ProcDeclaration(iAST, fpsAST, cAST, declarationPos);
  }
  break;

	case Token::FUNC:
  {
    acceptIt();
    if (check(Token::OPERATOR))
    {
      Operator *opAST = parseOperator();
      accept(Token::LPAREN);
      Identifier *i1AST = parseIdentifier();
      accept(Token::COLON);
      TypeDenoter *t1AST = parseTypeDenoter();
      Identifier *i2AST = NULL;
      TypeDenoter *t2AST = NULL;
      if (check(Token::COMMA))
      {
        acceptIt();
        i2AST = parseIdentifier();
        accept(Token::COLON);
        t2AST = parseTypeDenoter();
      }
      accept(Token::RPAREN);
      accept(Token::COLON);
      TypeDenoter *t3AST = parseTypeDenoter();
      accept(Token::IS);
      Expression *eAST = parseExpression();
      finish(declarationPos);
      if (i2AST == NULL)
        declarationAST = new FuncUnaryOpDeclaration(opAST, i1AST, t1AST, t3AST, eAST, declarationPos);
      else
        declarationAST = new FuncBinOpDeclaration(opAST, i1AST, t1AST, i2AST, t2AST, t3AST, eAST, declarationPos);
    }
    else
    {
      Identifier* iAST = parseIdentifier();
      accept(Token::LPAREN);
      FormalParameterSequence* fpsAST = parseFormalParameterSequence();
      accept(Token::RPAREN);
      accept(Token::COLON);
      TypeDenoter* tAST = parseTypeDenoter();
      accept(Token::IS);
      Expression* eAST = parseExpression();
      finish(declarationPos);
      declarationAST = new FuncDeclaration(iAST, fpsAST, tAST, eAST, declarationPos);
    }
  }
  break;

	case Token::TYPE:
      {
        acceptIt();
        Identifier* iAST = parseIdentifier();
		accept(Token::IS);
        TypeDenoter* tAST = parseTypeDenoter();
        finish(declarationPos);
        declarationAST = new TypeDeclaration(iAST, tAST, declarationPos);
      }
      break;

    default:

      syntacticError("\"%\" cannot start a declaration",
        currentToken->spelling);
      break;

    }
    return declarationAST;
  }

///////////////////////////////////////////////////////////////////////////////
//
// PARAMETERS
//
///////////////////////////////////////////////////////////////////////////////

FormalParameterSequence* Parser::parseFormalParameterSequence(){
  FormalParameterSequence* formalsAST;

  SourcePosition* formalsPos = new SourcePosition();

  start(formalsPos);
  if (currentToken->kind == Token::RPAREN) {
    finish(formalsPos);
    formalsAST = new EmptyFormalParameterSequence(formalsPos);
  } else {
    formalsAST = parseProperFormalParameterSequence();
  }
  return formalsAST;
}

FormalParameterSequence* Parser::parseProperFormalParameterSequence(){
  FormalParameterSequence* formalsAST = NULL; // in case there's a syntactic error;

  SourcePosition* formalsPos = new SourcePosition();
  start(formalsPos);
  FormalParameter* fpAST = parseFormalParameter();
  if (currentToken->kind == Token::COMMA) {
    acceptIt();
    FormalParameterSequence* fpsAST = parseProperFormalParameterSequence();
    finish(formalsPos);
    formalsAST = new MultipleFormalParameterSequence(fpAST, fpsAST,
      formalsPos);
  } else {
    finish(formalsPos);
    formalsAST = new SingleFormalParameterSequence(fpAST, formalsPos);
  }
  return formalsAST;
}

FormalParameter* Parser::parseFormalParameter(){
  FormalParameter* formalAST = NULL; // in case there's a syntactic error;

  SourcePosition* formalPos = new SourcePosition();
  start(formalPos);

  switch (currentToken->kind) {

	case Token::IDENTIFIER:
  {
    Identifier* iAST = parseIdentifier();
		accept(Token::COLON);
    TypeDenoter* tAST = parseTypeDenoter();
    finish(formalPos);
    formalAST = new ConstFormalParameter(iAST, tAST, formalPos);
  }
  break;

  case Token::IN_IN:
  {
    acceptIt();
    if (check(Token::OUT))  // IN OUT - Value-Result Param
    {
      acceptIt();
      Identifier* iAST = parseIdentifier();
		  accept(Token::COLON);
      TypeDenoter* tAST = parseTypeDenoter();
      finish(formalPos);
      formalAST = new ValueResultFormalParameter(iAST, tAST, formalPos);
    }
    else  // IN - Value Param
    {
      Identifier* iAST = parseIdentifier();
		  accept(Token::COLON);
      TypeDenoter* tAST = parseTypeDenoter();
      finish(formalPos);
      formalAST = new ConstFormalParameter(iAST, tAST, formalPos);
    }
  }
  break;
  
  case Token::OUT:  // OUT - Result Param
  {
    acceptIt();
    Identifier* iAST = parseIdentifier();
    accept(Token::COLON);
    TypeDenoter* tAST = parseTypeDenoter();
    finish(formalPos);
    formalAST = new ResultFormalParameter(iAST, tAST, formalPos);
  }
  break;

	case Token::VAR:
  {
    acceptIt();
    Identifier* iAST = parseIdentifier();
		accept(Token::COLON);
    TypeDenoter* tAST = parseTypeDenoter();
    finish(formalPos);
    formalAST = new VarFormalParameter(iAST, tAST, formalPos);
  }
  break;

	case Token::PROC:
  {
    acceptIt();
    Identifier* iAST = parseIdentifier();
		accept(Token::LPAREN);
    FormalParameterSequence* fpsAST = parseFormalParameterSequence();
		accept(Token::RPAREN);
    finish(formalPos);
    formalAST = new ProcFormalParameter(iAST, fpsAST, formalPos);
  }
  break;

	case Token::FUNC:
  {
    acceptIt();
    Identifier* iAST = parseIdentifier();
		accept(Token::LPAREN);
    FormalParameterSequence* fpsAST = parseFormalParameterSequence();
		accept(Token::RPAREN);
		accept(Token::COLON);
    TypeDenoter* tAST = parseTypeDenoter();
    finish(formalPos);
    formalAST = new FuncFormalParameter(iAST, fpsAST, tAST, formalPos);
  }
  break;

  default:
    syntacticError("\"%\" cannot start a formal parameter", currentToken->spelling);
    break;
  }
  return formalAST;
}


ActualParameterSequence* Parser::parseActualParameterSequence(){
    ActualParameterSequence* actualsAST;

    SourcePosition* actualsPos = new SourcePosition();

    start(actualsPos);
	if (currentToken->kind == Token::RPAREN) {
      finish(actualsPos);
      actualsAST = new EmptyActualParameterSequence(actualsPos);

    } else {
      actualsAST = parseProperActualParameterSequence();
    }
    return actualsAST;
  }

ActualParameterSequence* Parser::parseProperActualParameterSequence(){
    ActualParameterSequence* actualsAST = NULL; // in case there's a syntactic error

    SourcePosition* actualsPos = new SourcePosition();

    start(actualsPos);
    ActualParameter* apAST = parseActualParameter();
	if (currentToken->kind == Token::COMMA) {
      acceptIt();
      ActualParameterSequence* apsAST = parseProperActualParameterSequence();
      finish(actualsPos);
      actualsAST = new MultipleActualParameterSequence(apAST, apsAST,
        actualsPos);
    } else {
      finish(actualsPos);
      actualsAST = new SingleActualParameterSequence(apAST, actualsPos);
    }
    return actualsAST;
  }

ActualParameter* Parser::parseActualParameter(){
    ActualParameter* actualAST = NULL; // in case there's a syntactic error

    SourcePosition* actualPos = new SourcePosition();

    start(actualPos);

    switch (currentToken->kind) {

	case Token::IDENTIFIER:
  case Token::NIL:
  case Token::SUCC:
  case Token::PRED:
	case Token::INTLITERAL:
	case Token::CHARLITERAL:
	case Token::OPERATOR:
	case Token::LET:
	case Token::IF:
	case Token::LPAREN:
	case Token::LBRACKET:
	case Token::LCURLY:
      {
        Expression* eAST = parseExpression();
        finish(actualPos);
        actualAST = new ConstActualParameter(eAST, actualPos);
      }
      break;

	case Token::VAR:
      {
        acceptIt();
        Vname* vAST = parseVname();
        finish(actualPos);
        actualAST = new VarActualParameter(vAST, actualPos);
      }
      break;

	case Token::PROC:
      {
        acceptIt();
        Identifier* iAST = parseIdentifier();
        finish(actualPos);
        actualAST = new ProcActualParameter(iAST, actualPos);
      }
      break;

	case Token::FUNC:
      {
        acceptIt();
        Identifier* iAST = parseIdentifier();
        finish(actualPos);
        actualAST = new FuncActualParameter(iAST, actualPos);
      }
      break;

    default:
      syntacticError("\"%\" cannot start an actual parameter",
        currentToken->spelling);
      break;

    }
    return actualAST;
  }

///////////////////////////////////////////////////////////////////////////////
//
// TYPE-DENOTERS
//
///////////////////////////////////////////////////////////////////////////////

TypeDenoter* Parser::parseTypeDenoter(){
  TypeDenoter* typeAST = NULL; // in case there's a syntactic error
  SourcePosition* typePos = new SourcePosition();

  start(typePos);

  switch (currentToken->kind) {

  case Token::IDENTIFIER:
  {
    Identifier* iAST = parseIdentifier();

    if (iAST->spelling == "string")
    {
      IntegerLiteral *ilAST = parseIntegerLiteral();
      finish(typePos);
      typeAST = new StringTypeDenoter(ilAST, typePos);
      break;
    }

    finish(typePos);
    typeAST = new SimpleTypeDenoter(iAST, typePos);
  }
  break;

	case Token::ARRAY:
  {
    acceptIt();
    IntegerLiteral* ilAST = parseIntegerLiteral();
    accept(Token::OF);
    TypeDenoter* tAST = parseTypeDenoter();
    finish(typePos);
    typeAST = new ArrayTypeDenoter(ilAST, tAST, typePos);
  }
  break;

	case Token::RECORD:
  {
    acceptIt();
    FieldTypeDenoter* fAST = parseFieldTypeDenoter();
    accept(Token::END);
    finish(typePos);
    typeAST = new RecordTypeDenoter(fAST, typePos);
  }
  break;

  default:
    syntacticError("\"%\" cannot start a type denoter",
      currentToken->spelling);
    break;

  }
  return typeAST;
}

FieldTypeDenoter* Parser::parseFieldTypeDenoter() {
    FieldTypeDenoter* fieldAST = NULL; // in case there's a syntactic error

    SourcePosition* fieldPos = new SourcePosition();

    start(fieldPos);
    Identifier* iAST = parseIdentifier();
	accept(Token::COLON);
    TypeDenoter* tAST = parseTypeDenoter();
	if (currentToken->kind == Token::COMMA) {
      acceptIt();
      FieldTypeDenoter* fAST = parseFieldTypeDenoter();
      finish(fieldPos);
      fieldAST = new MultipleFieldTypeDenoter(iAST, tAST, fAST, fieldPos);
    } else {
      finish(fieldPos);
      fieldAST = new SingleFieldTypeDenoter(iAST, tAST, fieldPos);
    }
    return fieldAST;
  }
//}
#endif
