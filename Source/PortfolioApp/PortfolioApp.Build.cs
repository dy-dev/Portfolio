// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class PortfolioApp : ModuleRules
{
    //private string AssimpPath
    //{
    //    get { return Path.GetFullPath(@"D:\Personal Dev Projects\Tools\assimp-3.1.1-win-binaries"); } // TODO ; FIXME!!!!!!
    //}

    //private string AssimpStaticPath
    //{
    //    get { return Path.GetFullPath(@"D:\Personal Dev Projects\PortfolioApp\Binaries\Win64"); } // TODO ; FIXME!!!!!!
    //}

    public PortfolioApp(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "MediaAssets", "UMG", "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateDependencyModuleNames.AddRange(new string[] { "ProceduralMeshComponent" });
        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        PublicIncludePaths.AddRange(new string[] { "MediaAssets/Public", });
        PrivateIncludePathModuleNames.AddRange(new string[] { "Media", });
        //PublicAdditionalLibraries.Add(Path.Combine(AssimpPath, "lib64", "assimp.lib")); //TODO : FIXME MAYBE
        //PublicAdditionalLibraries.Add(Path.Combine(AssimpStaticPath, "assimp.lib"));
        //PublicIncludePaths.Add(Path.Combine(AssimpPath, "include"));
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
