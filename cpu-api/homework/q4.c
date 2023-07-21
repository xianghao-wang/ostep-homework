#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
    char *myargs[2];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = NULL; // Mark the end of array
    execvp(myargs[0], myargs);
  }
  else
  {
    // parent process
    // Do nothing
  }

  return 0;
}