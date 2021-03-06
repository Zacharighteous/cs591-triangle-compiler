#ifndef _ENCODER
#define _ENCODER

#include <cstdio>
#include <fstream>
#include <iostream>
#include "import_headers.h"
#include "./AST/Object.h"
#include "./AST/Integer.h"
#include "./AST/ResultParameterInfo.h"
#include "./TAM/Instruction.h"
#include "./TAM/Machine.h"

#include "./CodeGenerator/EqualityRoutine.h"
#include "./CodeGenerator/Field.h"
#include "./CodeGenerator/Frame.h"
#include "./CodeGenerator/HeapAddress.h"
#include "./CodeGenerator/KnownAddress.h"
#include "./CodeGenerator/KnownRoutine.h"
#include "./CodeGenerator/KnownValue.h"
#include "./CodeGenerator/ObjectAddress.h"
#include "./CodeGenerator/PrimitiveRoutine.h"
#include "./CodeGenerator/PointerAddress.h"
#include "./CodeGenerator/RuntimeEntity.h"
#include "./CodeGenerator/TypeRepresentation.h"
#include "./CodeGenerator/UnknownAddress.h"
#include "./CodeGenerator/UnknownRoutine.h"
#include "./CodeGenerator/UnknownValue.h"
#include "./ContextualAnalyzer/Checker.h"

#include "StdEnvironment.h"
#include <string>
#include <vector>

using namespace std;

class Encoder : public Visitor {
public:
ErrorReporter* reporter;
bool tableDetailsReqd;
int nextInstrAddr;
StdEnvironment* getvarz;
Machine* mach;
// Used for handling result and value result parameters
Frame *helperFrame;
vector<ResultParameterInfo *> parameterEntries;
// Commands	

  Object* visitAssignCommand(Object* obj, Object* o);
  Object* visitCallCommand(Object* obj, Object* o);
  Object* visitCaseCommand(Object* obj, Object* o);
  Object* visitEmptyCommand(Object* obj, Object* o);
  Object* visitForCommand(Object* obj, Object* o);
  Object* visitIfCommand(Object* obj, Object* o);
  Object* visitLetCommand(Object* obj, Object* o);
  Object* visitRepeatCommand(Object* obj, Object* o);
  Object* visitSequentialCommand(Object* obj, Object* o);
  Object* visitWhileCommand(Object* obj, Object* o);


  // Expressions
  Object* visitArrayExpression(Object* obj, Object* o);
  Object* visitBinaryExpression(Object* obj, Object* o);
  Object* visitCallExpression(Object* obj, Object* o);
  Object* visitCharacterExpression(Object* obj,Object* o);
  Object* visitEmptyExpression(Object* obj, Object* o) ;
  Object* visitIfExpression(Object* obj, Object* o);
  Object* visitIntegerExpression(Object* obj, Object* o);
  Object* visitNilExpression(Object* obj, Object* o);
  Object* visitPredExpression(Object* obj, Object* o);
  Object* visitStringExpression(Object* obj, Object* o);
  Object* visitSuccExpression(Object* obj, Object* o);
  Object* visitLetExpression(Object* obj, Object* o);
  Object* visitRecordExpression(Object* obj, Object* o);
  Object* visitUnaryExpression(Object* obj, Object* o);
  Object* visitVnameExpression(Object* obj, Object* o);


  // Declarations
  Object* visitBinaryOperatorDeclaration(Object* obj,Object* o);
  Object* visitConstDeclaration(Object* obj, Object* o);
  Object* visitEnumDeclaration(Object* obj, Object* o);
  Object* visitEnumValueDeclaration(Object* obj, Object* o);
  Object* visitFuncBinOpDeclaration(Object* obj, Object* o);
  Object* visitFuncDeclaration(Object* obj, Object* o);
  Object* visitFuncUnaryOpDeclaration(Object* obj, Object* o);
  Object* visitPackageDeclaration(Object* obj, Object* o);
  Object* visitProcDeclaration(Object* obj, Object* o);
  Object* visitRecTypeDeclaration(Object* obj, Object* o);
  Object* visitSequentialDeclaration(Object* obj, Object* o);
  Object* visitTypeDeclaration(Object* obj, Object* o);
  Object* visitUnaryOperatorDeclaration(Object* obj,Object* o);
  Object* visitVarDeclaration(Object* obj, Object* o);
  Object* visitVarInitDeclaration(Object* obj, Object* o);


  // Array Aggregates
  Object* visitMultipleArrayAggregate(Object* obj,Object* o);
  Object* visitSingleArrayAggregate(Object* obj, Object* o);


  // Record Aggregates
  Object* visitMultipleRecordAggregate(Object* obj,Object* o);
  Object* visitSingleRecordAggregate(Object* obj,Object* o);

  // Formal Parameters
  Object* visitConstFormalParameter(Object* obj, Object* o);
  Object* visitFuncFormalParameter(Object* obj, Object* o);
  Object* visitProcFormalParameter(Object* obj, Object* o);
  Object* visitResultFormalParameter(Object* obj, Object* o);
  Object* visitValueResultFormalParameter(Object* obj, Object* o);
  Object* visitVarFormalParameter(Object* obj, Object* o);
  Object* visitEmptyFormalParameterSequence(Object* obj, Object* o);
  Object* visitMultipleFormalParameterSequence(Object* obj, Object* o);
  Object* visitSingleFormalParameterSequence(Object* obj, Object* o);

  // Actual Parameters
  Object* visitConstActualParameter(Object* obj, Object* o);
  Object* visitFuncActualParameter(Object* obj, Object* o);
  Object* visitProcActualParameter(Object* obj, Object* o);
  Object* visitVarActualParameter(Object* obj, Object* o);
  Object* visitEmptyActualParameterSequence(Object* obj, Object* o);
  Object* visitMultipleActualParameterSequence(Object* obj, Object* o);
  Object* visitSingleActualParameterSequence(Object* obj, Object* o);

  // Type Denoters
  Object* visitAnyTypeDenoter(Object* obj, Object* o);
  Object* visitArrayTypeDenoter(Object* obj, Object* o);
  Object* visitBoolTypeDenoter(Object* obj, Object* o);
  Object* visitCharTypeDenoter(Object* obj, Object* o);
  Object* visitEnumTypeDenoter(Object* obj, Object* o);
  Object* visitErrorTypeDenoter(Object* obj, Object* o);
  Object* visitNilTypeDenoter(Object* obj, Object* o);
  Object* visitPointerTypeDenoter(Object* obj, Object* o);
  Object* visitSimpleTypeDenoter(Object* obj,Object* o);
  Object* visitStringTypeDenoter(Object* obj,Object* o);
  Object* visitVarStringTypeDenoter(Object* obj,Object* o);
  Object* visitIntTypeDenoter(Object* obj, Object* o);
  Object* visitRecordTypeDenoter(Object* obj, Object* o);
  Object* visitMultipleFieldTypeDenoter(Object* obj,Object* o);
  Object* visitSingleFieldTypeDenoter(Object* obj,Object* o);

  // Literals, Identifiers and Operators
  Object* visitCharacterLiteral(Object* obj, Object* o);
  Object* visitIdentifier(Object* obj, Object* o);
  Object* visitPackageIdentifier(Object* obj, Object* o);
  Object* visitIntegerLiteral(Object* obj, Object* o);
  Object* visitOperator(Object* obj, Object* o);
  Object* visitStringLiteral(Object* obj, Object* o);

  // Value-or-variable names
  Object* visitDotVname(Object* obj, Object* o);
  Object* visitSimpleVname(Object* obj, Object* o);
  Object* visitSubscriptVname(Object* obj, Object* o);

  // Programs
  Object* visitProgram(Object* obj, Object* o);


  Encoder(ErrorReporter* reporter,Checker* check_it);


  

  // Generates code to run a program.
  // showingTable is true iff entity description details
  // are to be displayed.

  void encodeRun (Program* theAST, bool showingTable);

  // Decides run-time representation of a standard constant.
  void elaborateStdConst (Object* obj,int value);

  // Decides run-time representation of a standard routine.
  void elaborateStdPrimRoutine (Object* obj,int routineOffset);
  void elaborateStdEqRoutine (Object* obj,int routineOffset);
  void elaborateStdRoutine (Object* obj,int routineOffset);
  void elaborateStdEnvironment();


  // Saves the object program in the named file.

  void saveObjectProgram(string objectName);


  

 static void writeTableDetails(AST* ast) ;

  // OBJECT CODE

  // Implementation notes:
  // Object code is generated directly into the TAM Code Store, starting at CB.
  // The address of the next instruction is held in nextInstrAddr.

  

