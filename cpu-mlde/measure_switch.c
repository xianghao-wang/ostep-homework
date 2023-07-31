#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

#define N 100000

int main()
{
  struct timeval t1, t2;
  float total, avg;
  int fd1[2];
  int fd2[2];
  int i;
  pipe(fd1);
  pipe(fd2);
  
  // Bind processes to a single GPU
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(2, &cpuset);

  int rc = fork();

  if (rc < 0)
  {
    fprintf(stderr, "FORK ERROR!\n");
    exit(1);
  }
  

  if (rc == 0)
  {
    // A
    sched_setaffinity(0, sizeof(cpuset), &cpuset);
    for (i = 0; i < N; i ++)
    {
      write(fd1[1], NULL, 0);
      read(fd2[0], NULL, 0);
    }
  }
  else
  {
    // B
    sched_setaffinity(0, sizeof(cpuset), &cpuset);
    gettimeofday(&t1, NULL);
    for (i = 0; i < N; i ++)
    {
      read(fd1[0], NULL, 0);
      write(fd2[1], NULL, 0);
    }
    gettimeofday(&t2, NULL);
    total = (t2.tv_sec * 1e6 + t2.tv_usec) - (t1.tv_sec * 1e6 + t1.tv_usec);
    avg = total / (N * 4.0);

    printf("Average time of a context switch: %f us (measured by gettimeofday)\n", avg);
  }

  return 0;
}