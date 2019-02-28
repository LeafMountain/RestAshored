// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Color.h"
#include "TTDayAndNight.generated.h"


UCLASS()
class GP2_TEAM3_API ATTDayAndNight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTDayAndNight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	class ASkyLight* skylight;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float skylightIntensityCap;
	
	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float skylightIntensityMin;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float dayLength = 300;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float sunPrecentage;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	class UCurveVector * sunCurve;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor DawnColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor SkylightDawnColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor NoonColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor  SkylightNoonColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float sunLuminCap;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float sunLuminMin;

	UPROPERTY(EditInstanceOnly, Category = DayAndNightLight)
	AActor* sunLightActor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	class UCurveFloat * sunlightCurve;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor EveningColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor SkyLightEveningColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor MidnightColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	FLinearColor SkyLightMidnightColor;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float moonLuminCap;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	float moonLuminMin;

	UPROPERTY(EditAnywhere, Category = DayAndNightLight)
	class UCurveFloat * moonlightCurve;

	UFUNCTION(BlueprintImplementableEvent, Category = DayAndNightLight)
	void OnNewDay();

	UFUNCTION(BlueprintImplementableEvent, Category = DayAndNightLight)
	void OnDayPassed();

	UFUNCTION(BlueprintImplementableEvent, Category = DayAndNightLight)
	void OnNightPassed();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class ATTGameMode* gameMode;
	float timeOfDay;

	class UDirectionalLightComponent* sunLight;
	
	bool isInitialized;
	bool day;

	float preTimer = 0;

	USkyLightComponent* skyLightComponent;



};
