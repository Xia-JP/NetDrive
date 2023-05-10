#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN 100 // 最大命令长度

/**
 * @brief 初始化用户界面
 */
void init_user_interface() 
{
    printf("This is client\n");
}

/**
 * @brief 获取用户输入的命令
 * @return 用户输入的命令字符串
 */
char* get_user_input() 
{
    char cmd[MAX_CMD_LEN]; // 命令缓冲区
    printf("> "); // 输出命令提示符
    fgets(cmd, MAX_CMD_LEN, stdin); // 读取用户输入的命令
    if (cmd[strlen(cmd) - 1] == '\n') 
    { // 去除换行符
        cmd[strlen(cmd) - 1] = '\0';
    }
    return strdup(cmd); // 返回动态分配的命令字符串指针
}

#endif /* USER_INTERFACE_H */
