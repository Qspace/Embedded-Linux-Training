#include <mysql.h>
#include <stdio.h>

int main(void)
{
	printf("%s\n",mysql_get_client_info());
	return 0; 
}
