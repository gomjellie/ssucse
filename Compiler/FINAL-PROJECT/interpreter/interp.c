#include "type.h"
extern char *opcode_name[];
extern INSTRUCTION code[];
extern int stack[];

extern float *stack_f;
extern char *stack_c;
void dump_stack();
void runtime_error(int, int);
int base(int);
void interp();
void lib_printf();
void lib_scanf();
void lib_malloc();

int p = 0,			// program counter
	b = 0,			// base register
	t = -1,			// stack top register
	hp = STACK_MAX; // heap pointer register

void dump_stack()
{
	int j = 0, i = 0;
	printf("\n===========stack dump================\n");
	for (i = 0; i <= t; i++)
	{
		printf("%08x", i);
		if (i == b)
			printf("*");
		else
			printf(" ");
		printf(":  %08x   %d,%f\n", stack[i], stack[i], *(stack_f + i));
	}
	printf("\n=====================================\n");
}

void runtime_error(int i, int a)
{
	printf("runtime error at pc %d : ", a);
	switch (i)
	{
	case 1:
		printf("devide by zero  \n");
		break;
	case 2:
		printf("array out of bound \n");
		break;
	case 3:
		printf("stack overflow \n");
		break;
	case 4:
		printf("unknown error in switch\n");
		break;
	case 100:
		printf("fatal error: unknown opcode\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
	exit(1);
}

int base(int l)
{
	if (l == 0)
		return (0);
	else
		return (b);
}

void interp()
{
	INSTRUCTION i;
	int j, k, l, m;
	stack[0] = 0;
	stack[1] = 0;
	stack[2] = 0;

	printf("start execution\n");

	do
	{
		i = code[p++];
		// dump_stack(); printf("%d : %s, %d, %d\n", p-1, opcode_name[i.f], i.l, i.a);
		switch (i.f)
		{
		case LOD:
			t++;
			stack[t] = stack[base(i.l) + i.a / 4];
			break;
		case LDI:
			stack[t] = stack[stack[t] / 4];
			break;
		case LDIB:
			stack[t] = *(stack_c + stack[t]);
			break;
		case LDX:
			t++;
			stack[t] = stack[stack[t - 1] / 4];
			break;
		case LDXB:
			t++;
			stack[t] = *(stack_c + stack[t - 1]);
			break;
		case LDA:
			stack[++t] = base(i.l) * 4 + i.a;
			break;
		case LITI:
			stack[++t] = i.a;
			break;
		case STO:
			t = t - 2;
			stack[stack[t + 1] / 4] = stack[t + 2];
			break;
		case STOB:
			t = t - 2;
			*(stack_c + stack[t + 1]) = stack[t + 2];
			break;
		case STX:
			t--;
			stack[stack[t] / 4] = stack[t + 1];
			stack[t] = stack[t + 1];
			break;
		case STXB:
			t--;
			*(stack_c + stack[t]) = stack[t + 1];
			stack[t] = stack[t + 1];
			break;
		case OFFSET:
			t--;
			stack[t] = stack[t] + stack[t + 1];
			break;
		case MOD:
			if (stack[t] == 0)
				runtime_error(1, p);
			else
			{
				t--;
				stack[t] = stack[t] % stack[t + 1];
			}
			break;
		case ADDI:
			t--;
			stack[t] = stack[t] + stack[t + 1];
			break;
		case SUBI:
			t--;
			stack[t] = stack[t] - stack[t + 1];
			break;
		case MULI:
			t--;
			stack[t] = stack[t] * stack[t + 1];
			break;
		case DIVI:
			if (stack[t] == 0)
				runtime_error(1, p);
			else
			{
				t--;
				stack[t] = stack[t] / stack[t + 1];
			}
			break;
		case ADDF:
			t--;
			*(stack_f + t) = *(stack_f + t) + *(stack_f + t + 1);
			break;
		case SUBF:
			t--;
			*(stack_f + t) = *(stack_f + t) - *(stack_f + t + 1);
			break;
		case MULF:
			t--;
			*(stack_f + t) = *(stack_f + t) * *(stack_f + t + 1);
			break;
		case DIVF:
			t--;
			*(stack_f + t) = *(stack_f + t) / *(stack_f + t + 1);
			break;

		case EQLI:
			t--;
			stack[t] = (stack[t] == stack[t + 1]) ? 1 : 0;
			break;
		case NEQI:
			t--;
			stack[t] = (stack[t] != stack[t + 1]) ? 1 : 0;
			break;
		case LSSI:
			t--;
			stack[t] = (stack[t] < stack[t + 1]) ? 1 : 0;
			break;
		case GEQI:
			t--;
			stack[t] = (stack[t] >= stack[t + 1]) ? 1 : 0;
			break;
		case GTRI:
			t--;
			stack[t] = (stack[t] > stack[t + 1]) ? 1 : 0;
			break;
		case LEQI:
			t--;
			stack[t] = (stack[t] <= stack[t + 1]) ? 1 : 0;
			break;

		case EQLF:
			t--;
			*(stack_f + t) = (*(stack_f + t) == *(stack_f + t + 1)) ? 1 : 0;
			break;
		case NEQF:
			t--;
			*(stack_f + t) = (*(stack_f + t) != *(stack_f + t + 1)) ? 1 : 0;
			break;
		case LSSF:
			t--;
			*(stack_f + t) = (*(stack_f + t) < *(stack_f + t + 1)) ? 1 : 0;
			break;
		case GEQF:
			t--;
			*(stack_f + t) = (*(stack_f + t) >= *(stack_f + t + 1)) ? 1 : 0;
			break;
		case GTRF:
			t--;
			*(stack_f + t) = (*(stack_f + t) > *(stack_f + t + 1)) ? 1 : 0;
			break;
		case LEQF:
			t--;
			*(stack_f + t) = (*(stack_f + t) <= *(stack_f + t + 1)) ? 1 : 0;
			break;

		case AND:
			t--;
			stack[t] = stack[t] && stack[t + 1];
			break;
		case OR:
			t--;
			stack[t] = stack[t] || stack[t + 1];
			break;
		case NOT:
			stack[t] = (stack[t] == 0) ? 1 : 0;
			break;
		case CVTI:
			stack[t] = (int)(*(stack_f + t));
			break;
		case CVTF:
			*(stack_f + t) = (float)stack[t];
			break;

		case JMP:
			p = i.a;
			break;
		case JPC:
			if (stack[t] == 0)
				p = i.a;
			t--;
			break;
		case JPCR:
			if (stack[t] == 0)
				p = i.a;
			else
				t--;
			break;
		case JPT:
			if (stack[t] != 0)
				p = i.a;
			t--;
			break;
		case JPTR:
			if (stack[t] != 0)
				p = i.a;
			else
				t--;
			break;
		case INT:
			t = t + i.a / 4;
			if (t >= 20000)
				runtime_error(3, p);
			break;
		case INCI:
			stack[t]++;
			break;
		case INCF:
			*(stack_f + t) += 1.0;
			break;
		case DECI:
			stack[t]--;
			break;
		case DECF:
			*(stack_f + t) -= 1.0;
			break;

		case POP:
			t = t - i.a;
			break;
		case MINUSF:
			*(stack_f + t) = -*(stack_f + t);
			break;
		case MINUSI:
			stack[t] = -stack[t];
			break;
		case RET:
			t = b - 1;
			p = stack[t + 3];
			b = stack[t + 2];
			break;
		case ADDR:
			t++;
			stack[t] = i.a;
			break;
		case SUP:
			stack[t + 1] = base(i.l);
			stack[t + 2] = b;
			stack[t + 3] = p;
			b = t + 1;
			p = i.a;
			break;
		case CAL:
			if (stack[t] > 0)
			{
				stack[t + 1] = b;
				stack[t + 2] = p;
				p = stack[t];
				stack[t] = base(i.l);
				b = t--;
				break;
			}
			else
				switch (-stack[t])
				{		// library functions
				case 1: // printf
					lib_printf();
					break;
				case 2: // malloc
					lib_malloc();
					break;
				case 3: // scanf
					lib_scanf();
					break;
				default:
					printf("library not yet implemented\n");
					break;
				}
			break;
		default:
			runtime_error(100, p);
			break;
		}
	} while (p);

	printf("\nend execution\n");
}
