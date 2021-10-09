#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>

struct Line{
    int valid;
    int tag;
    int count; //用来标记最近使用
};

struct Set{
    struct Line *lines; //每一组包含多个块
};

struct Cache{                     //整个cache
    int s;            //读取的组数的幂
    int e;            //每组包含的块数的幂
    int b;            //块的大小
    struct Set *sets; //指向第一组的指针
};

const char *command_option = "hvs:E:b:t:";
char filename[50];
char buffer[1000];

//全局变量
int hit = 0;
int miss = 0;
int eviction = 0;
int help_mode; //两个命令行选项
int verbose_mode;

struct Cache cache;

//函数声明
void InitCache();                          //初始化Cache
int getCommandline(int argc, char **argv); //通过输入的命令行指令获取Cache初始化信息
void test(unsigned int address);           //通过读取的数据进行访问操作
void printHelpMenu();                      //打印帮助信息

int main(int argc, char **argv){
    int temp;
    char ch;
    unsigned int address;
    FILE *fp=NULL;
    getCommandline(argc, argv);
    InitCache();
    fp = fopen(filename, "r"); //读取文件
    if (fp == NULL){
        fprintf(stderr, "The file path is wrong!\n");
        exit(-1);
    }
    while (fgets(buffer, 1000, fp)){
        sscanf(buffer, " %c %xu,%d", &ch, &address, &temp);
        switch (ch){
        case 'L':
            test(address);
            break;
        case 'M':
            test(address);
        case 'S':
            test(address);
            break;
        }
        for (int i = 0; i < (1 << cache.s); i++) //所有有效计数器自增
            for (int j = 0; j < cache.e; j++)
                if (cache.sets[i].lines[j].valid == 1)
                    cache.sets[i].lines[j].count++;
    }
    for (int i = 0; i < (1 << cache.s); i++)
        free(cache.sets[i].lines);
    free(cache.sets);
    fclose(fp);
    printSummary(hit, miss, eviction);
    return 0;
}

void test(unsigned int address){
    int max_count = -1, max_count_id = -1; //max_count_id用来记录该组count值最大的行的序号
    int t_address, s_address;              // 从address中提取出的t和s
    s_address = (address >> cache.b) & ((-1U) >> (32 - cache.s));
    t_address = address >> (cache.s + cache.b);
    for (int i = 0; i < cache.e; i++)                        //检查是否命中
        if (cache.sets[s_address].lines[i].tag == t_address){ //tag相同代表命中了
            cache.sets[s_address].lines[i].count = 0; //重新把计数器清0
            hit++;
            return;
        }
    for (int i = 0; i < cache.e; i++)                  //检查是否还有空行
        if (cache.sets[s_address].lines[i].valid == 0){ //还有空行
            cache.sets[s_address].lines[i].valid = 1; //占用这个空行
            cache.sets[s_address].lines[i].tag = t_address;
            cache.sets[s_address].lines[i].count = 0;
            miss++;
            return;
        }
    //如果没有空行，这时会发生替换LRU算法
    eviction++;                       //替换计数器加一
    miss++;                           //miss计数器加一
    for (int i = 0; i < cache.e; i++) //遍历整个组内，选取计数器最大的即最近最久未使用的那一行进行替换
        if (cache.sets[s_address].lines[i].count > max_count){
            max_count = cache.sets[s_address].lines[i].count;
            max_count_id = i;
        }
    cache.sets[s_address].lines[max_count_id].tag = t_address; //对应该淘汰的行进行替换
    cache.sets[s_address].lines[max_count_id].count = 0;
    return;
}

void InitCache(){
    int s = (1 << cache.s);
    cache.sets = (struct Set *)malloc(sizeof(struct Set) * s); //初始化组
    for (int i = 0; i < s; i++){ //初始化每一组的每一行
        cache.sets[i].lines = (struct Line *)malloc(sizeof(struct Line) * cache.e);
    }
    for (int i = 0; i < s; i++){ //全部信息初始化
        for (int j = 0; j < cache.e; j++){
            cache.sets[i].lines[j].valid = 0;
            cache.sets[i].lines[j].tag = -1;
            cache.sets[i].lines[j].count = -1;
        }
    }
}

int getCommandline(int argc, char **argv){
    int opt;
    while (-1 != (opt = (getopt(argc, argv, command_option)))){
        switch (opt){
        case 'h':
            help_mode = 1;
            break;
        case 'v':
            verbose_mode = 1;
            break;
        case 's':
            cache.s = atoi(optarg);
            break;
        case 'E':
            cache.e = atoi(optarg);
            break;
        case 'b':
            cache.b = atoi(optarg);
            break;
        case 't':
            strcpy(filename, optarg);
            break;
        }
    }
    if (help_mode == 1){
        printHelpMenu();
        exit(0);
    }
    return 0;
}

void printHelpMenu(){
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("-h         Print this help message.\n");
    printf("-v         Optional verbose flag.\n");
    printf("-s <num>   Number of set index bits.\n");
    printf("-E <num>   Number of lines per set.\n");
    printf("-b <num>   Number of block offset bits.\n");
    printf("-t <file>  Trace file.\n\n\n");
    printf("Examples:\n");
    printf("linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}
