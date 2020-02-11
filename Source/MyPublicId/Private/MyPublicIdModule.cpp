// Copyright 2019 MyPublicId LLC. All Rights Reserved.

#include "MyPublicIdModule.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif // WITH_EDITOR
#include "MyPublicId/MyPublicIdSettings.h"

#define LOCTEXT_NAMESPACE "FMyPublicIdModule"

void FMyPublicIdModule::StartupModule()
{
#if WITH_EDITOR
	// register settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "MyPublicId",
			LOCTEXT("PersonalitySettingsName", "MyPublicId"),
			LOCTEXT("PersonalitySettingsDescription", "Configure the MyPublicId plugin."),
			GetMutableDefault<UMyPublicIdSettings>()
		);

		if (SettingsSection.IsValid())
		{
			HandleModifiedSettings();
			SettingsSection->OnModified().BindRaw(this, &FMyPublicIdModule::HandleModifiedSettings);
		}
	}
#endif // WITH_EDITOR
}

void FMyPublicIdModule::ShutdownModule()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "MyPublicId");
	}
#endif
}

bool FMyPublicIdModule::HandleModifiedSettings()
{
	UMyPublicIdSettings* Settings = GetMutableDefault<UMyPublicIdSettings>();

	Settings->SaveConfig();

	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPublicIdModule, MyPublicId)