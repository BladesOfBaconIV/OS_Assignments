/***********************************************
Program: simpleConVar.c
ID: 16160703
Name: Lorcan Williamson
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Function declarations
void *functionA();
void *functionB();
void *functionC();
void sleep(int a);

// Initialise a mutex called mutex1
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// Initialise a condition variable called con_var_thread_1
pthread_cond_t con_var_thread_1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_var_thread_3 = PTHREAD_COND_INITIALIZER;

// Some global definitions and a variable
#define TOP_LIMIT 17
int counter = 1;

int main() {
    pthread_t thread1, thread2, thread3;  // declare 3 threads
    // Create three threads -no error checking for simplicity
    pthread_create(&thread1, NULL, &functionA,NULL);
    pthread_create(&thread2, NULL, &functionB,NULL);
    pthread_create(&thread3, NULL, &functionC,NULL);
    // Remember to use the thread joins
    pthread_join( thread1,NULL);
    pthread_join( thread2,NULL);
    pthread_join( thread3,NULL);
    // Destroy the mutex and the condition variable
    pthread_cond_destroy( &con_var_thread_1);
    pthread_cond_destroy( &con_var_thread_3 );
    pthread_mutex_destroy( &mutex1);
    printf("\nNow finished\n");// main exits
    exit(0);
}

// Thread 1 
void *functionA() {
    while(counter <= 15)  {
        pthread_mutex_lock( &mutex1 ); //Lock mutex1
        // Check the value of counter and if it is not divisible by 3
        // then wait on con_var_thread_1 for signal to relase mutex1 
        // i.e. blocks until signalled, mutex1 is unlocked if signalled.
	if( counter < 6 ) {
            pthread_cond_signal( &con_var_thread_3 );
	}
	else {
            if( !(counter % 3)) {   
                printf("I am Thread 1 the current value is: %d\n", counter);
            }
            else {
                pthread_cond_wait( &con_var_thread_1, &mutex1 );
                printf("I am Thread 1 the current value is: %d   *\n", counter);
            }
	    counter++;
	}
        pthread_mutex_unlock( & mutex1 );
        sleep(1); // allow some time threads can alternate on the mutex1
    }
    pthread_exit(NULL);
}

// Thread 2 
void *functionB() {
    while(counter < TOP_LIMIT) {
        pthread_mutex_lock( &mutex1 );
        // If counter is divisible by 3, then'if' condition is met so send signal
	if( counter < 6 ) {
            pthread_cond_signal( &con_var_thread_3 );
	}
	else {
            if(!(counter % 3))     
                pthread_cond_signal( &con_var_thread_1 );
            else {
                printf("I am Thread 2 the current value is: %d\n", counter);
                counter++; 
            }
	}
        pthread_mutex_unlock( &mutex1 );
        sleep(1); // allow some time threads can alternate on the mutex1
    }
    pthread_exit(NULL);
}

// Thread 3 
void *functionC() {
    while(counter < TOP_LIMIT) {
        pthread_mutex_lock( &mutex1 );
        // If counter is divisible by 3, the 'if' condition is met so send signal
        if( counter < 6) {
            pthread_cond_wait( &con_var_thread_3, &mutex1 );
	    printf("I am Thread 3 the current value is: %d\n", counter);
	    counter++;
	}
	else {
	    if(!(counter % 3))
                pthread_cond_signal( &con_var_thread_1 );
       	    else {
                printf("I am Thread 3 the current value is: %d\n", counter);
                counter++;
	    }
	}
        pthread_mutex_unlock( &mutex1 );
        sleep(1);  // allow some time threads can alternate on the mutex1
    }
    pthread_exit(NULL) ;
}
