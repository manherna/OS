/*
  Peterson Algorithm for two different processes
  by Manuel Hernández
*/
#include <stdio.h>
#include <iostream>       // std::cout
#include <unistd.h>

using namespace std;
int turn;
bool flag[2] = {false};
const int i = 0;
const int j = 1;
pid_t a;

//shmget() shmat() look for it

int main(){
  cout << "aa";
  a = fork();
  if(a == 0){
    cout << "Process A Started";
    do {
      flag [i] == true;
      turn = j;
      while (turn == j && flag[j]);

      for(int i = 0; i < 3; i++){
        cout << "Turn " << i << "of proccess A";
        sleep(1);
      }
      flag[i] = false;
    } while(true);
  }
  else{
        cout << "Process A Started";
    do {
      flag [j] = true;
      turn = i;
      while (turn == i && flag[i]);

      for(int i = 0; i < 3; i++){
        cout << "Turn " << i << "of proccess B";
        sleep(1);
      }
      flag[j] = false;
      /* code */
    } while(true);
  }
}
