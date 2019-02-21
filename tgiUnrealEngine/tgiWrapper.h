#pragma once

#pragma once

#include "tgiCppApi.h"

using namespace System;

namespace TGI
{
	public ref class TGIWrapper
	{
	private:
		TGICppAPI_WIN* NativePtr;

	public:
		TGIWrapper()
		{
			NativePtr = new TGICppAPI_WIN;
		}

		~TGIWrapper()
		{
			delete NativePtr;
		}

		void start()
		{
			NativePtr->startPoll();
		}

		void stop()
		{
			NativePtr->closePoll();
		}

		void update()
		{
			NativePtr->update();
		}
	};
} //TGI Namespace