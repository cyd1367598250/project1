#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "../log/log.h"

typedef struct{
    uint16_t seqnum;
    uint16_t revered;
    uint16_t err;
    char data[1000];
}seq;

enum{
    URP_ACK = 0x001,     // bit0
    URP_SYN = 0x002,     // bit1
    URP_FIN = 0x004,
    URP_NULL= 0x000
};
#define URP_HEADER_LEN 6
#define URP_MSS        1000
uint32_t expected_seq;
uint8_t acknow[URP_HEADER_LEN];

uint16_t urp_checksum(const uint8_t *p, size_t len);
int isbroken(const char *buf,size_t n);
int checkbuf(const char *buf,size_t n);
size_t formsendback(ssize_t n,int type,uint8_t *out);
static uint16_t csum16(const uint8_t *buf, size_t len);
void setexpected(const char*buf,ssize_t n);
bool isexpect(const char* buf,size_t n);
void sendagain(int fd,struct sockaddr_in * cli_addr,socklen_t *cli_len);
uint16_t getseq(const char*buf);