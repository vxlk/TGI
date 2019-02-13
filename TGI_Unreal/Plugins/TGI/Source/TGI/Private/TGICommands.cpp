// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TGICommands.h"

#define LOCTEXT_NAMESPACE "FTGIModule"

void FTGICommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TGI", "Bring up TGI window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
