// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryEvent, const UTTStoreableComponent*, storeable);

class UTTStoreableComponent;

UCLASS( ClassGroup=(Interactable), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 size;

	UPROPERTY(EditAnywhere)
	TArray<UTTStoreableComponent*> inventory;

	class UTTInteractorComponent* interactor;

public:	

	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddToInventory(UTTStoreableComponent* item);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
	TArray<UTTStoreableComponent*> GetInventoryArray();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	FORCEINLINE int32 GetInventorySize() const {return inventory.Num(); }

	UFUNCTION(BlueprintCallable, Category = Inventor)
	UTTStoreableComponent* GetItem(int32 index);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
	UTTStoreableComponent* TakeItemFromInventorybyIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	UTTStoreableComponent* GetItemByName(const FName name);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
	UTTStoreableComponent* DropItemByName(FName name, FVector dropPosition);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveItemFromInventory(class UTTStoreableComponent* item);

	UPROPERTY(BlueprintAssignable)
	FInventoryEvent OnAddedItem;

	UPROPERTY(BlueprintAssignable)
	FInventoryEvent OnRemovedItem;
};
