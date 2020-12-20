//
// Created by loki on 15. 11. 2..
//

#ifndef COMPILER_MID_TERM_SYNTAX_H
#define COMPILER_MID_TERM_SYNTAX_H

#include "type.h"

A_NODE *makeNode(NODE_NAME, A_NODE *, A_NODE *, A_NODE *);

A_NODE *makeNodeList(NODE_NAME, A_NODE *, A_NODE *);

A_ID *makeIdentifier(char *);

A_ID *makeDummyIdentifier();

A_TYPE *makeType(T_KIND);

A_SPECIFIER *makeSpecifier(A_TYPE *, S_KIND);

A_ID *searchIdentifier(char *, A_ID *);

A_ID *searchIdentifierAtCurrentLevel(char *, A_ID *);

A_SPECIFIER *updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND);

void checkForwardReference();

void setDefaultSpecifier(A_SPECIFIER *);

A_ID *linkDeclaratorList(A_ID *, A_ID *);

A_ID *getIdentifierDeclared(char *);

A_TYPE *getTypeOfStructOrEnumRefIdentifier(T_KIND, char *, ID_KIND);

A_ID *setDeclaratorInit(A_ID *, A_NODE *);

A_ID *setDeclaratorKind(A_ID *, ID_KIND);

A_ID *setDeclaratorType(A_ID *, A_TYPE *);

A_ID *setDeclaratorElementType(A_ID *, A_TYPE *);

A_ID *setDeclaratorTypeAndKind(A_ID *, A_TYPE *, ID_KIND);

A_ID *setDeclaratorListSpecifier(A_ID *, A_SPECIFIER *);

A_ID *setFunctionDeclaratorSpecifier(A_ID *, A_SPECIFIER *);

A_ID *setFunctionDeclaratorBody(A_ID *, A_NODE *);

A_ID *setParameterDeclaratorSpecifier(A_ID *, A_SPECIFIER *);

A_ID *setStructDeclaratorListSpecifier(A_ID *, A_TYPE *);

A_TYPE *setTypeNameSpecifier(A_TYPE *, A_SPECIFIER *);

A_TYPE *setTypeElementType(A_TYPE *, A_TYPE *);

A_TYPE *setTypeField(A_TYPE *, A_ID *);

A_TYPE *setTypeExpr(A_TYPE *, A_NODE *);

A_TYPE *setTypeAndKindOfDeclarator(A_TYPE *, ID_KIND, A_ID *);

A_TYPE *setTypeStructOrEnumIdentifier(T_KIND, char *, ID_KIND);

BOOLEAN isNotSameFormalParameters(A_ID *, A_ID *);

BOOLEAN isNotSameType(A_TYPE *, A_TYPE *);

BOOLEAN isPointerOrArrayType(A_TYPE *);

void syntax_error(int, char *);

void initialize();

#endif //COMPILER_MID_TERM_SYNTAX_H
