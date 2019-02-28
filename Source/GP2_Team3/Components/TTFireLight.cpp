// Fill out your copyright notice in the Description page of Project Settings.

#include "TTFireLight.h"
#include "Curves/CurveFloat.h"

// Sets default values for this component's properties
UTTFireLight::UTTFireLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTTFireLight::BeginPlay()
{
	Super::BeginPlay();
	
	movingUp = true;
	startPos = GetRelativeTransform().GetLocation();
	SetRandomvalues();

}


// Called every frame
void UTTFireLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (movingUp && timer > currentTime)
	{
		movingUp = false;
		SetRandomvalues();
	}
	else if (!movingUp && timer <= 0) 
	{
		movingUp = true;
		SetRandomvalues();
	}

	float lerpValue = LerpCurve->GetFloatValue(timer / currentTime);

	SetAttenuationRadius(FMath::Lerp(currenMinOuterRadius, currentMaxOuterRaduis, lerpValue));
	SetSourceRadius(FMath::Lerp(currentMinInnerRadius, currentMaxInnerRaduis, lerpValue));
	SetIntensity(FMath::Lerp(currenMinIntencity, currentMaxIntencity, lerpValue));
	SetLightColor(FMath::Lerp(MinLightColor, MaxLightColor, lerpValue));

	SetRelativeLocation(FMath::Lerp(startPos, currentDirectionPos, lerpValue));

	timer += movingUp ? DeltaTime : -DeltaTime;


}

void UTTFireLight::SetRandomvalues()
{
	if (movingUp)
	{
		FVector2D newPos = FMath::RandPointInCircle(RandomRadius);
		currentDirectionPos = FVector(startPos.X + newPos.X, startPos.Y + newPos.Y, startPos.Z + FMath::RandRange(-RandomRadius, RandomRadius));
		currentMaxOuterRaduis = FMath::RandRange(MaxLightOuterRadius.X, MaxLightOuterRadius.Y);
		currentMaxInnerRaduis = FMath::RandRange(MaxLighInnerRadius.X, MaxLighInnerRadius.Y);
		currentMaxIntencity = FMath::RandRange(MaxLightIntencity.X, MaxLightIntencity.Y);
		currentTime = FMath::RandRange(IncreaseSpeed.X, IncreaseSpeed.Y);
	}
	else
	{
		currenMinOuterRadius = FMath::RandRange(MinLightOuterRadius.X, MinLightOuterRadius.Y);
		currentMinInnerRadius = FMath::RandRange(MinLightInnerRadius.X, MinLightInnerRadius.Y);
		currenMinIntencity = FMath::RandRange(MinLightIntencity.X, MinLightIntencity.Y);;
		currentTime = FMath::RandRange(DecreaseSpeed.X, DecreaseSpeed.Y);
		timer = currentTime;
	}

}
