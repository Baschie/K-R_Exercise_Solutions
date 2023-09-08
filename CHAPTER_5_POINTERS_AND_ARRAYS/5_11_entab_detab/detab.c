#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFTAB 8
#define MAXTAB 100

int isint(char s[]);

int main(int argc, char *argv[])
{
    int i, c, tablist[MAXTAB], r, tab;

    for (i = 0; i < argc-1 && i < MAXTAB; i++)
        if (isint(*++argv) == 0 || ((tablist[i] = atoi(*argv)) <= 0)) {
            printf("Unacceptable tab stop %s\n", *argv);
            return 1;
        }
    if (i == 100) {
        printf("Too many arguments\n");
        return 1;
    }

    r = i = 0;
    while ((c = getchar()) != EOF) {
        tab = i < argc-1 ? tablist[i] : DEFTAB;
        if (c != '\t') {
            putchar(c);
            if (c == '\n') {
                r = i = 0;
            }
            else if (++r >= tab) {
                r = 0;
                i++;
            }
        }
        else {
            while (tab - r++)
                putchar(' ');
            i++;
            r = 0;
        }
    }
    return 0;
}

int isint(char s[])
{
    int i;

    for (i = 0; s[i] != '\0'; i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}