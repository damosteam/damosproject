
#ifndef KEY_LOG_PROCESSOR_CPP
#define KEY_LOG_PROCESSOR_CPP

#include "KeyLogProcessor.h"

struct KeyMap mLinuxKeyMap[] = 
{
        { "0",  "[RESERVED]" },
        { "1",  "[ESC]" },
        { "2",  "1" },
        { "3",  "2" },
        { "4",  "3" },
        { "5",  "4" },
        { "6",  "5" },                   
        { "7",  "6" },                   
        { "8",  "7" },                   
        { "9",  "8" },                   
        { "10", "9" },
        { "11", "0" },
        { "12", "-" },
        { "13", "=" },
        { "14", "[BACKSPACE]" },
        { "15", "[TAB]" },
        { "16", "q" },
        { "17", "w" },                   
        { "18", "e" },                   
        { "19", "r" },                   
        { "20", "t" },                   
        { "21", "y" },                   
        { "22", "u" },                   
        { "23", "i" },                   
        { "24", "o" },                   
        { "25", "p" },                   
        { "26", "[" },           
        { "27", "]" },          
        { "28", "[ENTER]" },               
        { "29", "[LEFT_CTRL]" },            
        { "30", "a" },                   
        { "31", "s" },                   
        { "32", "d" },                   
        { "33", "f" },                   
        { "34", "g" },                   
        { "35", "h" },                   
        { "36", "j" },                   
        { "37", "k" },                   
        { "38", "l" },                   
        { "39", ";" },           
        { "40", "KEY_APOSTROPHE" },          
        { "41", "KEY_GRAVE" },               
        { "42", "[LEFT_SHIFT]" },           
        { "43", "\\" },           
        { "44", "z" },                   
        { "45", "x" },                   
        { "46", "c" },                   
        { "47", "v" },                   
        { "48", "b" },                   
        { "49", "n" },                   
        { "50", "m" },                   
        { "51", "," },               
        { "52", "." },                 
        { "53", "/" },               
        { "54", "[RIGHT_SHIFT]" },          
        { "55", "*" },          
        { "56", "[LEFT_ALT]" },             
        { "57", "[SPACE]" },               
        { "58", "[CAPS_LOCK]" },            
        { "59", "[F1]" },                  
        { "60", "[F2]" },                  
        { "61", "[F3]" },                  
        { "62", "[F4]" },                  
        { "63", "[F5]" },                  
        { "64", "[F6]" },                  
        { "65", "[F7]" },                  
        { "66", "[F8]" },                  
        { "67", "[F9]" },                  
        { "68", "[F10]" },                 
        { "69", "[NUMLOCK]" },             
        { "70", "[SCROLLLOCK]" },          
        { "71", "[KP7]" },                 
        { "72", "[KP8]" },                 
        { "73", "[KP9]" },                 
        { "74", "[KPMINUS]" },             
        { "75", "[KP4]" },                 
        { "76", "[KP5]" },                 
        { "77", "[KP6]" },                 
        { "78", "[KPPLUS]" },              
        { "79", "[KP1]" },                 
        { "80", "[KP2]" },                 
        { "81", "[KP3]" },                 
        { "82", "[KP0]" },                 
        { "83", "[KPDOT]" },               
        { "87", "[F11]" },                 
        { "88", "[F12]" },                 
        { "96", "[KPENTER]" },             
        { "97", "[RIGHT_CTRL]" },           
        { "98", "[KPSLASH]" },             
        { "99", "[SYSRQ]" },               
        { "100", "[RIGHTALT]" },            
        { "101", "[LINEFEED]" },            
        { "102", "[HOME]" },                
        { "103", "[UP]" },                  
        { "104", "[PAGEUP]" },              
        { "105", "[LEFT]" },                
        { "106", "[RIGHT]" },               
        { "107", "[END]" },                 
        { "108", "[DOWN]" },                
        { "109", "[PAGEDOWN]" },            
        { "110", "[INSERT]" },              
        { "111", "[DELETE]" },              
        { "117", "[KPEQUAL]" },             
        { "118", "[KPPLUSMINUS]" },         
        { "119", "[PAUSE]" }         
};

KeyLogProcessor::KeyLogProcessor(int &argc, char **argv)
{
	if(argc != 2)
        {
		printf("Usage: %s filename.\n", argv[0]);
		exit(1);
      	}

    	if(!(mFp = fopen(argv[1], "r")))
      	{
		printf("Error opening keylog file.\n");
		exit(1);
      	}

    	if(hcreate(KEY_MAXIMUM) == 0)
      	{
		printf("Error initializing hash table.\n");
		exit(1);
      	}

    	for(int i = 0; i < KEY_MAXIMUM; i++)
      	{
		mEp.key  = (char*) mLinuxKeyMap[i].keyCode;
		mEp.data = (char*) mLinuxKeyMap[i].keyName;
	
		if(hsearch(mEp, ENTER) == NULL)
		{
	    		printf("Hash table search failed.\n");
	    		exit(1);
	  	}
	}
}


void KeyLogProcessor::processKeyLogFile()
{
	std::set<char*> hKey;

	while(1)
        {
		if(fscanf(mFp, "%d\n%d\n%d", &mCode[0], &mCode[1], &mCode[2]) < 0)
	  	{
	    		printf("Done reading from keylog file.\n");
	    		break;
	  	}

		char* temp = (char*) malloc(sizeof(int));
   		sprintf(temp, "%d", mCode[0]);
  		mEp.key = temp;
		mSearchResult = hsearch(mEp, FIND); 
		free(temp);
	
		if(mSearchResult)
	  	{
	    		if(mCode[1] == 1)
	      		{
				printf("%s", ((char*) mSearchResult->data));

				if(strcmp(((char*) mSearchResult->data), "[ENTER]") || strcmp(((char*) mSearchResult->data), "[KPENTER]"))
				{
		  			printf("\n");
				}

				continue;
	      		}

	    		if(mCode[1] == 2 || mCode[1] == 0)
	      		{
				if(mCode[1] == 2)
		  		{
		    			std::pair<std::set<char*>::iterator, bool> keyPair = hKey.insert(mSearchResult->key);
		    			bool addedToHash = keyPair.second;

		    			if(addedToHash)
					{
		      				printf("<");
					}
		  		}
				else
		  		{
		    			std::set<char*>::iterator pos = hKey.find(mSearchResult->key);

		    			if(pos != hKey.end())
		      			{
						printf(">");
						hKey.erase(pos);
		      			}
		  		}

				continue;
			}
		}
	}
}


KeyLogProcessor::~KeyLogProcessor()
{
	hdestroy();
	fclose(mFp);    
}

#endif
