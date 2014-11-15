// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using System;
using UnrealBuildTool;

public class NetPhysicsClient : ModuleRules
{
    //Path of this module
    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    //Path of project's third party path for external libs
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    //Loads the RakNet libs
    private bool LoadRakNet(TargetInfo Target)
    {
        bool isLibrarySupported = false;
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;
            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "RakNet", "lib");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "RakNet.lib"));
        }
        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "RakNet", "include"));
        }
        Definitions.Add(string.Format("WITH_RAK_NET_BINDING={0}", isLibrarySupported ? 1 : 0));
        return isLibrarySupported;
    }


    public NetPhysicsClient(TargetInfo Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        //#define CLIENT
        Definitions.Add("CLIENT");
        //#define PROJECT_HEADER_H

        //Directory for shared source with the server project
        PrivateIncludePaths.Add(Path.Combine(ModulePath, "../../../NetPhysicsServer/Source/XSource"));
        //Loads RakNet
        LoadRakNet(Target);

        //Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using internet features
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
