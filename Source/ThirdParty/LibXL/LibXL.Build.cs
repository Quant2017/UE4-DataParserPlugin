using System.IO;
using UnrealBuildTool;


public class LibXL : ModuleRules
{
    public LibXL(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        
        bool isLibrarySupported = false;
        string platform = "";
        string libname = "";
        string dllname = "";
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            isLibrarySupported = true;
            platform = "Win64";
            libname = "libxl.lib";
            dllname = "libxl.dll";
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            isLibrarySupported = true;
            platform = "Linux";
            libname = "libxl.so";
            dllname = "libxl.so";
        }
        
        if (isLibrarySupported)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

            PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "bin", platform));
            PublicAdditionalLibraries.Add(libname);
            PublicDelayLoadDLLs.Add(dllname);

            /*PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "bin", platform, libname));
            
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "bin", platform, dllname));*/
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ModuleDirectory, "bin", platform, dllname)));
        }
        
        Definitions.Add(string.Format("WITH_LIBXL_BINDING={0}", isLibrarySupported ? 1 : 0));
    }
}
