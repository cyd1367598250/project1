#include "log.h"
int* initlog(const char* name)
{
    g_fp=fopen(name,"w+");
    if(!g_fp)
    return -1;
    gettimeofday(&g_start,NULL);
    return 0;

}