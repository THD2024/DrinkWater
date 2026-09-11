// Tian Handong

using UnrealBuildTool;
using System.Collections.Generic;

public class DrinkWaterTarget : TargetRules
{
	public DrinkWaterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "DrinkWater" } );
	}
}
