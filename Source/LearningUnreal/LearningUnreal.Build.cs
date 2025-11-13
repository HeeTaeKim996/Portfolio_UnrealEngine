// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LearningUnreal : ModuleRules
{
	public LearningUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",

		"EnhancedInput", "GameplayTags",

		"NavigationSystem"/*Navigation(TopDown)*/, "AIModule"/*AI*/ , "Niagara"/*CursorEffect*/, "UMG"/*UI*/,

		"GameplayAbilities" /*GAS*/, "GameplayTasks"/*GAS*/,

		"ModuleTest",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { "LearningUnreal" });
	}
}
