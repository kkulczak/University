// Basedon on example program from makecontext(3)

#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"

static ucontext_t uctx_main, uctx_func1, uctx_func2, uctx_func3;

#define MAXSIZE 1000

int pipefd[2][2];
pid_t cpid;
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
        int bytesRead = strlen(inBuff) + 1;
        write(pipefd[0][1], inBuff, bytesRead);
    }
    close(pipefd[0][1]);
    printf("Words: %d\n", counterWords);
    exit(EXIT_SUCCESS);
}

static void func2(void)
{
    int bytesRead;
    while ((bytesRead = read(pipefd[0][0], inBuff, MAXSIZE)) > 0)
    {
        // printf("bR: %d\n", bytesRead);
        char *inPtr = inBuff;
        char *outPtr = outBuff;
        char howMany = 0;
        while (inPtr != inBuff + bytesRead)
        {
            do
            {
                if (isalnum(*inPtr))
                {
                    *(outPtr++) = *inPtr;
                }
            } while (*(inPtr++) != '\0');
            *outPtr++ = '\0';
        }
        write(pipefd[1][1], outBuff, outPtr - outBuff);
        
    }
    close(pipefd[0][0]);
    close(pipefd[1][1]);
    exit(EXIT_SUCCESS);
}

static void func3(void)
{
    int bytesRead;
    while ((bytesRead = read(pipefd[1][0], outBuff, MAXSIZE)) > 0)
    {
        char * ptr = outBuff;
        while ( ptr != outBuff + bytesRead ) {
            printf("%s ", ptr);
            int n = strlen(ptr);
            counterChars += n;
            ptr += n + 1;
        }
        memset(outBuff, '\0', bytesRead);
    }
    printf("Chars: %d\n", counterChars);
    close(pipefd[1][0]);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    pid_t cpid1, cpid2, cpid3;
    char buf;

    if (pipe(pipefd[0]) == -1 || pipe(pipefd[1]) == -1)
    {
        handle_error("pipe");
    }

    if ((cpid = fork()) == -1)
    {
        handle_error("fork");
    }

    if (cpid == 0)
    {                        /* Write to pipe */
        close(pipefd[0][0]); /* Close read */
        func1();
    }

    close(pipefd[0][1]);

    if ((cpid = fork()) == -1)
    {
        handle_error("fork");
    }

    if (cpid == 0)
    {                        /* Child reads from pipe */
        close(pipefd[1][0]); /* Close read */
        func2();
    }

    close(pipefd[0][0]);
    close(pipefd[1][1]);

    if ((cpid = fork()) == -1)
    {
        handle_error("fork");
    }

    if (cpid == 0)
    {                        /* Child reads from pipe */
        close(pipefd[1][1]); /* Close read */
        func3();
    }

    close(pipefd[1][0]);

    int status;
    for (int i = 0; i < 3; i++)
    {
        wait(&status);
        if(status > 0) {
            exit(EXIT_FAILURE);
        }
    }
}
