#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTEaterComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToHungryEvent);

UCLASS(ClassGroup = (Eater), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTEaterComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:

	UFUNCTION(BlueprintCallable, Category = "Eater")
		void EatFood(class UTTEdibleComponent* Edible);


	UFUNCTION(BlueprintCallable, Category = "Eater")
		FORCEINLINE float GetCurrentHunger() const { return Hunger; }
	UFUNCTION(BlueprintCallable, Category = "Eater")
		FORCEINLINE float GetHungerPercentage() const { return Hunger / MaxHunger; }

	UFUNCTION(BlueprintCallable, Category = "Eater")
		void SetCurrentHunger(float Value);

	UFUNCTION(BlueprintCallable, Category = "Eater")
		void AdjustCurrentHunger(float Value);


	UPROPERTY(EditAnywhere, Category = "Eater")
		float HungerPerSecond = 5.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Eater")
		float Hunger = 1;
	UPROPERTY(EditAnywhere, Category = "Eater")
		float MaxHunger = 100;
	UPROPERTY(BlueprintAssignable, Category = "Eater")
		FToHungryEvent OnToHungry;

};
