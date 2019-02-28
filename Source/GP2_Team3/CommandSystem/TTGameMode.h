// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TTCommandData.h"
#include "TTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GP2_TEAM3_API ATTGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void virtual BeginPlay() override;

private:
	class ATTCommandSystem* commandSystem;

public:

	TArray<class UTTInteractableComponent*> interactables;
	TArray<class UTTInteractableComponent*> noRangeInteractables;
	
	// Checks and creates command system
	UFUNCTION(BlueprintCallable)
	class ATTCommandSystem* GetCommandSystem();

	UPROPERTY(EditAnywhere, Category = "TT Keywords")
	TArray<FKeyDictionary> KeyDictionary;

	// Add words here that's you want the command system to understand. They will be added to the interactables list.
	UPROPERTY(EditAnywhere, Category = "TT Keywords")
		TArray<FString> ExtraWords;

	void AddInteractable(class UTTInteractableComponent* interactable);
	TArray<class UTTInteractableComponent*> GetInteractables();

	UFUNCTION(BlueprintCallable)
	class UTTInteractableComponent* GetInteractableByName(FName name);

	UFUNCTION(BlueprintCallable)
	TArray<class UTTInteractableComponent*> GetInteractablesByName(FName name);

	void AddExtraWord(FString word);

};
