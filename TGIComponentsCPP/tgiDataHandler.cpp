#include "tgiDataHandler.h"
#include <fstream>

#if __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else 
#error File system not supported.. Use a C++17 compiler for std::filesystem
#endif

FileWatcher::FileWatcher(const std::string &filePath, const std::string &hint)
{
	this->fileBeingWatched = filePath;
	this->currentHint = hint;
}

bool FileWatcher::checkIfFileChanged()
{
	//open file
	std::ifstream f;
	f.open(fileBeingWatched);

	if (f.good())
	{
		std::string mostRecentMessage = "";
		//skip to end of file
		f.seekg(0, std::ios_base::end);
		//skip the end of file character
		f.seekg(-1, std::ios_base::cur);
		//check if null character, some text editors end all files with a \n
		std::getline(f, mostRecentMessage);
		if (mostRecentMessage == "")
			std::getline(f, mostRecentMessage);

		return mostRecentMessage == currentHint;
	}
}

TGIDataHandler::TGIDataHandler()
{
	//open init file, and check
	
	chatLog = "";
	commands = "";

	//get bot path
	fs::path full_path(fs::canonical("TGIChatBot.exe"));


	full_path = fs::system_complete(fs::path("temp/"));
}

void TGIDataHandler::setFilePath(std::string path)
{
	this->filePathExe = path;
}

//add checks to make sure there is no double writing here
///these will need to use the master file path eventually ... not now though
void TGIDataHandler::readChatLogToMemory()
{
	std::ifstream chatLogFile;
	chatLogFile.open("ChatLog.txt");

	std::string buffer = "";
	while (std::getline(chatLogFile, buffer))
		this->chatLog += (buffer + "\n");

	chatLogFile.close();
}

void TGIDataHandler::readCommandListToMemory()
{
	std::ifstream commandsLog;
	commandsLog.open("Commands.txt");

	std::string buffer = "";
	while (std::getline(commandsLog, buffer))
		this->commands += (buffer + "\n");

	commandsLog.close();
}

bool TGIDataHandler::checkChatLogForChange()
{
	readChatLogToMemory();
	
	if (fileWatcherHint == "")
	{
		//get last line as hint
		int index = chatLog.size() - 1;
		while (chatLog[index--] != '\n')
			this->fileWatcherHint += chatLog[index];
	}

	if (!this->fileWatcher)
		fileWatcher = new FileWatcher(filePathLogFiles + "ChatLog.txt", fileWatcherHint);

	if (fileWatcher->checkIfFileChanged())
	{
		fileWatcherHint = ""; //reset hint
		return true;
	}

	return false;
}