  // Appends an instruction, with the given fields, to the object code.
  void emit (int op, int n, int r, int d) ;

  // Patches the d-field of the instruction at address addr.
  void patch (int addr, int d) ;

  // DATA REPRESENTATION

  int characterValuation(string spelling);

  // REGISTERS

  // Returns the register number appropriate for object code at currentLevel
  // to address a data object at objectLevel.
  int displayRegister (int currentLevel, int objectLevel) ;

  // Generates code to fetch the value of a named constant or variable
  // and push it on to the stack.
  // currentLevel is the routine level where the vname occurs.
  // frameSize is the anticipated size of the local stack frame when
  // the constant or variable is fetched at run-time.
  // valSize is the size of the constant or variable's value.

  void encodeStore(Vname* V, Frame* frame, int valSize);

  // Generates code to fetch the value of a named constant or variable
  // and push it on to the stack.
  // currentLevel is the routine level where the vname occurs.
  // frameSize is the anticipated size of the local stack frame when
  // the constant or variable is fetched at run-time.
  // valSize is the size of the constant or variable's value.

  void encodeFetch(Vname* V, Frame* frame, int valSize);
  // Generates code to compute and push the address of a named variable.
  // vname is the program phrase that names this variable.
  // currentLevel is the routine level where the vname occurs.
  // frameSize is the anticipated size of the local stack frame when
  // the variable is addressed at run-time.

  void encodeFetchAddress (Vname* V, Frame* frame);
};

Object* Encoder::visitAssignCommand(Object* obj, Object* o) {
  AssignCommand* ast = (AssignCommand*)obj;
  Frame* frame = (Frame*) o;
  Integer* valSize = (Integer*) ast->E->visit(this, frame);
  encodeStore(ast->V, new Frame(frame, valSize->value),valSize->value);
  return NULL;
}

Object* Encoder::visitCallCommand(Object* obj, Object* o) {
  CallCommand* ast = (CallCommand*)obj;
  Frame* frame = (Frame*) o;
  Integer* argsSize = (Integer*) ast->APS->visit(this, frame);
  ast->I->visit(this, new Frame(frame->level, argsSize));
  return NULL;
}

Object* Encoder::visitCaseCommand(Object* obj, Object* o)
{
  CaseCommand *ast = (CaseCommand *)obj;

  int numCases = ast->C.size();
  // List of addresses that will need to be filled in
  int jumpAddrs[numCases];
  int thisAddr, nextAddr, exprAddr;

  // Write each command along with jump instructions
  for (int i=0; i<numCases; i++)
  {
    // Get the integer to be compared
    ast->E->visit(this, o);
    // Load the integer literal
    emit(mach->LOADLop, 0, 0, atoi(ast->I[i]->spelling.c_str()));
    // Size of integers to be compared
    emit(mach->LOADLop, 0, 0, mach->integerSize);
    // Compare the 2 values
    emit(mach->CALLop, mach->LBr, mach->PBr, mach->eqDisplacement);
    thisAddr = nextInstrAddr;
    // Jump to the command associated with this int lit if it matches
    emit(mach->JUMPIFop, mach->trueRep, mach->CBr, 0);
    nextAddr = nextInstrAddr;
    // Jump to the next checker if it did not match
    emit(mach->JUMPop, 0, mach->CBr, 0);
    patch(thisAddr, nextInstrAddr);
    ast->C[i]->visit(this, o);
    // After the command is executed, jump to the end of the case statement
    jumpAddrs[i] = nextInstrAddr;
    emit(mach->JUMPop, 0, mach->CBr, 0);
    patch(nextAddr, nextInstrAddr);
  }
  // Handle the default case
  ast->elseC->visit(this, o);
  // Update all the final jump statements
  for (int i=0; i<numCases; i++)
  {
    patch(jumpAddrs[i], nextInstrAddr);
  }

  return NULL;
}

Object* Encoder::visitEmptyCommand(Object* obj, Object* o) {
    EmptyCommand* ast = (EmptyCommand*)obj;
    return NULL;
  }

Object* Encoder::visitForCommand(Object* obj, Object* o)
{
  ForCommand *ast = (ForCommand *)obj;
  Frame *frame = (Frame *)o;
  int loopAddr, endAddr;

  // Initialize I to E1
  emit(mach->PUSHop, 0, 0, mach->integerSize);
  int extraSize = ((Integer*) ast->D->E->visit(this, frame))->value;
  UnknownValue *iVal = new UnknownValue(extraSize, frame->level, frame->size);
  ast->D->entity = iVal;
  Frame *newFrame = new Frame(frame, extraSize);
  // Allocate space and store E1 into I
  emit(mach->STOREop, iVal->size, displayRegister(frame->level, iVal->address->level), iVal->address->displacement);

  loopAddr = nextInstrAddr;
  emit(mach->LOADop, iVal->size, displayRegister(frame->level, iVal->address->level), iVal->address->displacement);
  ast->E->visit(this, frame);
  // Exit loop when I > E2
  emit(mach->CALLop, mach->SBr, mach->PBr, mach->leDisplacement);
  endAddr = nextInstrAddr;
  emit(mach->JUMPIFop, mach->falseRep, mach->CBr, 0);
  ast->C->visit(this, newFrame);
  // Increment I
  emit(mach->LOADop, iVal->size, displayRegister(frame->level, iVal->address->level), iVal->address->displacement);
  emit(mach->CALLop, mach->LBr, mach->PBr, mach->succDisplacement);
  emit(mach->STOREop, iVal->size, displayRegister(frame->level, iVal->address->level), iVal->address->displacement);
  // Loop to beginning
  emit(mach->JUMPop, 0, mach->CBr, loopAddr);
  patch(endAddr, nextInstrAddr);

  emit(mach->POPop, 0, 0, mach->integerSize);

  return NULL;
}

Object* Encoder::visitIfCommand(Object* obj, Object* o) {
	  IfCommand* ast = (IfCommand*)obj;
    Frame* frame = (Frame*) o;
    int jumpifAddr;
	int jumpAddr;

    Integer* valSize = (Integer*) ast->E->visit(this, frame);
    jumpifAddr = nextInstrAddr;
	emit(mach->JUMPIFop, mach->falseRep, mach->CBr, 0);
    ast->C1->visit(this, frame);
    jumpAddr = nextInstrAddr;
	emit(mach->JUMPop, 0, mach->CBr, 0);
    patch(jumpifAddr, nextInstrAddr);
    ast->C2->visit(this, frame);
    patch(jumpAddr, nextInstrAddr);
    return NULL;
  }

Object* Encoder::visitLetCommand(Object* obj, Object* o) {
	LetCommand* ast = (LetCommand*)obj;
    Frame* frame = (Frame*) o;
    int extraSize = ((Integer*) ast->D->visit(this, frame))->value;
    ast->C->visit(this, new Frame(frame, extraSize));
    if (extraSize > 0)
		emit(mach->POPop, 0, 0, extraSize);
    return NULL;
  }

Object* Encoder::visitRepeatCommand(Object* obj, Object* o)
{
  RepeatCommand *ast = (RepeatCommand *)obj;
  int loopAddr = nextInstrAddr;

  // Execute command first
  ast->C->visit(this, o);
  // Evaluate boolean expression
  ast->E->visit(this, o);
  // If expression is false, loop back to the command
  emit(mach->JUMPIFop, mach->falseRep, mach->CBr, loopAddr);

  return NULL;
}

Object* Encoder::visitSequentialCommand(Object* obj, Object* o) {
	SequentialCommand* ast = (SequentialCommand*)obj;
    ast->C1->visit(this, o);
    ast->C2->visit(this, o);
    return NULL;
  }

Object* Encoder::visitWhileCommand(Object* obj, Object* o) {
	WhileCommand* ast = (WhileCommand*)obj;
    Frame* frame = (Frame*) o;
    int jumpAddr;
	int loopAddr;

    jumpAddr = nextInstrAddr;
	emit(mach->JUMPop, 0, mach->CBr, 0);
    loopAddr = nextInstrAddr;
    ast->C->visit(this, frame);
    patch(jumpAddr, nextInstrAddr);
    ast->E->visit(this, frame);
	emit(mach->JUMPIFop, mach->trueRep, mach->CBr, loopAddr);
    return NULL;
  }


  // Expressions
Object* Encoder::visitArrayExpression(Object* obj, Object* o) {
	ArrayExpression* ast = (ArrayExpression*) obj;
    ast->type->visit(this, NULL);
    return ast->AA->visit(this, o);
  }

