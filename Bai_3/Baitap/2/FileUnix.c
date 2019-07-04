#include <sys/stat.h>
#include <sys/types.h>
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
    if ((strcmp("r", argv[1]) == 0))
    {
        printf("this is read file program\n");
        int fd = open("myfile.txt", O_RDONLY);
        if (fd == -1)
        {
            printf("error open file\n");
            return -1;
        }
        else
        {
            char buf[1];
            int ret = read(fd, buf, 1);
            printf("%d\n",ret);
            if (ret)
            {
                printf("%s\n",buf);
                printf("Number: %d\n", atoi(buf));
            }
            close(fd);
            return ret;
        }
    }
    else
    {
        int fd = open("myfile.txt", O_WRONLY | O_CREAT, 0777);
        if (fd == -1)
        {
            printf("Error Number % d\n", errno);
            return -1;
        }
        else
        {
            write(fd, "1", 1);
            fsync(fd);          
        }
        close(fd);
    }

    return 0;
}