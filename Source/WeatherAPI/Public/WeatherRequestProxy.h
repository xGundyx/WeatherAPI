// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WeatherAPI.h"
#include "WeatherRequestProxy.generated.h"

UENUM(BlueprintType)
enum ERequestError
{
	WEATHER_SUCCESS,	//success
	WEATHER_FAIL,		//generic fail attempt
	WEATHER_INVALID,	//invalid data returned
};

/**
 * 
 */
UCLASS()
class UWeatherRequestProxy : public UObject
{
	GENERATED_BODY()
	
public:
	UWeatherRequestProxy(const FObjectInitializer& ObjectInitializer);

	void GetWeatherForID(int32 ID);
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SetOwningPlayerController(class AWeatherPlayerController *OwnerPC) { PC = OwnerPC; }
	void ResetResponseData();

protected:
	UPROPERTY()
		UPlayFabJsonObject* ResponseJsonObj;

	UPROPERTY()
		UPlayFabJsonObject* RequestJsonObj;

	static FString WeatherURL;
	static FString APPID;

	bool bIsValidJsonResponse;

	class AWeatherPlayerController *PC;
};
