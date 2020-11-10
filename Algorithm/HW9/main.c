#include <stdio.h>
#include "1.h"
#include "2.h"

#define Q2

int main(int argc, const char * argv[]) {
#ifdef Q1
    q1();
#endif
#ifdef Q2
    q2();
#endif
    return 0;
}
