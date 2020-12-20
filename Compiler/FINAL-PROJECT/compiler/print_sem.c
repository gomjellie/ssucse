//
// Created by loki on 15. 12. 19..
//

#include <stdio.h>
#include "print_sem.h"


#include "type.h"

extern char *node_name[];
extern char *type_kind_name[];
extern char *id_kind_name[];
extern char *spec_name[];

extern A_LITERAL literal_table[];
extern A_TYPE *int_type, *float_type, *char_type, *void_type, *string_type;

void print_sem_ast(A_NODE *node) {
    printf("======= semantic tree ==========\n");
    prt_sem_program(node, 0);
}

void prt_sem_program(A_NODE *node, int s) {
    print_node(node, s);
    switch (node->name) {
        case N_PROGRAM:
            prt_sem_A_ID_LIST((A_ID *) node->clink, s + 1);
            break;
        default :
            printf("****syntax tree error******");
            break;
    }
}

void prt_sem_initializer(A_NODE *node, int s) {
    print_node(node, s);
    switch (node->name) {
        case N_INIT_LIST:
            prt_sem_initializer(node->llink, s + 1);
            prt_sem_initializer(node->rlink, s + 1);
            break;
        case N_INIT_LIST_ONE:
            prt_sem_expression(node->clink, s + 1);
            break;
        case N_INIT_LIST_NIL:
            break;
        default :
            printf("****syntax tree error******");

    }
}

void prt_sem_expression(A_NODE *node, int s) {
    print_node(node, s);
    switch (node->name) {
        case N_EXP_IDENT :
            prt_sem_A_ID_NAME((A_ID *) node->clink, s + 1);
            break;
        case N_EXP_INT_CONST :
            prt_sem_integer((int) node->clink, s + 1);
            break;
        case N_EXP_FLOAT_CONST :
            prt_sem_LITERAL((int) node->clink, s + 1);
            break;
        case N_EXP_CHAR_CONST :
            prt_sem_integer((int) node->clink, s + 1);
            break;
        case N_EXP_STRING_LITERAL :
            prt_sem_LITERAL(node->clink, s + 1);
            break;
        case N_EXP_ARRAY :
            prt_sem_expression(node->llink, s + 1);
            prt_sem_expression(node->rlink, s + 1);
            break;
        case N_EXP_FUNCTION_CALL :
            prt_sem_expression(node->llink, s + 1);
            prt_sem_arg_expr_list(node->rlink, s + 1);
            break;
        case N_EXP_STRUCT :
            prt_sem_expression(node->llink, s + 1);
            prt_sem_A_ID_NAME((A_ID *) node->rlink, s + 1);
            break;
        case N_EXP_ARROW :
            prt_sem_expression(node->llink, s + 1);
            prt_sem_A_ID_NAME((A_ID *) node->rlink, s + 1);
            break;
        case N_EXP_POST_INC :
        case N_EXP_POST_DEC :
        case N_EXP_PRE_INC :
        case N_EXP_PRE_DEC :
        case N_EXP_AMP :
        case N_EXP_STAR :
        case N_EXP_NOT :
        case N_EXP_PLUS :
        case N_EXP_MINUS :
            prt_sem_expression(node->clink, s + 1);
            break;
        case N_EXP_SIZE_EXP :
        case N_EXP_SIZE_TYPE :
            prt_sem_integer((int) node->clink, s + 1);
            break;
        case N_EXP_CAST :
            prt_sem_A_TYPE((A_TYPE *) node->llink, s + 1);
            prt_sem_expression(node->rlink, s + 1);
            break;
        case N_EXP_MUL :
        case N_EXP_DIV :
        case N_EXP_MOD :
        case N_EXP_ADD :
        case N_EXP_SUB :
        case N_EXP_LSS :
        case N_EXP_GTR :
        case N_EXP_LEQ :
        case N_EXP_GEQ :
        case N_EXP_NEQ :
        case N_EXP_EQL :
        case N_EXP_AND :
        case N_EXP_OR :
        case N_EXP_ASSIGN :
            prt_sem_expression(node->llink, s + 1);
            prt_sem_expression(node->rlink, s + 1);
            break;
        default :
            printf("****syntax tree error******");

    }
}

void prt_sem_arg_expr_list(A_NODE *node, int s) {
    print_node(node, s);
    switch (node->name) {
        case N_ARG_LIST :
            prt_sem_expression(node->llink, s + 1);
            prt_sem_arg_expr_list(node->rlink, s + 1);
            break;
        case N_ARG_LIST_NIL :
            break;
        default :
            printf("****syntax tree error******");
    }
}

void prt_sem_statement(A_NODE *node, int s) {
    print_node(node, s);

    switch (node->name) {
        case N_STMT_LABEL_CASE :
            prt_sem_integer((int) node->llink, s + 1);
            prt_sem_statement(node->rlink, s + 1);
            break;
        case N_STMT_LABEL_DEFAULT :
            prt_sem_statement(node->clink, s + 1);
            break;
        case N_STMT_COMPOUND:
            if (node->llink) {
                prt_sem_A_ID_LIST((A_ID *) node->llink, s + 1);
            }
            prt_sem_statement_list(node->rlink, s + 1);
            break;
        case N_STMT_EMPTY:
            break;
        case N_STMT_EXPRESSION:
            prt_sem_expression(node->clink, s + 1);
            break;
        case N_STMT_IF:
            prt_sem_expression(node->llink, s + 1);
            prt_sem_statement(node->rlink, s + 1);
            break;
        case
            N_STMT_IF_ELSE:
            prt_sem_expression(node->llink, s + 1);
            prt_sem_statement(node->clink, s + 1);
            prt_sem_statement(node->rlink, s + 1);
            break;
        case N_STMT_SWITCH:
            prt_sem_expression(node->llink, s + 1);
            prt_sem_statement(node->rlink, s + 1);
            break;
        case N_STMT_WHILE:
            prt_sem_expression(node->llink, s + 1);
            prt_sem_statement(node->rlink, s + 1);
            break;
        case N_STMT_DO:
            prt_sem_statement(node->llink, s + 1);
            prt_sem_expression(node->rlink, s + 1);
            break;
        case N_STMT_FOR:
            prt_sem_for_expression(node->llink, s + 1);
            prt_sem_statement(node->rlink, s + 1);
            break;
        case N_STMT_CONTINUE:
            break;
        case N_STMT_BREAK:
            break;
        case N_STMT_RETURN:
            if (node->clink) prt_sem_expression(node->clink, s + 1);
            break;
        default :
            printf("****syntax tree error******");
    }
}

