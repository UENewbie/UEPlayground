// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEPlayground : ModuleRules
{
	public UEPlayground(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
