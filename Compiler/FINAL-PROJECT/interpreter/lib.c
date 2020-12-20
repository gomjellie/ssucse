#include <stdio.h>
extern float *stack_f;
extern char *stack_c;
extern int stack[];
extern int t, b, hp;

void lib_printf();
void lib_scanf();
void lib_malloc();

void lib_malloc()
{
	int j;
	j = stack[t + 3];
	if (j % 4)
		j = j / 4 * 4 + 4;
	hp = hp - j / 4;
	stack[--t] = hp * 4;
}

void lib_printf()
{
	char *s, c, *ss;
	int i, w = 0;
	i = (t--) + 3;
	ss = stack;
	s = &stack[stack[i] / 4];
	while (c = *(s++))
	{
		if (c == '\\')
		{
			c = *(s++);
			if (c == 'n')
				printf("\n");
			else if (c == 't')
				printf("\t");
			else
				printf("%c", c);
		}
		else if (c == '%')
		{
			c = *(s++);
			while (isdigit(c))
			{
				w = w * 10 + c - '0';
				c = *(s++);
			}
			switch (c)
			{
			case 'd':
				i++;
				printf("%d", stack[i]);
				break;
			case 'c':
				i++;
				printf("%c", stack[i]);
				break;
			case 'f':
				i++;
				printf("%f", *(stack_f + i));
				break;
			case 's':
				i++;
				ss = stack;
				ss = ss + stack[i];
				printf("%s", ss);
				break;
			case 0:
				printf("\%");
				return;
			default:
				printf("\%%c", c);
				break;
			}
		}
		else
			printf("%c", c);
	}
}

void lib_scanf()
{
	char *s, c, ch;
	int temp_i;
	float temp_f;
	char temp_s[80];
	int i, j = 0;
	i = (t--) + 3;
	s = &stack[stack[i] / 4];
	while (c = *(s++))
	{
		if (c == ' ' || c == '\t' || c == '\n')
			;
		else if (c == '%')
		{
			c = *(s++);
			switch (c)
			{
			case 'd':
				i++;
				scanf("%d", &temp_i);
				stack[stack[i] / 4] = temp_i;
				break;
			case 'c':
				i++;
				ch = getchar();
				while (ch == ' ' || ch == '\t' || ch == '\n')
					ch = getchar();
				*(stack_c + stack[i]) = ch;
				break;
			case 'f':
				i++;
				scanf("%f", &temp_f);
				*(stack_f + stack[i] / 4) = temp_f;
				break;
			case 's':
				i++;
				ch = getchar();
				while (ch == ' ' || ch == '\t' || ch == '\n')
					ch = getchar();
				while (ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF)
				{
					temp_s[j++] = ch;
					ch = getchar();
				}
				temp_s[j] = 0;
				strcpy(stack_c + stack[i], temp_s);
				break;
			case 0:
				return;
			default:
				printf("\%%c", c);
				break;
			}
		}
		else
		{
			while ((ch = getchar()) != EOF && ch != c)
				;
			if (ch == EOF)
				return;
		}
	}
}
