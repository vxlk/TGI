#pragma once
/* This is the file that contains all of the custom code for a chat function
 ********************** THIS FILE IS AUTO-GENERATED ******************************
						ANY CODE WRITTEN OUTSIDE OF					  
						DESIGNATED AREAS IS PRONE TO
 *********************		   DELETION           ********************************
 */

#include "tgiGeneratedTypes.h"
//#include "tgiVector.h"


/*
The data structure that holds the list of all the children of TGIType : ie all commands registered in the system
use regular vector for now...
*/

struct TypeList
{
	TypeList()
	{
		//List of types -> casted to each child
		types.push_back(dynamic_cast<speedTypeClass*>(new TGIType()));
	}

	~TypeList()
	{
		for (int i = 0; i < types.size(); ++i)
			types.pop_back();
	}

	bool operator==(const TypeList&) = delete;
	TypeList operator=(const TypeList&) = delete;


	static const std::vector<TGIType*> getTypeList() { return types; }
private:
	static std::vector<TGIType*> types;
};