Object* Encoder::visitBinaryExpression(Object* obj, Object* o) {
	BinaryExpression* ast = (BinaryExpression*)obj;
    Frame* frame = (Frame*) o;
    Integer* valSize = (Integer*) ast->type->visit(this, NULL);
    int valSize1 = ((Integer*) ast->E1->visit(this, frame))->value;
    Frame* frame1 = new Frame(frame, valSize1);
    int valSize2 = ((Integer*) ast->E2->visit(this, frame1))->value;
    Frame* frame2 = new Frame(frame->level, valSize1 + valSize2);
    ast->O->visit(this, frame2);
    return valSize;
  }

Object* Encoder::visitCallExpression(Object* obj, Object* o) {
	CallExpression* ast = (CallExpression*)obj;
  Frame* frame = (Frame*) o;
  Integer* valSize = (Integer*) ast->type->visit(this, NULL);
  Integer* argsSize = (Integer*) ast->APS->visit(this, frame);
  ast->I->visit(this, new Frame(frame->level, argsSize));
  if (ast->type->class_type() == "POINTERTYPEDENOTER")
  {
    int childSize = ((Integer *)((PointerTypeDenoter *) ast->type)->childType->visit(this, o))->value;
    emit(mach->LOADLop, 0, 0, childSize);
    emit(mach->CALLop, mach->SBr, mach->PBr, mach->newDisplacement);
    emit(mach->STOREIop, childSize, 0, 0);
  }
  return valSize;
}

Object* Encoder::visitCharacterExpression(Object* obj,Object* o) {
  CharacterExpression* ast = (CharacterExpression*)obj;
  Frame* frame = (Frame*) o;
  Integer* valSize = (Integer*) ast->type->visit(this, NULL);
  emit(mach->LOADLop, 0, 0, ast->CL->spelling.at(1));
  return valSize;
}

Object* Encoder::visitEmptyExpression(Object* obj, Object* o) {
  EmptyExpression* ast = (EmptyExpression*)obj;
  return new Integer(0);
}

Object* Encoder::visitIfExpression(Object* obj, Object* o) {
  IfExpression* ast = (IfExpression*)obj;
  Frame* frame = (Frame*) o;
  Integer* valSize;
  int jumpifAddr;
  int jumpAddr;

  ast->type->visit(this, NULL);
  ast->E1->visit(this, frame);
  jumpifAddr = nextInstrAddr;
  emit(mach->JUMPIFop, mach->falseRep, mach->CBr, 0);
  valSize = (Integer*) ast->E2->visit(this, frame);
  jumpAddr = nextInstrAddr;
  emit(mach->JUMPop, 0, mach->CBr, 0);
  patch(jumpifAddr, nextInstrAddr);
  valSize = (Integer*) ast->E3->visit(this, frame);
  patch(jumpAddr, nextInstrAddr);
  return valSize;
}

Object* Encoder::visitIntegerExpression(Object* obj, Object* o) {
  IntegerExpression* ast = (IntegerExpression*) obj;
  Frame* frame = (Frame*) o;
  Integer* valSize = (Integer*) ast->type->visit(this, NULL);
  emit(mach->LOADLop, 0, 0, atoi(ast->IL->spelling.c_str()));
  return valSize;
}

Object* Encoder::visitNilExpression(Object* obj, Object* o)
{
  // TODO - May want to load an address instead of an int
  emit(mach->LOADLop, 0, 0, 0);
  return new Integer(mach->integerSize);
}

Object* Encoder::visitPredExpression(Object* obj, Object* o)
{
  PredExpression *ast = (PredExpression *)obj;

  Integer *size = (Integer *)ast->E->visit(this, o);
  emit(mach->CALLop, mach->SBr, mach->PBr, mach->predDisplacement);

  return size;
}

Object* Encoder::visitStringExpression(Object* obj, Object* o)
{
  StringExpression *ast = (StringExpression *)obj;

  Integer *stringSize = (Integer *)ast->type->visit(this, NULL);
  int ch;
  for (int i=0; i<stringSize->value; i++)
  {
    ch = ast->SL->spelling.at(i+1);
    emit(mach->LOADLop, 0, 0, ch);
  }
  return stringSize;
}

Object* Encoder::visitSuccExpression(Object* obj, Object* o)
{
  SuccExpression *ast = (SuccExpression *)obj;

  Integer *size = (Integer *)ast->E->visit(this, o);
  emit(mach->CALLop, mach->SBr, mach->PBr, mach->succDisplacement);

  return size;
}

Object* Encoder::visitLetExpression(Object* obj, Object* o) {
	LetExpression* ast = (LetExpression*)obj;
  Frame* frame = (Frame*) o;
  ast->type->visit(this, NULL);
  int extraSize = ((Integer*) ast->D->visit(this, frame))->value;
  Frame* frame1 = new Frame(frame, extraSize);
  Integer* valSize = (Integer*) ast->E->visit(this, frame1);
  if (extraSize > 0)
  emit(mach->POPop, valSize->value, 0, extraSize);
  return valSize;
}

Object* Encoder::visitRecordExpression(Object* obj, Object* o){
  RecordExpression* ast = (RecordExpression*)obj;
  ast->type->visit(this, NULL);
  return ast->RA->visit(this, o);
}

Object* Encoder::visitUnaryExpression(Object* obj, Object* o) {
  UnaryExpression* ast = (UnaryExpression*)obj;
  Frame* frame = (Frame*) o;
  Integer* valSize = (Integer*) ast->type->visit(this, NULL);
  ast->E->visit(this, frame);
  ast->O->visit(this, new Frame(frame->level, valSize->value));
  return valSize;
}

Object* Encoder::visitVnameExpression(Object* obj, Object* o) {
  VnameExpression* ast =(VnameExpression*)obj;
  Frame* frame = (Frame*) o;
  Integer* valSize = (Integer*) ast->type->visit(this, NULL);
  encodeFetch(ast->V, frame, valSize->value);
  return valSize;
}


  // Declarations
Object* Encoder::visitBinaryOperatorDeclaration(Object* obj,Object* o){
	BinaryOperatorDeclaration* ast = (BinaryOperatorDeclaration*)obj;
  return new Integer(0);
}

Object* Encoder::visitConstDeclaration(Object* obj, Object* o) {
	ConstDeclaration* ast = (ConstDeclaration*)obj;
  Frame* frame = (Frame*) o;
  int extraSize = 0;

  if (ast->E->class_type() == "CHARACTEREXPRESSION") {
    CharacterLiteral* CL = ((CharacterExpression*) ast->E)->CL;
    ast->entity = new KnownValue(mach->characterSize,characterValuation(CL->spelling));
  } 
	else if (ast->E->class_type() =="INTEGEREXPRESSION") {
    IntegerLiteral* IL = ((IntegerExpression*) ast->E)->IL;
		ast->entity = new KnownValue(mach->integerSize,atoi(IL->spelling.c_str()));
  }
	else {
    int valSize = ((Integer*) ast->E->visit(this, frame))->value;
    ast->entity = new UnknownValue(valSize, frame->level, frame->size);
    extraSize = valSize;
  }
  writeTableDetails(ast);
  return new Integer(extraSize);
}

Object* Encoder::visitEnumDeclaration(Object* obj, Object* o)
{
  EnumDeclaration *ast = (EnumDeclaration *)obj;

  for (int i=0; i<ast->I.size(); i++)
  {
    if (ast->I[i]->decl)
      ast->I[i]->decl->entity = new KnownValue(mach->integerSize, i+1);
  }

  return new Integer(0);
}

Object* Encoder::visitEnumValueDeclaration(Object* obj, Object* o)
{
  EnumValueDeclaration *ast = (EnumValueDeclaration *)obj;

  return new Integer(0);
}

Object* Encoder::visitFuncBinOpDeclaration(Object* obj, Object* o)
{
  FuncBinOpDeclaration *ast = (FuncBinOpDeclaration *)obj;
  Frame *frame = (Frame *)o;

  int jumpAddr = nextInstrAddr;
  int argsSize = 0;
	int valSize = 0;

	emit(mach->JUMPop, 0, mach->CBr, 0);
	ast->D->entity = new KnownRoutine(mach->closureSize, frame->level, nextInstrAddr);

	if (frame->level == mach->maxRoutineLevel)
    reporter->reportRestriction("can't nest routines more than 7 deep");
  else {
    Frame* frame1 = new Frame(frame->level + 1, 0);
    argsSize += ((Integer*) ast->P2->visit(this, frame1))->value;
    Frame* frame2 = new Frame(frame->level + 1, argsSize);
    argsSize += ((Integer*) ast->P1->visit(this, frame2))->value;
	  Frame* frame3 = new Frame(frame->level + 1, mach->linkDataSize);
    valSize = ((Integer*) ast->E->visit(this, frame3))->value;
  }
	emit(mach->RETURNop, valSize, 0, argsSize);
  patch(jumpAddr, nextInstrAddr);

  return new Integer(0);
}

