#pragma once

#include "tgiDataHandler.h"

///do you need to cast in the type class or the generator

/*
A type is a representation of a command in code
A type has a name that will be recognized via twitch chat
A type has a trigger that can be customized and will execute upon being called
*/

//the base class
class TGIType
{

public:
	TGIType() {}
	virtual const std::string& getCommandName() const { return this->name; }

	bool operator<(const TGIType& rhs)
	{
		int index = 0;
		while (this->name[index] == rhs.getCommandName()[index])
			++index;
		return (unsigned int)name[index] < (unsigned int)rhs.getCommandName()[index];
	}

	bool operator>(const TGIType& rhs)
	{
		int index = 0;
		while (this->name[index] == rhs.getCommandName()[index])
			++index;
		return (unsigned int)name[index] > (unsigned int)rhs.getCommandName()[index];
	}

	TGIType(const std::string& _name)
	{
		name = _name;
		//							base     child
		castString = "dynamic_cast<TGIType>(TGIType);";
	}

	//virtual const std::string& getName() const { return name; }
	virtual void trigger() {}

protected:

	const int getCount() const { return count; }
	void incrementCount()	   { ++count; }


	//how many occurences were counted
	int count = 0;
	//maybe have a count threshold in the class, but it complicates things

private:
	std::string name;
	std::string castString;
};

//generates a TGIType class that inherits from the base class
//**This generates a new cpp file
class TGITypeGenerator
{
public:
	TGITypeGenerator();

	//append a new type class to the generated file
	void addType(const std::string& commandName);

	//return a derived type of base class TGIType
	TGIType createType(const std::string& commandName);

	/*
	** MODIFIES THE ARRAY **
	Generates the list of commands with their respective trigger functions
	this method goes through the list of command names, and figures out the 
	derived class' name.  it then casts the base class to that derived class
	before : List < Type > = { Type  , Type , Type  }
	after  : List < Type > = { Type1 , Type2, Type3 }
	*/
	void autoCastTypes(std::vector<TGIType* >& commandList);
private:

	void createCPPFile(const std::string& commandName);
	void createListFile(const std::string& commandName);

	bool canCreateCommand(const std::string& commandName);
	std::string createClassNameForCommand(const std::string& commandName);

	//do this later
	void writeDefaultFileFormats();

	TGIDataHandler commandListInterface;
	
};
