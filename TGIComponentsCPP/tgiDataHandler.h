#pragma once
#include <vector>
#include <string>

#define EXECUTABLE_NAME "TGIChatBot.exe"

struct FileWatcher
{
	FileWatcher() = delete;
	FileWatcher(const std::string &fileName, const std::string &hint);
	bool checkIfFileChanged();
private:
	std::string currentHint;
	std::string fileBeingWatched;
};

/*
A class to interface between data stored in logs files and data in memory
*/

///update the file paths here ... the idea of this class is to be an interface to the files using the given file path

class TGIDataHandler
{

public:
	/*
	 * On initialization:
	 * find file path
	 * store list of valid commands into memory as TGITypes
	 */
	TGIDataHandler();

	//getter functions
	inline const std::string& getFilePathString() const { return filePathExe; }
	inline const std::string& getUpdatedChatLogString() { readChatLogToMemory(); return chatLog; }
	inline const std::string& getUpdatedCommandListString() { readCommandListToMemory(); return commands; }

	bool checkChatLogForChange();

	void setFilePath(std::string path);

	std::vector<std::string> returnCommandList();

private:

//save space for other implementations

	void readChatLogToMemory();
	void readCommandListToMemory();

	/* File paths filled in by constructor and saved in the init file */
	std::string filePathExe;
	std::string filePathBot;
	std::string filePathLogFiles;

	std::string chatLog;
	std::string commands;

	FileWatcher* fileWatcher;
	std::string fileWatcherHint = "";
};
