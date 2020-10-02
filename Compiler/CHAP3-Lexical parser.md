
# 3장 어휘분석기 (Lexical Analyzer)

## 인트로

안녕하십니까 유재우 교수입니다.

우리가 2장에서는 C언어의 문법에대해서 배웠습니다.

문법을 쭉 나열해서 배웠는데. 문법을 배운것은 씨언어를 잘 알기 위한것도 목적이지만은,

구문분석기, 소위 말하는 parser를 만들기 위한것이 목적인데

구문 분석기 프로그램은 여러분이 잘 아시다시피 파싱 테이블하고 쉬프트 리듀스 하면서 돌아가잖아요.

그 프로그램을 yyparse라고해서 main에서 yyparse를 호출하잖아요?

이 구문분석기 프로그램안에서는 물론 yylex로 토큰을 자르는것도 필요하겠지요.

이런 프로그램을 짜는데 이런 프로그램은 다 똑같고 파싱테이블만 다르다. 

이 테이블을 어떻게 만드느냐, 만드는 방법은 안가르쳐 줬지만 이 문법가지고 만드는거다.

문법이 있으면 문법을 가지고, 손으로 돌려서 parsing테이블을 만들 수도 있지만, 좋은 소프트웨어 yacc이 있기 때문에 yacc을 돌리면 테이블이 생긴다.

그래서 나중에 메인함수하고 yylex 기타 error함수 몇가지를 추가해서 돌리면 구문분석하는 프로그램을 쉽게 만들 수 있다 이거죠.

그래서 파싱하는 프로그램은 다 됐어요. 문법이 준비가 됐기때문에, 뭐 문법에 모호성 문제가 있기는 하지만

큰 문제는 없기 때문에, 또 몇가지 문제점이 있지만 그건 나중에 또 설명을 하고.

메인 프로그램은 뭐 간단하죠 yyparse를 호출을 하면되고, yylex도 뭐 쉽게 확장을 할 수 있습니다.

이번시간에는 yylex프로그램을 어떻게 짤것인가 설명을 하도록 하겠습니다.

## 어휘분석기의 역할

어휘분석기는 결국 yyparse 프로그램이 필요할때마다 yylex를 호출을 하죠.

토큰을 잘라서 계속 리턴을 해줍니다.

syntax analysis (yyparse함수)는 결국엔 문법을 검사만 하는것이 아니라 syntax tree를 만들어줘요.

~는 나중에 설명하도록 하고, 이번시간에는 syntax analysis 프로그램이 yylex를 계속 호출하는데

yylex를 어떻게 짜는지 설명하도록 하겠습니다.

## 토큰 분류표

| 토큰 패턴 | 토큰 분류코드 | 부수 정보(yylval) |
| :---: | :---: | :---: |
| + | PLUS | NA |
| * | STAR | NA |
| ( | LPAREN | NA |
| ) | RPAREN | NA |
| = | EQL | NA |
| \n | NEW_LINE | NA |
| print | PRINT | 명칭 스트링의 저장 |
| 명칭 | IDENT | 주소 |
| 정수 | NUMBER | 정수값 |

어떤것들은 yylval이 필요합니다.

예를들어 kim이라는 이름을 자르면 yylval에다가 kim이라는 스트링을 카피하고

명칭의 주소를 yylval이 가리키도록 그렇게 할 수 있겠죠.

yylex프로그램은 사실 손으로 짜는게 아니라 이렇게 테이블을 만들어놓으면 lex라는 프로그램이 만들어줍니다.

그래서 lex를 어떻게 쓰는지 설명을 하겠습니다. 그래서 과제를 할때는 unix에서 하라고 설명을 했습니다.

## Lex 명세서 구성

```lex
declarations

%%
token-pattern1 { action1 }
token-pattern2 { action2 }
%%

auxiliary program
```

yacc과 마찬가지로 %%가 꼭 나와야하고 그 가운데 규칙에대한것이 나옵니다. 예를들면

## 패턴 정의 규칙과 예

(정규식 나옴. 설명 생략)

몇가지 주의해야하는 전역변수, 함수들이 있는데

yylval, yytext, yyleng 이런것은 yylex에서 사용하는 변수들입니다.

yylval을 통해서 yyparse와 소통합니다.

정규식을 token-pattern에 바로 써도되고

정규식 패턴을 declarations파트에 정의한후에 아래에서 가져다 써도 됩니다.

예를들면

[0-9] 이렇게 바로 token-pattern에 넣어도 되지만

위에 digit   [0-9]

해놓고서 아래에서는 tokken-pattern에 {digit} 이렇게만 쓰면 같습니다.

## C언어의 토큰 종류

### 예약어

```c
auto break case char
continue default do
else enum float for
if int return sizeof
static struct switch
typedef union void while
```

### 특수기호

```c
++ -- -> < >
<= >= == != 
&& ||
... ( ) [ ] { }
: . , ! * / % & +
- =
```

### 상수

정수형 상수, 실수형 상수, 문자형 상수, 스트링 리터럴

### 명칭

identifier

## C언어의 lex 프로그램

```lex
digit [0-9]
letter [a-zA-Z]
delim [ \t]
line [\n]
ws {delim}+

%{
#include "y.tab.h"

extern int yylval;
extern int line_no;
char *makeString();
int checkIdentifier();
%}

%%
{ws} { }
{line} { line_no ++; }
auto { return AUTO_SYM; }
break { return BREAK_SYM; }
case { return CASE_SYM; }
continue { return CONTINUE_SYM; }
default { return DEFAULT_SYM; }
do { return DO_SYM; }
else { return ELSE_SYM; }
enum { return ENUM_SYM; }

"\+\+" { return PLUSPLUS; }
"\-\-" { return MINUSMINUS; }
...
{digit}+ { return INTEGER_CONSTANT; }
{digit}+\.{digit}+ { return FLOAT_CONSTANT; }
{letter}({letter}|{digit})*
\"([^"\n][\\["\n])*\ { return STRING_LITERAL; }
...
%%

```
