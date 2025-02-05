// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PawnController : ModuleRules
{
	public PawnController(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
