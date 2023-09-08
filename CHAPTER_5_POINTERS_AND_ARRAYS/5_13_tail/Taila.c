#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isint(char s[]);
int toint(char s[]);
int readlines(char *lineptr[], int no);
void writelines(char *lineptr[], int no);

#define MAXLINE 100

int main(int argc, char *argv[])
{
    int n = 10, nlines;
    char *lineptr[MAXLINE];

    while (--argc > 0) {
        if ((*++argv)[0] == '-' && isint(*argv) && toint(*argv) <= MAXLINE) {
            n = toint(*argv);
            break;
        }
        else
            printf("invalid argument %s\n", *argv);
    }

    printf("Printing %d line%s\n", n, n > 1 ? "s" : "");
    if ((nlines = readlines(lineptr, n)) >= 0) {
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big too handle\n");
        return 1;
    }

    return 0;
}

int isint(char s[])
{
    while (*s == '-' || *s == '0')
        s++;
    if (isdigit(*s)) {
        while (*s != '\0')
            if (!isdigit(*s++))
                return 0;
        return 1;
    }
    else
        return 0;
}

int toint(char s[])
{
    while (*s == '-' || *s == '0')
        s++;
    return atoi(s);
}

#define MAXLEN 1000

int readlines(char *lineptr[], int no)
{
    char *alloc(int n, int no);
    int get_line(char *, int);
    void push(char *lineptr[], char *p, int len);

    int nlines, len, i;
    char *p, line[MAXLEN];

    for (i = 0; i < no; i++)
        lineptr[i] = NULL;

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if ((p = alloc(len, no)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            push(lineptr, p, no);
            nlines++;
        }
    return no < nlines ? no : nlines;
}

void writelines(char *lineptr[], int no)
{
    int i;
    
    for (i = 0; i < no; i++)
        if (lineptr[i] != NULL)
            printf("%s\n", lineptr[i]);
}

int get_line(char *line, int lim)
{
    int i, c;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';

    return i;
}

void push(char *lineptr[], char *p, int no)
{
    void shift(int i)
    {
        if (i > 1)
            shift(i-1);
        lineptr[i-1] = lineptr[i];
    }

    shift(no-1);
    lineptr[no-1] = p;
}

#define ALLOCSIZE MAXLINE * MAXLEN

static char allocbuf[ALLOCSIZE];
static int allocn = 0; /* the number of allocations */
static char *allocp = allocbuf;
static char *backallocp = allocbuf; /* the start of replaceable section of array */
static char *backallocpend = allocbuf - 1; /* the end of replaceable section of array */

char *alloc(int n, int no)
{
    int i;
    char *j;

    if (allocn%no == no - 1) { /* if the current allocation will reach */
        backallocp = allocbuf;
        backallocpend = allocbuf - 1;
    }
    if (allocn >= no) {
        while (allocn-no >= no)
            allocn -= no;
        for (i = 0; i < allocn%no; i++)
            while (*backallocpend++ != '\0');
                ;
    }

    if (n <= backallocpend - backallocp + 1) {
        backallocp += n;
        allocn++;
        return backallocp - n;
    } else if (n <= allocbuf + ALLOCSIZE - allocp) {
        allocp += n;
        allocn++;
        return allocp - n;
    } else
        return NULL;
}
