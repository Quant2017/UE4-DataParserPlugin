// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DataParserPlugin.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"


#define LOCTEXT_NAMESPACE "FDataParserPluginModule"

void FDataParserPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
//#if (WITH_LIBXL_BINDING == 1)
    // Get the base directory of this plugin
    FString BaseDir = IPluginManager::Get().FindPlugin("DataParserPlugin")->GetBaseDir();
    
    // Add on the relative location of the third party dll and load it
    FString LibraryPath;
#if PLATFORM_WINDOWS
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/LibXL/bin/Win64/libxl.dll"));
#elif PLATFORM_LINUX
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/LibXL/bin/Linux/libxl.so"));
#endif

    
    ParserHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (!ParserHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("DataParserPluginError", "Failed to load third party library"));
	}
//#endif
}

void FDataParserPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    
    // Free the dll handle
	FPlatformProcess::FreeDllHandle(ParserHandle);
	ParserHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDataParserPluginModule, DataParserPlugin)
