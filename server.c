#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define BUFF_LEN 256

typedef struct udp
{
    char msg[50];
    int num;
    double score;
}udp;

void udpserv_echo(int s,struct sockaddr *client)
{
    int n;                              //接收数据长度
    char buff[BUFF_LEN];                //接收发送缓冲区
    socklen_t   len;                    //地址长度
    int i;
    char buff[256] = {0};
    n = recvfrom(s,buff,BUFF_LEN,0,client,&len);
    struct udp rec_buf;
    memcpy(&rec_buf,buff,sizeof(rec_buf)+1); 
    len = sizeof(*client);
    printf("%s%d%f\n",rec_buf.msg,rec_buf.num,rec_buf.score);
}

void main()
{
//printf("1/n");
    int s;                              //套接字文件描述符
    struct sockaddr_in  local;          //本地的地址信息
    struct sockaddr_in  from;           //发送方的地址信息
    int from_len = sizeof(from);        //地址结构的长度
    int n;                              //接收到的数据长度
    char buf[128];                      //接受数据缓冲区
    s= socket(AF_INET,SOCK_DGRAM,0);    //初始化一个IPV4族的数据报套接字
    if(-1 == s) {
    perror("");
       exit(EXIT_FAILURE);
       }

    local.sin_family = AF_INET;
    local.sin_port = htons(8888);
    local.sin_addr.s_addr = inet_addr("127.0.0.1");
    //printf("2n");
    bind(s,(struct sockaddr *)&local,sizeof(local));

    udpserv_echo(s,(struct sockaddr *)&from);   //回显处理函数

}
