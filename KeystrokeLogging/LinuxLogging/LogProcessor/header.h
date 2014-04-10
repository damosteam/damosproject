
#ifndef HEADER_H
#define HEADER_H

#define KEY_MAXIMUM 104

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <signal.h>
#include <sys/epoll.h>
#include <linux/input.h>

#include <set>
#include <utility>
#include <iostream>

#include "KeyMap.h"
#include "KeyLogProcessor.h"

extern struct KeyMap mLinuxKeyMap[]; 

#endif
