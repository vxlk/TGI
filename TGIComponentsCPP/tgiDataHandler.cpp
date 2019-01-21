#include "tgiDataHandler.h"
#include <fstream>
#include <algorithm>

#if defined(__has_include)
#if __has_include("experimental/filesystem")
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else 
#error File system not supported.. Use a C++17 compiler for std::filesystem
#endif
#endif //if defined

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

		f.close();
		return mostRecentMessage == currentHint;
	}
}

TGIDataHandler::TGIDataHandler()
{
	//open init file, and check
	
	chatLog = "";
	commands = "";


	//clear log files before initialization
	std::ofstream log;
	log.open("PhantomBotLog.txt", std::ofstream::out | std::ofstream::trunc);
	log.close();

	log.open("ChatLog.txt", std::ofstream::out | std::ofstream::trunc);
	log.close();



	//get bot path
	//fs::path full_path(fs::canonical("TGIChatBot.exe"));


	//full_path = fs::system_complete(fs::path("temp/"));
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

	if (chatLog == "") return false; 

	if (fileWatcherHint == "")
	{
		//get last line as hint
		int index = chatLog.size() - 1;
		//skip end of file garbage
		while (chatLog[index] == '\n' || chatLog[index] == '\r' || chatLog[index] == '\t')
			--index;
		while (chatLog[index] != '\n' && chatLog[index--] != ':')
		{
			this->fileWatcherHint += chatLog[index];
			--index;
		}
		std::reverse(fileWatcherHint.begin(), fileWatcherHint.end());
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

const std::vector<std::string> TGIDataHandler::returnCommandList()
{
	std::ifstream f;
	f.open("Commands.txt");
	std::vector<std::string> toBeReturned;
	std::string command;
	while (std::getline(f, command))
		toBeReturned.push_back(command);
	return toBeReturned;
}
