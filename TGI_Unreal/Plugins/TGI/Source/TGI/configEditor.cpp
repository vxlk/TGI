#include "configEditor.h"
#include <fstream>

///
#include <iostream>

void ConfigEditor::readConfigIntoMem()
{
	configFile = ""; //clear previous version

	///add filepath support
	//open the file,					convert the new line characters
	std::ifstream file("botconfig.txt", std::ios_base::binary);

	//read the file into string
	std::string s = "";
	while (std::getline(file, s))
		configFile += s + '\n';

	/*
	Update the file, *** keep a backup
	*/
	//create backup
	configBackup = configFile;
	file.close();
	//std::cout << configBackup;
}

bool ConfigEditor::updateChannelName(std::string newChannel)
{
	/*
	Check and fix format ---- TODO::
	*/

	readConfigIntoMem();

	//find the twitch channel, replace it without ruining the string
	//break the string into segments, go to the 3rd segment
	std::vector<std::string> segments;
	int index = 0;
	int segmentIndex = 0;
	while (configFile[index] != '\0')
	{
		segments.push_back("");
		while (configFile[index] != '\n')
		{
			segments[segmentIndex] += configFile[index];
			++index;
		}
		++segmentIndex;
		++index;
	}

	///check the format...
	//add # if not included...
	//add \r to end
	//**check if channel exists...
	if (newChannel[0] != '#')
		newChannel.insert(newChannel.begin(), '#');

	if (newChannel[newChannel.size() - 1] != '\r')
		newChannel += '\r';

	segments[CHANNEL_NAME_POS_IN_FILE] = newChannel;

	//clear the file in memory
	configFile = "";
	//loop through, recreate the file -> call write to file
	for (int i = 0; i < segments.size(); ++i)
		configFile += segments[i] + '\n';

	//open bot to check if the channel exists, if it does not revert to previous version
	if (writeToFile()) return true;
	else return false;
}

bool ConfigEditor::writeToFile()
{
	std::ofstream file("botconfig.txt", std::ios_base::binary);
	if (!file) 
		return false;

	else
	{
		file << configFile;
		file.close();
	}

	return true;
}