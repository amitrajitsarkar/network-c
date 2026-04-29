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
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 4002

int main() {
  struct sockaddr_in server = {0}, client = {0};
  int sn, clen = sizeof(client);
  char str[512];

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_port = htons(SERVER_PORT);

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(CLIENT_IP);
  client.sin_port = htons(CLIENT_PORT);

  sn = socket(AF_INET, SOCK_STREAM, 0);

  connect(sn, (struct sockaddr *)&server, sizeof(server));

  do {
    memset(str, 0x0, 512);
    printf("Enter : ");
    fgets(str , sizeof(str) ,stdin);
    send(sn, str, sizeof(str), 0);
    recv(sn, str, strlen(str)+1, 0);
    printf("Echoed : %s\n", str);

  } while (strncmp(str, "END" ,3)!=0);

  return 0;
}
