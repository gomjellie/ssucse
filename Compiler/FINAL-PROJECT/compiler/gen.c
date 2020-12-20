//
// Created by loki on 15. 12. 19..
//

#include <stdio.h>
#include "gen.h"
#include "semantic.h"
#include "syntax.h"


char *opcode_name[] = {
        "OP_NULL",
        "LOD",
        "LDX",
        "LDXB",
        "LDA",
        "LITI",
        "STO",
        "STOB",
        "STX",
        "STXB",
        "SUBI",
        "SUBF",
        "DIVI",
        "DIVF",
        "ADDI",
        "ADDF",
        "OFFSET",
        "MULI",
        "MULF",
        "MOD",
        "LSSI",
        "LSSF",
        "GTRI",
        "GTRF",
        "LEQI",
        "LEQF",
        "GEQI",
        "GEQF",
        "NEQI",
        "NEQF",
        "EQLI",
        "EQLF",
        "NOT",
        "OR",
        "AND",
        "CVTI",
        "CVTF",
        "JPC",
        "JPCR",
        "JMP",
        "JPT",
        "JPTR",
        "INT",
        "INCI",
        "INCF",
        "DECI",
        "DECF",
        "SUP",
        "CAL",
        "ADDR",
        "RET",
        "MINUSI",
        "MINUSF",
        "CHK",
        "LDI",
        "LDIB",
        "SWITCH",
        "SWVALUE",
        "SWDEFAULT",
        "SWLABEL",
        "SWEND",
        "POP",
        "POPB"
};

int label_no = 0;
int gen_err = 0;
extern FILE *fout;
extern A_TYPE *int_type, *float_type, *char_type, *void_type, *string_type;
extern A_LITERAL literal_table[];
extern int literal_no;

void code_generation(A_NODE *node) {
    gen_program(node);
    gen_literal_table();
}

void gen_literal_table() {
    int i;
    for (i = 1; i <= literal_no; i++) {
        fprintf(fout, ".literal %5d ", literal_table[i].addr);
        if (literal_table[i].type == int_type)
            fprintf(fout, "%d\n", literal_table[i].value.i);
        else if (literal_table[i].type == float_type)
            fprintf(fout, "%f\n", literal_table[i].value.f);
        else if (literal_table[i].type == char_type)
            fprintf(fout, "%d\n", literal_table[i].value.c);
        else if (literal_table[i].type == string_type)
            fprintf(fout, "%s\n", literal_table[i].value.s);
    }
}

void gen_program(A_NODE *node) {
    switch (node->name) {
        case N_PROGRAM :
            gen_code_i(INT, 0, node->value);
            // gen_global_init_list((A_ID *) node->clink);
            gen_code_s(SUP, 0, "main");
            gen_code_i(RET, 0, 0);
            gen_declaration_list((A_ID *) node->clink);
            break;
        default :
            gen_error(100, node->line, "");
            break;
    }
}

// void gen_global_init_list(A_ID *id) {
//     while (id) {
//         if (id->kind == ID_VAR && id->level == 0 && id->init) {
//             gen_initializer_global(id->init, id->type, id->address);
//         } else if (id->kind == ID_FUNC) {
//             A_ID* fields = (A_ID *) id->type->expr->llink;
//             gen_global_init_list(fields);
//         } else {

//         }

//         id = id->link;
//     }
// }

