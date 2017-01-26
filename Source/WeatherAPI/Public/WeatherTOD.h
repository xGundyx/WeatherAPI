// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DirectionalLight.h"
#include "WeatherTOD.generated.h"

/**
 * 
 */
UCLASS()
class WEATHERAPI_API AWeatherTOD : public ADirectionalLight
{
	GENERATED_BODY()
	
public:
	virtual void PostLoad() override;
	
#if WITH_EDITOR
	virtual void LoadedFromAnotherClass(const FName& OldClassName) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	//allow blueprints to set our current time
	UFUNCTION(BlueprintCallable, Category = Weather)
		void SetTOD(FDateTime CurrentTime);

	//init with sunrise and sunset data
	UFUNCTION(BlueprintCallable, Category = Weather)
		void Init(FDateTime Rise, FDateTime Set) { Sunrise = Rise; Sunset = Set; }

	UFUNCTION(BlueprintImplementableEvent, Category = Weather)
		void EventTODUpdated();

private:
	FDateTime Sunrise;
	FDateTime Sunset;
};
