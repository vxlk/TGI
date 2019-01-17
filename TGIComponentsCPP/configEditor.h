#pragma once

#include "tgiType.h"

#define CHANNEL_NAME_POS_IN_FILE 3

/*
Interface to the config file used to decide the channel / connection settings
*/

class ConfigEditor
{

public:
	void updateOAuth(std::string newOAuth);
	bool updateChannelName(std::string newChannel);
	bool revertToBackup();
	//update url / port .. ? probably not needed - maybe add @ a future date
private:
	void displayOAuthWarning();
	void readConfigIntoMem();
	bool writeToFile();
	std::string configFile;
	std::string configBackup;

	//used for file path
	TGIDataHandler data;
};