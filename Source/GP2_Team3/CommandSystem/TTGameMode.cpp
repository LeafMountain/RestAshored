// Fill out your copyright notice in the Description page of Project Settings.

#include "TTGameMode.h"
#include "CommandSystem/TTCommandListenerComponent.h"
#include "TTCommandSystem.h"
#include "Components/Interaction/TTInteractableComponent.h"

void ATTGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetCommandSystem();
}

ATTCommandSystem* ATTGameMode::GetCommandSystem()
{
	if(!commandSystem)
		commandSystem = GetWorld()->SpawnActor<ATTCommandSystem>(ATTCommandSystem::StaticClass());

	return commandSystem;
}

void ATTGameMode::AddInteractable(class UTTInteractableComponent* interactable)
{
	interactables.Add(interactable);
	if (interactable->Waypoint)
		noRangeInteractables.Add(interactable);

	for(FName tag : interactable->GetSpeechTags())
		GetCommandSystem()->AddInteractable(tag);
}

TArray<UTTInteractableComponent*> ATTGameMode::GetInteractables()
{
	return interactables;
}

UTTInteractableComponent* ATTGameMode::GetInteractableByName(FName name)
{
	UTTInteractableComponent* _interactable = nullptr;

	for (UTTInteractableComponent* interactable : interactables)
	{
		if (interactable->HasNametag(name))
		{
			_interactable = interactable;
			break;
		}
	}
	
	return _interactable;
}

class TArray<UTTInteractableComponent*> ATTGameMode::GetInteractablesByName(FName name)
{
	TArray<UTTInteractableComponent*> foundInteractables;

	for (UTTInteractableComponent* interactable : interactables)
	{
		if (interactable->HasNametag(name))
		{
			foundInteractables.Add(interactable);
		}
	}

	return foundInteractables;
}

void ATTGameMode::AddExtraWord(FString word)
{
	ExtraWords.AddUnique(word);
	GetCommandSystem()->AddInteractable(FName(*word));
}
