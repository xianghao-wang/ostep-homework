#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void sender(int fd[2])
{ 
  close(fd[0]);
  dup2(fd[1], STDOUT_FILENO);

  printf("Hello\n");

  exit(0);
}

void receiver(int fd[2])
{
  close(fd[1]);
  dup2(fd[0], STDIN_FILENO);

  char s[10];
  scanf("%s", s);
  printf("%s\n", s);

  exit(0);
}

int main(int argc, char **argv)
{
  int fd[2];
  pipe(fd);

  int rc1, rc2;
  rc1 = fork();
  if (rc1 == 0)
    sender(fd);

  rc2 = fork();
  if (rc2 == 0)
    receiver(fd);

  return 0;
}