void gen_expression(A_NODE *node) {
    A_ID *id;
    A_TYPE *t;
    int i, ll;
    switch (node->name) {
        case N_EXP_IDENT :
            id = (A_ID *) node->clink;
            t = id->type;
            switch (id->kind) {
                case ID_VAR:
                case ID_PARM:
                    switch (t->kind) {
                        case T_ENUM:
                        case T_POINTER:
                            gen_code_i(LOD, id->level, id->address);
                            break;
                        case T_ARRAY:
                            if (id->kind == ID_VAR)
                                gen_code_i(LDA, id->level, id->address);
                            else
                                gen_code_i(LOD, id->level, id->address);
                            break;
                        case T_STRUCT:
                        case T_UNION:
                            gen_code_i(LDA, id->level, id->address);
                            i = id->type->size;
                            gen_code_i(LDI, 0, i % 4 ? i / 4 + 1 : i / 4);
                            break;
                        default:
                            gen_error(11, id->line, "");
                            break;
                    }
                    break;
                case ID_ENUM_LITERAL:
                    gen_code_i(LITI, 0, (int) id->init);
                    break;
                default:
                    gen_error(11, node->line, "");
                    break;
            }
            break;
        case N_EXP_INT_CONST :
            gen_code_i(LITI, 0, (int) node->clink);
            break;
        case N_EXP_FLOAT_CONST :
            i = (int) node->clink;
            gen_code_i(LOD, 0, literal_table[i].addr);
            break;
        case N_EXP_CHAR_CONST :
            gen_code_i(LITI, 0, (int) node->clink);
            break;
        case N_EXP_STRING_LITERAL :
            i = (int) node->clink;
            gen_code_i(LDA, 0, literal_table[i].addr);
            break;
        case N_EXP_ARRAY :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            // gen_code_i(CHK,0,node->llink->type->expr);
            if (node->type->size > 1) {
                gen_code_i(LITI, 0, node->type->size);
                gen_code_i(MULI, 0, 0);
            }
            gen_code_i(OFFSET, 0, 0);
            if (!isArrayType(node->type)) {
                i = node->type->size;
                if (i == 1) gen_code_i(LDIB, 0, 0);
                else
                    gen_code_i(LDI, 0, i % 4 ? i / 4 + 1 : i / 4);
            }
            break;
        case N_EXP_FUNCTION_CALL :
            t = node->llink->type;
            i = t->element_type->element_type->size;
            if (i % 4) i = i / 4 * 4 + 4;
            if (node->rlink) {
                gen_code_i(INT, 0, 12 + i);
                gen_arg_expression(node->rlink);
                gen_code_i(POP, 0, node->rlink->value / 4 + 3);
            }
            else
                gen_code_i(INT, 0, i);
            gen_expression(node->llink);
            gen_code_i(CAL, 0, 0);
            break;
        case N_EXP_STRUCT :
            gen_expression_left(node->llink);
            id = (A_ID *) node->rlink;
            if (id->address > 0) {
                gen_code_i(LITI, 0, id->address);
                gen_code_i(OFFSET, 0, 0);
            }
            if (!isArrayType(node->type)) {
                i = node->type->size;
                if (i == 1) gen_code_i(LDIB, 0, 0);
                else gen_code_i(LDI, 0, i % 4 ? i / 4 + 1 : i / 4);
            }
            break;
        case N_EXP_ARROW:
            gen_expression(node->llink);
            id = (A_ID *) node->rlink;
            if (id->address > 0) {
                gen_code_i(LITI, 0, id->address);
                gen_code_i(OFFSET, 0, 0);
            }
            if (!isArrayType(node->type)) {
                i = node->type->size;
                if (i == 1)
                    gen_code_i(LDIB, 0, 0);
                else
                    gen_code_i(LDI, 0, i % 4 ? i / 4 + 1 : i / 4);
            }
            break;

        case N_EXP_POST_INC :
            gen_expression(node->clink);
            gen_expression_left(node->clink);
            t = node->type;
            if (node->type->size == 1)
                gen_code_i(LDXB, 0, 0);
            else
                gen_code_i(LDX, 0, 1);
            if (isPointerOrArrayType(node->type)) {
                gen_code_i(LITI, 0, node->type->element_type->size);
                gen_code_i(ADDI, 0, 0);
            }
            else if (isFloatType(node->type))
                gen_code_i(INCF, 0, 0);
            else
                gen_code_i(INCI, 0, 0);
            if (node->type->size == 1)
                gen_code_i(STOB, 0, 0);
            else
                gen_code_i(STO, 0, 1);
            break;
        case N_EXP_POST_DEC :
            gen_expression(node->clink);
            gen_expression_left(node->clink);
            t = node->type;
            if (node->type->size == 1) gen_code_i(LDXB, 0, 0);
            else
                gen_code_i(LDX, 0, 1);
            if (isPointerOrArrayType(node->type)) {
                gen_code_i(LITI, 0, node->type->element_type->size);
                gen_code_i(SUBI, 0, 0);
            } else if (isFloatType(node->type))
                gen_code_i(DECF, 0, 0);
            else
                gen_code_i(DECI, 0, 0);
            if (node->type->size == 1)
                gen_code_i(STOB, 0, 0);
            else
                gen_code_i(STO, 0, 1);
            break;

        case N_EXP_PRE_INC :
            gen_expression_left(node->clink);
            t = node->type;
            if (node->type->size == 1)
                gen_code_i(LDXB, 0, 0);
            else
                gen_code_i(LDX, 0, 1);
            if (isPointerOrArrayType(node->type)) {
                gen_code_i(LITI, 0, node->type->element_type->size);
                gen_code_i(ADDI, 0, 0);
            } else if (isFloatType(node->type)) {
                gen_code_i(INCF, 0, 0);
            } else {
                gen_code_i(INCI, 0, 0);
            }

            if (node->type->size == 1) {
                gen_code_i(STXB, 0, 0);
            } else {
                gen_code_i(STX, 0, 1);
            }
            break;

        case N_EXP_PRE_DEC :
            gen_expression_left(node->clink);
            t = node->type;
            if (node->type->size == 1)
                gen_code_i(LDXB, 0, 0);
            else
                gen_code_i(LDX, 0, 1);
            if (isPointerOrArrayType(node->type)) {
                gen_code_i(LITI, 0, node->type->element_type->size);
                gen_code_i(SUBI, 0, 0);
            } else if (isFloatType(node->type))
                gen_code_i(DECF, 0, 0);
            else
                gen_code_i(DECI, 0, 0);
            if (node->type->size == 1)
                gen_code_i(STXB, 0, 0);
            else
                gen_code_i(STX, 0, 1);
            break;

        case N_EXP_NOT :
            gen_expression(node->clink);
            gen_code_i(NOT, 0, 0);
            break;

        case N_EXP_PLUS :
            gen_expression(node->clink);
            break;
        case N_EXP_MINUS :
            gen_expression(node->clink);
            if (isFloatType(node->type))
                gen_code_i(MINUSF, 0, 0);
            else
                gen_code_i(MINUSI, 0, 0);
            break;

        case N_EXP_AMP :
            gen_expression_left(node->clink);
            break;
        case N_EXP_STAR :
            gen_expression(node->clink);
            i = node->type->size;
            if (i == 1)
                gen_code_i(LDIB, 0, 0);
            else
                gen_code_i(LDI, 0, i % 4 ? i / 4 + 1 : i / 4);
            break;

        case N_EXP_SIZE_EXP :
            gen_code_i(LITI, 0, (int) node->clink);
            break;
        case N_EXP_SIZE_TYPE :
            gen_code_i(LITI, 0, (int) node->clink);
            break;
        case N_EXP_CAST :
            gen_expression(node->rlink);
            if (node->type != node->rlink->type) {
                if (isFloatType(node->type)) {
                    gen_code_i(CVTF, 0, 0);
                }
                else if (isFloatType(node->rlink->type)) {
                    gen_code_i(CVTI, 0, 0);
                }
            }
            break;

        case N_EXP_MUL :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->type))
                gen_code_i(MULF, 0, 0);
            else
                gen_code_i(MULI, 0, 0);
            break;

        case N_EXP_DIV :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->type))
                gen_code_i(DIVF, 0, 0);
            else
                gen_code_i(DIVI, 0, 0);
            break;
        case N_EXP_MOD :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            gen_code_i(MOD, 0, 0);
            break;

        case N_EXP_ADD :
            gen_expression(node->llink);
            if (isPointerOrArrayType(node->rlink->type)) {
                gen_code_i(LITI, 0, node->rlink->type->element_type->size);
                gen_code_i(MULI, 0, 0);
            }
            gen_expression(node->rlink);
            if (isPointerOrArrayType(node->llink->type)) {
                gen_code_i(LITI, 0, node->llink->type->element_type->size);
                gen_code_i(MULI, 0, 0);
            }
            if (isFloatType(node->type)) gen_code_i(ADDF, 0, 0);
            else
                gen_code_i(ADDI, 0, 0);
            break;

        case N_EXP_SUB :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isPointerOrArrayType(node->llink->type) &&
                !isPointerOrArrayType(node->rlink->type)) {
                gen_code_i(LITI, 0, node->llink->type->element_type->size);
                gen_code_i(MULI, 0, 0);
            }
            if (isFloatType(node->type)) gen_code_i(SUBF, 0, 0);
            else
                gen_code_i(SUBI, 0, 0);
            break;
        case N_EXP_LSS :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->llink->type))
                gen_code_i(LSSF, 0, 0);
            else
                gen_code_i(LSSI, 0, 0);
            break;
        case N_EXP_GTR :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->llink->type))
                gen_code_i(GTRF, 0, 0);
            else
                gen_code_i(GTRI, 0, 0);
            break;
        case N_EXP_LEQ :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->llink->type)) {
                gen_code_i(LEQF, 0, 0);
            }
            else {
                gen_code_i(LEQI, 0, 0);
            }
            break;

        case N_EXP_GEQ :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->llink->type))
                gen_code_i(GEQF, 0, 0);
            else
                gen_code_i(GEQI, 0, 0);
            break;
        case N_EXP_NEQ :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->llink->type))
                gen_code_i(NEQF, 0, 0);
            else
                gen_code_i(NEQI, 0, 0);
            break;
        case N_EXP_EQL :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            if (isFloatType(node->llink->type))
                gen_code_i(EQLF, 0, 0);
            else
                gen_code_i(EQLI, 0, 0);
            break;
        case N_EXP_AND :
            gen_expression(node->llink);
            gen_code_l(JPCR, 0, i = get_label());
            gen_expression(node->rlink);
            gen_label_number(i);
            break;
        case N_EXP_OR :
            gen_expression(node->llink);
            gen_code_l(JPTR, 0, i = get_label());
            gen_expression(node->rlink);
            gen_label_number(i);
            break;
        case N_EXP_ASSIGN :
            gen_expression_left(node->llink);
            gen_expression(node->rlink);
            i = node->type->size;
            if (i == 1) gen_code_i(STXB, 0, 0);
            else
                gen_code_i(STX, 0, i % 4 ? i / 4 + 1 : i / 4);
            break;
        default :
            gen_error(100, node->line, "");
            break;
    }
}

