#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char p[50] = {0};

        sprintf(p, "tar -jcvf %s.tar.bz2 %s", argv[1], argv[1]);
        printf("\nyour command is : %s\n", p);
        system(p);
        printf("\nyour command is : %s\n", p);
    }
    else
    {
        printf("\ntarc Usage :\n");
        printf("        tarc <filename>\n");
        printf("    by default,we compress the file into \".tar.bz2\" format\n");
    }
    exit(0);
}