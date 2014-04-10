
#ifndef  KEY_LOG_PROCESSOR_H
#define KEY_LOG_PROCESSOR_H

#include "header.h"

class KeyLogProcessor
{
	private:
		FILE *mFp;
		ENTRY mEp, *mSearchResult;
  		
		int mCode[3];

	public:
		KeyLogProcessor(int &argc, char **argv);

		~KeyLogProcessor();
		
		void processKeyLogFile();  		
};

#endif
