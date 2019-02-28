// Fill out your copyright notice in the Description page of Project Settings.

#include "TTInteractableComponent.h"
#include "TTInteractorComponent.h"
#include "TTInventoryComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "CommandSystem/TTGameMode.h"
#include "CommandSystem/TTCommandSystem.h"
#include "../Equipment/TTEquiperComponent.h"
#include "../Equipment/TTEquipableComponent.h"

// Sets default values for this component's properties
UTTInteractableComponent::UTTInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


bool UTTInteractableComponent::HasNametag(const FName nametag)
{
	return speachTags.Contains(nametag);
}

FName UTTInteractableComponent::GetName()
{
	return (speachTags.Num() == 0? FName("NoName") : speachTags[0]);
}

void UTTInteractableComponent::SetName(FName name)
{
	speachTags.Add(name);
	AddNameToCommandSystem();
}

// Called when the game starts
void UTTInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	AddNameToCommandSystem();
}

void UTTInteractableComponent::AddNameToCommandSystem()
{
	ATTGameMode* correctGameMode = Cast<ATTGameMode>(GetWorld()->GetAuthGameMode());

	if (correctGameMode)
	{
		for (int i = 0; i < speachTags.Num(); i++)
		{
			//correctGameMode->GetCommandSystem()->AddInteractable(speachTags[i]);
			correctGameMode->AddInteractable(this);
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Using Wrong GameMode!"));
}

void UTTInteractableComponent::StopInteraction()
{
	DontInteractWithMe = true;
}

void UTTInteractableComponent::TickUpdate(UTTEquiperComponent* equiper, AActor* equipment, float deltaTime)
{
	OnUseTick.Broadcast(equiper, equipment, deltaTime);
}

TArray<FName> UTTInteractableComponent::GetSpeechTags()
{
	return speachTags;
}

void UTTInteractableComponent::Use(const UTTEquiperComponent* equiper, const UTTEquipableComponent* currentEquipment)
{
	DontInteractWithMe = false;
	OnUse.Broadcast(equiper, (currentEquipment != nullptr ? currentEquipment->GetOwner() : nullptr));
}

void UTTInteractableComponent::Punch(UTTInteractorComponent* interctor)
{
	OnGetPunched.Broadcast(interctor);
}

void UTTInteractableComponent::Hug(UTTInteractorComponent* interactor)
{
	OnGetHuged.Broadcast(interactor);
}

void UTTInteractableComponent::SpeakWith(UTTInteractorComponent* interactor)
{
	OnGetSpokenTo.Broadcast(interactor);
}

void UTTInteractableComponent::Call(UTTInteractorComponent* interactor)
{
	OnGetCalled.Broadcast(interactor);
}

void UTTInteractableComponent::Highfive(UTTInteractorComponent* interactor)
{
	OnGetHighfived.Broadcast(interactor);
}

void UTTInteractableComponent::Pat(UTTInteractorComponent* interactor)
{
	OnGetPated.Broadcast(interactor);
}

void UTTInteractableComponent::Anoy(UTTInteractorComponent* interactor)
{
	OnGetAnoyed.Broadcast(interactor);
}
