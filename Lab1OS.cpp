//============================================================================
// Name        : LAB1OS	.cpp
// Author      : Manuel Hernández
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

int CURRENT_PRIORITY = 0;
bool WAITING [6]= {false};
int STORED_PRIORITY[5]= {0};

void handler(int sig){


	short i = 0;

	switch (sig){
	case 2: 	//Case of SIGINT signal
		i = 5;
		break;

	case 11: 	//Case of SIGSEVG signal
		i = 4;
		break;

	case 17:   	//Case of SIGCHLD
		i = 3;
		break;

	case 23:  	//Case of SIGURG signal
		i = 2;
		break;

	case 29:	//Case of SIGIO signal
		i = 1;
		break;


	}

	WAITING[i] = true;
	int x;
	do{
		x = 0;
		for(short j = CURRENT_PRIORITY+1; j<6; j++){
			if (WAITING[j]){
				x = j;
			}
		}


		if (x> 0){
			WAITING[x]= 0;
			STORED_PRIORITY[x] = CURRENT_PRIORITY;
			CURRENT_PRIORITY = x;
			sigrelse(sig);

			cout<< " ";
				for(int j = 0; j< 6; j++){
					if(j+1 == i)cout << "X  ";
					else cout << "-  ";
				}
				cout << endl;

			for(int k = 1; k < 11; k++){

			cout << " ";
			for(int j = 0; j< 6; j++){
			if(j+1 == i)cout << k << "  ";
			else cout << "-  ";
							}
			cout << endl;
			sleep(1);
			}

			sighold(sig);

			CURRENT_PRIORITY = STORED_PRIORITY[x];
			STORED_PRIORITY[x] = 0;

		}
	}while(x>0);
}

int main (void)
{
	cout << (int) getpid() << endl;
	cout << " MP  1  2  3  4  5"<<endl;
	cout << "__________________" << endl;
	sigset(SIGINT, handler);
	sigset(SIGURG, handler);
	sigset(SIGIO, handler);
	sigset(SIGCHLD, handler);
	sigset(SIGSEGV, handler);

	int i = 0;
	while(++i){
		cout << " ";
		cout << i<<"  -  -  -  -  - "<< endl;
		sleep(1);
	}
   return 0;
}

