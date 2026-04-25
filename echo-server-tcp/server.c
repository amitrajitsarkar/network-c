#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000

int main(){
    struct sockaddr_in server ={0} , client ={0};
    int pid ,sn,newS,clen = sizeof(client);
    char str[512];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sn = socket(AF_INET ,SOCK_STREAM ,0);

    int placeHolder  = bind(sn , (struct sockaddr *)&server , sizeof(server));
    listen(sn, 5);

    printf("TCP Echo server is listening...........\n");

    while(1){
        printf("Waiting...\n");
        newS = accept(sn , (struct sockaddr *)&client , &clen);
        printf("connected...\n");
        pid = fork();
        if(pid == 0){
            printf("working");
        }else if(pid > 0){
            close(newS);
        }else{
            printf("Error while forking !!");
        }
    }
    return 0;
}
