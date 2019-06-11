#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char p[30] = {0};
        if (strstr(argv[1], ".tar.gz") != 0)
        {
            sprintf(p, "tar -zxvf %s", argv[1]);
            printf("\nyour command is : %s\n", p);
            system(p);
            printf("\nyour command is : %s\n", p);
        }
        else if (strstr(argv[1], ".tar.bz2") != 0)
        {
            sprintf(p, "tar -jxvf %s", argv[1]);
            printf("\nyour command is : %s\n", p);
            system(p);
            printf("\nyour command is : %s\n", p);
        }
        else
        {
            printf("\ntarx only supports files ended with \".tar.gz\" or \".tar.bz2\"\n");
        }
    }
    else
    {
        printf("\ntarx Usage :\n");
        printf("        tarx <filename>\n");
    }
    exit(0);
}