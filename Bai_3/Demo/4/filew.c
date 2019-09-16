#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//fprintf(fptr,"%d",num);
//fscanf(fptr, "%d", &num);
int main(int argc, char **argv)
{
    printf("agrc: %d \n", argc);
    printf("%s %s %s \n", argv[0], argv[1], argv[2]);
    if ((strcmp("r", argv[1]) == 0))
    {
        printf("this is read file program\n");
        FILE *fp;
        fp = fopen("myfile.txt", "r");
        if (fp == NULL)
        {
            printf("error open file\n");
            return -1;
        }
        else
        {
            int num =0;
            while(!feof(fp))
            {
                printf("%d\n",fscanf(fp, "%d", &num));
                printf("%d\n",num);
            }
            fclose(fp);
        }
    }
    else
    {
        FILE *fp;
        fp = fopen("myfile.txt", "w");
        if (fp == NULL)
        {
            printf("error open file\n");
            return -1;
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                if(i!=9)
                {
                    fprintf(fp, "%d\n", i);
                }
                else
                {
                     fprintf(fp, "%d", i);
                }
            }
        }
        fclose(fp);
    }

    return 0;
}
