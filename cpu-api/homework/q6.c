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
    printf("Hello, I am %d.\n", getpid());
    int rp = wait(NULL);
    printf("Who are you, %d?\n", rp);
  }
  else
  {
    int rp = waitpid(rc, NULL, 0);
    printf("Bye, %d.\n", rp);
  }

  return 0;
}