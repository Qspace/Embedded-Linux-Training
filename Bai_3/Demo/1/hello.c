#include <stdio.h>
#include <stdlib.h>
//#define TEST
int main(int argc, char** argv)
{
	#ifdef TEST
		printf("test\n");
    	#endif 
	printf("Hello world\n");
	while(1);
	return 0;
}
