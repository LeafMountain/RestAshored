// Fill out your copyright notice in the Description page of Project Settings.

#include "TTEquiperComponent.h"
#include "Components/Interaction/TTInteractableComponent.h"
#include "Array.h"
#include "Components/Interaction/TTInteractorComponent.h"
#include "TTEquipableComponent.h"

// Sets default values for this component's properties
UTTEquiperComponent::UTTEquiperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UTTEquiperComponent::Equip(UTTEquipableComponent* equipment) //bool
{
	if(equipment->CurrentOwner != nullptr)
		return false;

	if (currentEquipment != equipment) {
		DropEquipment();
	}
	//	equipmentSocket->AddObject
	currentEquipment = equipment;
	if(currentEquipment != nullptr)
		currentEquipment->Equip(this);
	return true;
}

TEnumAsByte<EInteractionAnimation> UTTEquiperComponent::UseEqupment(UTTInteractableComponent* interactable)
{
	interactable->Use(this, currentEquipment);
	return interactable->UsageAnimation;
}

float UTTEquiperComponent::GetEquipmentRange()
{
	return currentEquipment != nullptr ? currentEquipment->Range : 5;
}

void UTTEquiperComponent::DropEquipment()
{
	if(currentEquipment != nullptr)
		currentEquipment->Drop(this);

	currentEquipment = nullptr;
}
