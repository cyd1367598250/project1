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
#include "../log/log.h"

static int sender_port;
static int receiver_port;
static char *name;
static int max_win;
static int rto;
static float flp;
static float rlp;
static float fcp;
static float rcp;

void initpa(int argv,char *argc);
static void sys_err(const char *msg);