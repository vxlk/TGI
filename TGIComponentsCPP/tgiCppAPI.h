#pragma once

#include "configEditor.h"
#include "tgiVector.h"


#ifdef _WIN32
#define TGI_WIN 1
#include <Windows.h>
#endif

#define CHANNEL_CONNECTION "Recieved USERSTATE Command:"

enum TGIStatus
{
	ExecutableNotFound,
	FilePathNotValid,
	OpenSuccess,
	CloseSuccess,
	ChannelUpdated,
	ChannelNotFound
};

#ifdef TGI_WIN

///needs 3 rule
//figure out a way to check if userstate is received
//after the bot has fully run .. 
//scan log file, if Recieved USERSTATE Command: is not in the file, then we did not connect to the file, throw an error
//***** log file needs to be rewritten every time the bot is run

class TGICppAPI_WIN
{
public:
	TGICppAPI_WIN();
	TGIStatus startPoll();
	TGIStatus closePoll();
	TGIStatus addCommand(const std::string& toBeAdded);
	const std::string getCommandList();
	TGIStatus update();
	
	TGIStatus changeChannel(std::string newChannel);

	bool isRunning = false;
private:

	void clearLogFile();
	bool checkForChannelConnection();
	void runCommands();

	/*Info about each command*/
	tgiVector<TGIType*> types;

	/*Info about the bot process*/
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	/* TGI Components */ ///make these pointers
	TGIDataHandler   data;
	ConfigEditor     config;
	TGITypeGenerator* generator;
};

#endif