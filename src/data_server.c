#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <winsock2.h>

#define BLOCK_SIZE 4*1024*1024
#define SERVER_PORT 7070
#define BACKLOG 128

typedef struct {
    char data[BLOCK_SIZE];
    char md5_hash[33];
} FileBlock;

int verify_md5(char* block, char* md5_hash) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5(block, strlen(block), hash);
    char md5_str[33] = "";
    for(int i=0; i<MD5_DIGEST_LENGTH; i++) {
        sprintf(md5_str+2*i, "%02x", hash[i]);
    }
    if (strcmp(md5_str, md5_hash) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void receive_file_block(FileBlock* file_block, int socket_fd) {
    // 接收文件块并验证MD5哈希值
    int bytes_received = 0;
    while (bytes_received < BLOCK_SIZE) {
        int n = recv(socket_fd, file_block->data + bytes_received, BLOCK_SIZE - bytes_received, 0);
        if (n <= 0) {
            break;
        }
        bytes_received += n;
    }
    if (verify_md5(file_block->data, file_block->md5_hash)) {
        // 存储文件块



    } else {
        // 文件块传输失败



    }
}

void send_file_block(FileBlock* file_block) {
    // 发送文件块并验证MD5哈希值
    if (verify_md5(file_block->data, file_block->md5_hash)) {
        // 传输文件块



    } else {
        // 文件块传输失败



    }
}

int main() {
    // 创建套接字
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket");
        exit(1);
    }

    // 绑定端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    // 监听套接字
    if (listen(socket_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    // 接收连接请求并处理客户端请求
    while (1) {
        int client_fd = accept(socket_fd, NULL, NULL);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        // 处理客户端请求
        handle_client_request(client_fd);

        // 关闭与客户端的连接
        close(client_fd);
    }

    // 关闭套接字
    close(socket_fd);

    return 0;
}