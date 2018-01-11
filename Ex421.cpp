#include <iostream>       // std::cout
#include <pthread.h>



void * min(void* param);
void * max(void* param);
void * average(void * param);

const int TAMARR = 7;
int values [TAMARR] = {90, 81, 78, 95, 79, 72, 85};
int avg, maximum, minimum;

int main(){



avg = maximum = minimum = 0;
pthread_t avt, maxt, mint;

pthread_attr_t attr1, attr2, attr3; //Thread attributes
pthread_attr_init(&attr1);
pthread_attr_init(&attr2);
pthread_attr_init(&attr3);


pthread_create(&avt, NULL, average, NULL);
pthread_create(&mint, NULL, min, NULL);
pthread_create(&maxt, NULL, max, NULL);

pthread_join(avt, NULL);
pthread_join(mint, NULL);
pthread_join(maxt, NULL);

printf("The average value is %d \n", avg);
printf("The minimum value is %d \n", minimum);
printf("The maximum value is %d \n", maximum);
return 0;
}




void * average (void * param){
  int sum = 0;
  for(int i = 0; i < TAMARR; i++)
    sum += values[i];

  sum/=TAMARR;
  avg = sum;
  pthread_exit(0);
}
void * min (void * param){
  minimum = values[0];
  for (int i = 1; i < TAMARR; i++){
    if (values[i]< minimum)minimum = values [i];
  }
  pthread_exit(0);
}
void * max (void * param){
  maximum = values [0];
  for(int i = 0; i < TAMARR; i++)
    if(values[i]> maximum)maximum = values[i];

    pthread_exit(0);
}