Object* Encoder::visitFuncDeclaration(Object* obj, Object* o) {
	FuncDeclaration* ast = (FuncDeclaration*)obj;
  Frame* frame = (Frame*) o;
  int jumpAddr = nextInstrAddr;
  int argsSize = 0;
	int valSize = 0;

	emit(mach->JUMPop, 0, mach->CBr, 0);
	ast->entity = new KnownRoutine(mach->closureSize, frame->level, nextInstrAddr);
  writeTableDetails(ast);

	if (frame->level == mach->maxRoutineLevel)
    reporter->reportRestriction("can't nest routines more than 7 deep");
  else {
    Frame* frame1 = new Frame(frame->level + 1, 0);
    argsSize = ((Integer*) ast->FPS->visit(this, frame1))->value;
    Frame* frame2 = new Frame(frame->level + 1, mach->linkDataSize);
    valSize = ((Integer*) ast->E->visit(this, frame2))->value;
  }
	emit(mach->RETURNop, valSize, 0, argsSize);
  patch(jumpAddr, nextInstrAddr);
  return new Integer(0);
}

Object* Encoder::visitFuncUnaryOpDeclaration(Object* obj, Object* o)
{
  FuncUnaryOpDeclaration *ast = (FuncUnaryOpDeclaration *)obj;
  Frame *frame = (Frame *)o;

  int jumpAddr = nextInstrAddr;
  int argsSize = 0;
	int valSize = 0;

	emit(mach->JUMPop, 0, mach->CBr, 0);
	ast->D->entity = new KnownRoutine(mach->closureSize, frame->level, nextInstrAddr);

	if (frame->level == mach->maxRoutineLevel)
    reporter->reportRestriction("can't nest routines more than 7 deep");
  else {
    Frame* frame1 = new Frame(frame->level + 1, 0);
    argsSize = ((Integer*) ast->P1->visit(this, frame1))->value;
	  Frame* frame2 = new Frame(frame->level + 1, mach->linkDataSize);
    valSize = ((Integer*) ast->E->visit(this, frame2))->value;
  }
	emit(mach->RETURNop, valSize, 0, argsSize);
  patch(jumpAddr, nextInstrAddr);

  return new Integer(0);
}

Object* Encoder::visitPackageDeclaration(Object* obj, Object* o)
{
  PackageDeclaration *ast = (PackageDeclaration *)obj;
  Frame *frame = (Frame *)o;
  int size = 0;

  if (ast->D2)
    size += ((Integer *)ast->D2->visit(this, frame))->value;
  size += ((Integer *)ast->D1->visit(this, frame))->value;

  return new Integer(size);
}

Object* Encoder::visitProcDeclaration(Object* obj, Object* o) {
	ProcDeclaration* ast = (ProcDeclaration*)obj;
  Frame* frame = (Frame*) o;
  int jumpAddr = nextInstrAddr;
  int argsSize = 0;

	emit(mach->JUMPop, 0, mach->CBr, 0);
	ast->entity = new KnownRoutine (mach->closureSize, frame->level,nextInstrAddr);
  writeTableDetails(ast);
	if (frame->level == mach->maxRoutineLevel)
    reporter->reportRestriction("can't nest routines so deeply");
  else {
    // Initialize secondary frame so that when the args are evaluated, space can be properly allocated
    helperFrame = new Frame(frame->level + 1, mach->linkDataSize);
    parameterEntries.clear();
    Frame* frame1 = new Frame(frame->level + 1, 0);
    argsSize = ((Integer*) ast->FPS->visit(this, frame1))->value;
	  
    // Create space for all result and value-result parameters(local copy)
    // Handle initilization of value-result parameters
    for (int i=0; i<parameterEntries.size(); i++)
    {
      int newSize = parameterEntries[i]->argSize;
      emit(mach->PUSHop, 0, 0, newSize);
      parameterEntries[i]->param->entity = new KnownAddress(newSize, helperFrame->level, helperFrame->size);
      if (parameterEntries[i]->copyIn)
      {
        // Transfer data in
        UnknownAddress *mainLoc = parameterEntries[i]->mainLoc;
        emit(mach->LOADop, mach->addressSize, displayRegister(helperFrame->level, mainLoc->address->level), mainLoc->address->displacement);
        emit(mach->LOADIop, newSize, 0, 0);
        emit(mach->STOREop, newSize, mach->LBr, helperFrame->size);
      }
      helperFrame = new Frame(helperFrame->level, newSize);
    }
    ast->C->visit(this, helperFrame);
    // Handle data transfer for result and value-result parameters
    int totalSize = 0;
    for (int i=0; i<parameterEntries.size(); i++)
    {
      // Transfer data out
      int newSize = parameterEntries[i]->argSize;
      KnownAddress *newLoc = (KnownAddress *)parameterEntries[i]->param->entity;
      UnknownAddress *mainLoc = parameterEntries[i]->mainLoc;
      emit(mach->LOADop, newSize, displayRegister(helperFrame->level, newLoc->address->level), newLoc->address->displacement);
      emit(mach->LOADop, mach->addressSize, displayRegister(helperFrame->level, mainLoc->address->level), mainLoc->address->displacement);
      emit(mach->STOREIop, newSize, 0, 0);
      totalSize += newSize;
    }
    emit(mach->POPop, 0, 0, totalSize);
    // Null the secondary frame just in case it is used improperly later
    helperFrame = NULL;
  }
	emit(mach->RETURNop, 0, 0, argsSize);
  patch(jumpAddr, nextInstrAddr);
  return new Integer(0);
}

Object* Encoder::visitRecTypeDeclaration(Object* obj, Object* o)
{
  RecTypeDeclaration *ast = (RecTypeDeclaration *)obj;

  ast->T->visit(this, NULL);

  return new Integer(0);
}

Object* Encoder::visitSequentialDeclaration(Object* obj, Object* o) {
  SequentialDeclaration* ast=(SequentialDeclaration*)obj;
  Frame* frame = (Frame*) o;
  int extraSize1;
  int extraSize2;

  extraSize1 = ((Integer*) ast->D1->visit(this, frame))->value;
  Frame* frame1 = new Frame (frame, extraSize1);
  extraSize2 = ((Integer*) ast->D2->visit(this, frame1))->value;
  return new Integer(extraSize1 + extraSize2);
}

Object* Encoder::visitTypeDeclaration(Object* obj, Object* o) {
  TypeDeclaration* ast = (TypeDeclaration*)obj;
  // just to ensure the type's representation is decided
  ast->T->visit(this, NULL);
  return new Integer(0);
}

Object* Encoder::visitUnaryOperatorDeclaration(Object* obj,Object* o) {
  UnaryOperatorDeclaration* ast = (UnaryOperatorDeclaration*)obj;
  return new Integer(0);
}

Object* Encoder::visitVarDeclaration(Object* obj, Object* o) {
  VarDeclaration* ast = (VarDeclaration*)obj;
  Frame* frame = (Frame*) o;
  int extraSize;

  extraSize = ((Integer*) ast->T->visit(this, NULL))->value;
  emit(mach->PUSHop, 0, 0, extraSize);
  if (ast->T->class_type() == "VARSTRINGTYPEDENOTER")
    ast->entity = new HeapAddress(mach->addressSize, frame->level, frame->size);
  else if (ast->T->class_type() == "POINTERTYPEDENOTER")
  {
    Integer *childSize = (Integer *)((PointerTypeDenoter *) ast->T)->childType->visit(this, o);
    ast->entity = new PointerAddress(mach->addressSize, frame->level, frame->size, childSize->value);
  }
  else
    ast->entity = new KnownAddress(mach->addressSize, frame->level, frame->size);
  writeTableDetails(ast);
  return new Integer(extraSize);
}

Object* Encoder::visitVarInitDeclaration(Object* obj, Object* o)
{
  VarInitDeclaration* ast = (VarInitDeclaration*)obj;
  Frame* frame = (Frame*) o;
  int extraSize;

  extraSize = ((Integer*) ast->T->visit(this, NULL))->value;
	emit(mach->PUSHop, 0, 0, extraSize);
	ast->entity = new KnownAddress(mach->addressSize, frame->level, frame->size);
  ast->E->visit(this, o);
  emit(mach->STOREop, extraSize, displayRegister(frame->level, frame->level), frame->size);
  return new Integer(extraSize);
}


  // Array Aggregates
