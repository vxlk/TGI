#pragma once
#ifndef TGI_CPP_API_H
#define TGI_CPP_API_H
#include "configEditor.h"
#include "typeList.h"

///todo: add destructor code

#ifdef UE_EDITOR //is it in unreal engine?
#define TGI_UNREAL

#else
	//check for unity later
	#ifdef _WIN32 
	#define TGI_WIN 1
	#include <Windows.h>
	#endif
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

///needs 3 rule
//figure out a way to check if userstate is received
//after the bot has fully run .. 
//scan log file, if Recieved USERSTATE Command: is not in the file, then we did not connect to the file, throw an error
//***** log file needs to be rewritten every time the bot is run

/*
	Automatically decides the platform. Just call use TGIAPI in code, and it will be the right
	platform's version.
*/
class TGICppAPI
{
public:
	TGICppAPI();
	virtual ~TGICppAPI() {}

	virtual TGIStatus startPoll()=0;
	virtual TGIStatus closePoll()=0;

	TGIStatus addCommand(const std::string& toBeAdded);
	const std::string getCommandList();
	void update();

	TGIStatus changeChannel(std::string newChannel);

	bool isRunning = false;

protected:

	void clearLogFile();
	bool checkForChannelConnection();
	void runCommands();

	/*Info about each command*/
	TypeList* types;

	/* TGI Components */ ///make these pointers
	TGIDataHandler   data;
	ConfigEditor     config;
	TGITypeGenerator* generator;

private:

};

#ifdef TGI_WIN
typedef TGICppAPI_WIN TGIAPI;
class TGICppAPI_WIN
{
public:

	TGICppAPI_WIN();

	virtual TGIStatus startPoll() override;
	virtual TGIStatus closePoll() override;


private:
	/*Info about the bot process*/
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
};
#endif

#ifdef TGI_UNREAL
/* implementation of the cpp api in unreal plugin format... */
class TGIUnrealAPI : public TGICppAPI
{
public:
	virtual ~TGIUnrealAPI() {}
	//TGIUnrealAPI();
	virtual TGIStatus startPoll() override;
	virtual TGIStatus closePoll() override;

private:
	/*Info about the bot process*/
	FProcHandle program;
};

#endif
#endif //include guard