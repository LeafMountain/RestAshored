// Fill out your copyright notice in the Description page of Project Settings.

#include "TTCommandListenerComponent.h"
#include "GameFramework/GameMode.h"
#include "TTGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "TTCommandSystem.h"

FString GetVictoryEnumAsString(FVerbEnum EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("FVerbEnum"), true);
	if (!EnumPtr) return FString("Invalid");

	FString enumName = EnumPtr->GetNameByValue((int64)EnumValue).ToString();
	enumName.RemoveFromStart("FVerbEnum::CE_");

	return enumName;
}

// Called when the game starts
void UTTCommandListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	 //Add myself to the command system
	ATTGameMode* correctGameMode = Cast<ATTGameMode>(GetWorld()->GetAuthGameMode());

	if (correctGameMode)
		correctGameMode->GetCommandSystem()->AddUnit(this);
	else
		UE_LOG(LogTemp, Warning, TEXT("Using Wrong GameMode!"));
}

void UTTCommandListenerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		if (GetWorld())
		{
			ATTGameMode* correctGameMode = Cast<ATTGameMode>(GetWorld()->GetAuthGameMode());

			if (correctGameMode)
				correctGameMode->GetCommandSystem()->RemoveUnit(this);
		}
	}
}

void UTTCommandListenerComponent::SetListenerTag(FName name)
{
	ListenerTag = name;
}

void UTTCommandListenerComponent::TriggerCommand(FCommandStruct command)
{
	switch (command.Verb)
	{
	case FVerbEnum::CE_Unknown:
		OnUnknownCommand.Broadcast();
		break;
	case (FVerbEnum::CE_PickUp):
		OnPickUp.Broadcast(command.Verb, command.Object1, command.Object2);
		break;
	case (FVerbEnum::CE_Use):
		OnUse.Broadcast(command.Object1);
		break;
	case (FVerbEnum::CE_Drop):
		OnDrop.Broadcast(command.Object1);
		break;
	case (FVerbEnum::CE_Throw):
		OnThrow.Broadcast(command.Object1);
		break;
	case (FVerbEnum::CE_Eat):
		OnEat.Broadcast(command.Object1);
		break;
	case (FVerbEnum::CE_Go):
		OnGo.Broadcast(command.Object1);
		break;

	// Movement
	case (FVerbEnum::CE_GoTo):
		OnGoTo.Broadcast(command.Object1);
		break;
	case (FVerbEnum::CE_Turn):
		OnTurn.Broadcast(command.Object1);
		break;

	case (FVerbEnum::CE_Harvest):
		OnHarvest.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_Store:
		OnStore.Broadcast(command.Verb, command.Object1, command.Object2);
		break;
	case FVerbEnum::CE_Stop:
		OnStop.Broadcast();
		break;
	case FVerbEnum::CE_Craft:
		OnCraft.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_WhatsUp:
		OnWhatsUp.Broadcast();
		break;
	case FVerbEnum::CE_Build:
		OnBuild.Broadcast(command.Object1);
		break;

	// social
	case FVerbEnum::CE_Hug:
		OnHug.Broadcast(command.Object1);
		break;	
	case FVerbEnum::CE_Hit:
		OnHit.Broadcast(command.Object1);
		break;	
	case FVerbEnum::CE_Call:
		OnCall.Broadcast(command.Object1);
		break;	
	case FVerbEnum::CE_Highfive:
		OnHighFive.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_Assist:
		OnAssist.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_Speak:
		OnSpeak.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_Pat:
		OnPat.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_Annoy:
		OnAnnoy.Broadcast(command.Object1);
		break;
	case FVerbEnum::CE_Kill:
		OnKill.Broadcast(command.Object1);
		break;

	case FVerbEnum::CE_ScanArea:
		OnScan.Broadcast(command.Object1);
		break;

	case FVerbEnum::CE_Equip:
		OnEquip.Broadcast(command.Verb, command.Object1, command.Object2);
		break;

	}

	OnCommand.Broadcast(command.Verb, command.Object1);

	FString enumName = GetVictoryEnumAsString(command.Verb);
	FString	logMessage = "[CommandListerner] ";
	logMessage += ListenerTag.ToString() + ": " + enumName;

	if (command.Object1 != "")
		logMessage += " " + command.Object1;
	if (command.Object2 != "")
		logMessage += " and " + command.Object2;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *logMessage);
}

void UTTCommandListenerComponent::ClearCommand()
{
	commandInProgress.Verb = FVerbEnum::CE_Unknown;
	commandInProgress.Object1 = "";
	commandInProgress.Object2 = "";
}

void UTTCommandListenerComponent::Select()
{
	OnSelected.Broadcast();
	removeFirstCommand = true;
}

void UTTCommandListenerComponent::Deselect()
{
	OnDeselected.Broadcast();
}

void UTTCommandListenerComponent::AddCommand(FCommandStruct command)
{
	// A new verb has been found
	if (command.Verb != FVerbEnum::CE_Unknown)
	{
		// Clear command if a new verb has been received
		ClearCommand();
		commandInProgress.Verb = command.Verb;
	}

	// Add object 1 and 2
	if (commandInProgress.Verb != FVerbEnum::CE_Unknown)
	{
		commandInProgress.Object1 = command.Object1;
		commandInProgress.Object2 = command.Object2;
	}

	commandQueue.Add(commandInProgress);
	DoCommand();
}

void UTTCommandListenerComponent::AddCommandFirst(FCommandStruct command)
{
	commandQueue.Insert(command, 0);
	DoCommand();
}

void UTTCommandListenerComponent::AddCommandAndClear(FCommandStruct command)
{
	commandQueue.Empty();
	AddCommand(command);
}

void UTTCommandListenerComponent::RemoveFirstCommandInQueue()
{
	commandQueue.RemoveAt(0);
	commandQueue.Shrink();
}

void UTTCommandListenerComponent::DoCommand()
{
	// exit if command loop is already running
	if (GetWorld()->GetTimerManager().IsTimerActive(moveTimerHandle))
		return;

	FCommandStruct currentCommand = commandQueue[0];
	if (!removeFirstCommand)
	{
		TriggerCommand(currentCommand);
	}

	if (removeFirstCommand)
	{
		if (currentCommand.Verb == FVerbEnum::CE_Unknown)
		{
			ClearCommand();
			RemoveFirstCommandInQueue();
		}

		removeFirstCommand = false;
	}

	// Remove command if it's recognized as a complete command
	if (currentCommand.Object1 != "")
	{
		ClearCommand();
		RemoveFirstCommandInQueue();
	}
}

void UTTCommandListenerComponent::AddMoveCommand(FVector position)
{
	destination = position;
}
