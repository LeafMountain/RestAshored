// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTEquipableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipEvent, const class UTTEquiperComponent*, equiper);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTEquipableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTEquipableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FEquipEvent OnDrop;
	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FEquipEvent OnPickup;
	UPROPERTY(EditAnywhere, Category = "Equipment")
	float Range;

	class AActor* CurrentOwner;

public:
	void Drop(class UTTEquiperComponent* equiper);
	void Equip(class UTTEquiperComponent* equiper);
};
