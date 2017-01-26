// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "WeatherAPI.h"
#include "WeatherPlayerController.generated.h"

#define WEATHER_UPDATE 30.0f		//update our weather data every 30 seconds

/**
 * 
 */
UCLASS()
class AWeatherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = Weather)
		void EventWeatherDataReceived(UPlayFabJsonObject *Obj);

	virtual void BeginPlay() override;						//called at actor creation, we will initialize our weather proxy here
	void TickWeather();										//update our weather info every WEATHER_UPDATE seconds

	UFUNCTION(BlueprintCallable, Category = Weather)
		FDateTime GetUnixTime(int32 UnixTime);

private:
	FTimerHandle WeatherTimer;

	//make sure this doesn't get garbage collected
	UPROPERTY()
		class UWeatherRequestProxy *WeatherManager;
};