Object* Encoder::visitMultipleArrayAggregate(Object* obj,Object* o) {
	MultipleArrayAggregate* ast = (MultipleArrayAggregate*)obj;
  Frame* frame = (Frame*) o;
  int elemSize = ((Integer*) ast->E->visit(this, frame))->value;
  Frame* frame1 = new Frame(frame, elemSize);
  int arraySize = ((Integer*) ast->AA->visit(this, frame1))->value;
  return new Integer(elemSize + arraySize);
}

Object* Encoder::visitSingleArrayAggregate(Object* obj, Object* o) {
	SingleArrayAggregate* ast = (SingleArrayAggregate*)obj;
  return ast->E->visit(this, o);
}


  // Record Aggregates
Object* Encoder::visitMultipleRecordAggregate(Object* obj,Object* o) {
	MultipleRecordAggregate* ast =(MultipleRecordAggregate*)obj;
  Frame* frame = (Frame*) o;
  int fieldSize = ((Integer*) ast->E->visit(this, frame))->value;
  Frame* frame1 = new Frame (frame, fieldSize);
  int recordSize = ((Integer*) ast->RA->visit(this, frame1))->value;
  return new Integer(fieldSize + recordSize);
}

Object* Encoder::visitSingleRecordAggregate(Object* obj,Object* o) {
	SingleRecordAggregate* ast = (SingleRecordAggregate*)obj;
  return ast->E->visit(this, o);
}


  // Formal Parameters
Object* Encoder::visitConstFormalParameter(Object* obj, Object* o) {
	ConstFormalParameter* ast = (ConstFormalParameter*)obj;
  Frame* frame = (Frame*) o;
  int valSize = ((Integer*) ast->T->visit(this, NULL))->value;
  if (ast->T->class_type() == "POINTERTYPEDENOTER")
  {
    int childSize = ((Integer *)((PointerTypeDenoter *)ast->T)->childType->visit(this, NULL))->value;
    ast->entity = new PointerAddress(valSize, frame->level, -frame->size-valSize, childSize);
  }
  else
    ast->entity = new UnknownValue (valSize, frame->level, -frame->size - valSize);
  writeTableDetails(ast);
  return new Integer(valSize);
}

Object* Encoder::visitFuncFormalParameter(Object* obj, Object* o) {
	FuncFormalParameter* ast = (FuncFormalParameter*)obj;
  Frame* frame = (Frame*) o;
	int argsSize = mach->closureSize;
	ast->entity = new UnknownRoutine (mach->closureSize, frame->level, -frame->size - argsSize);
  writeTableDetails(ast);
  return new Integer(argsSize);
}

Object* Encoder::visitProcFormalParameter(Object* obj, Object* o) {
	ProcFormalParameter* ast = (ProcFormalParameter*)obj;
  Frame* frame = (Frame*) o;
	int argsSize = mach->closureSize;
	ast->entity = new UnknownRoutine (mach->closureSize, frame->level,-frame->size - argsSize);
  writeTableDetails(ast);
  return new Integer(argsSize);
}

Object* Encoder::visitResultFormalParameter(Object* obj, Object* o)
{
  ResultFormalParameter *ast = (ResultFormalParameter *)obj;
  Frame* frame = (Frame*) o;
  int valSize = ((Integer *)ast->T->visit(this, o))->value;
  UnknownAddress *mainLocation = new UnknownAddress (mach->addressSize, frame->level,-frame->size - mach->addressSize);
  ResultParameterInfo *entry = new ResultParameterInfo(ast, mainLocation, valSize, false);
  parameterEntries.push_back(entry);

  return new Integer(mach->addressSize);
}

Object* Encoder::visitValueResultFormalParameter(Object* obj, Object* o)
{
  ValueResultFormalParameter *ast = (ValueResultFormalParameter *)obj;
  Frame* frame = (Frame*) o;
  int valSize = ((Integer *)ast->T->visit(this, o))->value;
  UnknownAddress *mainLocation = new UnknownAddress (mach->addressSize, frame->level,-frame->size - mach->addressSize);
  ResultParameterInfo *entry = new ResultParameterInfo(ast, mainLocation, valSize, true);
  parameterEntries.push_back(entry);

  return new Integer(mach->addressSize);
}

Object* Encoder::visitVarFormalParameter(Object* obj, Object* o) {
	VarFormalParameter* ast = (VarFormalParameter*)obj;
  Frame* frame = (Frame*) o;
  ast->T->visit(this, NULL);
  ast->entity = new UnknownAddress (mach->addressSize, frame->level,-frame->size - mach->addressSize);
  writeTableDetails(ast);
  return new Integer(mach->addressSize);
}


Object* Encoder::visitEmptyFormalParameterSequence(Object* obj, Object* o) {
	EmptyFormalParameterSequence* ast = (EmptyFormalParameterSequence*)obj;
  return new Integer(0);
}

Object* Encoder::visitMultipleFormalParameterSequence(Object* obj, Object* o) {
	MultipleFormalParameterSequence* ast = (MultipleFormalParameterSequence*)obj;
  Frame* frame = (Frame*) o;
  int argsSize1 = ((Integer*) ast->FPS->visit(this, frame))->value;
  Frame* frame1 = new Frame(frame, argsSize1);
  int argsSize2 = ((Integer*) ast->FP->visit(this, frame1))->value;
  return new Integer(argsSize1 + argsSize2);
}

Object* Encoder::visitSingleFormalParameterSequence(Object* obj, Object* o) {
	SingleFormalParameterSequence* ast = (SingleFormalParameterSequence*)obj;
  return ast->FP->visit (this, o);
}


  // Actual Parameters
Object* Encoder::visitConstActualParameter(Object* obj, Object* o) {
	ConstActualParameter* ast =(ConstActualParameter*)obj;
    return ast->E->visit (this, o);
  }

Object* Encoder::visitFuncActualParameter(Object* obj, Object* o) {
	FuncActualParameter* ast = (FuncActualParameter*)obj;
    Frame* frame = (Frame*) o;
    if (ast->I->decl->entity->class_type() == "KNOWNROUTINE") {
      ObjectAddress* address = ((KnownRoutine*) ast->I->decl->entity)->address;
      // static link, code address
	  emit(mach->LOADAop, 0, displayRegister(frame->level, address->level), 0);
	  emit(mach->LOADAop, 0, mach->CBr, address->displacement);
		}
	else if (ast->I->decl->entity->class_type() == "UNKNOWNROUTINE") {
      ObjectAddress* address = ((UnknownRoutine*) ast->I->decl->entity)->address;
	  emit(mach->LOADop, mach->closureSize, displayRegister(frame->level,
           address->level), address->displacement);
		}
	else if (ast->I->decl->entity->class_type() == "PRIMITIVEROUTINE") {
      int displacement = ((PrimitiveRoutine*) ast->I->decl->entity)->displacement;
      // static link, code address
	  emit(mach->LOADAop, 0, mach->SBr, 0);
	  emit(mach->LOADAop, 0, mach->PBr, displacement);
    }
	return new Integer(mach->closureSize);
  }

Object* Encoder::visitProcActualParameter(Object* obj, Object* o) {
	ProcActualParameter* ast = (ProcActualParameter*)obj;
    Frame* frame = (Frame*) o;
    if (ast->I->decl->entity->class_type() == "KNOWNROUTINE") {
      ObjectAddress* address = ((KnownRoutine*) ast->I->decl->entity)->address;
      // static link, code address
	  emit(mach->LOADAop, 0, displayRegister(frame->level, address->level), 0);
	  emit(mach->LOADAop, 0, mach->CBr, address->displacement);
		}
	else if (ast->I->decl->entity->class_type() == "UNKNOWNROUTINE") {
      ObjectAddress* address = ((UnknownRoutine*) ast->I->decl->entity)->address;
	  emit(mach->LOADop, mach->closureSize, displayRegister(frame->level,
           address->level), address->displacement);
		}
	else if (ast->I->decl->entity->class_type() == "PRIMITIVEROUTINE") {
      int displacement = ((PrimitiveRoutine*) ast->I->decl->entity)->displacement;
      // static link, code address
	  emit(mach->LOADAop, 0, mach->SBr, 0);
	  emit(mach->LOADAop, 0, mach->PBr, displacement);
    }
	return new Integer(mach->closureSize);
  }

Object* Encoder::visitVarActualParameter(Object* obj, Object* o) {
	VarActualParameter* ast = (VarActualParameter*)obj;
    encodeFetchAddress(ast->V, (Frame*) o);
	return new Integer(mach->addressSize);
  }


Object* Encoder::visitEmptyActualParameterSequence(Object* obj, Object* o) {
	EmptyActualParameterSequence* ast = (EmptyActualParameterSequence*)obj;
    return new Integer(0);
  }

