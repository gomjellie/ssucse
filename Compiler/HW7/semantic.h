#ifndef SEMANTIC_H
#define SEMANTIC_H
// resource & copyright : 책, C언어와 컴파일러, 2015, (유재우, 최재영, 신경희), SSU Press

// included by student
#include <stdio.h>
#include <string.h>

#include "type.h"
//float atof(); // in main, already stdlib.h was called
void semantic_analysis(A_NODE *);
void set_literal_address(A_NODE *);
int put_literal(A_LITERAL, int);
void sem_program(A_NODE *);
A_TYPE*sem_expression(A_NODE *);
int sem_statement(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
int sem_statement_list(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);
void sem_for_expression(A_NODE *);
int sem_A_TYPE(A_TYPE *) ;
int sem_declaration_list(A_ID *id, int addr);
int sem_declaration(A_ID *,int);
void sem_arg_expr_list(A_NODE *, A_ID *);
A_ID *getStructFieldIdentifier(A_TYPE *, char *);
A_ID *getPointerFieldIdentifier(A_TYPE *, char *);
A_NODE *convertScalarToInteger(A_NODE *);
A_NODE *convertUsualAssignmentConversion(A_TYPE *, A_NODE *);
A_NODE *convertUsualUnaryConversion(A_NODE *);
A_TYPE *convertUsualBinaryConversion(A_NODE *);
A_NODE *convertCastingConversion(A_NODE *,A_TYPE *);
BOOLEAN isAllowableAssignmentConversion(A_TYPE *, A_TYPE *, A_NODE *); 
BOOLEAN isAllowableCastingConversion(A_TYPE *, A_TYPE *);
BOOLEAN isModifiableLvalue(A_NODE *);
BOOLEAN isConstantZeroExp(A_NODE *);
BOOLEAN isSameParameterType(A_ID *, A_ID *);
BOOLEAN isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatibleType(A_TYPE *, A_TYPE *);
BOOLEAN isCompatiblePointerType(A_TYPE *, A_TYPE *);
BOOLEAN isIntType(A_TYPE *);
BOOLEAN isFloatType(A_TYPE *);
BOOLEAN isArithmeticType(A_TYPE *);
BOOLEAN isAnyIntegerType(A_TYPE *);
BOOLEAN isIntegralType(A_TYPE *);
BOOLEAN isStructOrUnionType(A_TYPE *);
BOOLEAN isFunctionType(A_TYPE *);
BOOLEAN isScalarType(A_TYPE *);
BOOLEAN isPointerType(A_TYPE *);
BOOLEAN isPointerOrArrayType_sem(A_TYPE *);
BOOLEAN isArrayType(A_TYPE *);
BOOLEAN isStringType(A_TYPE *);
BOOLEAN isVoidType(A_TYPE *);
A_LITERAL checkTypeAndConvertLiteral(A_LITERAL,A_TYPE*, int);
A_LITERAL getTypeAndValueOfExpression(A_NODE *);
A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);
A_TYPE *makeType(T_KIND);
void setTypeSize(A_TYPE *, int);
void semantic_warning(int, int);
void semantic_error();
A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE*);
extern A_TYPE *int_type, *float_type, *char_type, *string_type, *void_type;

#endif /* SEMANTIC_H */
