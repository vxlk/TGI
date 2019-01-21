#pragma once
/* This is the file that contains all of the custom code for a chat function
 ********************** THIS FILE IS AUTO-GENERATED ******************************
						ANY CODE WRITTEN OUTSIDE OF					  
						DESIGNATED AREAS IS PRONE TO
 *********************		   DELETION           ********************************
 */
#include "TGIType.h"

/*Below is each custom "Type"*/
class speedTypeClass : public TGIType 
{
public:
	speedTypeClass() : name("speed") {}
	virtual void trigger() 
	{
		//Code that will be run when the command is triggered will go here
	}
private:
	std::string name;
};

/*
The data structure that holds the list of all the children of TGIType : ie all commands registered in the system
*/
struct typeList
{
	typeList()
	{
		//List of types -> casted to each child
		types.push_back(dynamic_cast<speedTypeClass*>(new speedTypeClass()));
	}

	static const std::vector<TGIType*> getTypeList() { return types; }
private:
	static std::vector<TGIType*> types;
};