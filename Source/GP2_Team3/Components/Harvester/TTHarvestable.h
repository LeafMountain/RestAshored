#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTHarvestable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHaveBeenHarvest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceDepleted);

UCLASS(ClassGroup = (Edible), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTHarvestable : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:


	UFUNCTION(BlueprintCallable, Category = "Harvestabke")
	AActor* Harvest();

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = "Harvestable")
	int32 StartAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvestable")
	int32 CurrentAmount = 0;

	UPROPERTY(BlueprintAssignable, Category = "Harvestable")
	FOnHaveBeenHarvest OnBeenHarvested;
	UPROPERTY(BlueprintAssignable, Category = "Harvestable")
	FOnResourceDepleted OnResourceDepleted;

	UPROPERTY(EditAnywhere, Category = "Harvestable")
	float HarvestDuration = 1;

	UPROPERTY(EditAnywhere, Category = "Harvestable")
	TSubclassOf<AActor> Resource;

	UFUNCTION(BlueprintCallable ,Category = Harvestable)
	bool IsAvailableForHarvest();

	UFUNCTION(BlueprintCallable, Category = Harvestable)
	void UpdateProgression(float deltaTime);

private:

	float progression;
};
