#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <mutex>

using namespace std;

// Pedro Schmidt
// CSci 451
// to compile  g++ hw9-pedroschmidt.cpp -std=c++11 -lpthread
mutex m;
int limit; //
int fin;  // 
ofstream outFile;
pthread_mutex_t current = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t completed = PTHREAD_MUTEX_INITIALIZER;


struct dataStruct
 {
	string fileName;
	int identifier;
};


void *readFile(void* passedStruct)
 {
	ifstream selectedFile;
	struct dataStruct *threadData;
	threadData = (struct dataStruct *) passedStruct;
	
	int id = threadData->identifier;
	string fileName = threadData -> fileName;
	selectedFile.open(fileName);
	string lineString;
	
	
	while(1)
    {
		selectedFile >> skipws >> lineString;
		if(selectedFile.eof()) 
      {
			pthread_mutex_lock(&completed);
			fin++;
			pthread_mutex_unlock(&completed);
			break;
		}
		//cout << lineString << endl;
		if(lineString == "C")  //r indicates the start of a critical section
      {
			pthread_mutex_lock(&current); //where we aquire the balance
         
		} 
      else if(lineString == "B")  //w // end of the critical section where we write the account balance to a global storage 
      {
	cout << limit << id << "" << endl; //AFTER EVERY NEW THREAD THIS WILL BE ITERATED 
	pthread_mutex_unlock(&current);
	sleep(.3);
      }
     else 
      {
	limit += stoi(lineString);
	}
	}
    
}

int main() 
{
	
	limit = 0;
	fin = 0;
	
	outFile.open("hw9.data"); //mom thread 
   pthread_t p1;
	pthread_t p2;
	pthread_t p3;
   pthread_t p4;
	pthread_t p5;
	pthread_t p6;
   pthread_t p7;
	pthread_t p8;
	pthread_t p9;
   pthread_t p10;
		
	dataStruct id1 = {"hw9.nomutex", 1}; //FIRST THREAD 
	dataStruct id2 = {"hw9.mutex", 2}; // 2nd THREAD 
		
	pthread_create(&p1, NULL, readFile, (void*)&id1);
	pthread_detach(p1);
	pthread_create(&p2, NULL, readFile, (void*)&id2);
	pthread_detach(p2);
	pthread_create(&p3, NULL, readFile, (void*)&id1);
	pthread_detach(p3);
   pthread_create(&p4, NULL, readFile, (void*)&id2);
	pthread_detach(p4);
   pthread_create(&p5, NULL, readFile, (void*)&id1);
	pthread_detach(p5);
   pthread_create(&p6, NULL, readFile, (void*)&id2);
	pthread_detach(p6);
	pthread_create(&p7, NULL, readFile, (void*)&id1);
	pthread_detach(p7);
	pthread_create(&p8, NULL, readFile, (void*)&id2);
	pthread_detach(p8);
   pthread_create(&p9, NULL, readFile, (void*)&id1);
	pthread_detach(p9);
   pthread_create(&p10, NULL, readFile, (void*)&id2);
	pthread_detach(p10);
    
	while(fin != 10)   
	{
		
	}

	cout << ""<< limit << endl;
	cout << "FIN! " << endl;
		
	return 0;
}