Object* Encoder::visitMultipleActualParameterSequence(Object* obj, Object* o) {
	MultipleActualParameterSequence* ast = (MultipleActualParameterSequence*)obj;
    Frame* frame = (Frame*) o;
    int argsSize1 = ((Integer*) ast->AP->visit(this, frame))->value;
    Frame* frame1 = new Frame (frame, argsSize1);
    int argsSize2 = ((Integer*) ast->APS->visit(this, frame1))->value;
    return new Integer(argsSize1 + argsSize2);
  }

Object* Encoder::visitSingleActualParameterSequence(Object* obj, Object* o) {
	SingleActualParameterSequence* ast = (SingleActualParameterSequence*)obj;
    return ast->AP->visit (this, o);
  }


  // Type Denoters
Object* Encoder::visitAnyTypeDenoter(Object* obj, Object* o) {
	AnyTypeDenoter* ast = (AnyTypeDenoter*)obj;
    return new Integer(0);
  }

Object* Encoder::visitArrayTypeDenoter(Object* obj, Object* o) {
	ArrayTypeDenoter* ast = (ArrayTypeDenoter*)obj;
    int typeSize;
    if (ast->entity == NULL) {
      int elemSize = ((Integer*) ast->T->visit(this, NULL))->value;
      typeSize = (atoi(ast->IL->spelling.c_str())) * elemSize;
      ast->entity = new TypeRepresentation(typeSize);
      writeTableDetails(ast);
		}
	else
      typeSize = ast->entity->size;
    return new Integer(typeSize);
  }

Object* Encoder::visitBoolTypeDenoter(Object* obj, Object* o) {
	BoolTypeDenoter* ast = (BoolTypeDenoter*)obj;
    if (ast->entity == NULL) {
		ast->entity = new TypeRepresentation(mach->booleanSize);
      writeTableDetails(ast);
    }
	return new Integer(mach->booleanSize);
  }

Object* Encoder::visitCharTypeDenoter(Object* obj, Object* o) {
	CharTypeDenoter* ast = (CharTypeDenoter*)obj;
    if (ast->entity == NULL) {
		ast->entity = new TypeRepresentation(mach->characterSize);
      writeTableDetails(ast);
    }
	return new Integer(mach->characterSize);
  }

Object* Encoder::visitEnumTypeDenoter(Object* obj, Object* o)
{
  EnumTypeDenoter *ast = (EnumTypeDenoter *)obj;
  ast->entity = new TypeRepresentation(mach->integerSize);
  return new Integer(mach->integerSize);
}

Object* Encoder::visitErrorTypeDenoter(Object* obj, Object* o) {
  ErrorTypeDenoter* ast = (ErrorTypeDenoter*)obj;
  return new Integer(0);
}

Object* Encoder::visitNilTypeDenoter(Object* obj, Object* o)
{
  NilTypeDenoter *ast = (NilTypeDenoter *)obj;
  ast->entity = new TypeRepresentation(mach->addressSize);
  return new Integer(mach->addressSize);
}
Object* Encoder::visitPointerTypeDenoter(Object* obj, Object* o)
{
  PointerTypeDenoter *ast = (PointerTypeDenoter *)obj;

  // Ensure you only visit this fully once
  if (ast->entity == NULL)
  {
    ast->entity = new TypeRepresentation(mach->addressSize);
    ast->childType->visit(this, o);
  }

  return new Integer(mach->addressSize);
}

Object* Encoder::visitSimpleTypeDenoter(Object* obj,Object* o) {
  SimpleTypeDenoter* ast = (SimpleTypeDenoter*)obj;
  return new Integer(0);
}

Object* Encoder::visitStringTypeDenoter(Object* obj,Object* o)
{
  StringTypeDenoter *ast = (StringTypeDenoter *)obj;

  int size = atoi(ast->IL->spelling.c_str());
  ast->entity = new TypeRepresentation(size);
  return new Integer(size);
}

Object* Encoder::visitVarStringTypeDenoter(Object* obj,Object* o)
{
  VarStringTypeDenoter *ast = (VarStringTypeDenoter *)obj;

  // Variable-length strings have a handle that consists of a length field and pointer(to a location in the heap)
  int size = mach->integerSize+mach->addressSize;
  ast->entity = new TypeRepresentation(size);
  return new Integer(size);
}

Object* Encoder::visitIntTypeDenoter(Object* obj, Object* o) {
	IntTypeDenoter* ast = (IntTypeDenoter*)obj;
    if (ast->entity == NULL) {
		ast->entity = new TypeRepresentation(mach->integerSize);
      writeTableDetails(ast);
    }
	return new Integer(mach->integerSize);
  }

Object* Encoder::visitRecordTypeDenoter(Object* obj, Object* o) {
	RecordTypeDenoter* ast = (RecordTypeDenoter*)obj;
    int typeSize;
    if (ast->entity == NULL) {
		typeSize = ((Integer*) ast->FT->visit(this, new Integer(0)))->value;
		ast->entity = new TypeRepresentation(typeSize);
		writeTableDetails(ast);
		}
	else
      typeSize = ast->entity->size;
    return new Integer(typeSize);
  }


Object* Encoder::visitMultipleFieldTypeDenoter(Object* obj,Object* o) {
	MultipleFieldTypeDenoter* ast = (MultipleFieldTypeDenoter*)obj;
    int offset = ((Integer*) o)->value;
    int fieldSize;

    if (ast->entity == NULL) {
      fieldSize = ((Integer*) ast->T->visit(this, NULL))->value;
      ast->entity = new Field (fieldSize, offset);
      writeTableDetails(ast);
		} 
	else
      fieldSize = ast->entity->size;

    Integer* offset1 = new Integer(offset + fieldSize);
    int recSize = ((Integer*) ast->FT->visit(this, offset1))->value;
    return new Integer(fieldSize + recSize);
  }

Object* Encoder::visitSingleFieldTypeDenoter(Object* obj,Object* o) {
	  SingleFieldTypeDenoter* ast = (SingleFieldTypeDenoter*)obj;
    int offset = ((Integer*) o)->value;
    int fieldSize;

    if (ast->entity == NULL) {
      fieldSize = ((Integer*) ast->T->visit(this, NULL))->value;
      ast->entity = new Field (fieldSize, offset);
      writeTableDetails(ast);
		}
	else
      fieldSize = ast->entity->size;

    return new Integer(fieldSize);
  }


  // Literals, Identifiers and Operators
Object* Encoder::visitCharacterLiteral(Object* obj, Object* o) {
	CharacterLiteral* ast = (CharacterLiteral*)obj;
    return NULL;
  }

Object* Encoder::visitIdentifier(Object* obj, Object* o) {
  Identifier* ast = (Identifier*)obj;
  Frame* frame = (Frame*) o;
  if (ast->decl->entity->class_type() == "KNOWNROUTINE") {
    ObjectAddress* address = ((KnownRoutine*) ast->decl->entity)->address;
    emit(mach->CALLop, displayRegister(frame->level, address->level),mach->CBr, address->displacement);
  }
  else if (ast->decl->entity->class_type() == "UNKNOWNROUTINE") {
    ObjectAddress* address = ((UnknownRoutine*) ast->decl->entity)->address;
    emit(mach->LOADop, mach->closureSize, displayRegister(frame->level,address->level), address->displacement);
    emit(mach->CALLIop, 0, 0, 0);
  }
  else if (ast->decl->entity->class_type() == "PRIMITIVEROUTINE") {
    int displacement = ((PrimitiveRoutine*) ast->decl->entity)->displacement;

    if (displacement != mach->idDisplacement)
      emit(mach->CALLop, mach->SBr, mach->PBr, displacement);
  }
  else if (ast->decl->entity->class_type() == "EQUALITYROUTINE") { // "=" or "\="
    int displacement = ((EqualityRoutine*) ast->decl->entity)->displacement;
    emit(mach->LOADLop, 0, 0, frame->size / 2);
    emit(mach->CALLop, mach->SBr, mach->PBr, displacement);
  }
  return NULL;
}

Object* Encoder::visitPackageIdentifier(Object* obj, Object* o)
{
  // Handling of PackageIdentifiers at this stage is identical to Identifiers
  visitIdentifier(obj, o);

  return NULL;
}

Object* Encoder::visitIntegerLiteral(Object* obj, Object* o) {
  IntegerLiteral* ast = (IntegerLiteral*)obj;
  return NULL;
}

