// LMGTestTask Huskov Illia

using UnrealBuildTool;
using System.Collections.Generic;

public class LMGTestTaskTarget : TargetRules
{
	public LMGTestTaskTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "LMGTestTask" } );
	}
}
