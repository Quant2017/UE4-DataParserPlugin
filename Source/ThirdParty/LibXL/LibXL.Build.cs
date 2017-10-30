using System.IO;
using UnrealBuildTool;


public class LibXL : ModuleRules
{
    public LibXL(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        
        bool isLibrarySupported = false;
        
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            isLibrarySupported = true;
            
            PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "bin", "Win64"));
            PublicAdditionalLibraries.Add("libxl.lib");
            PublicDelayLoadDLLs.Add("libxl.dll");
            
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ModuleDirectory, "bin", "Win64", "libxl.dll")));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            isLibrarySupported = true;
            
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", "Linux", "libxl.so"));
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "bin", "Linux", "libxl.so"));
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ModuleDirectory, "bin", "Linux", "libxl.so")));
        }
        
        Definitions.Add(string.Format("WITH_LIBXL_BINDING={0}", isLibrarySupported ? 1 : 0));
    }
}
