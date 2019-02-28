// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTCharacter.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class ETTAction : uint8
{
	Walk,
	Use,
	Eat,
	PickUp,
	Drop,
	Collect, 
	Craft,
	Stop,
	Repair,
	Store,
	Equip
};

USTRUCT(BlueprintType)
struct FActionAvailibility 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ETTAction Action;
	UPROPERTY(BlueprintReadOnly)
	bool IsNew;

	TArray<UTTInteractableComponent*> Interactables;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVisbilityEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionVisbilityEvent, ETTAction, actiontype);

UCLASS()
class GP2_TEAM3_API ATTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AddVisibleInteractable(class UTTInteractableComponent* interactable);

	UFUNCTION(BlueprintCallable)
	void RemoveVisibleInteractable(class UTTInteractableComponent* interactable);

	UFUNCTION(BlueprintCallable)
	void SetCraftinAvailable(bool available);


	UFUNCTION(BlueprintCallable)
	TArray<FActionAvailibility> GetAvailableActions();


	TArray<FActionAvailibility> GetUnavailableActions();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable)
	FVisbilityEvent OnVisibilityUpdate;

	UPROPERTY(BlueprintAssignable)
	FActionVisbilityEvent OnStopsbeingAvailable;
private:

	TMap<ETTAction, FActionAvailibility> visibleInteractions;

	void SetInteractability(UTTInteractableComponent* interactable, bool add);
	
	void AddActions(ETTAction action, class UTTInteractableComponent* interactable);


};
