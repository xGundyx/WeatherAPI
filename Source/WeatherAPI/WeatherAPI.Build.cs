// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WeatherAPI : ModuleRules
{
	public WeatherAPI(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "HTTP", "Json", "InputCore", "HeadMountedDisplay", "UnrealEd" });
	}
}