void gen_expression_left(A_NODE *node) {
    A_ID *id;
    A_TYPE *t;
    int result;
    switch (node->name) {
        case N_EXP_IDENT :
            id = (A_ID *) node->clink;
            t = id->type;
            switch (id->kind) {
                case ID_VAR:
                case ID_PARM:
                    switch (t->kind) {
                        case T_ENUM:
                        case T_POINTER:
                        case T_STRUCT:
                        case T_UNION:
                            gen_code_i(LDA, id->level, id->address);
                            break;
                        case T_ARRAY:
                            if (id->kind == ID_VAR)
                                gen_code_i(LDA, id->level, id->address);
                            else
                                gen_code_i(LOD, id->level, id->address);
                            break;
                        default:
                            gen_error(13, node->line, id->name);
                            break;
                    }
                    break;
                case ID_FUNC:
                    gen_code_s(ADDR, 0, id->name);
                    break;
                default:
                    gen_error(13, node->line, id->name);
                    break;
            }
            break;
        case N_EXP_ARRAY :
            gen_expression(node->llink);
            gen_expression(node->rlink);
            // gen_code_i(CHK,0,node->llink->type->expr);
            if (node->type->size > 1) {
                gen_code_i(LITI, 0, node->type->size);
                gen_code_i(MULI, 0, 0);
            }
            gen_code_i(OFFSET, 0, 0);
            break;

        case N_EXP_STRUCT :
            gen_expression_left(node->llink);
            id = (A_ID *) node->rlink;
            if (id->address > 0) {
                gen_code_i(LITI, 0, id->address);
                gen_code_i(OFFSET, 0, 0);
            }
            break;
        case N_EXP_ARROW :
            gen_expression(node->llink);
            id = (A_ID *) node->rlink;
            if (id->address > 0) {
                gen_code_i(LITI, 0, id->address);
                gen_code_i(OFFSET, 0, 0);
            }
            break;

        case N_EXP_STAR :
            gen_expression(node->clink);
            break;
        case N_EXP_INT_CONST :
        case N_EXP_FLOAT_CONST :
        case N_EXP_CHAR_CONST :
        case N_EXP_STRING_LITERAL :
        case N_EXP_FUNCTION_CALL :
        case N_EXP_POST_INC :
        case N_EXP_POST_DEC :
        case N_EXP_PRE_INC :
        case N_EXP_PRE_DEC :
        case N_EXP_NOT :
        case N_EXP_MINUS :
        case N_EXP_SIZE_EXP :
        case N_EXP_SIZE_TYPE :
        case N_EXP_CAST :
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
        case N_EXP_AMP :
        case N_EXP_AND :
        case N_EXP_OR :
        case N_EXP_ASSIGN :
            gen_error(12, node->line, "");
            break;
        default :
            gen_error(100, node->line, "");
            break;
    }
}

