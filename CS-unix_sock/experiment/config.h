/*
 * config.h 包含该tcp/ip套接字编程所需要的基本头文件 & 统一端口和基本socket参数。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>


#ifndef CONNECT_SIZE
#define CONNECT_SIZE 256
#endif

#define ADDRESS "127.0.0.1"
#define PORT 4183
#define MAX_LINE 2048
#define LISTENQ 20

