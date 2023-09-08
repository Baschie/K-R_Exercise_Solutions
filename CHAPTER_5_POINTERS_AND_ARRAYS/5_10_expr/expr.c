/* Exercise 5-10. Write the program expr, which evaluates a reverse Polish
expression from the command line, where each operator or operand is separate
argument. For example, expr 2 3 4 + * evaluates 2×(3+4) */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    char c;
    double op2;

    while (--argc > 0) {
        switch (c = (*++argv)[0]) {
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
                /* to recieve * as an argument puting a \ before it is neccassery, 
                otherwise all the file names in current directory would be recieved
                 as arguments */
            case '*':
                push(pop() * pop());
                break;
            case '/':
                if ((op2 = pop()) != 0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            default:
                if (isdigit(c))
                    push(atof(*argv));
                else
                    printf("unknown operator: %s\n", *argv);
                break;
        }
    }
    printf("%.8g\n", pop());
    return 0;
}

#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}