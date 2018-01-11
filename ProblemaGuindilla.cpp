#include <iostream>
#include <pthread.h>
#define TAM 1000

using namespace std;

//Callback functions for threads
void * evenProducer(void * unused);
void * oddProducer(void * unused);
void * consumer(void * unused);

//Mutex for each buffer
pthread_mutex_t parMut;
pthread_mutex_t imparMut;

//Threads
pthread_t par, impar, cons;

//Variables to control each buffers' size and fullness
int parProd, imparProd;

//Odd and Even Buffer
int buffPar [TAM/2] = {};
int buffImpar [TAM/2] = {};

int main(){
  parProd = 0;
  imparProd = 0;

  pthread_mutex_init(&parMut, NULL);
  pthread_mutex_init(&imparMut, NULL);
  cout << "Mutex inited "<< endl;
  pthread_create(&par, NULL, evenProducer, NULL);
  pthread_create(&impar,NULL, oddProducer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);




  pthread_join(par, NULL);
  pthread_join(impar, NULL);
  pthread_join(cons, NULL);
  return 0;
}
void * consumer(void * unsued){
  int parConsum = 0;
  int imparConsum = 0;

  for(int i = 1; i <= TAM+1; i++){
    if(i % 2 != 0){
      if(imparProd > imparConsum){
        pthread_mutex_lock(&imparMut);
        cout << buffImpar[imparConsum] << " ";
        imparConsum++;
        pthread_mutex_unlock(&imparMut);
      }
    }
    if(i % 2 == 0){
      if(parProd > parConsum){
        pthread_mutex_lock(&parMut);
        cout << buffPar[parConsum] << " ";
        parConsum++;
        pthread_mutex_unlock(&parMut);
      }
    }
  }
}

void * evenProducer(void * unused){
  for(int i = 2; i <= TAM; i+= 2){
    pthread_mutex_lock(&parMut);
    buffPar[parProd] = i;
    parProd++;
    pthread_mutex_unlock(&parMut);
  }
}
void * oddProducer(void * unused){
  for(int i = 1; i <= TAM; i+=2){
    pthread_mutex_lock(&imparMut);
    buffImpar[imparProd] = i;
    imparProd++;
    pthread_mutex_unlock(&imparMut);
  }

}
