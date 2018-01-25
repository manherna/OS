/*
  Dining Phylosophers problem solution as explained
  in Operating Systems Concepts book.
  By Manuel Hernández
*/
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define P_NUMBER 5
using namespace std;
//Monitor is condition variables and mutexes
//final exam will have monitors task
pthread_t philosophers [P_NUMBER];

pthread_cond_t p_cond [P_NUMBER];
//We will conisder that for a given i philosopher, the fork on their left
// will be the i fork and the one on their right the (i+1)%P_NUMBER
bool forks [P_NUMBER] ;
pthread_mutex_t monitor;
pthread_mutex_t consolewrite;
bool eat = true;


//Function prototypes
void * philosopher (void * number);
void pickup_fork(int p_n);
void release_fork(int p_n);


int main(){
  pthread_mutex_init(&monitor,NULL);
  pthread_mutex_init(&consolewrite,NULL);
  for(int i = 0; i < P_NUMBER; i++){
    pthread_cond_init(&p_cond[i],NULL);
    forks[i] = true;
}

  sleep(2);

  for(int i = 0; i < P_NUMBER; i++){
    int * threadID = (int *) malloc(sizeof(int));
    *threadID = i;
    pthread_create(&philosophers[i], NULL, philosopher,(void *)threadID);
  }

  sleep(rand()%50 + 25);

for(int i = 0; i < P_NUMBER; i++)
    pthread_join(philosophers[i], NULL);


  return 0;
}

void * philosopher (void * number)
{
  int  n = *((int*)number);
  cout << "Philosopher "<< n << " sitting down\n";
  while(eat){

    int aux = rand() % 5;
    sleep (aux);
    pickup_fork(n);
    
    pthread_mutex_lock(&consolewrite);
    cout <<"Philosopher "<< n+1 <<" is eating\n";
    pthread_mutex_unlock(&consolewrite);

    sleep(rand()%3);
    release_fork(n);

    pthread_mutex_lock(&consolewrite);
    cout <<"Philosopher "<< n+1 <<" has eaten.\n";
    pthread_mutex_unlock(&consolewrite);


    sleep(2);
  }
}

void pickup_fork(int p_n){
  pthread_mutex_lock(&monitor);
  while (!forks[p_n]||!forks[(p_n+1)%P_NUMBER])
      pthread_cond_wait(&p_cond[p_n], &monitor);

  forks[p_n] = forks[(p_n+1)%P_NUMBER] = false;
  pthread_mutex_unlock(&monitor);
}
void release_fork(int p_n){
    pthread_mutex_lock(&monitor);

    forks[p_n] = forks[(p_n+1)%P_NUMBER] = true;
    int before = (p_n+P_NUMBER-1)%P_NUMBER;
    int after = (p_n+1)%P_NUMBER;


    pthread_cond_signal(&p_cond[before]);
    pthread_cond_signal(&p_cond[after]);

    pthread_mutex_unlock(&monitor);
}
