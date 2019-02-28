// Fill out your copyright notice in the Description page of Project Settings.

#include "TTCharacter.h"
#include "Array.h"
#include "Components/Interaction/TTInteractableComponent.h"
#include "Components/Eater/TTEdibleComponent.h"
#include "Components/Equipment/TTStoreableComponent.h"

// Sets default values
ATTCharacter::ATTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATTCharacter::AddVisibleInteractable(UTTInteractableComponent* interactable)
{
	SetInteractability(interactable, true);
}

void ATTCharacter::RemoveVisibleInteractable(UTTInteractableComponent* interactable)
{
	SetInteractability(interactable, false);
}

void ATTCharacter::SetCraftinAvailable(bool available)
{
	if(available && visibleInteractions.Contains(ETTAction::Craft) || !available && !visibleInteractions.Contains(ETTAction::Craft)) return;

	if (!available && visibleInteractions.Contains(ETTAction::Craft))
	{
		visibleInteractions.Remove(ETTAction::Craft);
		OnStopsbeingAvailable.Broadcast(ETTAction::Craft);
	}
	else if (available && !visibleInteractions.Contains(ETTAction::Craft))
	{
		FActionAvailibility tempAction;
		tempAction.IsNew = true;
		tempAction.Action = ETTAction::Craft;
		visibleInteractions.Add(ETTAction::Craft, tempAction);
		OnVisibilityUpdate.Broadcast();
	}	
}

TArray<FActionAvailibility> ATTCharacter::GetAvailableActions()
{
	TArray<FActionAvailibility> tempActions;

	for (TPair<ETTAction, FActionAvailibility> pair : visibleInteractions)
	{
		FActionAvailibility tempAction = pair.Value;
		tempActions.Add(tempAction);
		pair.Value.IsNew = false;
	}


	return tempActions;
}
// Called every frame
void ATTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATTCharacter::SetInteractability(UTTInteractableComponent* interactable, bool add)
{
	if(interactable == nullptr || interactable->GetOwner() == nullptr) return;


	for (uint8 i = 0; i < (uint8)ETTAction::Equip ; i++)
	{
		if(!(1 << i & interactable->ActionTags)) continue;
		
		ETTAction currentAction = (ETTAction)i;

		if(add)
			AddActions(currentAction, interactable);
		else if(visibleInteractions.Contains(currentAction))
		{
			if(visibleInteractions[currentAction].Interactables.Contains(interactable))
				visibleInteractions[currentAction].Interactables.Remove(interactable);

			if (visibleInteractions[currentAction].Interactables.Num() == 0)
			{
				visibleInteractions.Remove(currentAction);
				OnStopsbeingAvailable.Broadcast(currentAction);
			}		
		}
	}

}

void ATTCharacter::AddActions(ETTAction action, UTTInteractableComponent* interactable)
{
	if (visibleInteractions.Contains(action))
		visibleInteractions[action].Interactables.Add(interactable);
	else 
	{
		FActionAvailibility tempAction;
		tempAction.Action = action;
		tempAction.IsNew = true;
		tempAction.Interactables.Add(interactable);
		visibleInteractions.Add(action, tempAction);
		OnVisibilityUpdate.Broadcast();
	}
}