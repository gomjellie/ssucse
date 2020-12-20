//
// Created by loki on 15. 12. 19..
//

#ifndef COMPILER_FINAL_TERM_PRINT_SEM_H
#define COMPILER_FINAL_TERM_PRINT_SEM_H

#include "type.h"

void print_sem_ast(A_NODE *);

void prt_sem_program(A_NODE *, int);

void prt_sem_initializer(A_NODE *, int);

void prt_sem_arg_expr_list(A_NODE *, int);

void prt_sem_statement(A_NODE *, int);

void prt_sem_statement_list(A_NODE *, int);

void prt_sem_for_expression(A_NODE *, int);

void prt_sem_expression(A_NODE *, int);

void prt_sem_A_TYPE(A_TYPE *, int);

void prt_sem_A_ID_LIST(A_ID *, int);

void prt_sem_A_ID(A_ID *, int);

void prt_sem_A_ID_NAME(A_ID *, int);

void prt_sem_LITERAL(int, int);

void prt_sem_integer(int, int);

void print_space(int);

void print_node(A_NODE *, int);

#endif //COMPILER_FINAL_TERM_PRINT_SEM_H
