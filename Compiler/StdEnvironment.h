#ifndef _STDENVIRONMENT
#define _STDENVIRONMENT

#include "./AST/BinaryOperatorDeclaration.h"
#include "./AST/ConstDeclaration.h"
#include "./AST/FuncDeclaration.h"
#include "./AST/ProcDeclaration.h"
#include "./AST/TypeDeclaration.h"
#include "./AST/TypeDenoter.h"
#include "./AST/UnaryOperatorDeclaration.h"

class StdEnvironment {

  // These are small ASTs representing standard types.

public:
	 TypeDenoter* booleanType;
	 TypeDenoter* charType;
	 TypeDenoter* integerType;
   TypeDenoter *nilType;
	 TypeDenoter* anyType;
	 TypeDenoter* errorType;
   TypeDenoter *strType;
   TypeDenoter *varstrType;

   TypeDeclaration* booleanDecl;
   TypeDeclaration* charDecl;
   TypeDeclaration* integerDecl;
   TypeDeclaration *varstrDecl;

  // These are small ASTs representing "declarations" of standard entities.

   ConstDeclaration* falseDecl;
   ConstDeclaration* trueDecl;
   ConstDeclaration* maxintDecl;
    

   UnaryOperatorDeclaration* notDecl;

   BinaryOperatorDeclaration* andDecl;
   BinaryOperatorDeclaration* orDecl;
   BinaryOperatorDeclaration* addDecl;
   BinaryOperatorDeclaration* subtractDecl;
   BinaryOperatorDeclaration* multiplyDecl;
   BinaryOperatorDeclaration* divideDecl;
   BinaryOperatorDeclaration* moduloDecl;
   BinaryOperatorDeclaration* equalDecl;
   BinaryOperatorDeclaration* unequalDecl;
   BinaryOperatorDeclaration* lessDecl;
   BinaryOperatorDeclaration* notlessDecl;
   BinaryOperatorDeclaration* greaterDecl;
   BinaryOperatorDeclaration* notgreaterDecl;
   BinaryOperatorDeclaration* strcompDecl;

   ProcDeclaration* getDecl;
   ProcDeclaration* putDecl;
   ProcDeclaration* getintDecl;
   ProcDeclaration* putintDecl;
   ProcDeclaration* geteolDecl;
   ProcDeclaration* puteolDecl;

   FuncDeclaration* chrDecl;
   FuncDeclaration* ordDecl;
   FuncDeclaration* eolDecl;
   FuncDeclaration* eofDecl;
  
  StdEnvironment(){
	  int a=3;
	}
};


#endif
