/* Exercise 5-13. Write the program tail, which prints the last n lines of its input.
By default, n is set to 10, let us say, but it can be changed by an optional argument
so that "tail -n" prints the last n lines. The program should behave rationally 
no matter how unreasonable the input or the value of n.
Write the program so it makes the best use of available storage; 
lines should be stored as in the sorting program of Section 5.6, 
not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isint(char s[]); 
int toint(char s[]); /* convert s to an integer */
int readlines(char *lineptr[], int no); /* read the last 'no' lines and save them in lineptr */
void writelines(char *lineptr[], int no);

#define MAXLINE 100 /* the maximum acceptable number of lines to be printed */

int main(int argc, char *argv[])
{
    int n = 10;
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
    if (readlines(lineptr, n) >= 0) {
        writelines(lineptr, n);
        return 0;
    } else {
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
    } else
        return 0;
}

int toint(char s[])
{
    while (*s == '-' || *s == '0')
        s++;
    return atoi(s);
}

#define MAXLEN 1000 /* maximum acceptable length of a line to be saved */

int readlines(char *lineptr[], int no)
{
    char *alloc(int n, int no);
    int get_line(char *, int); /* returns the length of a line excluding '\0' */
    void push(char *lineptr[], char *p, int len); /* pushes a pointer in lineptr */

    int len, i;
    char *p, line[MAXLEN];

    for (i = 0; i < no; i++)
        lineptr[i] = NULL;  /* in case the number of to-be-printed lines is less thatn 'no' */

    while ((len = get_line(line, MAXLEN)) > 0)
        if ((p = alloc(len, no)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0'; /* remove the nl character, -*/
                                /*-the last line of input is expected to end in a nl */
            strcpy(p, line);
            push(lineptr, p, no);
        }
    return 1;
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
    int i;

    for (i = 0; i < no-1; i++)
        lineptr[i] = lineptr[i+1];
    lineptr[no-1] = p;
}

#define ALLOCSIZE MAXLINE * MAXLEN

static char allocbuf[ALLOCSIZE];
static int allocn = 0; /* the number of allocations */
static char *allocp = allocbuf;
static char *leftalloc = allocbuf; /* left edge of the replaceable section of array */
static char *rightalloc = allocbuf - 1; /* right edge of the replaceable section of array */

char *alloc(int n, int no)
{
    int i;
    char *j;

    if (allocn%no == no - 1) {
        leftalloc = allocbuf;
        rightalloc = allocbuf - 1; /* no line is replaceable yet */
    }
    if (allocn >= no) {
        while (allocn-no >= no) /* reduce allocn to congruent modulo 'no' value to prevent overflow */
            allocn -= no;
        for (i = 0; i < allocn%no; i++)
            while (*rightalloc++ != '\0');
                ;
    }

    if (n <= rightalloc - leftalloc + 1) {
        leftalloc += n;
        allocn++;
        return leftalloc - n;
    } else if (n <= allocbuf + ALLOCSIZE - allocp) {
        allocp += n;
        allocn++;
        return allocp - n;
    } else
        return NULL;
}
