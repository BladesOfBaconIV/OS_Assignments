////////////////////////////////////////////////////////////////////////
// Program: threadArg.c
// A program example, passing anargument to a thread function.
//
// D. Heffernan 28/November/2012
/////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void *my_function (void* a); // Function for the thread 

struct rusage ru;

// MAIN
int main () {
    pthread_t my_thread; // Declare a thread identifier
    int rc1, x = 700000; 
    // Create my_thread 
    if( (rc1 = pthread_create(& my_thread, NULL,  & my_function,  (void*) &x))) {
        printf ("Error in creating thread %d\n", rc1);
    }
    pthread_join( my_thread, NULL); // wait for thread to exit
    getrusage(RUSAGE_SELF, &ru);
    printf ("Usage results for this program are:\n\n");
    printf("User space CPU time used:%2lus %4luus\n",  ru.ru_utime.tv_sec,ru.ru_utime.tv_usec );
    printf("Kernel CPU time used:%2lus %4luus\n",  ru.ru_stime.tv_sec,ru.ru_stime.tv_usec );
    exit(0); // exit the main function
}

// The my_thread is created with my_function()which accepts an argument 
void  *my_function(void* arg) {
    int i = *(int*)arg;
    for(i; i > 0; i--) {
	if(!(i%1000)) {    
            printf("i = %d\n", i ); 
        }
    }
    pthread_exit(NULL);    // thread exits
}
