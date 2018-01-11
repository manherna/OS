#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <pthread.h>

using namespace std;

 int value = 0;
 void * kek (void * param);

 int main(){
  pthread_t tid;
  pthread_attr_t attr;

  pid_t pid;
  pid = fork();
  cout << "forked\n";

  printf("id: %d ", pid);


  if(pid == 0){
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, kek, NULL);
    pthread_join(tid, NULL);
    printf("Child value: %d \n", value);
  }
  else if(pid > 0){
      printf("Parent value: %d \n", value);
    }
}


void * kek (void * param){
  value = 5;
  pthread_exit(0);
}
