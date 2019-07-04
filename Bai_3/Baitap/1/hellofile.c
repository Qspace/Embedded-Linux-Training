#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//fprintf(fptr,"%d",num);
//fscanf(fptr, "%d", &num);
extern int errno;
int main(int argc, char **argv)
{
    printf("agrc: %d \n", argc);
    printf("%s %s %s \n", argv[0], argv[1], argv[2]);
    int fd = open("myfile.txt", O_WRONLY | O_CREAT, 0777);
    if (fd == -1)
    {
        printf("Error Number % d\n", errno);
        return -1;
    }
    else
    {
        char buf[] = "helloword\n";
        write(fd, buf, sizeof(buf));
        close(fd);
    }

    return 0;
}