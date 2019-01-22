#include "tgiCppAPI.h"
#include <fstream>

///temp
#include <iostream>

#ifdef TGI_WIN

std::string getExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

TGICppAPI_WIN::TGICppAPI_WIN()
{
	//open init file, if no init file - make file path null
	std::fstream initFile;
	initFile.open("config.tgi");

	//first use - create config
	if (initFile.peek() == std::ifstream::traits_type::eof())
	{
		data.setFilePath(getExePath());
		initFile << getExePath();
	}
	else
	{
		//find the file path in the file - is first line
		std::string path;
		std::getline(initFile, path);
		data.setFilePath(path);
	}
	initFile.close();

	//init generator
	this->generator = new TGITypeGenerator();
}

/// CloseHandle( pi.hProcess ); to close

TGIStatus TGICppAPI_WIN::startPoll()
{
	std::string botPath = data.getFilePathString() + "\\TGIChatBot.exe";

	//init process structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	///current problem is getting the process to start via the file path

	//clear log before running...
	clearLogFile();

	// start the program up
	if (CreateProcess(/*botPath.c_str()*/ "TGIChatBot.exe",   // the path
		NULL,           // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		TRUE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	))
	{
		isRunning = true;

		//instantiate a watcher over the chat log
		data.checkChatLogForChange();

		if (!checkForChannelConnection())
			return ChannelNotFound;
		return OpenSuccess;
	}

	else
	{
		std::cout << botPath << "\n";
		return ExecutableNotFound;

	}
}

TGIStatus TGICppAPI_WIN::closePoll()
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pi.dwProcessId);
	if (hProcess == NULL)
		return ExecutableNotFound;

	TerminateProcess(hProcess, GetExitCodeProcess(hProcess, NULL));

	CloseHandle(hProcess);
	isRunning = false;
	return CloseSuccess;
}

TGIStatus TGICppAPI_WIN::changeChannel(std::string newChannel)
{
	closePoll(); //close the bot before you change the channel...
	config.updateChannelName(newChannel);
	return ChannelUpdated;
}

void TGICppAPI_WIN::clearLogFile()
{
	std::fstream logFile;
	logFile.open("PhantomBotLog.txt");
	logFile.clear();
	logFile.close();
}

bool TGICppAPI_WIN::checkForChannelConnection()
{
	std::fstream logFile;
	logFile.open("PhantomBotLog.txt");
	std::string buffer = "";
	std::string logFileInMemory = "";
	while (std::getline(logFile, buffer))
		logFileInMemory += buffer;
	if (logFileInMemory.find(CHANNEL_CONNECTION) != logFileInMemory.npos)
		return true;
	return false;
}

TGIStatus TGICppAPI_WIN::addCommand(const std::string& toBeAdded)
{
	return CloseSuccess;
}

void TGICppAPI_WIN::runCommands()
{
	//loop through loop and types and do what u need to do
	std::vector<std::string> newChatMessages = data.getChangedData();
	for(int i = 0; i < newChatMessages.size(); ++i)
		if (data.getUpdatedCommandListString().find(newChatMessages[i])
			//find which command, run the trigger

			//you have a list of types
			//each type has a name
			//go thru each type and see if name matches?

			///overload [] operator of typeList to take a string, find the type that way -> can i do without On time??
}

void TGICppAPI_WIN::update()
{
	if (isRunning)
	{
		if (data.checkChatLogForChange())
			runCommands();
	}
}
#endif