void gen_arg_expression(A_NODE *node) {
    A_NODE *n;
    switch (node->name) {
        case N_ARG_LIST :
            gen_expression(node->llink);
            gen_arg_expression(node->rlink);
            break;
        case N_ARG_LIST_NIL :
            break;
        default :
            gen_error(100, node->line, "");
            break;
    }
}

int get_label() {
    label_no++;
    return (label_no);
}

void gen_statement(A_NODE *node, int cont_label, int break_label, A_SWITCH sw[], int *sn) {
    A_SWITCH switch_table[100];
    int switch_no = 0;
    A_NODE *n;
    int i, l1, l2, l3;
    switch (node->name) {
        case N_STMT_LABEL_CASE :
            if (sw) {
                *sn = *sn + 1;
                sw[*sn].kind = SW_VALUE;
                sw[*sn].val = (int) node->llink;
                sw[*sn].label = l1 = get_label();
                gen_label_number(l1);
            }
            else
                gen_error(21, node->line, "");
            gen_statement(node->rlink, cont_label, break_label, sw, sn);
            break;
        case N_STMT_LABEL_DEFAULT :
            if (sw) {
                *sn = *sn + 1;
                sw[*sn].kind = SW_DEFAULT;
                sw[*sn].label = l1 = get_label();
                gen_label_number(l1);
            }
            else
                gen_error(20, node->line, "");
            gen_statement(node->clink, cont_label, break_label, sw, sn);
            break;
        case N_STMT_COMPOUND:
            if (node->llink) gen_declaration_list(node->llink);
            gen_statement_list(node->rlink, cont_label, break_label, sw, sn);
            break;
        case N_STMT_EMPTY:
            break;
        case N_STMT_EXPRESSION:
            n = node->clink;
            gen_expression(n);
            i = n->type->size;
            if (i)
                gen_code_i(POP, 0, i % 4 ? i / 4 + 1 : i / 4);
            break;
        case N_STMT_IF:
            gen_expression(node->llink);
            gen_code_l(JPC, 0, l1 = get_label());
            gen_statement(node->rlink, cont_label, break_label, 0, 0);
            gen_label_number(l1);
            break;
        case N_STMT_IF_ELSE:
            gen_expression(node->llink);
            gen_code_l(JPC, 0, l1 = get_label());
            gen_statement(node->clink, cont_label, break_label, 0, 0);
            gen_code_l(JMP, 0, l2 = get_label());
            gen_label_number(l1);
            gen_statement(node->rlink, cont_label, break_label, 0, 0);
            gen_label_number(l2);
            break;
        case N_STMT_SWITCH:
            gen_expression(node->llink);
            gen_code_l(SWITCH, 0, l1 = get_label());
            gen_code_l(JMP, 0, l2 = get_label());
            gen_statement(node->rlink, cont_label, l2, switch_table, &switch_no);
            gen_label_number(l1);
            for (i = 1; i <= switch_no; i++) {
                if (switch_table[i].kind == SW_VALUE)
                    gen_code_i(SWVALUE, 0, switch_table[i].val);
                else
                    gen_code_i(SWDEFAULT, 0, 0);
                gen_code_l(SWLABEL, 0, switch_table[i].label);
            }
            gen_code_i(SWEND, 0, 0);
            gen_label_number(l2);
            break;
        case N_STMT_WHILE:
            l3 = get_label();
            gen_label_number(l1 = get_label());
            gen_expression(node->llink);
            gen_code_l(JPC, 0, l2 = get_label());
            gen_statement(node->rlink, l3, l2, 0, 0);
            gen_label_number(l3);
            gen_code_l(JMP, 0, l1);
            gen_label_number(l2);
            break;
        case N_STMT_DO:
            l3 = get_label();
            l2 = get_label();
            gen_label_number(l1 = get_label());
            gen_statement(node->llink, l2, l3, 0, 0);
            gen_label_number(l2);
            gen_expression(node->rlink);
            gen_code_l(JPT, 0, l1);
            gen_label_number(l3);
            break;
        case N_STMT_FOR:
            n = node->llink;
            l3 = get_label();
            if (n->llink) {
                gen_expression(n->llink);
                i = n->llink->type->size;
                if (i)
                    gen_code_i(POP, 0, i % 4 ? i / 4 + 1 : i / 4);
            }
            gen_label_number(l1 = get_label());
            l2 = get_label();
            if (n->clink) {
                gen_expression(n->clink);
                gen_code_l(JPC, 0, l2);
            }
            gen_statement(node->rlink, l3, l2, 0, 0);
            gen_label_number(l3);
            if (n->rlink) {
                gen_expression(n->rlink);
                i = n->rlink->type->size;
                if (i)
                    gen_code_i(POP, 0, i % 4 ? i / 4 + 1 : i / 4);
            }
            gen_code_l(JMP, 0, l1);
            gen_label_number(l2);
            break;
        case N_STMT_CONTINUE:
            if (cont_label) gen_code_l(JMP, 0, cont_label);
            else
                gen_error(22, node->line, "");
            break;
        case N_STMT_BREAK:
            if (break_label)
                gen_code_l(JMP, 0, break_label);
            else
                gen_error(23, node->line, "");
            break;
        case N_STMT_RETURN:
            n = node->clink;
            if (n) {
                i = n->type->size;
                if (i % 4) i = i / 4 * 4 + 4;
                gen_code_i(LDA, 1, -i);
                gen_expression(n);
                gen_code_i(STO, 0, i / 4);
            }
            gen_code_i(RET, 0, 0);
            break;
        default :
            gen_error(100, node->line, "");
            break;
    }
}

