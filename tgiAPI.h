#pragma once

/*

Tyler Small

*/
#pragma once
#include <string>
#include "PhantomBot.h"

//#include "../PhantomBot.h"

namespace tgiAPI
{
		// First a Forward Declaration to Cpp::Logic class:
		//class PhantomBot; // This allows us to mention it in this header file
					 // without actually including the native version of Logic.h

		namespace CLI
		{
			// Next is the managed wrapper of Logic:
			public ref class tgiApp
			{
			public:
				// Managed wrappers are generally less concerned 
				// with copy constructors and operators, since .NET will
				// not call them most of the time.
				// The methods that do actually matter are:
				// The constructor, the "destructor" and the finalizer
				tgiApp();
				~tgiApp();
				!tgiApp();

				int createInstance();
				const PhantomBot* getInstance();
				void closeInstance();

				void botInit();
				std::string editConfigFile(/*args*/);

				/*
				//do later
				std::string editCommand();
				std::string addCommand();
				std::string deleteCommand();
				std::string getCommandList();
				*/
			private:
				// Pointer to our implementation
				PhantomBot* _impl;
			};
		}
}