void prt_sem_statement_list(A_NODE *node, int s) {
    print_node(node, s);
    switch (node->name) {
        case N_STMT_LIST:
            prt_sem_statement(node->llink, s + 1);
            prt_sem_statement_list(node->rlink, s + 1);
            break;
        case N_STMT_LIST_NIL:
            break;
        default :
            printf("****syntax tree error******");
    }
}

void prt_sem_for_expression(A_NODE *node, int s) {
    print_node(node, s);
    switch (node->name) {
        case N_FOR_EXP :
            if (node->llink) prt_sem_expression(node->llink, s + 1);
            if (node->clink) prt_sem_expression(node->clink, s + 1);
            if (node->rlink) prt_sem_expression(node->rlink, s + 1);
            break;
        default :
            printf("****syntax tree error******");
            break;
    }
}

void prt_sem_integer(int a, int s) {
    print_space(s);
    printf("INT=%d\n", a);
}

void prt_sem_LITERAL(int lit, int s) {
    print_space(s);
    printf("LITERAL: ");
    if (literal_table[lit].type == int_type)
        printf("%d\n", literal_table[lit].value.i);
    if (literal_table[lit].type == float_type)
        printf("%f\n", literal_table[lit].value.f);
    else if (literal_table[lit].type == string_type)
        printf("%s\n", literal_table[lit].value.s);
}

void prt_sem_A_TYPE(A_TYPE *t, int s) {
    print_space(s);
    if (t == int_type)
        printf("(int)\n");
    else if (t == float_type)
        printf("(float)\n");
    else if (t == char_type)
        printf("(char %d)\n", t->size);
    else if (t == void_type)
        printf("(void)\n");
    else if (t->kind == T_NULL)
        printf("(null)\n");
    else if (t->prt == FALSE)
        printf("(DONE:%x)\n", t);
    else {
        switch (t->kind) {
            case T_ENUM:
                t->prt = FALSE;
                printf("ENUM\n");
                print_space(s);
                printf("| ENUMERATORS\n");
                prt_sem_A_ID_LIST(t->field, s + 2);
                break;
            case T_POINTER:
                t->prt = FALSE;
                printf("POINTER\n");
                print_space(s);
                printf("| ELEMENT_TYPE\n");
                prt_sem_A_TYPE(t->element_type, s + 2);
                break;
            case T_ARRAY:
                t->prt = FALSE;
                printf("ARRAY\n");
                print_space(s);
                printf("| INDEX\n");
                prt_sem_integer((int) t->expr, s + 2);
                print_space(s);
                printf("| ELEMENT_TYPE\n");
                prt_sem_A_TYPE(t->element_type, s + 2);
                break;
            case T_STRUCT:
                t->prt = FALSE;
                printf("STRUCT\n");
                print_space(s);
                printf("| FIELD\n");
                prt_sem_A_ID_LIST(t->field, s + 2);
                break;
            case T_UNION:
                t->prt = FALSE;
                printf("UNION\n");
                print_space(s);
                printf("| FIELD\n");
                prt_sem_A_ID_LIST(t->field, s + 2);
                break;
            case T_FUNC:
                t->prt = FALSE;
                printf("FUNCTION\n");
                print_space(s);
                printf("| PARAMETER\n");
                prt_sem_A_ID_LIST(t->field, s + 2);
                print_space(s);
                printf("| TYPE\n");
                prt_sem_A_TYPE(t->element_type, s + 2);
                if (t->expr) {
                    print_space(s);
                    printf("| BODY\n");
                    prt_sem_statement(t->expr, s + 2);
                }
            case T_NULL:
                break;
            case T_VOID:
                break;
        }
    }
}

void prt_sem_A_ID_LIST(A_ID *id, int s) {
    while (id) {
        prt_sem_A_ID(id, s);
        id = id->link;
    }
}

void prt_sem_A_ID_NAME(A_ID *id, int s) {
    print_space(s);
    printf("(ID=\"%s\") TYPE:%x KIND:%s SPEC=%s LEV=%d VAL=%d ADDR=%d \n", id->name, id->type,
           id_kind_name[id->kind], spec_name[id->specifier], id->level, id->value, id->address);
}

void prt_sem_A_ID(A_ID *id, int s) {
    print_space(s);
    printf("(ID=\"%s\") TYPE:%x KIND:%s SPEC=%s LEV=%d VAL=%d ADDR=%d \n", id->name, id->type,
           id_kind_name[id->kind], spec_name[id->specifier], id->level, id->value, id->address);
    if (id->type) {
        print_space(s);
        printf("| TYPE\n");
        prt_sem_A_TYPE(id->type, s + 2);
    }
    if (id->init) {
        print_space(s);
        printf("| INIT\n");
        if (id->kind == ID_ENUM_LITERAL) {
            if (id->init) {
                prt_sem_integer((int) id->init, s + 2);
            }
            else {

            }
        }
        else
            prt_sem_initializer(id->init, s + 2);
    }
}

