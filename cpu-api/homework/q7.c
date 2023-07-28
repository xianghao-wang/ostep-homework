#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "fork error.\n");
    exit(1);
  }
  else if (rc == 0)
  {
    // child process
    close(STDOUT_FILENO);
    printf("Hello from child.\n");
  }
  else
  {
    // parent process
    printf("Hello from parent.\n");
  }

  return 0;
}