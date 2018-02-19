// Basedon on example program from makecontext(3)

#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"

static ucontext_t uctx_main, uctx_func1, uctx_func2, uctx_func3;

#define MAXSIZE 1000

char inBuff[MAXSIZE];
char outBuff[MAXSIZE];
int counterWords = 0;
int counterChars = 0;
int finished = 0;

static void func1(void)
{
    while (scanf("%s", inBuff) != EOF)
    {
        counterWords++;
        if (swapcontext(&uctx_func1, &uctx_func2) == -1)
            handle_error("swapcontext 1->2");
    }
    finished = 1;
    printf("\nWords: %d\n", counterWords);
}

static void func2(void)
{
    while (1)
    {
        if (finished)
        {
            return;
        }

        char *inPtr = inBuff;
        char *outPtr = outBuff;

        while (*inPtr != '\0')
        {
            if (isalnum(*inPtr))
            {
                *(outPtr++) = *inPtr;
            }
            *(inPtr++) = '\0';
        }
        if (swapcontext(&uctx_func2, &uctx_func3) == -1)
            handle_error("swapcontext 2->3");
    }
}

static void func3(void)
{
    while (1)
    {
        if (finished)
        {
            printf("Chars: %d\n", counterChars);
            return;
        }

        char *outPtr = outBuff;

        while (*outPtr != '\0')
        {
            printf("%c", *outPtr);
            *(outPtr++) = '\0';
            counterChars++;
        }
        putchar(' ');
        if (swapcontext(&uctx_func3, &uctx_func1) == -1)
            handle_error("swapcontext 2->3");
    }
}

int main(int argc, char *argv[])
{
    char func1_stack[16384];
    char func2_stack[16384];
    char func3_stack[16384];
    for (int i = 0; i < MAXSIZE; i++)
    {
        *inBuff = '\0';
        *outBuff = '\0';
    }

    if (getcontext(&uctx_func1) == -1)
        handle_error("getcontext");
    uctx_func1.uc_stack.ss_sp = func1_stack;
    uctx_func1.uc_stack.ss_size = sizeof(func1_stack);
    uctx_func1.uc_link = &uctx_func2;
    makecontext(&uctx_func1, func1, 0);

    if (getcontext(&uctx_func2) == -1)
        handle_error("getcontext");
    uctx_func2.uc_stack.ss_sp = func2_stack;
    uctx_func2.uc_stack.ss_size = sizeof(func2_stack);
    uctx_func2.uc_link = &uctx_func3;
    makecontext(&uctx_func2, func2, 0);

    if (getcontext(&uctx_func3) == -1)
        handle_error("getcontext");
    uctx_func3.uc_stack.ss_sp = func3_stack;
    uctx_func3.uc_stack.ss_size = sizeof(func3_stack);
    uctx_func3.uc_link = NULL;
    makecontext(&uctx_func3, func3, 0);

    if (swapcontext(&uctx_main, &uctx_func2) == -1)
        handle_error("swapcontext");
    
    exit(EXIT_SUCCESS);
}
