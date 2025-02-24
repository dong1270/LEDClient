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
    struct sockaddr_in serv_addr;
    int buf[1024];
    int recv_len = 0;
    char *ret;

    if(argc == 0) return (1);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)  return (1);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_port          = htons(MY_PORT);
    serv_addr.sin_addr.s_addr   = inet_addr("192.168.0.69");
    
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) 
    {
        return (1);
    }

    write(sock, argv[1], 15);

    recv_len = read(sock, buf, 200);

    if(recv_len == 0) return (1);
    else{
        ret = calloc(recv_len, sizeof(char));

        if(ret == NULL) 
        {
            close(sock);
            return (0);
        }

        for(int i = 0; i < recv_len; i++) ret[i] = buf[i];
        if(strcmp("e", ret) == 0) 
        {
            free(ret);
            close(sock);
            return (1);
        }
        free(ret);
    }

    close(sock);
    return (0);
}