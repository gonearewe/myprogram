#include "stdheader.h"
int main(int argc, char const *argv[])
{
    
    printf("%s",current_time);
    return 0;
}
char *gettime(void)
{
    timespec time;
    tm nowtime;
    char current_time[32]={0};
    clock_gettime(CLOCK_REALTIME,&time);
    localtime_r(&time.tv_sec,&nowtime);
    sprintf(current_time,"%04d-%02d-%02d %02d:%02d:%02d",nowtime.tm_year+1900,nowtime.tm_mon,nowtime.tm_mday,nowtime.tm_hour,nowtime.tm_min,nowtime.tm_sec);
    return current_time;
}
char *CreateLogHead(void)
{
    char head[128]={0};
    sprintf(head,"(%s) [%s : %s] ",gettime(),getlogin(),getcwd());
    head[127]=0;
    return head;
}