Object* Encoder::visitOperator(Object* obj, Object* o) {
  Operator* ast = (Operator*)obj;
  Frame* frame = (Frame*) o;
  if (ast->decl->entity->class_type() == "KNOWNROUTINE") {
    ObjectAddress* address = ((KnownRoutine*) ast->decl->entity)->address;
    emit(mach->CALLop, displayRegister (frame->level, address->level),mach->CBr, address->displacement);
  }
  else if (ast->decl->entity->class_type() == "UnknownRoutine") {
    ObjectAddress* address = ((UnknownRoutine*) ast->decl->entity)->address;
    emit(mach->LOADop, mach->closureSize, displayRegister(frame->level,address->level),
    address->displacement);
    emit(mach->CALLIop, 0, 0, 0);
  }
  else if (ast->decl->entity->class_type() =="PRIMITIVEROUTINE") {
    int displacement = ((PrimitiveRoutine*) ast->decl->entity)->displacement;
    if (displacement != mach->idDisplacement)
      emit(mach->CALLop, mach->SBr, mach->PBr, displacement);
  }
  else if (ast->decl->entity->class_type() == "EQUALITYROUTINE") { // "=" or "\="
    int displacement = ((EqualityRoutine*) ast->decl->entity)->displacement;
    emit(mach->LOADLop, 0, 0, frame->size / 2);
    emit(mach->CALLop, mach->SBr, mach->PBr, displacement);
  }
  return NULL;
}

Object* Encoder::visitStringLiteral(Object* obj, Object* o)
{
  StringLiteral *ast = (StringLiteral *)obj;

  return NULL;
}


  // Value-or-variable names
Object* Encoder::visitDotVname(Object* obj, Object* o) {
	DotVname* ast = (DotVname*)obj;
  Frame* frame = (Frame*) o;
  RuntimeEntity* baseObject = (RuntimeEntity*) ast->V->visit(this, frame);
  ast->offset = ast->V->offset + ((Field*) ast->I->decl->entity)->fieldOffset;
  // I.decl points to the appropriate record field
  ast->indexed = ast->V->indexed;
  return baseObject;
}

Object* Encoder::visitSimpleVname(Object* obj, Object* o) {
	SimpleVname* ast = (SimpleVname*)obj;
  ast->offset = 0;
  ast->indexed = false;
  return ast->I->decl->entity;
}

Object* Encoder::visitSubscriptVname(Object* obj, Object* o) {
  SubscriptVname* ast = (SubscriptVname*)obj;
  Frame* frame = (Frame*) o;
  RuntimeEntity* baseObject;
  int elemSize;
  int indexSize;

  baseObject = (RuntimeEntity*) ast->V->visit(this, frame);
  ast->offset = ast->V->offset;
  ast->indexed = ast->V->indexed;
  elemSize = ((Integer*) ast->type->visit(this, NULL))->value;

  if (ast->E->class_type() == "INTEGEREXPRESSION") {
    IntegerLiteral* IL = ((IntegerExpression*) ast->E)->IL;
    ast->offset = ast->offset + atoi(IL->spelling.c_str()) * elemSize;
  }
  else {
    // v-name is indexed by a proper expression, not a literal
    if (ast->indexed)
      frame->size = frame->size + mach->integerSize;
    indexSize = ((Integer*) ast->E->visit(this, frame))->value;

    // 9.15 Index checking
    emit(mach->LOADLop, 0, 0, 0);
    emit(mach->LOADLop, 0, 0, atoi(((ArrayTypeDenoter *)ast->V->type)->IL->spelling.c_str()));
    emit(mach->CALLop, mach->SBr, mach->PBr, mach->rangecheckDisplacement);

    if (elemSize != 1) {
      emit(mach->LOADLop, 0, 0, elemSize);
      emit(mach->CALLop, mach->SBr, mach->PBr,mach->multDisplacement);
    }
    if (ast->indexed)
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
    else
      ast->indexed = true;
  }
  return baseObject;
}


  // Programs
Object* Encoder::visitProgram(Object* obj, Object* o) {
	Program* ast = (Program*)obj;
  return ast->C->visit(this, o);
}

Encoder::Encoder (ErrorReporter* reporter,Checker* check_std) {
  this->reporter = reporter;
	
  mach=new Machine();
	
  getvarz = check_std->getvariables;
  nextInstrAddr = mach->CB;
	
  elaborateStdEnvironment();
}


// Generates code to run a program.
// showingTable is true iff entity description details
// are to be displayed.
void Encoder::encodeRun (Program* theAST, bool showingTable) {
  tableDetailsReqd = showingTable;
  //startCodeGeneration();
  theAST->visit(this, new Frame (0, 0));
  emit(mach->HALTop, 0, 0, 0);
}

// Decides run-time representation of a standard constant.
void Encoder::elaborateStdConst (Object* obj,int value) {
  Declaration* constDeclaration = (Declaration*)obj;

  if (constDeclaration->class_type() == "CONSTDECLARATION") {
    ConstDeclaration* decl = (ConstDeclaration*) constDeclaration;
    int typeSize= ((Integer*) decl->E->type->visit(this, NULL))->value;
    decl->entity = new KnownValue(typeSize, value);
    writeTableDetails(constDeclaration);
  }
}

// Decides run-time representation of a standard routine.
void Encoder::elaborateStdPrimRoutine (Object* obj,int routineOffset) {
  Declaration* routineDeclaration = (Declaration*)obj;
  routineDeclaration->entity = new PrimitiveRoutine (mach->closureSize, routineOffset);
  writeTableDetails(routineDeclaration);
}

void Encoder::elaborateStdEqRoutine (Object* obj,int routineOffset) {
	Declaration* routineDeclaration = (Declaration*)obj;
	routineDeclaration->entity = new EqualityRoutine (mach->closureSize, routineOffset);
    writeTableDetails(routineDeclaration);
  }

void Encoder::elaborateStdRoutine (Object* obj,int routineOffset) {
	Declaration* routineDeclaration = (Declaration*)obj;
	routineDeclaration->entity = new KnownRoutine (mach->closureSize, 0, routineOffset);
    writeTableDetails(routineDeclaration);
  }

void Encoder::elaborateStdEnvironment() {
    tableDetailsReqd = false;
	elaborateStdConst(getvarz->falseDecl, mach->falseRep);
	elaborateStdConst(getvarz->trueDecl, mach->trueRep);
	elaborateStdPrimRoutine(getvarz->notDecl, mach->notDisplacement);
	
	elaborateStdPrimRoutine(getvarz->andDecl, mach->andDisplacement);
	elaborateStdPrimRoutine(getvarz->orDecl, mach->orDisplacement);
	elaborateStdConst(getvarz->maxintDecl, mach->maxintRep);
	elaborateStdPrimRoutine(getvarz->addDecl, mach->addDisplacement);
	elaborateStdPrimRoutine(getvarz->subtractDecl, mach->subDisplacement);
	elaborateStdPrimRoutine(getvarz->multiplyDecl, mach->multDisplacement);
	elaborateStdPrimRoutine(getvarz->divideDecl, mach->divDisplacement);
	elaborateStdPrimRoutine(getvarz->moduloDecl, mach->modDisplacement);
	elaborateStdPrimRoutine(getvarz->lessDecl, mach->ltDisplacement);
	elaborateStdPrimRoutine(getvarz->notgreaterDecl, mach->leDisplacement);
	elaborateStdPrimRoutine(getvarz->greaterDecl, mach->gtDisplacement);
	elaborateStdPrimRoutine(getvarz->notlessDecl, mach->geDisplacement);
	elaborateStdPrimRoutine(getvarz->chrDecl, mach->idDisplacement);
	elaborateStdPrimRoutine(getvarz->ordDecl, mach->idDisplacement);
	elaborateStdPrimRoutine(getvarz->eolDecl, mach->eolDisplacement);
	elaborateStdPrimRoutine(getvarz->eofDecl, mach->eofDisplacement);
	elaborateStdPrimRoutine(getvarz->getDecl, mach->getDisplacement);
	elaborateStdPrimRoutine(getvarz->putDecl, mach->putDisplacement);
	elaborateStdPrimRoutine(getvarz->getintDecl, mach->getintDisplacement);
	elaborateStdPrimRoutine(getvarz->putintDecl, mach->putintDisplacement);
	elaborateStdPrimRoutine(getvarz->geteolDecl, mach->geteolDisplacement);
	elaborateStdPrimRoutine(getvarz->puteolDecl, mach->puteolDisplacement);
  elaborateStdEqRoutine(getvarz->strcompDecl, mach->strcmpDisplacement);
	elaborateStdEqRoutine(getvarz->equalDecl, mach->eqDisplacement);
	elaborateStdEqRoutine(getvarz->unequalDecl, mach->neDisplacement);
	
  //elaborateStdRoutine(getvarz->strcompDecl, 0);
  }

  // Saves the object program in the named file.

