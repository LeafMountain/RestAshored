// Fill out your copyright notice in the Description page of Project Settings.

#include "TTDayAndNight.h"
#include "CommandSystem/TTGameMode.h"
#include "Components/LightComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Curves/CurveVector.h"
#include "Components/SkyLightComponent.h"
#include "Engine/SkyLight.h"

// Sets default values
ATTDayAndNight::ATTDayAndNight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ATTDayAndNight::BeginPlay()
{
	Super::BeginPlay();
	//gameMode = CastChecked<ATTGameMode>(GetWorld()->GetAuthGameMode());
	sunLight = CastChecked<UDirectionalLightComponent>(sunLightActor->GetComponentByClass(UDirectionalLightComponent::StaticClass()));

	skyLightComponent = skylight->GetLightComponent();

	isInitialized = false;

	preTimer = 1.0f;
}

// Called every frame
void ATTDayAndNight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (preTimer > 0)
	{
		preTimer -= DeltaTime;
		return;
	}

	if (!isInitialized && !sunLightActor->IsActorInitialized() || !sunlightCurve->IsValidLowLevel()) return;

	if(!isInitialized)
		isInitialized = true;


	if (timeOfDay >= dayLength)
	{
		timeOfDay = 0;
		OnNewDay();
	}


	
	float sunTime = dayLength * sunPrecentage;
	float moonTime = dayLength - sunTime;

	if (day && timeOfDay > sunTime)
	{
		OnNightPassed();
		day = false;
	}
	else if(!day && timeOfDay < sunTime)
	{
		OnDayPassed();
		day = true;
	}

	float sunLerp = FMath::Clamp(timeOfDay / sunTime, 0.0f, 1.0f);
	float moonLerp = FMath::Clamp((timeOfDay - sunTime) / moonTime, 0.0f, 1.0f);

	if (sunLerp > KINDA_SMALL_NUMBER) 
	{
		FRotator sunRot(0, 0, 0);
		sunRot.Pitch = sunCurve->GetVectorValue(sunLerp).Y;
		sunRot.Yaw = sunCurve->GetVectorValue(sunLerp).Z;
		sunRot.Normalize();
		sunLightActor->SetActorRotation(sunRot);
	}
	if(moonLerp > KINDA_SMALL_NUMBER)
	{
		FRotator moonRot(0, 0, 0);
		moonRot.Pitch = sunCurve->GetVectorValue(moonLerp).Y;
		moonRot.Yaw = sunCurve->GetVectorValue(moonLerp).Z;
		moonRot.Normalize();
		sunLightActor->SetActorRotation(moonRot);
	}

	FLinearColor sunColor;
	FLinearColor moonColor;
	FLinearColor skylightColor;

	bool afterNoon = sunLerp > 0.5;
	bool afterMidnight = moonLerp > 0.5;

	FLinearColor color;

	if (day) 
	{
		skylightColor = FMath::Lerp((afterNoon ? SkyLightEveningColor : SkylightDawnColor), (afterNoon ? SkylightNoonColor : SkylightNoonColor), sunlightCurve->GetFloatValue(sunLerp));
		color = FMath::Lerp((afterNoon ? EveningColor : DawnColor), (afterNoon ? NoonColor : NoonColor), sunlightCurve->GetFloatValue(sunLerp));
	}
	else 
	{
		skylightColor = FMath::Lerp((afterMidnight ? SkylightDawnColor : SkyLightEveningColor), (afterMidnight ? SkyLightMidnightColor : SkyLightMidnightColor), moonlightCurve->GetFloatValue(moonLerp));
		color = FMath::Lerp((afterMidnight ? DawnColor : EveningColor), (afterMidnight ? MidnightColor : MidnightColor), moonlightCurve->GetFloatValue(moonLerp));
	}

	float light = 0;
	
	if (day)
	{
		float lightDif = sunLuminCap - sunLuminMin;
		light = sunLuminMin + sunlightCurve->GetFloatValue(sunLerp) * lightDif;
	}
	else
	{
		float lightDif = moonLuminCap - moonLuminMin;
		light = moonLuminMin + moonlightCurve->GetFloatValue(moonLerp) * lightDif;
	}


	
	skyLightComponent->SetLightColor(skylightColor);
	float skyLightDif = skylightIntensityCap - skylightIntensityMin;
	skyLightComponent->SetIntensity(skylightIntensityMin +((day ? sunlightCurve->GetFloatValue(sunLerp) : moonlightCurve->GetFloatValue(moonLerp)) *  skyLightDif));

	sunLight->SetLightColor(color);
	sunLight->SetIntensity(light);

	timeOfDay += DeltaTime;
}

