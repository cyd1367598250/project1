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

int initrlog(const char* name)
{
    sen_log=fopen(name,"w+");
    if(!sen_log)
    return -1;
    gettimeofday(&gs_start,NULL);
    memset(&sf,0,sizeof(senLogFile));
    return 0;
}

//buf区，大小，方向send1/recv0，ok/重复/，是哪种字段
int writeserlog(const char* buf,size_t n,int dir,int staus,int type)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    double time_ms = (now.tv_sec - g_start.tv_sec) * 1000.0
               + (now.tv_usec - g_start.tv_usec) / 1000.0;
    char p1[4];
    char p2[4];
    char p3[5];
    int size;
    if (dir==0)
        strcpy(p1, "rcv");
    else if(dir==1)
        strcpy(p1,"snd");
    if(staus==1)
        strcpy(p2,"ok");
    else if(staus==2)
        strcpy(p2,"drp");
    else if(staus==3)
        strcpy(p2,"cor");
    
    if(type==1)
        strcpy(p3,"SYN");
    else if(type==2)
        strcpy(p3,"ACK");
    else if(type==3)
        strcpy(p3,"DATA");

    uint16_t seq=getseq(buf);
    if(n==6)
        size=0;
    else
    size=n-6;

    if(dir==0)
    {
        
    }
    fprintf(sen_log,"%-3s %-3s %7.2f %-4s %6u %5u\n",p1,p2,time_ms,p3,seq,size);
}
//typedef struct{
//    int origin_data_received;
//    int total_data_received;
//    int origin_segment_received;
//    int total_segment_received;
//    int corrupted_segments_discarded;
//    int duplicate_segment_received;
//    int total_ack_sent;
//    int dulicate_acks_sent;
//}recLogFile;