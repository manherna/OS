/*
Page replacement algorithm simulation
implementing FIFO LRU and OPT algorithms
by Manuel Hernández Nájera-Alesón
*/

#include <stdio.h>
#include <iostream>
#include <list>
#define MEMORY 10

using namespace std;

typedef int page;

//Function definition
void LRU (list  <page> *b, page value);
void FIFO (list <page> *b, page value);
void OPT (list <page> *b, page value);



int main(){
  int aux;
  cout << "------- Page replacement simulation -------"<< endl;
  cout<< "Please select an algorithm"<< endl;
  cout << "1. Least Recently Used Algorithm (LRU)"<< endl;
  cout << "2. First In First Out Algorithm (FIFO)"<< endl;
  cout << "3. Optimal Replacement Algorithm (OPT)"<< endl;
  cout << "-------------------------------------------" << endl;
  cin >> aux;

switch(aux){
  case 1:
  cout<<"LRU chosen"<<endl;
  break;
  case 2:
  cout<<"FIFO chosen"<<endl;
  break;
  case 3:
  cout<<"LRU chosen"<<endl;
  break;
}

  list <page> * buffer = new list<page> (MEMORY);
  bool finish = false;
  while (!finish){

    int newPage;
    cout << "Enter a new page value"<< endl;
    cin >> newPage;


    if(newPage == -1)finish = true;


    if(!finish){
      switch (aux){
        case 1:
        LRU(buffer, newPage);
        break;
        case 2:
        FIFO(buffer, newPage);
        break;
        case 3:
        OPT(buffer, newPage);
        break;
      }


      cout << "Memory state: "<< endl;
      for(list<page>::const_iterator it = buffer->cbegin(); it != buffer->cend(); ++it){
        cout << *it << " ";
      }
      cout << endl;



    }
    else cout<< "program finished!"<< endl;
  }
  return 0;
}

void LRU (list <page> * b,  page value){
  bool found = false;
  for(list<page>::const_iterator it = b->cbegin(); !found && it != b->cend(); ++it){
      if(value == *it){
        b->erase(it);
        b->push_back(value);
        found = true;
    }
  }
    if(!found){
      if(b->size() >= MEMORY)
        b->pop_front();

      b->push_back(value);
      }
}
void FIFO (list <page> * b,  page value){
  bool found = false;
for(list<page>::const_iterator it = b->cbegin(); !found && it != b->cend(); ++it){
  if(value == *it)found = true;
}
if(found){
  cout << "found\n";
  return;
}

  if(b->size() < MEMORY){
    b->push_back(value);
  }
  else if (b->size() == MEMORY){
    b->pop_front();
    b->push_back(value);
  }

}
void OPT(list <page> * b,  page value){

}
