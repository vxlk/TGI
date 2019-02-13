// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TGIStyle.h"

class FTGICommands : public TCommands<FTGICommands>
{
public:

	FTGICommands()
		: TCommands<FTGICommands>(TEXT("TGI"), NSLOCTEXT("Contexts", "TGI", "TGI Plugin"), NAME_None, FTGIStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};