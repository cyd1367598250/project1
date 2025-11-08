#include "base.h"

void sys_err(const char str)
{
    perror(str);
    exit(1);
}


int initserver(struct sockaddr_in *sev_addr)
{
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    if (fd==-1)
        sys_err("server socketfd created failed");
    
    socklen_t sev_addr_len=sizeof(*sev_addr);
    
    int ret=bind(fd,(struct sockaddr *)sev_addr,sev_addr_len);
    if(ret==-1)
        sys_err("server bind failed");
    
    return fd;
}

bool isreclost()
{

    return true;
}

int sendwin(const char *buf,size_t n)
{

}

bool sendback(int fd,const char* buf,struct sockaddr_in * cli_addr,ssize_t n,int type,bool isdata)
{   
    uint8_t pro[6];
    size_t pron=formsendback(n,type,pro);
    if (isdata)
    {
        datasendback();
    }
    else
    {
        socklen_t cli_addr_len=sizeof(*cli_addr);
        for(;;){
        ssize_t sendn=sendto(fd,pro,6,0,(struct sockaddr*)cli_addr,cli_addr_len);
        if(sendn>=0)
        {
            writeserlog(buf,n,1,1,1);
            return true;
        }
        if (errno == EINTR) continue;                    // 被信号打断，重试
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            // 非阻塞套接字：这里应配合 poll/select 等待可写后再重试
            // 简化：短暂休眠或直接返回错误
            // usleep(1000);
            perror("sendto EAGAIN");
            return false;
        }
        sys_err("ser sendto err");
        }
    }
}


bool isconnected(int sockfd,struct sockaddr_in * cli_addr,socklen_t *cli_len)
{
    while(true){
        char buf[BUFSIZ];
        *cli_len = sizeof(*cli_addr);
        ssize_t n=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)cli_addr,cli_len);
        if(n<0)
            continue;
        int status=checkbuf(buf,n);
        if (status==3)
        {
            
            writeserlog(buf,n,0,1,1);
            setexpected(buf,n);
            if(sendback(sockfd,buf,cli_addr,n,1,false))
            return true;
        }
        else
        {
            writeserlog(buf,n,0,3,1);
            printf("waiting ...");
            continue;
        }
        //
    }
}


void work(int fd)
{
     while(true)
    {
        char buf[2*BUFSIZ];
        struct sockaddr_in cli_addr;
        bzero(&cli_addr,sizeof(struct sockaddr_in));
        socklen_t cli_len=sizeof(cli_addr);
        for(;;)
        {
            int n=recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&cli_addr,&cli_len);
            if(n<-1)
                recverr();
            if(!isexpect(buf,n))
            {
                int type=checkbuf(buf,n);
                if(type==-2)
                    writeserlog(buf,n,0,2,3);
                writeserlog(buf,n,0,3,type);
                sendagain(fd,&cli_addr,&cli_len);
                continue;
            }

            int which=checkbuf(buf,n);
            if (which==2)
            {
                dealwith(buf,n);
                over();
            }
            else if(which==3)
            {
                writeserlog(buf,n,1,2,1);
                sendagain(fd,&cli_addr,&cli_len);
            }
            else if(which==1)
            {
                writeserlog(buf,n,1,1,3);
                setexpected(buf,n);
                sendback(fd,buf,(struct sockaddr *)&cli_addr,cli_len,1,false);
            }
            else
            {
                writeserlog(buf,n,1,2,1);
                sendagain(fd,&cli_addr,&cli_len);
            }
            
            
        }
    }
}