#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  char cmd_cpu[256];
  char cmd_mem[256];
  int pid = fork();

  time_t last, now;
  last = time(NULL);

  snprintf (cmd_cpu, 256, "ps -p %d -o %%cpu | grep -v %%CPU", pid);
  snprintf (cmd_mem, 256, "pmap %d | grep -i total | awk '{print$2}'", pid);


  if (pid > 0)
  {
    int i = 0;
    while (i < 10)
    {
      system(cmd_cpu);
      system(cmd_mem);
      i ++;
      sleep (1);
    }
    char kill[256];
    snprintf (kill, 256, "kill %d", pid);
    system(kill);
  }
  else
  {
    if (strcmp(argv[1], "cpu") == 0)
    {
      for(;;){}
    }
    if (strcmp(argv[1], "cpu-mem") == 0)
    {
      int i;
      for (;;)
      {
        now = time(NULL);
        if (difftime(now, last) >= 0.5)
        {
          for (i = 0; i < 10000; i++)
          {
            malloc(3000*sizeof(int));
          }
          last = time(NULL);
        }
      }
    }
  }

}
