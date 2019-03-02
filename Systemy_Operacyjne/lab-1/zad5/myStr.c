#include "myStr.h"
#include <string.h>

int existsInSet(const char  x,const char *set) {
    for (const char * i = set; *i != '\0'; i++) {
        if (*i == x) {
            return 1;
        }
    }
    return 0;
}

int strdrop(char *str, char*set) {
    int len = 0;
    char * writePtr = str;
    char * readPtr = str;
    while (*(readPtr) != '\0') {
        if (existsInSet(*readPtr, set)) {
            readPtr++;
        } 
        else {
            *(writePtr++) = *(readPtr++); 
            len++;
        }
    }
    *writePtr = '\0';
    return len;
}

int strcnt(const char *str, const char *set){
    int res = 0;
    const char * readPtr = str;
    while (*(readPtr) != '\0') {
        res += existsInSet(*readPtr, set);
        readPtr++;
    }
    return res;
}
