#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include<stdlib.h>

int main()
{
  int pipe_fds[2];
  pid_t pid;

  pipe(pipe_fds);

  char *cmd[] = {"raspivid" , "-t 0 -w 1280 -h 720 -fps 60 -hf -b 2000000 -o -" , 0};
  char *cmd2[] = {"./Test" , 0};

  if((pid = fork()) == 1)
  {
    dup2(pipe_fds[1] , 1);
    close(pipe_fds[0]);
    execvp(cmd[0] , cmd);

    perror(cmd[0]);
    exit(0);

  } else if(pid == -1)
  {
    perror("fork");
    exit(1);
  }

  dup2(pipe_fds[0] , 0);
  close(pipe_fds[1]);
  execvp(cmd2[0] , cmd2);

  perror(cmd2[0]);
  exit(0);

  
}
