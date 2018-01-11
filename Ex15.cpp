#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
using namespace std;

int main(){

  pid_t pid;
  pid = fork();
  cout << pid << endl;
  cout << "forked FIRST"<< endl;

  if(pid == 0){
    fork();
    cout<< "forked IN" << endl;
    cout << "Hilo creado"<< endl;
  }
  fork();
  cout << "forked OUT"<< endl;



    return 0;
}
