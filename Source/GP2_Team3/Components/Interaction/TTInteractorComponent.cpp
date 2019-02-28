// Fill out your copyright notice in the Description page of Project Settings.

#include "TTInteractorComponent.h"
#include "WorldCollision.h"
#include "TTInteractableComponent.h"
#include "Engine/EngineTypes.h"
#include "UObjectBaseUtility.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Array.h"
#include "../Equipment/TTEquipableComponent.h"
#include "CommandSystem/TTGameMode.h"
// Sets default values for this component's properties
UTTInteractorComponent::UTTInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTTInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	UWorld* world = GetWorld();
	gameMode = Cast<ATTGameMode>(world->GetAuthGameMode());
}


bool UTTInteractorComponent::CheckRange(FVector TargetPosition, float Range)
{
	FVector ThisActorLocation = GetOwner()->GetActorLocation();
	float DistanceToObject = FVector::Distance(TargetPosition, ThisActorLocation);
	return DistanceToObject < Range;
}

UTTInteractableComponent* UTTInteractorComponent::GetClosestInteractable(FName name, UTTEquipableComponent* equipment)
{
	float extraRange = (equipment != nullptr ? equipment->Range : 0);

	return GetObjectInRange(name, InteractionRange + extraRange);
}

UTTInteractableComponent* UTTInteractorComponent::GetClosestVisible (FName name)
{
	return GetObjectInRange(name, ViewRange);
}

UTTInteractableComponent* UTTInteractorComponent::GetObjectInRange(FName name, float Range)
{
	FCollisionShape collisonShape;
	collisonShape.SetSphere(Range);

	TArray<FOverlapResult> overlapResults;

	GetWorld()->OverlapMultiByChannel(overlapResults, GetOwner()->GetActorLocation(), FQuat::Identity, InteractableChannel, collisonShape);

	if(overlapResults.Num() < 1 ) return nullptr;

	TArray<TPair<UTTInteractableComponent*, float>> objectsInRange;
	float distToObject = Range;

	// Add waypoints to objectsInRange
	for (UTTInteractableComponent* interactable : gameMode->noRangeInteractables)
	{
		if(interactable->HasNametag(name))
			objectsInRange.Add(TPair<UTTInteractableComponent*, float>(interactable, 0));
	}

	for (FOverlapResult overlap : overlapResults)
	{	
		if(overlap.GetActor()->GetComponentByClass(UTTInteractableComponent::StaticClass()) == nullptr)
			continue;

		UTTInteractableComponent* interactable = CastChecked<UTTInteractableComponent>(overlap.GetActor()->GetComponentByClass(UTTInteractableComponent::StaticClass()));
		if(interactable->HasNametag(name))
			objectsInRange.Add(TPair<UTTInteractableComponent*, float>(interactable, FVector::DistSquared(interactable->GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation())));
	}


	objectsInRange.Sort([](const TPair<UTTInteractableComponent*, float>& A, const TPair<UTTInteractableComponent*, float>& B) { return A.Value < B.Value; });

	if(objectsInRange.Num() > 0)
		return objectsInRange[0].Key;

	return nullptr;
}

TArray<UTTInteractableComponent*> UTTInteractorComponent::GetAllInteractablesInView()
{
	TArray<UTTInteractableComponent*> interactables;

	FCollisionShape collisonShape;
	collisonShape.SetSphere(ViewRange);

	TArray<FOverlapResult> overlapResults;

	GetWorld()->OverlapMultiByChannel(overlapResults, GetOwner()->GetActorLocation(), FQuat::Identity, InteractableChannel, collisonShape);

	if (overlapResults.Num() < 1) return interactables;

	TArray<TPair<UTTInteractableComponent*, float>> objectsInRange;
	float distToObject = ViewRange;

	for (FOverlapResult overlap : overlapResults)
	{

		if (overlap.GetActor()->GetComponentByClass(UTTInteractableComponent::StaticClass()) == nullptr)
			continue;

		UTTInteractableComponent* interactable = CastChecked<UTTInteractableComponent>(overlap.GetActor()->GetComponentByClass(UTTInteractableComponent::StaticClass()));
		interactables.Add(interactable);
	}

	return interactables;
}

UTTInteractableComponent* UTTInteractorComponent::GetInteractableNoRange(FName name)
{
	if (gameMode)
	{
		return gameMode->GetInteractableByName(name);
	}
	return nullptr;
}

UTTInteractableComponent* UTTInteractorComponent::FindInteractable(FName name, float range)
{
	UTTInteractableComponent* closestInteractable = nullptr;


	if (gameMode)
	{
		TArray<UTTInteractableComponent*> interactables = gameMode->GetInteractablesByName(name);
		FVector actorPosition = GetOwner()->GetActorLocation();
		float distance = 99999;

		for (UTTInteractableComponent* interactable : interactables)
		{
			FVector interactablePosition = interactable->GetOwner()->GetActorLocation();
			if (float _distance = FVector::Distance(actorPosition, interactablePosition) <= range && _distance < distance)
			{
				closestInteractable = interactable;
			}
		}
	}

	return closestInteractable;
}

UTTInteractableComponent* UTTInteractorComponent::GetRanomInteractableInView()
{
	TArray<UTTInteractableComponent*> interactables = GetAllInteractablesInView();
	int32 length = interactables.Num();

	if(length <= 0)
		return nullptr;

	return interactables[FMath::RandRange(0, length - 1)];
}

