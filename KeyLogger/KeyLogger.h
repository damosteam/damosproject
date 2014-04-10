
#ifndef KEY_LOGGER_H
#define KEY_LOGGER_H

#define EVENT_MAXIMUM 100

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <linux/input.h>

#include <iostream>

class KeyLogger 
{
	private:
  		int mFd, mEfd, mCfg, mRet;

  		struct input_event mInputEvent;
  		struct epoll_event mEpollEvent;

		FILE *mFile;
		struct epoll_event *mEpollEvents;

	public:
	  	KeyLogger(int argc, char **argv);

		~KeyLogger();

		void log();
};

#endif
