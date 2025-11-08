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
#include "../segment/seg.h"
#include "../log/log.h"
#define true 1
#define false 0
int recport;
int senport;
char *rec_file_name;
int max_win;

void sys_err(const char str);
int initserver(struct sockaddr_in *sev_addr);
int createwin();
int sendwin(const char *buf,size_t n);
bool isreclost();
bool isconnected(int sockfd,struct sockaddr_in * cli_addr,socklen_t *cli_len);
int dealwith(const char *buf,size_t n);
bool sendback(int fd,const char* buf,
        struct sockaddr_in * cli_addr,ssize_t n,int type,bool isdata);
void work(int fd);
