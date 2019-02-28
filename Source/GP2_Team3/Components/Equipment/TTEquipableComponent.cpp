// Fill out your copyright notice in the Description page of Project Settings.

#include "TTEquipableComponent.h"
#include "TTEquiperComponent.h"

// Sets default values for this component's properties
UTTEquipableComponent::UTTEquipableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTTEquipableComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTTEquipableComponent::Drop( UTTEquiperComponent* equiper)
{
	OnDrop.Broadcast(equiper);
	if(CurrentOwner)
		CurrentOwner = nullptr;
}

void UTTEquipableComponent::Equip(UTTEquiperComponent* equiper)
{
	if(!CurrentOwner)
	{
		OnPickup.Broadcast(equiper);
		CurrentOwner = equiper->GetOwner();
	}
}

