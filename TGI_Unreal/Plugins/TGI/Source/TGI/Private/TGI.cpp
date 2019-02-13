// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TGI.h"
#include "TGIStyle.h"
#include "TGICommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "TGI/tgiCppAPI.h"

static const FName TGITabName("TGI");

#define LOCTEXT_NAMESPACE "FTGIModule"

void FTGIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTGIStyle::Initialize();
	FTGIStyle::ReloadTextures();

	FTGICommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	Tgi = MakeShareable(new TGIUnrealAPI);

	PluginCommands->MapAction(
		FTGICommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTGIModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FTGIModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FTGIModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TGITabName, FOnSpawnTab::CreateRaw(this, &FTGIModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTGITabTitle", "TGI"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTGIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FTGIStyle::Shutdown();

	FTGICommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TGITabName);

	Tgi.Get()->closePoll();
	Tgi.Reset();
	//Tgi->closePoll();
	//Tgi = nullptr;
}

TSharedRef<SDockTab> FTGIModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	if (!Tgi.Get())
		Tgi = MakeShareable(new TGIUnrealAPI);
	Tgi.Get()->startPoll();

	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTGIModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TGI.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];

}

void FTGIModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(TGITabName);
	
}

void FTGIModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FTGICommands::Get().OpenPluginWindow);
}

void FTGIModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FTGICommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTGIModule, TGI)