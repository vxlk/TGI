#pragma once

#include <string>

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

//generates a TGIType class that inherits from the base class
//**This generates a new cpp file
class TGITypeGenerator
{
public:
	void createType(const std::string& commandName);

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
	//TGIType* castToChildType(TGIType* base, const std::string& commandName);
	void createCPPFile(const std::string& commandName);
	bool canCreateCommand(const std::string& commandName);
};
