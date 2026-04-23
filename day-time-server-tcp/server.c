#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9400

int main(){
    struct sockaddr_in server ={0},client;
    int sd,newS;
    char str[512];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET ,SOCK_STREAM,0);
    int x= bind(sd ,(struct sockaddr *)&server , sizeof(server));

    listen(sd ,5);
    printf("TCP DAYTIME SERVER IS ONLINE...!\n");

    while(1){
        time_t now = time(NULL);
        char *time_str = ctime(&now);

    }
    close(sd);
    return 0;
}
