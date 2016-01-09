// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class PortFolioApp : ModuleRules
{
    private string AssimpPath
    {
        get { return Path.GetFullPath(@"D:\Personal Dev Projects\Tools\assimp-3.1.1-win-binaries"); } // TODO ; FIXME!!!!!!
    }

    public PortFolioApp(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
	    PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PublicAdditionalLibraries.Add(Path.Combine(AssimpPath, "lib64", "assimp.lib")); //TODO : FIXME MAYBE

        PublicIncludePaths.Add(Path.Combine(AssimpPath, "include"));
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        // if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        // {
        //		if (UEBuildConfiguration.bCompileSteamOSS == true)
        //		{
        //			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //		}
        // }
    }
}
