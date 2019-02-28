#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTCommandData.h"
#include "NameTypes.h"
#include "TTCommandListenerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FListenerEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FListenerEventWithObject, const FString, object);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListenerCommandEvent, FVerbEnum, command, const FString, object);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FListenerCommandEvent_pos, FVector, position);

// Example:	"Get Rock"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommandEvent_VerbObject, const FString, object);
// Example:	"Combine Rock and Stick"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCommandEvent_VerbObjectObject, const FVerbEnum, verb, const FString, object1, const FString, object2);

UCLASS(Blueprintable, ClassGroup = (TTComponent), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTCommandListenerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	// Store last command
	FCommandStruct commandInProgress;

	FVector destination;
	bool transportingToDestination;

	TArray<FCommandStruct> commandQueue;

	void TriggerCommand(FCommandStruct command);
	void ClearCommand();

	// This is a temporary fix to let the player select the character without triggering unknown command
	bool removeFirstCommand;

public:	
	// The name of the unit
	UPROPERTY(EditAnywhere)
	FName ListenerTag = "NULLNULLNULLNULL";

	UFUNCTION(BlueprintCallable, Category = "TT Command")
	void SetListenerTag(FName name);


	// Trigger select event
	void Select();

	// Trigger deselect event
	void Deselect();

	void AddCommand(FCommandStruct command);
	void AddCommandFirst(FCommandStruct command);
	void AddCommandAndClear(FCommandStruct command);
	void RemoveFirstCommandInQueue();

	// Temp
	void DoCommand();

	UPROPERTY(BlueprintAssignable)
	FListenerEvent OnRequestPosition;


	// Move to position before doing the command
	UFUNCTION(BlueprintCallable)
	void AddMoveCommand(FVector position);

	//UFUNCTION(BlueprintCallable)
	//void CheckIfMoveDone();

	FTimerHandle moveTimerHandle;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEvent OnSelected;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEvent OnDeselected;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
		FListenerEvent OnUnknownCommand;

	// Storage
	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObjectObject OnPickUp;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObjectObject OnEquip;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObjectObject OnStore;

	// unsorted
	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnUse;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnDrop;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnThrow;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnEat;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnGo;


	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnHarvest;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnCraft;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnBuild;

	// Movement
	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnGoTo;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEventWithObject OnTurn;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEvent OnStop;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerEvent OnWhatsUp;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FListenerCommandEvent OnCommand;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObjectObject OnStoreIn;

	// Social
	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnHug;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnHit;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnHighFive;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnCall;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnSpeak;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnPat;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnAssist;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnAnnoy;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnKill;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObject OnScan;

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FCommandEvent_VerbObjectObject OnSpecial;
};




