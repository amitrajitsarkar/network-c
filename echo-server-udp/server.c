#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000

int main() {
  struct sockaddr_in server = {0}, client = {0};
  int pid, sn, newS, clen = sizeof(client);
  char str[512];

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_port = htons(SERVER_PORT);

  sn = socket(AF_INET, SOCK_DGRAM, 0);

  int placeHolder = bind(sn, (struct sockaddr *)&server, sizeof(server));

  printf("UDP Echo server is listening...........\n");

      do {
        recvfrom(sn,str,512,0,(struct sockaddr *)&client ,&clen);
        printf("connected !\n");

        sendto(sn, str, strlen(str) + 1, 0,(struct sockaddr *)&client ,clen);
        printf("Recieved : %s\n" , str);
      }while(strncmp(str , "end",3)!=0);
  return 0;
}
