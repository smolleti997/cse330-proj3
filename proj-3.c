//Omer Abdelsalam && Sai Madhuri Molleti
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define _GNU_SOURCE
#include "sem.h"

void method1_1();
void method1_2();
void method2_1();
void method2_2();
int globalint = 0;
int in = 0;
int out = 0;
int buffer[5];
struct Semaphore *s, *full, *empty;

int main(void) {
	RunQ = (Queue*)malloc(sizeof(Queue));
	s = (struct Semaphore*)malloc(sizeof(struct Semaphore));
	full = (struct Semaphore*)malloc(sizeof(struct Semaphore));
	empty = (struct Semaphore*)malloc(sizeof(struct Semaphore));

	InitQueue(RunQ);
	InitSem(s, 1);
	InitSem(full, 5);
	InitSem(empty, 0);
	
	start_thread(method2_1);
	start_thread(method2_2);
	
	run(); // Output for threads should be : A, B, A, B...
}

//Method1
void method1_1() {
	while (1) {
		P(s);
		printf("A\n");
		V(s);
	}
}

void method1_2() {
	while (1) {
		P(s);
		printf("B\n");
		V(s);
	}
}

//Method2
void method2_1() { // producer
	while(1){
		int item = -1;
		P(full);
		printf("producer\n");
		buffer[in] = item;
		in = (in+1) % 5; // n = 5
		V(empty);
	}
}

void method2_2() { // consumer
	int item;
	while(1){
		P(empty);
		printf("consumer\n");
		item = buffer[out];
		out = (out + 1) % 5; // n = 5
		V(full);
		printf("%d\n", item);
	}
}
