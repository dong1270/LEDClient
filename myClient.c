#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFFSIZE 1024
#define NAMESIZE 20
#define MY_PORT 12700

int main(int argc, char **argv)
{
    int sock;
    int recv_len = 0;
    char *ret;
    
    struct sockaddr_in serv_addr;
    
    int buf[1024];
    char id[100];

    if(argc != 2) return 0;

    printf("%s\n", argv[1]);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) 
    {
        printf("socket() err\n ");
        return (0);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_port          = htons(MY_PORT);
    serv_addr.sin_addr.s_addr   = inet_addr("127.0.0.1");
    
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) 
    {
        printf("connect() err\n");
        return (0);
    }

    // printf("send: %s\n", argv[1]);
    write(sock, argv[1], 15);

    sleep(1);
    recv_len = read(sock, buf, 200);

    printf("test %d \n", recv_len);

    if(recv_len == 0) printf("err\n");
    else{
        ret = calloc(recv_len, sizeof(char));
        
        for(int i = 0; i < recv_len; i++) ret[i] = buf[i];

        printf("ret : %s\n", ret);
    }

    close(sock);
    return (0);
}