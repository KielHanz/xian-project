// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TDFinals_TRNDD : ModuleRules
{
	public TDFinals_TRNDD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
