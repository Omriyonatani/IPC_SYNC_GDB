#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

/*
fd[0]=read
fd[1]=write
*/

pid_t pid;  //Child process id
int size=0;
int STOP=1;
int fd[2];

// Father signal handler
void Fsignal_handler(int signum){
  read(fd[0],&size,sizeof(size));
  if(size<=5){
    printf("%d\n",size);
    ++size;
    write(fd[1], &size,sizeof(size));
    usleep(100000);
    kill(pid,SIGUSR1); // send signal
  } else {
    STOP=0;     // the father can stop waiting..
  }
}

// Son signal handler
void Ssignal_handler(int signum){
  read(fd[0],&size,sizeof(size));
  printf("%d\n",size);
  ++size;
  write(fd[1], &size,sizeof(size));
  usleep(100000);
  kill(getppid(),SIGUSR1); // send signal
  if(size==6){
    exit(0);    // kill the son
  }
}


int main(){
  if (pipe(fd) < 0) {
    printf("pipe failed");
    return -1;
  }
  
  pid = fork();
  
  if (pid < 0) {
    printf("fork failed");
    return -1;
  }
  
  if (pid) {    // parent write to pipe
    signal(SIGUSR1,Fsignal_handler);  //in the father process--> when father process get SIGUSR1 signal, the Fsignal function will take care of this.
  } 
  
  else {  // child read from pipe
    signal(SIGUSR1,Ssignal_handler);  //in the son process--> when son process get SIGUSR1 signal, the Ssignal function will take care of this.
    write(fd[1],&size,sizeof(size));
    kill(getppid(),SIGUSR1);
  }
  
  while(STOP);   //Keep The Father ALIVE.

  wait(NULL);  //The father wait till the son is dead.
  
  printf("Child is going to be terminated\n");
  printf("Parent is going to be terminated\n");

  close(fd[0]);
  close(fd[1]);
  return 0;
}
