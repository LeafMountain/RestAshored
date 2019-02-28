#include "TTEnergyComponent.h"
#include "Components/ActorComponent.h"
#include "UnrealMathUtility.h"
#include "Engine/World.h"
#include "../Eater/TTEdibleComponent.h"

void UTTEnergyComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentEnergy = MaxEnergy;
}

void UTTEnergyComponent::RegainEnergy(class UTTEdibleComponent* Edible)
{
	if (Edible == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("NOT EDIBLE"));
		return;
	}

	CurrentEnergy += Edible->GetFoodValue();
	Edible->GetBeingEaten();
}

void UTTEnergyComponent::SetCurrentEnergy(float Value)
{
	CurrentEnergy = Value;
}

void UTTEnergyComponent::AdjustCurrentEnergy(float Value)
{
	CurrentEnergy += Value;
	if (CurrentEnergy <= 0)
		OnToExhausted.Broadcast();
}
