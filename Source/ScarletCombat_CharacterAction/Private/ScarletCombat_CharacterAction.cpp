// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScarletCombat_CharacterAction.h"

#define LOCTEXT_NAMESPACE "FScarletCombat_CharacterActionModule"

void FScarletCombat_CharacterActionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FScarletCombat_CharacterActionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FScarletCombat_CharacterActionModule, ScarletCombat_CharacterAction)