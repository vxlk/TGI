#pragma once

#include "tgiType.h"
#include <vector>

/*
A class to interface between data stored in logs files and data in memory
*/

class TGIDataHandler
{

public:
	/*
	 * On initialization:
	 * find file path
	 * store list of valid commands into memory as TGITypes
	 */
	TGIDataHandler();

	void readChatLogToMemory();
	void readCommandListToMemory();

	void setFilePath(std::string path);
	inline std::string getFilePath() { return this->filePath; }

private:
	/*
	Contains a pair, the type and the count of how many occurances are in the current chat log
	 */
	std::vector<std::pair<TGIType, int> > commandList;
	std::string filePath;
	std::string chatLog;
	std::string commands;
};
