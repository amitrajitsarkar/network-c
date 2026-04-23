// header -> vars -> bzero -> config -> socket -> bind() -> listen -> accept -> recv -> send -> close

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

int main(){
    struct sockaddr_in server ,client;
    int sd,newS,pid,clen = sizeof(client);
    char str[512];

    bzero((char *)&server ,sizeof(server) );

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET ,SOCK_STREAM ,0);

    int ex = bind(sd , (struct sockaddr *)&server ,sizeof(server));
    listen(sd ,5);

    while(1){
        printf("waiting ....\n");
        newS = accept(sd ,(struct sockaddr *)&client ,&clen);
        pid = fork();
        if(pid ==0){
            printf("connected !\n");
            do{
                memset(str ,0x0 ,500);
                recv(newS,str,512,0);
                send(newS,str,strlen(str)+1 ,0);

                printf("Emitted : %s\n",str);
                if(!strcmp(str , "end")){
                    printf("Disconecting.........\n");
                }
                fflush(stdout);
            }while(strcmp(str , "end"));
        }else if(pid > 0){
            close(newS);
        }else{
            printf("Error!\n");
        }
    }
    return 0;
}
