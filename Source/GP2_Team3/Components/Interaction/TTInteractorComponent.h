// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTInteractorComponent.generated.h"
UENUM(BlueprintType)
enum class EUsageType : uint8
{
	Use, Pickup, Drop, Eat
};

UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTTInteractorComponent();

	UPROPERTY(EditDefaultsOnly)
		TEnumAsByte<ECollisionChannel>InteractableChannel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
		float InteractionRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
		float ViewRange;

	class ATTGameMode* gameMode;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool CheckRange(FVector TargetPosition, float Range);

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	class UTTInteractableComponent* GetClosestInteractable(FName name, class UTTEquipableComponent* equipment);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	class UTTInteractableComponent* GetClosestVisible(FName name);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	class UTTInteractableComponent* GetRanomInteractableInView();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	TArray<class UTTInteractableComponent*> GetAllInteractablesInView();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		class UTTInteractableComponent* GetInteractableNoRange(FName name);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		class UTTInteractableComponent* FindInteractable(FName name, float range);


private:
	class UTTInteractableComponent* GetObjectInRange(FName name, float Range);

};
