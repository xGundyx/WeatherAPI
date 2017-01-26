// Fill out your copyright notice in the Description page of Project Settings.

#include "WeatherAPI.h"
#include "WeatherRequestProxy.h"
#include "WeatherPlayerController.h"

void AWeatherPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TickWeather();
}

void AWeatherPlayerController::TickWeather()
{
	//make sure our manager is initialized
	if (!WeatherManager)
	{
		WeatherManager = NewObject<UWeatherRequestProxy>();

		if (WeatherManager)
			WeatherManager->SetOwningPlayerController(this);
	}
	if(WeatherManager)
		WeatherManager->GetWeatherForID(6071618); //test id for Medicine Hat

	//set our weather timer
	GetWorldTimerManager().SetTimer(WeatherTimer, this, &AWeatherPlayerController::TickWeather, WEATHER_UPDATE, false);
}

FDateTime AWeatherPlayerController::GetUnixTime(int32 UnixTime)
{
	return FDateTime::FromUnixTimestamp(UnixTime);
}


