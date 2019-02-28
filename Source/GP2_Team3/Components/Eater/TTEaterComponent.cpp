#include "TTEaterComponent.h"
#include "TTEdibleComponent.h"
#include "Components/ActorComponent.h"
#include "UnrealMathUtility.h"
#include "Engine/World.h"


void UTTEaterComponent::BeginPlay()
{
	Super::BeginPlay();
	Hunger = MaxHunger;
}

void UTTEaterComponent::EatFood(UTTEdibleComponent* Edible)
{
	if (Edible == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NOT EDIBLE"));
		return;
	}

	Hunger += Edible->GetFoodValue();
	Edible->GetBeingEaten();	
}

void UTTEaterComponent::SetCurrentHunger(float Value)
{
	Hunger = Value;
}

void UTTEaterComponent::AdjustCurrentHunger(float Value)
{
	Hunger = FMath::Clamp(Hunger + Value, 0.0f, MaxHunger);
	if(Hunger <= 0)
		OnToHungry.Broadcast();
}



