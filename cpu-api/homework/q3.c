#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

/*
  Use file as a indicator for communication
*/
int main(int argc, char **argv)
{
  char buf[5];
  int fd = open("swap.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "fork error.\n");
    exit(1);
  }
  else if (rc == 0)
  {
    // child process
    printf("hello\n");
    write(fd, "done", 4);
    close(fd);
  }
  else
  {
    // parent process
    buf[4] = '\0';
    while (strcmp(buf, "done") != 0)
    {
      close(fd);
      fd = open("swap.txt", O_RDWR, S_IRWXU);
      read(fd, buf, 4);
    }
    close(fd);

    printf("goodbye\n");
  }

  return 0;
}