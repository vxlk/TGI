<<<<<<< HEAD
#pragma once
/* This is the file that contains all of the custom code for a chat function
 ********************** THIS FILE IS AUTO-GENERATED ******************************
						ANY CODE WRITTEN OUTSIDE OF					  
						DESIGNATED AREAS IS PRONE TO
 *********************		   DELETION           ********************************
 */
#include "TGIType.h"
#include <iostream>

///keep the count before trigger code the responsibility of the user. trigger is called every time the 
///command is found.  What happens is not my responsibility, but the responsibility of the user who
///implements trigger eg private var count -> trigger() { if count == 5 then trigger }

//UPDATE AUTO-GEN!
class speedTypeClass : public TGIType 
{
public:
	speedTypeClass() : TGIType("speed")	{}
	virtual const std::string& getCommandName() const { return this->name; }
	virtual void trigger()
	{
		//Code that will be run when the command is triggered will go here
		std::cout << "hello world" << "\n";
	}
private:
	//std::string name;
};
class anotherCommandTypeClass : public TGIType 
{
public:
	anotherCommandTypeClass() : TGIType("anotherCommand")	{}
	virtual const std::string& getCommandName() const { return this->name; }
	virtual void trigger()
	{
		//Code that will be run when the command is triggered will go here
	}
private:
	//std::string name;
};
=======
#pragma once
/* This is the file that contains all of the custom code for a chat function
 ********************** THIS FILE IS AUTO-GENERATED ******************************
						ANY CODE WRITTEN OUTSIDE OF					  
						DESIGNATED AREAS IS PRONE TO
 *********************		   DELETION           ********************************
 */
#include "TGIType.h"
#include <iostream>

///keep the count before trigger code the responsibility of the user. trigger is called every time the 
///command is found.  What happens is not my responsibility, but the responsibility of the user who
///implements trigger eg private var count -> trigger() { if count == 5 then trigger }

//UPDATE AUTO-GEN!
class speedTypeClass : public TGIType 
{
public:
	speedTypeClass() : TGIType("speed")	{}
	virtual const std::string& getCommandName() const { return this->name; }
	virtual void trigger()
	{
		//Code that will be run when the command is triggered will go here
		std::cout << "hello world" << "\n";
	}
private:
	//std::string name;
};
class anotherCommandTypeClass : public TGIType 
{
public:
	anotherCommandTypeClass() : TGIType("anotherCommand")	{}
	virtual const std::string& getCommandName() const { return this->name; }
	virtual void trigger()
	{
		//Code that will be run when the command is triggered will go here
	}
private:
	//std::string name;
};
>>>>>>> 097491726b552982cadd880f08a3a46382d039d2
