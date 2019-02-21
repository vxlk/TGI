#include "tgiCppAPI.h"
#include <fstream>

TGICppAPI::TGICppAPI()
{
	//open init file, if no init file - make file path null
	///do later

	//init generator
	this->generator = new TGITypeGenerator();
	this->types = new TypeList();
}

TGIStatus TGICppAPI::changeChannel(std::string newChannel)
{
	closePoll(); //close the bot before you change the channel...
	config.updateChannelName(newChannel);
	return ChannelUpdated;
}

void TGICppAPI::clearLogFile()
{
	std::fstream logFile;
	logFile.open("PhantomBotLog.txt");
	logFile.clear();
	logFile.close();
}

bool TGICppAPI::checkForChannelConnection()
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

TGIStatus TGICppAPI::addCommand(const std::string& toBeAdded)
{
	//update typeList
	return CloseSuccess;
}

void TGICppAPI::runCommands()
{
	//loop through loop and types and do what u need to do
	std::vector<std::string> newChatMessages = data.getChangedData(); ///not working... ALSO NEED TO STRIP NAME OUT OF COMMANDS
	for (int i = 0; i < newChatMessages.size(); ++i)
		//if its a valid command
		if (data.getUpdatedCommandListString().find(data.stripNameOutOfChatLine(newChatMessages[i])))
			//pull the trigger for the type with this name
			if (this->types->getTypeByName(data.stripExclamationPoint(data.stripNameOutOfChatLine(newChatMessages[i]))))
				this->types->getTypeByName(data.stripExclamationPoint(data.stripNameOutOfChatLine(newChatMessages[i])))->trigger();
}

void TGICppAPI::update()
{
	if (isRunning)
	{
		if (data.checkChatLogForChange()) 
			runCommands();
	}
}

/* WINDOWS APP IMPLEMENTATION */

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
	this->types = new TypeList();

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
#endif


/* UNREAL PLUGIN IMPLEMENTATION */

#ifdef TGI_UNREAL
#
#ifdef _WIN32
#include <Core/Public/Windows/WindowsPlatformProcess.h>
#endif
//here i would also want to do mac / android / ios etc

TGIStatus TGIUnrealAPI::startPoll()
{
	const TCHAR botPath[] = TEXT("C:\\Users\\Tyler\\Documents\\Unreal Projects\\tgiExampleProject\\Plugins\\TGI\\Source\\TGI\\TGIChatBot.exe");
	const TCHAR workingDir[] = TEXT("C:\\Users\\Tyler\\Documents\\Unreal Projects\\tgiExampleProject\\Plugins\\TGI\\Source\\TGI");
	const TCHAR params[] = TEXT("");
	///current problem is getting the process to start via the file path

	//clear log before running...
	clearLogFile();
	uint32 pid = 0;
	// start the program up
	this->program = FPlatformProcess::CreateProc(botPath, params, false, false, false, &pid, 0, workingDir, nullptr);
	if (  this->program.IsValid() ) //start program goes here
	{

		FPlatformProcess::OpenProcess(pid);

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

TGIStatus TGIUnrealAPI::closePoll()
{
	
	return CloseSuccess;
}

#endif