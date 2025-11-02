#include "log.h"
int* initlog(const char* name)
{
    ser_log=fopen(name,"w+");
    if(!g_fp)
    return -1;
    gettimeofday(&g_start,NULL);
    return 0;
}