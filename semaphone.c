#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#define KEY 50


int main(int argc, char * argv[]){

  int sem;
  if (argc < 2){
    printf("Incorrect number of args\n");
  }else if(argc == 3){
    if(!strcmp(argv[1], "-c")){
      if(sem = semget(KEY, 1, IPC_EXCL | IPC_CREAT | 0664) != -1){
          sem = semget(KEY, 0, 0);
          int x;
          sscanf(argv[2], "%d", &x);
          semctl(sem, 0, SETVAL, x);
          printf("semaphore created: %d\n", sem);
      }else{
      printf("semaphore already exists\n");
      }
    }
  }else if(!strcmp(argv[1], "-v") && argc == 2){
    sem = semget(KEY, 0, 0);
    printf("value of semaphore: %d\n", semctl(sem, 0, GETVAL));
  }else if(!strcmp(argv[1], "-r") && argc == 2){
    sem = semget(KEY, 0, 0);
    printf("semaphore removed: %d\n", semctl(sem, 0, IPC_RMID));
  }else{
    printf("Invalid/Incorrect Arguments\n");
  }

  return 0;
}


