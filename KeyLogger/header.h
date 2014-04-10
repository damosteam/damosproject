
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <iostream>

#include "KeyLogger.h"

extern KeyLogger* mKeyLogger;

void signalHandler(int signal);

#endif
