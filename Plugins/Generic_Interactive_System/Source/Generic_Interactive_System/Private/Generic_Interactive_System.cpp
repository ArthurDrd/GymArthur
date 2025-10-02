// Copyright Epic Games, Inc. All Rights Reserved.

#include "Generic_Interactive_System.h"

#define LOCTEXT_NAMESPACE "FGeneric_Interactive_SystemModule"

void FGeneric_Interactive_SystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGeneric_Interactive_SystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGeneric_Interactive_SystemModule, Generic_Interactive_System)