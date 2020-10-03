
# 과제 5 구문분석기 프로그램

동영상 강의 5주-2 에서 설명한대로 C 언어 위한 구문분석기 프로그램을 lex 와 yacc 을 이용하여 완성하고 실험결과를 보이시오

```c
yywrap() {
    return 1;
}
```

EOF 문제 때문에 필요할 수 있습니다. (.l 파일에)

문법이 맞으면 아무것도 안나오고 끝남. 틀리면 에러가 뜸.

## Install Dependencies

```sh
sudo apt install bison flex
```

## run

```sh
make
```
