#include "TTCrafterComponent.h"
#include "Engine/World.h"
#include "Map.h"
#include "CommandSystem/TTGameMode.h"
#include "CommandSystem/TTCommandSystem.h"
#include "../Equipment/TTStoreableComponent.h"
#include "../Interaction/TTInventoryComponent.h"
#include "SubclassOf.h"



void UTTCrafterComponent::BeginPlay()
{
	Super::BeginPlay();

	AddNameToCommandSystem();

}

void UTTCrafterComponent::AddNameToCommandSystem()
{
	ATTGameMode* correctGameMode = Cast<ATTGameMode>(GetWorld()->GetAuthGameMode());

	if (correctGameMode)
	{
		for (int i = 0; i < Recipes.Num(); i++)
		{
			for (int k = 0; k < Recipes[i].Name.Num(); k++)
			{
				correctGameMode->AddExtraWord(Recipes[i].Name[k].ToString());
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Using Wrong GameMode!"));
}

TSubclassOf<AActor> UTTCrafterComponent::CraftByInventory(UTTInventoryComponent* inventory)
{
	for (FRecipe recipe : Recipes)
	{
		if(recipe.Ingridients.Num() != inventory->GetInventorySize()) continue;

		TArray<FIngredientPair> stuffINeed = WhatAmIMissing(inventory, recipe.Name[0]);
		if(stuffINeed.Num() == 0)
			return recipe.CraftIntoThisObject;
	}

	return nullptr;
}

TSubclassOf<AActor> UTTCrafterComponent::CraftByName(UTTInventoryComponent* inventory, FName RecipeName, bool consumeItems)
{
	FRecipe theRecipe;
	TArray<UTTStoreableComponent*> craftingMaterials = inventory->GetInventoryArray();
	TArray<UTTStoreableComponent*> materialToRemove;

	bool hasFoundStuff = false;;
	
	for (FRecipe recipe : Recipes)
	{
		if (recipe.Name.Contains(RecipeName))
		{
			theRecipe = recipe;
			hasFoundStuff = true;
			break;
		}

	}
	if(!hasFoundStuff)
		return nullptr;
	
	TMap<UClass*, int> materialCompletion;

	for (FIngredientPair ingredient : theRecipe.Ingridients)
	{
		materialCompletion.Add(ingredient.Ingredient->GetDefaultObject()->GetClass(), ingredient.Amount);
	}


	for (UTTStoreableComponent* craftingMaterial : craftingMaterials)
	{
		if(craftingMaterial == nullptr || !materialCompletion.Contains(craftingMaterial->GetOwner()->GetClass()) || materialCompletion[craftingMaterial->GetOwner()->GetClass()] <= 0) continue;

		materialCompletion[craftingMaterial->GetOwner()->GetClass()]--;
		materialToRemove.Add(craftingMaterial);
	}
	
	for (TPair<UClass*, int> ingidientPair : materialCompletion)
	{
		if(ingidientPair.Value > 0) return nullptr;
	}
	
	if(!consumeItems) return theRecipe.CraftIntoThisObject;

	for (UTTStoreableComponent* usedMaterial : materialToRemove)
	{
		inventory->RemoveItemFromInventory(usedMaterial);
	}

	return theRecipe.CraftIntoThisObject;
}

TArray<FIngredientPair> UTTCrafterComponent::WhatAmIMissing(UTTInventoryComponent* inventory, FName RecipeName) 
{
	TArray<FIngredientPair> missingIngredients;

	FRecipe theRecipe;
	TArray<UTTStoreableComponent*> craftingMaterials = inventory->GetInventoryArray();

	bool hasFoundStuff = false;;

	for (FRecipe recipe : Recipes)
	{
		if (recipe.Name.Contains(RecipeName))
		{
			theRecipe = recipe;
			hasFoundStuff = true;
			break;
		}

	}
	if (!hasFoundStuff)
		return missingIngredients;

	TMap<UClass*, FIngredientPair> materialCompletion;

	for (FIngredientPair ingredient : theRecipe.Ingridients)
	{
		materialCompletion.Add(ingredient.Ingredient->GetDefaultObject()->GetClass(), ingredient);
	}


	for (UTTStoreableComponent* craftingMaterial : craftingMaterials)
	{
		if (craftingMaterial == nullptr || !materialCompletion.Contains(craftingMaterial->GetOwner()->GetClass()) || materialCompletion[craftingMaterial->GetOwner()->GetClass()].Amount <= 0) continue;

		materialCompletion[craftingMaterial->GetOwner()->GetClass()].Amount--;
	}

	for (TPair<UClass*, FIngredientPair> ingidientPair : materialCompletion)
	{
		if (ingidientPair.Value.Amount > 0)
		{
			TSubclassOf<AActor> storable = ingidientPair.Key;
			FIngredientPair pair;
			pair.Ingredient = storable;
			pair.Amount = ingidientPair.Value.Amount;
			pair.DispayName = ingidientPair.Value.DispayName;
			missingIngredients.Add(pair);
		}
			
	}


	return missingIngredients;
}

int32 UTTCrafterComponent::NumberOfIngredient(TArray<UTTStoreableComponent*> listOfIngerdients, TSubclassOf<AActor> Ingredient)
{
	//Sometimes the ingredien (storableis null)
	int stuff = 0;
	for (int i = 0; i < listOfIngerdients.Num(); i++)
	{
		if (listOfIngerdients[i]->GetOwner()->IsA(Ingredient->GetDefaultObject()->GetClass()))
		{
			stuff++;
		}
	}
	return stuff;
}