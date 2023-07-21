#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int main(int argc, char **argv)
{
  /*
    Open a file
    - O_CREATE: create file if not exits
    - O_WRONLY: write only
    - O_TRUNC: existing file's size is truncated to 0
    - S_IRWXU: file is created with read, write, and execute permission
  */
  char msg[N] = "CREATED by parent\n"; 
  int fd = open("a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  write(fd, msg, strlen(msg));

  int rc = fork();
  if (rc < 0)
  {
    fprintf(stderr, "fork error.\n");
    exit(1);
  }
  else if (rc == 0)
  {
    // child process
    strcpy(msg, "UPDATED by child\n");
    write(fd, msg, strlen(msg));
  }
  else
  {
    // parent process
    strcpy(msg, "UPDATED by parent\n");
    write(fd, msg, strlen(msg));
  }

  close(fd);

  return 0;
}