#include <netinet/in.h>
#include<stdio.h>
#include <sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000

int main(){
    struct sockaddr_in server = {0}, client = {0};
    int pid,newS,sn ,clen = sizeof(client);
    char str[512];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sn = socket(AF_INET,SOCK_STREAM,0);

    int x = bind(sn,(struct sockaddr *)&server,sizeof(server));
    listen(sn, 5);
    printf("Waiting............!\n");
    while(1){
        newS= accept(sn,(struct sockaddr *)&client ,&clen);
        printf("Connected !\n");
        pid = fork();
        if(pid == 0){
            do{
                memset(str,0x0,512);
                recv(newS,str,512,0);
                send(newS,str,strlen(str)+1,0);
                printf("Recieved : %s\n" , str);
            }while (strncmp(str, "end" ,3)!=0);
        }else if(pid > 0 ){
            close(newS);
        }else{
            printf("pid error !!");
        }
    }
    return 0;
}