void Encoder::saveObjectProgram(string objectName) {

	//FILE* objectStream = fopen(objectName.c_str(),"w");

    
	std::ofstream objectStream(objectName.c_str(),ios_base::binary);//,ios::binary);
	
	//objectStreadddm.open("something.txt");


    int addr;

   
	addr = mach->CB;
	for (addr = mach->CB; addr < nextInstrAddr; addr++)
		mach->code[addr]->write(objectStream);
	}
      

  void Encoder::writeTableDetails(AST* ast) {

	//  printf("This is the class: %s\n",ast->class_type().c_str());
  }

  // OBJECT CODE

  // Implementation notes:
  // Object code is generated directly into the TAM Code Store, starting at CB.
  // The address of the next instruction is held in nextInstrAddr.

  int nextInstrAddr;

  // Appends an instruction, with the given fields, to the object code.
  void Encoder::emit (int op, int n, int r, int d) {
    Instruction* nextInstr = new Instruction();
    if (n > 255) {
        reporter->reportRestriction("length of operand can't exceed 255 words");
        n = 255; // to allow code generation to continue
    }
    nextInstr->op = op;
    nextInstr->n = n;
    nextInstr->r = r;
    nextInstr->d = d;
    if (nextInstrAddr == mach->PB)
      reporter->reportRestriction("too many instructions for code segment");
    else {
		mach->code[nextInstrAddr] = nextInstr;
        nextInstrAddr = nextInstrAddr + 1;
    }
  }

  // Patches the d-field of the instruction at address addr.
  void Encoder::patch (int addr, int d) {
	  mach->code[addr]->d = d;
  }

  // DATA REPRESENTATION


  
  int Encoder::characterValuation (string spelling) {
  // Returns the machine representation of the given character literal.
	  int temp = (int)spelling.at(1);
		return temp;
      // since the character literal is of the form 'x'}
  }

  // REGISTERS

  // Returns the register number appropriate for object code at currentLevel
  // to address a data object at objectLevel.
  int Encoder::displayRegister (int currentLevel, int objectLevel) {
    if (objectLevel == 0)
      return mach->SBr;
    else if (currentLevel - objectLevel <= 6)
      return mach->LBr + currentLevel - objectLevel; // LBr|L1r|...|L6r
    else {
      reporter->reportRestriction("can't access data more than 6 levels out");
      return mach->L6r;  // to allow code generation to continue
    }
  }

  // Generates code to fetch the value of a named constant or variable
  // and push it on to the stack.
  // currentLevel is the routine level where the vname occurs.
  // frameSize is the anticipated size of the local stack frame when
  // the constant or variable is fetched at run-time.
  // valSize is the size of the constant or variable's value.

void Encoder::encodeStore(Vname* V, Frame* frame, int valSize) {
  RuntimeEntity* baseObject = (RuntimeEntity*) V->visit(this, frame);
  // If indexed = true, code will have been generated to load an index value.
  if (valSize > 255) {
    reporter->reportRestriction("can't store values larger than 255 words");
    valSize = 255; // to allow code generation to continue
  }
  if (baseObject->class_type() == "KNOWNADDRESS") {
    ObjectAddress* address = ((KnownAddress*) baseObject)->address;
    if (V->indexed) {
      emit(mach->LOADAop, 0, displayRegister(frame->level, address->level), address->displacement + V->offset);
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
      emit(mach->STOREIop, valSize, 0, 0);
    } else {
      emit(mach->STOREop, valSize, displayRegister(frame->level, address->level), address->displacement + V->offset);
    }
  } else if (baseObject->class_type() == "UNKNOWNADDRESS") {
    ObjectAddress* address = ((UnknownAddress*) baseObject)->address;
    emit(mach->LOADop, mach->addressSize, displayRegister(frame->level, address->level), address->displacement);
    if (V->indexed)
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
    if (V->offset != 0) {
      emit(mach->LOADLop, 0, 0, V->offset);
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
    }
    emit(mach->STOREIop, valSize, 0, 0);
  } else if (baseObject->class_type() == "HEAPADDRESS") {
    ObjectAddress* address = ((HeapAddress*) baseObject)->address;
    // Load the length field
    emit(mach->LOADop, mach->integerSize, displayRegister(frame->level, address->level), address->displacement);
    emit(mach->CALLop, mach->SBr, mach->PBr, mach->newDisplacement);
    // Store the address in the pointer field
    emit(mach->STOREop, mach->addressSize, displayRegister(frame->level, address->level), address->displacement + 1);
    emit(mach->LOADop, mach->addressSize, displayRegister(frame->level, address->level), address->displacement + 1);
    emit(mach->STOREIop, 1, 0, 0);
  } else if (baseObject->class_type() == "POINTERADDRESS") {
    ObjectAddress* address = ((PointerAddress*) baseObject)->address;
    emit(mach->LOADop, mach->addressSize, displayRegister(frame->level, address->level), address->displacement);
    emit(mach->STOREIop, ((PointerAddress*) baseObject)->childSize, 0, 0);
  }
}

// Generates code to fetch the value of a named constant or variable
// and push it on to the stack.
// currentLevel is the routine level where the vname occurs.
// frameSize is the anticipated size of the local stack frame when
// the constant or variable is fetched at run-time.
// valSize is the size of the constant or variable's value.
void Encoder::encodeFetch(Vname* V, Frame* frame, int valSize)
{
  RuntimeEntity* baseObject = (RuntimeEntity*) V->visit(this, frame);
  // If indexed = true, code will have been generated to load an index value.
  if (valSize > 255) {
    reporter->reportRestriction("can't load values larger than 255 words");
    valSize = 255; // to allow code generation to continue
  }
  if (baseObject->class_type() == "KNOWNVALUE") {
    // presumably offset = 0 and indexed = false
    int value = ((KnownValue*) baseObject)->value;
    emit(mach->LOADLop, 0, 0, value);
	} else if ( (baseObject->class_type() == "UNKNOWNVALUE") ||
              (baseObject->class_type() == "KNOWNADDRESS")) {
    ObjectAddress* address = (baseObject->class_type() == "UNKNOWNVALUE") ?
      ((UnknownValue*) baseObject)->address :
      ((KnownAddress*) baseObject)->address;
    if (V->indexed) {
      emit(mach->LOADAop, 0, displayRegister(frame->level, address->level), address->displacement + V->offset);
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
      emit(mach->LOADIop, valSize, 0, 0);
    } else
      emit(mach->LOADop, valSize, displayRegister(frame->level, address->level), address->displacement + V->offset);
  }
	else if (baseObject->class_type() == "UNKNOWNADDRESS") {
    ObjectAddress* address = ((UnknownAddress*) baseObject)->address;
    emit(mach->LOADop, mach->addressSize, displayRegister(frame->level, address->level), address->displacement);
    if (V->indexed)
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
    if (V->offset != 0) {
      emit(mach->LOADLop, 0, 0, V->offset);
      emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
    }
    emit(mach->LOADIop, valSize, 0, 0);
  } else if (baseObject->class_type() == "POINTERADDRESS") {
    ObjectAddress* address = ((PointerAddress*) baseObject)->address;
    emit(mach->LOADop, mach->addressSize, displayRegister(frame->level, address->level), address->displacement);
    emit(mach->LOADIop, ((PointerAddress*) baseObject)->childSize, 0, 0);
  }
}

  // Generates code to compute and push the address of a named variable.
  // vname is the program phrase that names this variable.
  // currentLevel is the routine level where the vname occurs.
  // frameSize is the anticipated size of the local stack frame when
  // the variable is addressed at run-time.

  void Encoder::encodeFetchAddress (Vname* V, Frame* frame) {

    RuntimeEntity* baseObject = (RuntimeEntity*) V->visit(this, frame);
    // If indexed = true, code will have been generated to load an index value.
	if (baseObject->class_type() == "KNOWNADDRESS") {
		ObjectAddress* address = ((KnownAddress*) baseObject)->address;
		emit(mach->LOADAop, 0, displayRegister(frame->level, address->level),
           address->displacement + V->offset);
      if (V->indexed)
		  emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
    
	} else if (baseObject->class_type() == "UNKNOWNADDRESS") {

      ObjectAddress* address = ((UnknownAddress*) baseObject)->address;

	  emit(mach->LOADop, mach->addressSize,displayRegister(frame->level,
           address->level), address->displacement);
      if (V->indexed)
		  emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
      if (V->offset != 0) {
			emit(mach->LOADLop, 0, 0, V->offset);
			emit(mach->CALLop, mach->SBr, mach->PBr, mach->addDisplacement);
      }
    }
  }





#endif
