// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interaction/TTInteractableComponent.h"
#include "TTEquiperComponent.generated.h"

class UTTEquipableComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTEquiperComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTEquiperComponent();

protected:

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshSocket* equipmentSocket;

	UPROPERTY(BlueprintReadOnly)
	UTTEquipableComponent* currentEquipment;

public:	
	UFUNCTION(BlueprintCallable)
	bool Equip(UTTEquipableComponent* equipment);

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EInteractionAnimation> UseEqupment(UTTInteractableComponent* interactable);

	UFUNCTION(BlueprintCallable)
	float GetEquipmentRange();

	UFUNCTION(BlueprintCallable)
	void DropEquipment();

};
