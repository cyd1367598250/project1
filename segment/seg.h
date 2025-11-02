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

uint16_t urp_checksum(const uint8_t *p, size_t len);
int isbroken(const char *buf,size_t n);
int checkbuf(const char *buf,size_t n);
size_t formsendback(const char* buf,ssize_t n,int type,uint8_t *out);
static uint16_t csum16(const uint8_t *buf, size_t len);
