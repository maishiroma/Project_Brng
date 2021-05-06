// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Brng_Source : ModuleRules
{
	public Brng_Source(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" , "UMG", "Slate", "SlateCore"});
	}
}
