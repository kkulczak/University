#include "../utils.h"

char *myName;

void handleError()
{
    fprintf(stderr, "select error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

void runPS()
{
    puts("Creating ps process");
    pid_t secondChildPid = fork();
    if (secondChildPid < 0)
        handleError();
    if (secondChildPid == 0)
    {
        puts("Executing ps");
        char *newArgv[] = {"ps", "-C", myName, "-l", NULL};
        char *newEnviron[] = {NULL};
        if (execve("/bin/ps", newArgv, newEnviron) < 0)
            handleError();
    }
}

void createZombie()
{
    pid_t childPid = fork();
    if (childPid < 0)
        handleError();
    if (childPid == 0)
    {
        puts("Child Exits.");
        exit(EXIT_SUCCESS);
    }
    runPS();
    sleep(1);
}

void ignoreSIGCHLD()
{
    struct sigaction new_action = {0};
    new_action.sa_handler = SIG_IGN;
    if (sigaction(SIGCHLD, &new_action, NULL) < -1)
        handleError();
}

void becameReaper()
{
    prctl(PR_SET_CHILD_SUBREAPER, 1);
}

void makeOrphan()
{
    pid_t childPid = fork();
    if (childPid < 0)
    {
        handleError();
    }
    if (childPid == 0)
    {   
        printf("[%d] I'm a son\n",getpid());
        childPid = fork();
        if (childPid < 0)
        {
            handleError();
        }
        if (childPid == 0)
        {
            printf("[%d] I'm a grandson\n", getpid());
            sleep(2);
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char const *argv[])
{
    char nameData[15];
    myName = nameData;
    strncpy(myName, argv[0], 10);
    myName = basename(myName);

    if (argc == 2 && strcmp(argv[1], "zombie") == 0)
    {
        createZombie();
    }
    else if (argc == 2 && strcmp(argv[1], "zombiePrevention") == 0)
    {
        ignoreSIGCHLD();
        createZombie();
    }
    else if (argc == 2 && strcmp(argv[1], "orphan") == 0)
    {
        ignoreSIGCHLD();
        makeOrphan();
        runPS();
        sleep(2);
    }
    else if (argc == 2 && strcmp(argv[1], "orphanReaper") == 0)
    {
        ignoreSIGCHLD();
        becameReaper();
        makeOrphan();
        runPS();
        sleep(2);
    }
    else
    {
        printf("Program usage: %s <zombie|zombiePrevention|orphan|orphanReaper>\n", argv[0]);
    }
    return 0;
}
