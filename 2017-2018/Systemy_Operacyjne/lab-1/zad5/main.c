#include "../utils.h"
#include "myStr.h"

#define MAXSIZE 1000




int main()
{
    char str[MAXSIZE] = "aaa slowo q slowo a slowo qqq";
    char set[MAXSIZE] = "aq";
    int counter = strcnt(str,set);
    char set2[MAXSIZE] = "qs";
    int newSize = strdrop(str,set2);
    if (counter == 8) {
        puts("TEST 1: OK");        
    } else
        puts("TEST 1: ERROR");                
    if (strcmp(str, "aaa lowo  lowo a lowo ") == 0) {
        puts("TEST 2: OK");
    } else
        puts("TEST 2: ERROR");
    if ( newSize == 22) {
        puts("TEST 3: OK");
    }else
        puts("TEST 3: ERROR");

}
