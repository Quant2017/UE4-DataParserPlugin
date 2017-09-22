using System.IO;
using UnrealBuildTool;


public class LibXL : ModuleRules
{
    public LibXL(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Add the import library
            PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib", "Win64"));
            PublicAdditionalLibraries.Add("libxl.lib");
            
            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add("libxl.dll");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "lib", "Linux", "libxl.so"));
        }
    }
}
