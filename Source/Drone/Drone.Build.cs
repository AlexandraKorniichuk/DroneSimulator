// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Drone : ModuleRules
{
	public Drone(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		PublicIncludePaths.AddRange(new string[] {
			"Drone/Components",
			"Drone/UI",
			"Drone/AI",
			"Drone/Player"
		});
	}
}
