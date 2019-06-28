#include <apue.h>
#include <stdheader.h>
char *gettime(void);
char *CreateLogHead(void);
int main(int argc, char const *argv[])
{
    
    getlogin_r(name,32);
    printf("%s",name);
    return 0;
}
