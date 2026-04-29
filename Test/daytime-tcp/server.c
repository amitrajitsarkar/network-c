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
  int newS, sn, clen = sizeof(client);
  char str[512];

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_port = htons(SERVER_PORT);

  sn = socket(AF_INET, SOCK_STREAM, 0);

  int x = bind(sn, (struct sockaddr *)&server, sizeof(server));
  listen(sn, 5);
  printf("Waiting............!\n");
  while (1) {
    newS = accept(sn, (struct sockaddr *)&client, &clen);
    printf("Connected !\n");


      time_t now = time(NULL);
      char *time_str = ctime(&now);

      recv(newS, str, 0, 0);

      send(newS, time_str, strlen(time_str) + 1, 0);
  }
  return 0;
}
