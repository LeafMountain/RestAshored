#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTEdibleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHaveBeenEaten);

UCLASS(ClassGroup = (Edible), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTEdibleComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	//virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, Category = "Eater")
		FORCEINLINE float GetFoodValue()const { return FoodValue; }

		void GetBeingEaten();

	UPROPERTY(EditAnywhere, Category = "Edible")
		float FoodValue = 0;

	UPROPERTY(BlueprintAssignable, Category = "Edible")
	FOnHaveBeenEaten BeenEaten;
};
