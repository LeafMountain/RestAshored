#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTHarvester.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHarvesterComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHarvesterFail);

UCLASS(ClassGroup = (Edible), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTHarvester : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:

	void GetHarvestedComplete();

	UFUNCTION(BlueprintCallable, Category = "Harvestabke")
	void ResetHarvest();

	UFUNCTION(BlueprintCallable, Category = "Harvestabke")
		AActor* Harvest(AActor* HarvestTarget, UTTEquiperComponent* CurrentToolEquiped);

	UPROPERTY(BlueprintAssignable, Category = "Harvestable")
		FOnHarvesterComplete OnHarvesterComplete;

	UPROPERTY(BlueprintAssignable, Category = "Harvestable")
		FOnHarvesterFail OnHarvestFailed;
		class UTTHarvestable* TargetHarvest;
	
	float CurrentHarvestTime = 0;
	float HarvestTime = 0;

};
