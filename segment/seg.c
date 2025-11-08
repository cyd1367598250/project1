#include "seg.h"

void setexpected(const char*buf,ssize_t n)
{
    uint16_t seq;
    memcpy(&seq,buf,2);
    seq = ntohs(seq);
    expected_seq=seq;
}

bool isexpect(const char* buf,size_t n)
{
    uint16_t seq;
    memcpy(&seq,buf,2);
    seq = ntohs(seq);
    if(seq==expected_seq)
    return true;
    return false;
}


uint16_t urp_checksum(const uint8_t *p, size_t len) {
    uint32_t sum = 0;
    while (len > 1) {
        uint16_t w = ((uint16_t)p[0] << 8) | p[1];
        sum += w;
        if (sum > 0xFFFF) sum = (sum & 0xFFFF) + 1; // 回卷进位
        p += 2;
        len -= 2;
    }
    if (len == 1) { // 奇数字节
        uint16_t w = ((uint16_t)p[0] << 8);
        sum += w;
        if (sum > 0xFFFF) sum = (sum & 0xFFFF) + 1;
    }
    return (uint16_t)~sum;
}

int checkbuf(const char *buf,size_t n)
{
    
    uint8_t *p=(const uint8_t*)buf;
    if(n<URP_HEADER_LEN)
    return -1;
    uint16_t seq, flags, checksum;

    memcpy(&seq,      p + 0, 2);
    memcpy(&flags,    p + 2, 2);
    memcpy(&checksum, p + 4, 2);
    seq      = ntohs(seq);
    flags    = ntohs(flags);
    checksum = ntohs(checksum);
    uint8_t tmp[n];
    memcpy(tmp, buf, n);
    tmp[4] = tmp[5] = 0;
    uint16_t calc_sum = urp_checksum(tmp, n);
    if (calc_sum != checksum) {
        return -2;
    }
    if (flags &URP_ACK)
    return 1;
    else if (flags&URP_FIN)
    return 2;
    else if(flags&URP_SYN)
    return 3;
    
}

static uint16_t csum16(const uint8_t *buf, size_t len)
{
    uint32_t sum = 0;

    while (len > 1) {
        sum += (uint16_t)((buf[0] << 8) | buf[1]); // 按网络序配对
        buf += 2;
        len -= 2;
    }
    if (len == 1) {                 // 奇数字节，补到高位
        sum += (uint16_t)(buf[0] << 8);
    }
    while (sum >> 16) {             // 折叠进位
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    return (uint16_t)(~sum); 
}

size_t formsendback(ssize_t n,int type,uint8_t *out)
{
    uint16_t seq,flags,checksum;
    seq      = expected_seq;
    
    if(n==6)
        seq+=1;
    else
        seq+=n-6;
    if (type==1)
        flags=URP_ACK;
    else if(type==2)
        flags=URP_SYN;
    else if (type==3)
        flags=URP_FIN;
    
    seq      = htons(seq);
    flags    = htons(flags);
    checksum=0;
    
    memcpy(out,&seq,2);
    memcpy(out+2,&flags,2);
    memcpy(out+4,&checksum,2);
    checksum=csum16(out,6);
    checksum=htons(checksum);
    memcpy(out+4,&checksum,2);
    memcpy(acknow,out,6);
    return 6;
}

void sendagain(int fd,struct sockaddr_in * cli_addr,socklen_t *cli_len)
{
    sendto(fd,acknow,sizeof(acknow),0,(struct sockaddr*)cli_addr,*cli_len);
    writeserlog(acknow,sizeof(acknow),1,1,1);
}

uint16_t getseq(const char*buf)
{
    uint16_t seq;
    memcmy(&seq,buf,2);
    seq=ntohs(seq);
    return seq;
}