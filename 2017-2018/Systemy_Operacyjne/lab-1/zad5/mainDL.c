//based on man 3 dlopen example
#include "../utils.h"
#include <dlfcn.h>

#define MAXSIZE 1000

int (*strdrop)(char *str, const char *set);
int (*strcnt)(const char *str, const char *set);

int main()
{
    void *handle;
    char *error;
    getchar();

    handle = dlopen("./libshared.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    getchar();
    dlerror(); /* Clear any existing error */

    strdrop = (int (*)(char *, const char *)) dlsym(handle, "strdrop");

    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    strcnt  = (int (*)(const char *, const char *)) dlsym(handle, "strcnt");

    error = dlerror();
    if (error != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }


    


// *******************************************
// *******************************************
// ******  TEST  *****************************
// *******************************************
// *******************************************

    char str[MAXSIZE] = "aaa slowo q slowo a slowo qqq";
    char set[MAXSIZE] = "aq";
    int counter = strcnt(str, set);
    char set2[MAXSIZE] = "qs";
    int newSize = strdrop(str, set2);
    if (counter == 8)
    {
        puts("TEST 1: OK");
    }
    else
        puts("TEST 1: ERROR");
    if (strcmp(str, "aaa lowo  lowo a lowo ") == 0)
    {
        puts("TEST 2: OK");
    }
    else
        puts("TEST 2: ERROR");
    if (newSize == 22)
    {
        puts("TEST 3: OK");
    }
    else
        puts("TEST 3: ERROR");

    dlclose(handle);
    getchar();
    return 0;
}
