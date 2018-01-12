// Class that implements the bounded buffer for the
// Producer-Consumer problem

#define BUFFER_SIZE 5

typedef int buffer_item;

class Buffer {
  buffer_item b[BUFFER_SIZE] = {-1, -1, -1, -1, -1};;
  int prod, con;

public:

  Buffer(){
  }
  ~Buffer(){  };


  void init(){
    prod = con = 0;
  }

  bool insert_item(buffer_item nItem){
    if(b[prod] == -1){
      b[prod] = nItem;
      prod = (prod+1)%BUFFER_SIZE;
      return false;
    }
    else return true;
  }


  bool remove_item(buffer_item *oItem){
    if(b[con] != -1){
      *oItem = b[con];
      b[con] = -1;
      con = (con+1)%BUFFER_SIZE;
      return false;
    }
    else return true;
  }
};
