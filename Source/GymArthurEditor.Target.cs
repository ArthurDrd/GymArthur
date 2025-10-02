// // Copyright (c) 2025, Arthur Durand. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GymArthurEditorTarget : TargetRules
{
	public GymArthurEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "GymArthur" } );
	}
}
