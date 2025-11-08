#include "../base/base.h"

int main(int argv,char* argc[])
{
    recport=atoi(argc[1]);
    senport=atoi(argc[2]);
    rec_file_name=argc[3];
    max_win=atoi(argc[4]);

    int ret=createwin();

    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(struct sockaddr_in));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(recport);
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    socklen_t ser_addr_len=sizeof(ser_addr);
    struct sockaddr_in cli_addr;
    bzero(&cli_addr,sizeof(struct sockaddr_in));
    socklen_t cli_len=sizeof(cli_addr);

    int fd=initserver(&ser_addr);
    ret=initlog(rec_file_name );
    if (ret!=1)
    sys_err("receiver_log created failed!");
    if(isconnected(fd,&cli_addr,&cli_len))
    {
        work(fd);
    }
    
    return 0;
}