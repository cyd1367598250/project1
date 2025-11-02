#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>    
#include <time.h>      
#include <sys/time.h>  
#include <stdint.h>    
#include <unistd.h> 
#include <pthread.h>

static FILE *g_fp = NULL;
static struct timeval g_start;
static pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;
typedef struct{

}LogFile;

int initlog(const char* name);