/*
  Peterson Algorithm for two different threads
  by Manuel Hernández
*/
#include <stdio.h>
#include <iostream>       // std::cout
#include <pthread.h>      //threading
#include <unistd.h>


using namespace std;

int turn;
bool flag[2] = {false};
const int i = 0;
const int j = 1;

void * petersonA(void * param){
  printf("Thread %d started!\n", i);
  do{
    //Entry Section
    flag[i]= true;
    turn = j;
    while(turn == j && flag [j] == true);
  //Critical section
    for(int x = 0; x < 5; x ++){
      printf("A %d\n", x );
      sleep(1);
    }
    //Exit Section
    flag[i] = false;
    }while(true);
}

void * petersonB(void * param){
  printf("Thread %d started!\n", j);
  do{
    //Entry Section
    flag[j] = true;
    turn = i;
    while(turn == i && flag[i] == true);
  //Critical section

    for(int x = 0; x < 5; x ++){
      printf("B %d\n", x);
      sleep(1);
    }
    //Exit Section
  flag[j] = false;
  }while(true);
}


int main(){

  pthread_t a, b;
  pthread_create(&a, NULL, petersonA, NULL);
  pthread_create(&b, NULL, petersonB, NULL);
  pthread_join(a, NULL);
  pthread_join(b,NULL);



  return 0;
}
