#pragma once
/* This is the file that contains all of the custom code for a chat function
 ********************** THIS FILE IS AUTO-GENERATED ******************************
						ANY CODE WRITTEN OUTSIDE OF					  
						DESIGNATED AREAS IS PRONE TO
 *********************		   DELETION           ********************************
 */
#include "TGIType.h"

/*Below is each custom "Type"*/

//casting is temporarily disabled

class speedTypeClass
{
public:
	speedTypeClass(const std::string& _name)
	{
		name = _name;
		//castString = dynamic_cast<TGIType*>(speedTypeClass);
	}
	virtual TGIType* castToChildType(TGIType* typeToBeCasted) {}
	virtual void trigger() {}
private:
	std::string name;
	std::string castString;
};
