// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "TTFireLight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTFireLight : public UPointLightComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTFireLight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = FireLight)
	class UCurveFloat * LerpCurve;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D IncreaseSpeed;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D DecreaseSpeed;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D MaxLightOuterRadius;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D MinLightOuterRadius;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D MinLightInnerRadius;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D MaxLighInnerRadius;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D MaxLightIntencity;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FVector2D MinLightIntencity;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FLinearColor MaxLightColor;

	UPROPERTY(EditAnywhere, Category = FireLight)
	FLinearColor MinLightColor;

	UPROPERTY(EditAnywhere, Category = FireLight)
	float RandomRadius;

private:

	float timer;
	float currentTime;
	bool movingUp;

	float currentMaxOuterRaduis;
	float currenMinOuterRadius;

	float currentMaxInnerRaduis;
	float currentMinInnerRadius;

	float currentMaxIntencity;
	float currenMinIntencity;

	FVector startPos;
	FVector currentDirectionPos;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	void SetRandomvalues();
};
