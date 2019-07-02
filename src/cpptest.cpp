#include <iostream>
#include <ctime>
#include <apue.h>
#include <cstring>
#include "cJSON.h"
#include <pwd.h>
using namespace std;
char *CreateLogHead(void);
class MyLog
{
    string time, name, abs_filepath, file_basename, cmd,logfile_addr;
    char *GetTime(void)
    {
        timespec time;
        tm nowtime;
        static char current_time[32] = {0};
        clock_gettime(CLOCK_REALTIME, &time);
        localtime_r(&time.tv_sec, &nowtime);
        sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d", nowtime.tm_year + 1900,
         nowtime.tm_mon, nowtime.tm_mday, nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec);
        return current_time;
    }

public:
    MyLog(string logfile_addr, string file_addr,string command)
    {
       

       
        char abs_filepath[128] = {0};
        struct passwd *ps;
        ps = getpwuid(getuid());

        time = GetTime();
        name=ps->pw_name;
        realpath(file_addr.c_str(), abs_filepath);
        file_basename=basename(file_addr.c_str());
        cmd =command;
        logfile_addr=logfile_addr;
    }
    bool CreateLog()
      {  
           cJSON *root;
        char *out;
         FILE *fp = fopen(logfile_addr.c_str(), "a+");
         if(!fp) return false;
        root = cJSON_CreateObject();
        cJSON_AddStringToObject(root, "date and time",time.c_str());
        cJSON_AddStringToObject(root, "login name",name.c_str());
        cJSON_AddStringToObject(root, "file original path", abs_filepath.c_str());
        cJSON_AddStringToObject(root, "filename",file_basename.c_str() );
        cJSON_AddStringToObject(root, "command", cmd.c_str());

        out = cJSON_Print(root);
        fprintf(fp, out);
        fclose(fp);

        cJSON_Delete(root);
        free(out);

        out = NULL;
        root = NULL;
        return true;
    }
};


void CreateJsonFile(char *option1, char *option2);
cJSON *GetJsonObject(char *filepath, cJSON *json);
void UsageHint();

int main(int argc, char **argv)
{

    cJSON *json;
    MyLog log;
    string logfile_addr, trashbin_addr;

    if ((json = GetJsonObject("./jsontest.json", json)) == NULL)
    {
        cJSON_Delete(json);
        return -1;
    }
    else
    {
        logfile_addr = cJSON_GetObjectItem(json, "logfile_addr")->valuestring;
        trashbin_addr = cJSON_GetObjectItem(json, "trashbin_addr")->valuestring;
        cJSON_Delete(json);
    }

    if (argc == 2 && ((argv[1] == "-h") || (argv[1] == "--help")))
        UsageHint();
    else if (argc == 2)
    {
        char command_buf[128] = {0};
        char abs_filepath[128] = {0};
        char *file_basename;
        if (getgid() == 0)
            sprintf(command_buf, "sudo mv %s %s", argv[1], trashbin_addr);
        else
            sprintf(command_buf, "mv %s %s", argv[1], trashbin_addr);
        if (realpath(argv[1], abs_filepath))
            return -1;
        file_basename = basename(argv[1]);
        system(command_buf);

   
    }
    else if (argc == 3 && argv[1] == "-r")
    {
        printf("not competed");
    }
    else
        UsageHint();

    return 0;
}

int create_js(void)
{
    cJSON *root;
    /*create json string root*/
    root = cJSON_CreateObject();
    if (!root)
        return -1;
    else

    {
        cJSON *js_body;

        const char *const body = "body";
        cJSON_AddItemToObject(root, body, js_body = cJSON_CreateObject());
        cJSON_AddStringToObject(js_body, "name", "xiaohui");
        cJSON_AddNumberToObject(js_body, "value", 600);
        cJSON_Delete(root);
    }

    return 0;
}

void UsageHint()
{
    printf("\nUsage for del :\n");
    printf("        del <file address>\n");
    printf(" del will clear the file or the dictionary,but unlike \"rm\",it's recoverable\n");
    exit(0);
}
cJSON *GetJsonObject(char *filepath, cJSON *json)
{
    long len;
    char *pContent;
    int tmp;
    FILE *fp = fopen(filepath, "rb+");
    if (!fp)
    {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    if (0 == len)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_SET);
    pContent = (char *)malloc(sizeof(char) * len);
    tmp = fread(pContent, 1, len, fp);

    fclose(fp);
    json = cJSON_Parse(pContent);
    if (!json)
    {
        return NULL;
    }
    free(pContent);
    return json;
}

bool GetValueString(cJSON *json, int id, char *name, char *param)
{
    cJSON *node;
    node = cJSON_GetArrayItem(json, id);
    if (!node)
    {
        return false;
    }
    sprintf(param, "%s", cJSON_GetObjectItem(node, name)->valuestring);
    return true;
}

void CreateJsonFile(char *filepath, char *option2)
{
    cJSON *root, *fld;
    char *out;
    FILE *fp = fopen(filepath, "w+");
    root = cJSON_CreateObject();

    cJSON_AddStringToObject(root, "id", "c1");

    cJSON_AddStringToObject(root, "fid", "1");

    cJSON_AddStringToObject(root, "id", "p1");
    cJSON_AddStringToObject(root, "option", option2);
    cJSON_AddStringToObject(root, "fid", "2");

    out = cJSON_Print(root);
    fprintf(fp, out);
    fclose(fp);

    cJSON_Delete(root);
    free(out);

    out = NULL;
    root = NULL;
}
