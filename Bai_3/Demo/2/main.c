#include "lib.h"
//#define TEST 
int main()
{
    #ifdef TEST
	printf("test\n");
    #else
    	printf("release\n");
    #endif	
    return 0;
}
