#define _GNU_SOURCE
#include <ucontext.h>
#include "../utils.h"

#define MAXSIZE 1000
#define PAGE_SIZE 4096

void f(int sig, siginfo_t *info, void *ptr)
{
    if (sig != SIGSEGV)
        handle_error("Diffrent signal");
    ucontext_t *context = (ucontext_t *)ptr;
    unsigned char *pc = (unsigned char *)context->uc_mcontext.gregs[REG_RIP];
    unsigned char *sp = (unsigned char *)context->uc_mcontext.gregs[REG_RSP];

    char msg[MAXSIZE];
    snprintf(
        msg,
        MAXSIZE,
        "SIGSEGV : %s\n"
        "Memory address %zu\n"
        "Instruction address %zu\n"
        "Stack pointer %zu\n",
        info->si_code == SEGV_MAPERR 
            ? "Address not mapped"
            : "Invalid permissions",
        (size_t)info->si_addr,
        (size_t)pc,
        (size_t)sp
    );
    write(STDERR_FILENO, msg, strlen(msg));
    void *data[MAXSIZE];
    int howMany = backtrace(data, MAXSIZE);
    backtrace_symbols_fd(data, howMany, STDERR_FILENO);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_flags = SA_SIGINFO;
    act.sa_handler = (void *)f;

    struct sigaction oldact;
    memset(&oldact, 0, sizeof(oldact));

    if (sigaction(SIGSEGV, &act, &oldact) == -1)
    {
        handle_error("sigaction");
    }

    void *ptr;
    int var;

    if (argc == 2 && strcmp(argv[1], "unmapped") == 0)
    {
        ptr = NULL;
        var = *((int *)ptr);
    }
    else if (argc == 2 && strcmp(argv[1], "readonly") == 0)
    {

        if (posix_memalign(&ptr, PAGE_SIZE, PAGE_SIZE))
        {
            handle_error("memalign");
        }

        if (mprotect(ptr, PAGE_SIZE, PROT_NONE | PROT_READ) < 0)
        {
            handle_error("mprotect");
        }

        *((int *)ptr) = 0;
    }
    else
    {

        printf("Prgoram usage: %s <unmapped|readonly>\n", argv[0]);
    }
    return 0;
}
