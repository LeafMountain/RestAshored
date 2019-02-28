#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Map.h"
#include "TTCrafterComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoneCrafting);

USTRUCT(BlueprintType)
struct FIngredientPair
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafter")
	FName DispayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafter")
	TSubclassOf<AActor> Ingredient;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafter")
	int Amount;
};

USTRUCT(BlueprintType)
struct FRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafter")
		TArray<FName> Name;

	bool IsthisMyName(FName name)
	{
		if(Name.Contains(name)) return true;
		return false;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafter")
	TArray<FIngredientPair> Ingridients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafter")
	TSubclassOf<AActor> CraftIntoThisObject;

	UPROPERTY()
		bool DoesThisCombine = false;
};

UCLASS(ClassGroup = (Crafter), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTCrafterComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	//virtual void BeginPlay() override;
public:

	virtual void BeginPlay() override;

	void AddNameToCommandSystem();

	UFUNCTION(BlueprintCallable, Category = "Crafter")
	TSubclassOf<AActor> CraftByInventory(class UTTInventoryComponent* inventory);
	UFUNCTION(BlueprintCallable, Category = "Crafter")
	TSubclassOf<AActor> CraftByName(class UTTInventoryComponent* inventory, FName RecipeName, bool consumeItems);
	UFUNCTION(BlueprintCallable, Category = "Crafter")
	TArray<FIngredientPair> WhatAmIMissing(UTTInventoryComponent* inventory, FName RecipeName);
	UPROPERTY(BlueprintAssignable, Category = "Crafter")
	FOnDoneCrafting OnDoneCrafting;

	UPROPERTY(EditAnywhere, Category = "Crafter")
	TArray<FRecipe> Recipes;

	int32 NumberOfIngredient(TArray<class UTTStoreableComponent*> listOfIngerdients, TSubclassOf<AActor> Ingredient);
};
