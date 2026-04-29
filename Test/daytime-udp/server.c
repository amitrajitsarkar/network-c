#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000

int main() {
  struct sockaddr_in server = {0}, client = {0};
  int newS, sn;
  int clen = sizeof(client);
  char str[512];

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_port = htons(SERVER_PORT);

  sn = socket(AF_INET, SOCK_DGRAM, 0);

  int x = bind(sn, (struct sockaddr *)&server, sizeof(server));

  printf("UDP TIME SERVER is Waiting............!\n");
  while (1) {
    recvfrom(sn,str,512,0,(struct sockaddr *)&client , &clen);
    printf("Connected !\n");


    time_t now= time(NULL);
    char *time_str = ctime(&now);

    sendto(sn,time_str,strlen(time_str)+1,0 ,(struct sockaddr *)&client , clen);
    printf("Time sent: %s\n", time_str);
  }
  return 0;
}
