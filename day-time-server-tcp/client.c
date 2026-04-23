#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 4001

int main(){
    struct sockaddr_in client ={0}, server ={0};
    int sd;
    char str[512];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET,SOCK_STREAM,0);
    int x = connect(sd,(struct sockaddr *)&server ,sizeof(server));

    printf("Enter : ");
    scanf("%s" ,str);

    send(sd,str,512,0);
    recv(sd,str,512,0);

    printf("Server responded with : %s",str);
    close(sd);
    return 0;
}