void gen_statement_list(A_NODE *node, int cont_label, int break_label, A_SWITCH sw[], int *sn) {
    switch (node->name) {
        case N_STMT_LIST:
            gen_statement(node->llink, cont_label, break_label, sw, sn);
            gen_statement_list(node->rlink, cont_label, break_label, sw, sn);
            break;
        case N_STMT_LIST_NIL:
            break;
        default :
            gen_error(100, node->line, "");
            break;
    }
}

void gen_initializer_global(A_NODE *node, A_TYPE *t, int addr) {
    gen_code_i(LDA, 0, addr);
    gen_expression(node->clink);
    gen_code_i(STX, 0, 1);
    gen_code_i(POP, 0, 1);
}

void gen_initializer_local(A_NODE *node, A_TYPE *t, int addr) {
    gen_code_i(LDA, 1, addr);
    gen_expression(node->clink);
    gen_code_i(STX, 0, 1);
    gen_code_i(POP, 0, 1);
}

void gen_declaration_list(A_ID *id) {
    while (id) {
        gen_declaration(id);
        id = id->link;
    }
}

void gen_declaration(A_ID *id) {
    int i;
    A_NODE *node;
    switch (id->kind) {
        case ID_VAR:
            if (id->init) {
                if (id->level == 0) {
                    // skip here
                } else {
                    gen_initializer_local(id->init, id->type, id->address);
                }
            }
            break;

        case ID_FUNC:
            if (id->type->expr) {
                gen_label_name(id->name);
                gen_code_i(INT, 0, id->type->local_var_size);
                gen_statement(id->type->expr, 0, 0, 0, 0);
                gen_code_i(RET, 0, 0);
            }
            break;

        case ID_PARM:
        case ID_TYPE:
        case ID_ENUM:
        case ID_STRUCT:
        case ID_FIELD:
        case ID_ENUM_LITERAL:
        case ID_NULL:
            break;
        default:
            gen_error(100, id->line, "");
            break;
    }
}

