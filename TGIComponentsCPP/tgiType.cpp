#include "tgiType.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

/*
Generator Functions
*/

TGITypeGenerator::TGITypeGenerator()
{
	//first init, open list of commands
	//generate the class name for each
	//if it doesnt exist in the file -> make it
	//if it does exist, skip it
	std::ifstream commands;
	commands.open("Commands.txt");
	std::ifstream generatedFile;
	generatedFile.open("tgiGeneratedTypes.h");

	//read generatedFile into a string
	std::string buffer = "";
	std::string generatedFileString = "";
	while (std::getline(generatedFile, buffer))
		generatedFileString += buffer;

	//if the class does not already exist for the command, make it
	while (std::getline(commands, buffer))
		if (generatedFileString.find(createClassNameForCommand(buffer)) == generatedFileString.npos)
			createCPPFile(buffer);

	commands.close();
	generatedFile.close();
}

/*
PUT ERROR CODES HERE
*/
void TGITypeGenerator::createCPPFile(const std::string& commandName)
{
	/*
	<includes>
	*/
	//maybe have this in the base file and read it in instead
	std::vector<std::string> fileString;
	std::fstream generatedFile;
	generatedFile.open("tgiGeneratedTypes.h");
	if (!generatedFile) return;
	//temp string
	std::string currentLine = "";
	while (std::getline(generatedFile, currentLine))
		fileString.push_back(currentLine + "\n");

	//reset file pointer back to beginning
	generatedFile.clear();
	generatedFile.seekg(0, std::ios::beg);

	//generate new type code and append to current file string
	std::string className = createClassNameForCommand(commandName);

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
		"class " + className + "\n" +
		"{\n" +
		"public:\n\t" +
		className + "(const std::string& _name)" +
		"\n\t{\n" +
		"\t\tname = _name;\n" +
		"\t\tcastString = dynamic_cast<TGIType>(" + className + ");\n\t}\n" +
		"\tvirtual TGIType* castToChildType(TGIType* typeToBeCasted) {}\n" +
		"\tvirtual void trigger() {}\n" +
		"private:\n" +
		"\tstd::string name;\n" +
		"\tstd::string castString;\n"
		"};\n"
	);

	//add the new class to the file
	fileString.push_back(classContentsString);

	//write new cpp file
	if (generatedFile)
		for (int i = 0; i < fileString.size(); ++i)
			generatedFile << fileString[i];

	generatedFile.close();
}

void TGITypeGenerator::createType(const std::string& commandName)
{

}

std::string TGITypeGenerator::createClassNameForCommand(const std::string& commandName)
{
	//create the name -> search for name in file
	//name doesnt exist ? return className : return ""
	//strip the ! out of command, as well as spaces and unavailable characters
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

	str += "TypeClass";

	/* Some Additional Checks may be needed here*/
	//check class name so that it will compile
	//if it starts with a number ... add a _ to the beginning
	if (isdigit(str[0]))
		str.insert(str.begin(), '_');

	return str;
}
