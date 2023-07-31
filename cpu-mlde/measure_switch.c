#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

int main()
{
  struct timeval t1, t2;
  float total, avg;
  int fd1[2];
  int fd2[2];
  pipe(fd1);
  pipe(fd2);
  
  // Bind processes to a single GPU


  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "FORK ERROR!\n");
    exit(1);
  }
  

  if (rc == 0)
  {
    // A
    gettimeofday(&t1, NULL);
    write(fd1[1], "A", 1);
    gettimeofday(&t2, NULL);
    total = (t2.tv_sec * 1e6 + t2.tv_usec) - (t1.tv_sec * 1e6 + t1.tv_usec);
    avg = total / 2.0;

    printf("Average time of a context switch: %f us (measured by gettimeofday)\n", avg);
  }
  else
  {
    // B
    write(fd2[1], "B", 1);
  }

  return 0;
}