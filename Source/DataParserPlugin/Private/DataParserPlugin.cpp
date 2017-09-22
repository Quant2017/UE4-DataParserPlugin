// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DataParserPlugin.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"
//#include "xlnt/xlnt.hpp"
#include "DataParser.h"


#define LOCTEXT_NAMESPACE "FDataParserPluginModule"

void FDataParserPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
    // Get the base directory of this plugin
    FString BaseDir = IPluginManager::Get().FindPlugin("DataParserPlugin")->GetBaseDir();
    
    // Add on the relative location of the third party dll and load it
    FString LibraryPath;
#if PLATFORM_WINDOWS
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/LibXL/lib/Win64/libxl.dll"));
#elif PLATFORM_LINUX
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/LibXL/lib/Linux/libxl.so"));
#endif
    
    ParserHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ParserHandle)
	{
		// Call the test function in the third party library that opens a message box
		//ExampleLibraryFunction();
        /*FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryOk", "Load example third party library is OK"));
        UDataParser *dp = NewObject<UDataParser>(UDataParser::StaticClass());
        if (dp)
        {
            FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryOk", "Create UDataParser successed"));
            FString filePath = FPaths::Combine(*BaseDir, TEXT("demo.xlsx"));
            dp->ParseFile(FPaths::ConvertRelativePathToFull(filePath));
        }
        else
        {
            FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Create UDataParser failed"));
        }*/
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("DataParserPluginError", "Failed to load third party library"));
	}
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
