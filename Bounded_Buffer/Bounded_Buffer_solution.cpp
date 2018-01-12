/*
  Producer-Consumer problem solution
  using a bounded buffer, 2 semaphores
  and a mutex.
  by Manuel Hernández Nájera-Alesón.
*/

#include "buffer.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#define MAX_RAND 3000000

//Producer and consumer functions declaration
void * producer(void * param);
void * consumer(void * param);

sem_t empty;
sem_t full;
pthread_mutex_t bufMutex;
Buffer b;
int slp, prods, cons;

int main(int argc, char *argv[]){
  //Get command line args
  /*if(argc > 4|| argc < 4){
    printf("Number of arguments should be 3.\n Closing Program");
    return 0;
  }*/
  slp= 15;//atoi(argv[1]);
  prods = 3;//atoi(argv[2]);
  cons = 3;//atoi (argv[3]);


  b = Buffer();
  b.init();


  //Semaphore and mutex init
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&bufMutex, NULL);

  //Create producers
  printf("producers init\n");
  for(int i = 0; i <prods; i++){
    pthread_t aux;
    pthread_create(&aux,NULL,producer, NULL);
  }

  //Create consumers
  printf("consumers init\n");
  for(int i = 0; i < cons; i++){
    pthread_t aux;
    pthread_create(&aux, NULL, consumer, NULL);
  }

  //Sleep
  sleep(slp);

  //Exit
  return 0;
}

void *producer(void * param){
  buffer_item item;
  while(true){
    int aux = rand() % 5 + 1;
    sleep(aux);
    item = rand() % MAX_RAND;

    sem_wait(&empty);
    pthread_mutex_lock(&bufMutex);

    if (b.insert_item(item)) printf("Could not produce!\n");
    else printf("producer produced %d \n",item);

    pthread_mutex_unlock(&bufMutex);
    sem_post(&full);

  }
}
void * consumer (void * param){
  buffer_item item;
  while (true) {
  int aux = rand() % 5 + 1;

  sleep(aux);
  sem_wait(&full);
  pthread_mutex_lock(&bufMutex);

  if(b.remove_item(&item)) printf("Could not consume!\n");
  else printf("consumer consumed %d\n", item);

  pthread_mutex_unlock(&bufMutex);
  sem_post(&empty);
  }
}
