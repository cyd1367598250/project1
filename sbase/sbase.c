#include "sbase.h"

void initpa(int argv,char *argc)
{
    sender_port=atoi(argc[1]);
    receiver_port=atoi(argc[2]);
    name=argc[3];
    max_win=atoi(argc[4]);
    rto=atoi(argc[5]);
    flp=atof(argc[6]);
    rlp=atof(argc[7]);
    fcp=atof(argc[8]);
    rcp=atof(argc[9]);
}

static void sys_err(const char *msg) 
{ perror(msg); exit(EXIT_FAILURE); }


