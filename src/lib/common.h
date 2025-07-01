#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/signal.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/time.h>
#ifndef TEST_ERROR

#define TEST_ERROR                                                             \
  if (errno)                                                                   \
  {                                                                            \
    fprintf(stderr, "%s:%d: PID=%5d: Error %d (%s)\n", __FILE__, __LINE__,     \
	    getpid(), errno, strerror(errno));                                 \
  }
/* __LINE__ is a preprocessor macro that expands to current line number in the
   source file, as an integer.
     __LINE__ is useful when generating log statements
 */
 #endif 

typedef struct 
{
     int client_fd; 
     int port; 
     char buffer[1024];
     pthread_mutex_t* log_file_mutex; 
     char log_path[512]; 
}thread_args_t;
