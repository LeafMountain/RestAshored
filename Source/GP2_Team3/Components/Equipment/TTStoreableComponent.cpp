// Fill out your copyright notice in the Description page of Project Settings.

#include "TTStoreableComponent.h"
#include "../Interaction/TTInteractableComponent.h"

// Sets default values for this component's properties
UTTStoreableComponent::UTTStoreableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTTStoreableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTTStoreableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

class UTTInteractableComponent* UTTStoreableComponent::GetInteractable()
{
	if (interactable == nullptr) {
		 UActorComponent* tempComp =  GetOwner()->GetComponentByClass(UTTInteractableComponent::StaticClass());
		 interactable = (tempComp != nullptr ?  CastChecked<UTTInteractableComponent>(tempComp) : nullptr);
	}
		
	return interactable;
}

