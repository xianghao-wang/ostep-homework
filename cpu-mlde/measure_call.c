#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define N 1000000

int main()
{
  int fd = open("measure_call.c", O_RDONLY);
  struct timeval t1, t2;
  int i;
  float total, avg;

  // Measure by gettimeofday
  gettimeofday(&t1, NULL);
  for (i = 0; i < N; i ++)
    read(fd, NULL, 0);  
  gettimeofday(&t2, NULL);

  total = (t2.tv_sec * 1e6 + t2.tv_usec) - (t1.tv_sec * 1e6 + t1.tv_usec);
  avg = total / N;

  printf("Average time of a system call: %f us (measured by gettimeofday)\n", avg);

  return 0;
}