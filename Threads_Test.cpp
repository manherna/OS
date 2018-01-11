
#include <iostream>       // std::cout
#include <pthread.h>         // std::thread
#define LETTERS 255

using namespace std;

void * af (void *);
void * bf (void *);

void * af(void * unused){
	int x = 0;
	while(x< LETTERS){
		std::cout << x;
			x++;
		}

}

void * bf(void * unused){
	int x = 0;
	char c = 'a';
	while (c < 255){
		std::cout << c;
		c++;
	}
}

int main(){
	pthread_t t1, t2; //Thread Identifiers
	pthread_attr_t attr1, attr2; //Thread attributes
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	pthread_create(&t1, NULL, af, NULL );
	pthread_create(&t2, NULL, bf, NULL );
	pthread_join(t1, NULL);
	//pthread_join(t2, NULL);

 return 0;
	}
