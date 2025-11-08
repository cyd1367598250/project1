#include "../sbase/sbase.h"

int main(int argv,char* argc[])
{
    initpa(argv,argc);
    initrlog(name);
    const char ip="127.0.0.1";
    struct sockaddr_in cli_addr;
    memset(&cli_addr,0,sizeof(cli_addr));
    cli_addr.sin_family=AF_INET;
    cli_addr.sin_port=htons(sender_port);
    if (inet_pton(AF_INET,ip , &cli_addr.sin_addr) != 1) { fprintf(stderr,"bad ip\n"); return 1; }

    return 0;
}