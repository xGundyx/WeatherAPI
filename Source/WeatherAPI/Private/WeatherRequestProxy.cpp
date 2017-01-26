// Fill out your copyright notice in the Description page of Project Settings.

#include "WeatherAPI.h"
#include "WeatherPlayerController.h"
#include "WeatherRequestProxy.h"

//grab a city by its unique city id
FString UWeatherRequestProxy::WeatherURL(TEXT("api.openweathermap.org/data/2.5/weather?id="));
FString UWeatherRequestProxy::APPID(TEXT("2d1a2df43d33199b67390cae843dc04e"));

UWeatherRequestProxy::UWeatherRequestProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PC = nullptr;
}

void UWeatherRequestProxy::GetWeatherForID(int32 ID)
{
	FString URL = FString::Printf(TEXT("%s%i&appid=%s&units=metric"), *WeatherURL, ID, *APPID);

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);

	HttpRequest->SetVerb("POST");

	//delegate
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UWeatherRequestProxy::OnProcessRequestComplete);

	//process
	HttpRequest->ProcessRequest();
}

void UWeatherRequestProxy::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Be sure that we have no data from previous response
	ResetResponseData();

	// Check we have result to process futher
	if (!bWasSuccessful)
	{
		// let the player know about this failed attempt
		if (PC)
		{
			ResponseJsonObj->SetNumberField(TEXT("code"), WEATHER_FAIL);
			PC->EventWeatherDataReceived(ResponseJsonObj);
		}

		return;
	}

	// Save response data as a string
	FString ResponseContent = Response->GetContentAsString();

	// Save response code as int32
	int32 ResponseCode = Response->GetResponseCode();

	// Try to deserialize data to JSON
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseContent);
	FJsonSerializer::Deserialize(JsonReader, ResponseJsonObj->GetRootObject());

	// Decide whether the request was successful
	bIsValidJsonResponse = bWasSuccessful && ResponseJsonObj->GetRootObject().IsValid();

	// Log errors
	if (!bIsValidJsonResponse)
	{
		if (!ResponseJsonObj->GetRootObject().IsValid())
		{
			// As we assume it's recommended way to use current class, but not the only one,
			// it will be the warning instead of error
			if (PC)
			{
				ResponseJsonObj->SetNumberField(TEXT("code"), WEATHER_INVALID);
				PC->EventWeatherDataReceived(ResponseJsonObj);
			}
		}
	}

	int32 code = int32(ResponseJsonObj->GetNumberField(TEXT("code")));

	//send the successfully read in data back to our player controller
	if (PC)
	{
		ResponseJsonObj->SetNumberField(TEXT("code"), WEATHER_SUCCESS);
		PC->EventWeatherDataReceived(ResponseJsonObj);
	}
}

void UWeatherRequestProxy::ResetResponseData()
{
	if (ResponseJsonObj != NULL)
	{
		ResponseJsonObj->Reset();
	}
	else
	{
		ResponseJsonObj = NewObject<UPlayFabJsonObject>();
	}

	bIsValidJsonResponse = false;
}