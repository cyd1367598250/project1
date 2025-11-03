#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>    
#include <time.h>      
#include <sys/time.h>  
#include <stdint.h>    
#include <unistd.h> 
#include <pthread.h>

static FILE *ser_log = NULL;
static FILE *sen_log = NULL;
static struct timeval g_start;
static pthread_mutex_t g_mtx = PTHREAD_MUTEX_INITIALIZER;
typedef struct{
    int origin_data_received;
    int total_data_received;
    int origin_segment_received;
    int total_segment_received;
    int corrupted_segments_discarded;
    int duplicate_segment_received;
    int total_ack_sent;
    int dulicate_acks_sent;
}recLogFile;

static recLogFile rf;
int initlog(const char* name);
int writeserlog(const char* buf,size_t n);
