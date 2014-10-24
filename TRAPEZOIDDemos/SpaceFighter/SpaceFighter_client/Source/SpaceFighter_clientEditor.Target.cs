

using UnrealBuildTool;
using System.Collections.Generic;

public class SpaceFighter_clientEditorTarget : TargetRules
{
	public SpaceFighter_clientEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "SpaceFighter_client" } );
	}
}
