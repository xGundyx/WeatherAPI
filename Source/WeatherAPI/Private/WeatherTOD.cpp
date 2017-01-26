// Fill out your copyright notice in the Description page of Project Settings.

#include "WeatherAPI.h"
#include "WeatherTOD.h"


void AWeatherTOD::PostLoad()
{
	ALight::PostLoad();

	PrimaryActorTick.bCanEverTick = true;

	LightComponent->SetMobility(EComponentMobility::Movable);
}

#if WITH_EDITOR
void AWeatherTOD::LoadedFromAnotherClass(const FName& OldClassName)
{
}

void AWeatherTOD::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
}
#endif

void AWeatherTOD::SetTOD(FDateTime CurrentTime)
{
	//find our sun's pitch based on the sunrise and sunset
	FRotator rot = GetActorRotation();

	bool bNight = CurrentTime <= Sunrise || CurrentTime >= Sunset;

	//86000 seconds in 24 hours
	int32 Seconds = 1;
	int32 SecondsTillChange = 1;

	if (bNight)
	{
		Seconds = 86000 - (Sunset - Sunrise).GetTotalSeconds();
		SecondsTillChange = (Sunrise - CurrentTime).GetTotalSeconds();
	}
	else
	{
		Seconds = (Sunset - Sunrise).GetTotalSeconds();
		SecondsTillChange = (Sunset - CurrentTime).GetTotalSeconds();
	}

	float Ratio = float(SecondsTillChange) / float(Seconds);
	float Pitch = 180.0f * Ratio * (bNight ? 1.0f : -1.0f);

	rot.Pitch = Pitch;
	SetActorRotation(rot);

	//tell the blueprint about this
	EventTODUpdated();
}