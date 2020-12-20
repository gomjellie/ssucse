//
// Created by loki on 15. 12. 19..
//

#ifndef COMPILER_MID_TERM_SEMANTIC_H
#define COMPILER_MID_TERM_SEMANTIC_H


#include "type.h"

void semantic_analysis(A_NODE *);

void set_literal_address(A_NODE *);

int put_literal(A_LITERAL, int);

void sem_program(A_NODE *);

A_TYPE *sem_expression(A_NODE *);

int sem_statement(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);

int sem_statement_list(A_NODE *, int, A_TYPE *, BOOLEAN, BOOLEAN, BOOLEAN);

void sem_for_expression(A_NODE *);

int sem_A_TYPE(A_TYPE *);

int sem_declaration_list(A_ID *, int);

int sem_declaration(A_ID *, int);

void sem_arg_expr_list(A_NODE *, A_ID *);

A_ID *getStructFieldIdentifier(A_TYPE *, char *);

A_ID *getPointerFieldIdentifier(A_TYPE *, char *);

A_NODE *convertScalarToInteger(A_NODE *);

A_NODE *convertUsualAssignmentConversion(A_TYPE *, A_NODE *);

A_NODE *convertUsualUnaryConversion(A_NODE *);

A_TYPE *convertUsualBinaryConversion(A_NODE *);

A_NODE *convertCastingConversion(A_NODE *, A_TYPE *);

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

BOOLEAN isArrayType(A_TYPE *);

BOOLEAN isStringType(A_TYPE *);

BOOLEAN isVoidType(A_TYPE *);

A_LITERAL checkTypeAndConvertLiteral(A_LITERAL, A_TYPE *, int);

A_LITERAL getTypeAndValueOfExpression(A_NODE *);

A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);

A_TYPE *makeType(T_KIND);

void setTypeSize(A_TYPE *, int);

void semantic_warning(int, int);

void semantic_error(int, int, char*);

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);


#endif //COMPILER_MID_TERM_SEMANTIC_H
