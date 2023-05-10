  //用户接口模块文件
#include <stdio.h>;
#include <stdlib.h>

typedef enum{           //用户命令类型枚举
    CMD_create_dir,     //创建目录命令
    CMD_delete_dir,     //删除目录命令
    CMD_rename_dir,     //重命名目录命令
    CMD_dir_info,       //获取目录信息命令
    CMD_create_file,    //创建文件命令
    CMD_delete_file,    //删除文件命令
    CMD_rename_file,    //重命名文件命令
    CMD_file_info,      //获取文件信息命令
    CMD_download_file,  //下载文件命令
    CMD_backup_file,    //文件备份命令
    CMD_client_exit     //退出客户端命令
}cmd_type;

typedef enum{
    Npermission,//没有权限
    RD_ONLY,    //只能搜索查看
    WRT_ONLY,   //只能创建修改
    APD_ONLY,   //只能追加
    RD_AND_WRT, //可查可改
    ADMIN       //管理员（最高权限）
}permission_type;

int usr_login(void);    //用户登陆文件系统（可能根据用户账号，密码登陆，需要查询服务器）失败返回-1，在函数内打印错误信息

int get_usr_id(int usr_info);   //获得用户的id信息

permission_type check_usr_prm(int usr_id);  //获得用户权限信息

char* permission_chg(int usr_id);   //进行用户权限信息变更

cmd_type get_usr_cmd(void);     //通过用户输入获取用户操作指令
//可以用getchar等方法获得用户输入确定用户项进行的操作
//输入非法命令直接打印错误信息即可
int client_operation(int cmd_type);//根据命令进行操作
//根据命令将信息构造消息块准备发送
//或者等待接收服务器传过来的消息快
//需要引用msg/file模块的接口
//成功返回1失败返回-1
char* exit_and_check(void);//退出之前检查当前有没有在执行某项活动，若无进行退出并保存此次登陆相关信息
//发现问题返回问题信息（如正在上传、下载某文件）
#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 内部指令类型定义
typedef enum {
    CMD_INVALID, // 无效指令
    CMD_HELP,    // 帮助指令
    CMD_LOGIN,   // 登陆指令
    CMD_LOGOUT,  // 注销指令
    CMD_LIST,    // 列出文件列表指令
    CMD_UPLOAD,  // 上传文件指令
    CMD_DOWNLOAD // 下载文件指令
} command_t;

// 解析用户输入的命令，并返回对应的内部指令类型
command_t parse_command(const char* cmd);

#endif /* COMMAND_PARSER_H */
