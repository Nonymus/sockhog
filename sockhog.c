#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define NUM_SOCK 2000

int main(int argc, char *argv[])
{
  int sock_fds[NUM_SOCK];
  int i;
  int err;
  struct sockaddr_in serv_addr;

  for (i=0; i<NUM_SOCK; i++)
  {
    sock_fds[i] = socket(AF_INET6, SOCK_STREAM|SOCK_NONBLOCK, 0);
    if (sock_fds[i] == -1)
    {
      printf("Could not create socket %i\n", i);
    }
  }

  puts("Press any key to connect sockets");
  getchar();

  // Boilerplate. Connect to localhost port 5000
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  for (i=0; i<NUM_SOCK; i++)
  {
    if (sock_fds[i] != -1)
    {
      if (connect(sock_fds[i], (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
      {
        printf("Failed connecting socket %i\n", i);
      }
    }
  }

  puts("Press any key to exit");
  getchar();
  return 0;
}
