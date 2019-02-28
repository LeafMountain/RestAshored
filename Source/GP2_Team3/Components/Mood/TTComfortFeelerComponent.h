// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTComfortFeelerComponent.generated.h"

UENUM(BlueprintType)
enum EMoods
{
	Cold, Normal, Tired, Hungry, Sad
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTComfortFeelerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTComfortFeelerComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Mood")
		FORCEINLINE EMoods GetCurrentMood() const { return CurrentMood; }

	UFUNCTION(BlueprintCallable, Category = "Mood")
		void SetCurrentMood(EMoods Mood);

	UPROPERTY(EditAnywhere, Category = "Mood")
		TArray<TEnumAsByte<EMoods>> ListOfMoods;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mood")
		TEnumAsByte <EMoods> CurrentMood;



};
