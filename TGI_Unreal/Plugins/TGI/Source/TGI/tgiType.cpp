#include "tgiType.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

/*
Utility Functions
*/

std::string cleanCommandName(const std::string& commandName)
{
	std::string str = commandName;

	//this list should be updated before beta testing -> also might want to write your own algorithm
	str.erase(std::remove(str.begin(), str.end(), '!'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '#'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\''), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\\'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '/'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ';'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ':'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
	str.erase(std::remove(str.begin(), str.end(), ','), str.end());
	str.erase(std::remove(str.begin(), str.end(), '`'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());

	return str;
}

/*
Generator Functions
*/

TGITypeGenerator::TGITypeGenerator()
{
	//first init, open list of commands
	//generate the class name for each
	//if it doesnt exist in the file -> make it
	//if it does exist, skip it
	std::ifstream generatedFile;
	generatedFile.open("tgiGeneratedTypes.h");

	//read generatedFile into a string
	std::string buffer = "";
	std::string generatedFileString = "";
	while (std::getline(generatedFile, buffer))
		generatedFileString += buffer;

	std::stringstream commands(commandListInterface.getUpdatedCommandListString());
	//if the class does not already exist for the command, make it
	while (std::getline(commands, buffer))
		if (generatedFileString.find(createClassNameForCommand(buffer)) == generatedFileString.npos)
			createCPPFile(buffer);

	commands.clear();
	generatedFile.close();
}

/*
PUT ERROR CODES HERE
*/
void TGITypeGenerator::createListFile(const std::string& commandName)
{
	//generate class name
	std::string className = createClassNameForCommand(commandName);

	//maybe have this in the base file and read it in instead
	std::vector<std::string> fileString;
	std::fstream generatedFile;
	generatedFile.open("typeList.h");
	if (!generatedFile) return;
	//temp string
	std::string currentLine = "";
	//read the entire file into an array, make sure you are not making a duplicate class
	while (std::getline(generatedFile, currentLine))
		if (currentLine.find(className) != currentLine.npos)
		{
			generatedFile.close();
			return;
		}
		else
			fileString.push_back(currentLine + "\n");

	//go thru and find TypeList(), go 1 more to skip { then append the new class to the constructor
	for (int i = 0; i < fileString.size(); ++i)
		if (fileString[i].find("TypeList()") != fileString[i].npos)
		{
			//skip the { and go to the cast line
			i += 2;
			fileString[i] += "\n\t\ttypes.push_back(new " + createClassNameForCommand(commandName) + ");\n";
			break;
		}

	//reset file pointer back to beginning
	generatedFile.clear();
	generatedFile.seekg(0, std::ios::beg);

	//write new file
	if (generatedFile)
		for (int i = 0; i < fileString.size(); ++i)
			generatedFile << fileString[i];

	generatedFile.close();
}

void TGITypeGenerator::createCPPFile(const std::string& commandName)
{
	/*
	<includes>
	*/

	//generate class name
	std::string className = createClassNameForCommand(commandName);

	//maybe have this in the base file and read it in instead
	std::vector<std::string> fileString;
	std::fstream generatedFile;
	generatedFile.open("tgiGeneratedTypes.h");
	if (!generatedFile) return;
	//temp string
	std::string currentLine = "";
	//read the entire file into an array, make sure you are not making a duplicate class
	while (std::getline(generatedFile, currentLine))
		if (currentLine.find(className) != currentLine.npos) 
		{
			generatedFile.close();
			return;
		}
		else 
			fileString.push_back(currentLine + "\n");

	//if the beginning contents dont match ... append this
#if 0
	
#pragma once
/* This is the file that contains all of the custom code for a chat function
 ********************** THIS FILE IS AUTO-GENERATED ******************************
						ANY CODE WRITTEN OUTSIDE OF					  
						DESIGNATED AREAS IS PRONE TO
 *********************		   DELETION           ********************************
 */
#include "TGIType.h"

 /*Below is each custom "Type"*/

#endif

	//reset file pointer back to beginning
	generatedFile.clear();
	generatedFile.seekg(0, std::ios::beg);

	/*
	class TGIType
{

public:
	TGIType(const std::string& _name)
	{
		name = _name;
		//							base     child
		castString = "dynamic_cast<TGIType>(TGIType);";
	}

	virtual TGIType* castToChildType(TGIType*) {}
	virtual void trigger() {}

private:
	std::string name;
	std::string castString;
};
	*/
	std::string classContentsString
	(
		"class " + className + " : public TGIType " + "\n" +
		"{\n" +
		"public:\n\t" +
		className + "() : TGIType(" + "\"" + cleanCommandName(commandName) + "\"" + ")\t{}\n" +
		"\tvirtual void trigger()\n\t{\n" +
		"\t\t//Code that will be run when the command is triggered will go here\n" +
		"\t}\n" +
		"private:\n" +
		"//your private variables go here\n" +
		"};\n"
	);

	//add the new class to the file
	fileString.push_back(classContentsString);

	//write new cpp file
	if (generatedFile)
		for (int i = 0; i < fileString.size(); ++i)
			generatedFile << fileString[i];

	//update the list file
	createListFile(commandName);

	generatedFile.close();
}

void TGITypeGenerator::addType(const std::string& commandName)
{
	/*
	std::ofstream generatedFile;
	generatedFile.open("tgiGeneratedTypes.h", std::ios::app);
	if (!generatedFile) return;
	*/
	createCPPFile(commandName);
}

std::string TGITypeGenerator::createClassNameForCommand(const std::string& commandName)
{
	//create the name -> search for name in file
	//name doesnt exist ? return className : return ""
	//strip the ! out of command, as well as spaces and unavailable characters
	std::string str = cleanCommandName(commandName);
	str += "TypeClass";

	/* Some Additional Checks may be needed here*/
	//check class name so that it will compile
	//if it starts with a number ... add a _ to the beginning
	if (isdigit(str[0]))
		str.insert(str.begin(), '_');

	return str;
}
