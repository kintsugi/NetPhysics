using System.IO;
using UnrealBuildTool;

public class SpaceFighter_client : ModuleRules
{
	private string ModulePath {
		get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
	}

    private string ThirdPartyPath {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    private bool LoadRakNet(TargetInfo Target) {
		bool isLibrarySupported = false;

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32)) {
			isLibrarySupported = true;

			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
			string LibrariesPath = Path.Combine(ThirdPartyPath, "RakNet", "lib");

			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "RakNet.lib"));

		}
		if (isLibrarySupported) {
			// Include path
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "RakNet", "include"));
		}
		Definitions.Add(string.Format("WITH_RAK_NET_BINDING={0}", isLibrarySupported ? 1 : 0));

		return isLibrarySupported;
	}

	public SpaceFighter_client(TargetInfo Target)
	{
        Definitions.Add(string.Format("CLIENT", 0));
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
        PrivateIncludePaths.Add(Path.GetFullPath("C:/dev/proj/TRAPEZOID/TRAPEZOIDDemos/SpaceFighter/server/src/SharedSrc"));
		LoadRakNet(Target);
	}
}
