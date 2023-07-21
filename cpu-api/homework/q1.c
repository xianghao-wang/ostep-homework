#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int x = 100;

  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "fork error.\n");
    exit(1);
  }
  else if (rc == 0)
  {
    // child process
    printf("I am child, holding value of %d\n", x);
    x = 50;
    printf("I am child, holding value of %d\n", x);
  }
  else
  {
    // parent process
    printf("I am parent, holding value of %d\n", x);
    x = 25;
    printf("I am parent, holding value of %d\n", x);
  }

  return 0;
}