void gen_error(int i, int ll, char *s) {
    gen_err++;
    printf("*** error at line %d: ", ll);
    switch (i) {
        case 11:
            printf("illegal identifier in expression \n");
            break;
        case 12:
            printf("illegal l-value expression \n");
            break;
        case 13:
            printf("identifier %s not l-value expression \n", s);
            break;
        case 20:
            printf("illegal default label in switch statement \n");
            break;
        case 21:
            printf("illegal case label in switch statement \n");
            break;
        case 22:
            printf("no destination for continue statement \n");
            break;
        case 23:
            printf("no destination for break statement \n");
            break;
        case 100:
            printf("fatal compiler error during code generation\n");
            break;
        default:
            printf("unknown \n");
            break;
    }
}

void gen_code_i(OPCODE op, int l, int a) {
    fprintf(fout, "\t%9s %d, %d\n", opcode_name[op], l, a);
}

void gen_code_f(OPCODE op, int l, float a) {
    fprintf(fout, "\t%9s %d, %f\n", opcode_name[op], l, a);
}

void gen_code_s(OPCODE op, int l, char *a) {
    fprintf(fout, "\t%9s %d, %s\n", opcode_name[op], l, a);
}

void gen_code_l(OPCODE op, int l, int a) {
    fprintf(fout, "\t%9s %d, L%d\n", opcode_name[op], l, a);
}

void gen_label_number(int i) {
    fprintf(fout, "L%d:\n", i);
}

void gen_label_name(char *s) {
    fprintf(fout, "%s:\n", s);
}