#include "log.h"
int  initlog(const char* name)
{
    ser_log=fopen(name,"w+");
    if(!ser_log)
    return -1;
    gettimeofday(&g_start,NULL);
    memset(&rf,0,sizeof(recLogFile));
    return 0;
}

int writeserlog(const char* buf,size_t n)
{
    fprintf();
}