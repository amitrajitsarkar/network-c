// header -> vars -> bzero -> config -> socket -> connect  -> send -> recv
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 4001

int main() {
  struct sockaddr_in client, server;
  int sd, clen = sizeof(client);
  char str[512];

  bzero((char *)&server, sizeof(server));
  bzero((char *)&client, sizeof(client));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_port = htons(SERVER_PORT);

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(CLIENT_IP);
  client.sin_port = htons(CLIENT_PORT);

  sd = socket(AF_INET, SOCK_STREAM, 0);
  int x = connect(sd, (struct sockaddr *)&server, sizeof(server));

  do {
      printf("Enter : ");
      scanf("%s",str);
      send(sd, str, strlen(str) + 1, 0);
      recv(sd, str, 512, 0);

    printf("Echoed : %s\n", str);
    fflush(stdout);
  } while (strcmp(str, "end"));
close(sd);
return 0;
}


