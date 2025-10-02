// // Copyright (c) 2025, Arthur Durand. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GymArthurTarget : TargetRules
{
	public GymArthurTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GymArthur" } );
	}
}
