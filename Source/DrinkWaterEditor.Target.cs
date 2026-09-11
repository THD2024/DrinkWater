// Tian Handong

using UnrealBuildTool;
using System.Collections.Generic;

public class DrinkWaterEditorTarget : TargetRules
{
	public DrinkWaterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "DrinkWater" } );
	}
}
