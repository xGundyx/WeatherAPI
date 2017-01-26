// Fill out your copyright notice in the Description page of Project Settings.

#include "WeatherAPI.h"
#include "WeatherAPIHUD.h"
#include "WeatherGame.h"

AWeatherGame::AWeatherGame(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//set default pawn
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerControllerObject(TEXT("/Game/Weather/Character/Blueprints/WeatherPlayerController"));
	if (PlayerControllerObject.Object != NULL)
	{
		PlayerControllerClass = (UClass*)PlayerControllerObject.Object->GeneratedClass;
	}

	HUDClass = AWeatherAPIHUD::StaticClass();

	//GameStateClass = AWeatherGRI::StaticClass();
	//PlayerStateClass = AWeatherPRI::StaticClass();

	//this will keep players connected and keep their data persistent across map changes
	bUseSeamlessTravel = true;
}