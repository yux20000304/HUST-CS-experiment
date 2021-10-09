#include <unistd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

void getRWX(const unsigned short m)
{
    if (m & S_IRUSR)
        printf("r");
    else
        printf("-");

    if (m & S_IWUSR)
        printf("w");
    else
        printf("-");

    if (m & S_IXUSR)
        printf("x");
    else
        printf("-");

    if (m & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (m & S_IWGRP)
        printf("w");
    else
        printf("-");

    if (m & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (m & S_IROTH)
        printf("r");
    else
        printf("-");

    if (m & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (m & S_IXOTH)
        printf("x   ");
    else
        printf("-   ");
    return;
}

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(dir)) == NULL)
    {
        printf("path error!");
        return;
    }
    chdir(dir);     //把dir设置成当前目录
    while ((entry = readdir(dp)) != NULL)
    { //读取到一个目录项
        lstat(entry->d_name, &statbuf);     //以该目录项的名字为参数,调用lstat得到该目录项的相关信息
        if (S_ISDIR(statbuf.st_mode))       //是目录
        {
            if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)    //目录项的名字是..或者是.
                continue;       //跳过该目录项
            getRWX(statbuf.st_mode);   //把8进制转换为rwx格式字符显示        
            printf("%d\t", depth); //打印深度
            struct passwd *pwd;     //创建的passwd结构体可以存储用户的名字id等信息
            pwd = getpwuid(statbuf.st_uid);
            printf("%s\t", pwd->pw_name); //打印文件所有者ID
            struct passwd *gpwd;
            gpwd = getpwuid(statbuf.st_gid);
            if(gpwd==NULL)
                return 0;
            printf("%s\t", gpwd->pw_name);    //文件所有者组ID
            printf("%ld\t", statbuf.st_size); //文件大小
            char time[50];
            strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&statbuf.st_ctime));    //打印文件的修改日期
            printf("%s\t", time); //最后修改内容时间
            printf(BLU "%s\n" RESET, entry->d_name);
            printdir(entry->d_name, depth + 4);
        }
        else
        {
            getRWX(statbuf.st_mode);
            printf("%d\t", depth); //深度
            struct passwd *pwd;
            pwd = getpwuid(statbuf.st_uid);
            printf("%s\t", pwd->pw_name); //文件所有者ID
            struct passwd *gpwd;
            gpwd = getpwuid(statbuf.st_gid);
            if(gpwd==NULL)
                return 0;
            printf("%s\t", gpwd->pw_name);    //文件所有者组ID
            printf("%ld\t", statbuf.st_size); //文件大小
            char time[50];
            strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&statbuf.st_ctime));    //打印文件的修改日期
            printf("%s\t", time); //最后修改内容时间
            printf(BLU "%s\n" RESET, entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[])
{
    printdir(argv[1], 1); //深度为1
    return 0;
}
