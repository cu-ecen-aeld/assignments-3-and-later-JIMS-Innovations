#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
	
	int state;

	DEBUG_LOG("Sleeping %d milliseconds\n", thread_func_args->obtain_wait);

	usleep(thread_func_args->obtain_wait*1000);
	
	state = pthread_mutex_lock(thread_func_args->mutex);
	if (state != 0)
	{
		ERROR_LOG("pthread mutex lock failed %d\n", state);
	}
		
	usleep(thread_func_args->release_wait*1000);
	
	DEBUG_LOG("Sleeping %d milliseconds\n", thread_func_args->release_wait);
		
	
	state = pthread_mutex_unlock(thread_func_args->mutex);
	if (state != 0)
	{
		ERROR_LOG("pthread mutex unlock failed %d\n", state);
		thread_func_args->thread_complete_success = false;
	}
	
	thread_func_args->thread_complete_success = true;
	
	DEBUG_LOG("Thread completed with: %d\n", thread_func_args->thread_complete_success);
		
    return thread_func_args;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
	
	struct thread_data * my_thread_data = (struct thread_data *) malloc (sizeof(struct thread_data *));


	int state;

	if (my_thread_data == NULL)
	{
		ERROR_LOG("Memory allocation for thread data struct failed!\n");
	}	
	else 
	{
		my_thread_data->mutex 		 = mutex;
		my_thread_data->release_wait = wait_to_release_ms;		
		my_thread_data->obtain_wait  = wait_to_obtain_ms;	
		my_thread_data->thread_complete_success = false;		
		
		state = pthread_create( thread, NULL, threadfunc, (void *) my_thread_data );
		
		if (state != 0)
		{
			ERROR_LOG("pthread create failed with error %d\n", state);
		}
		else
		{
			return true;
		}
	}
	
		
    return false;
}
	
