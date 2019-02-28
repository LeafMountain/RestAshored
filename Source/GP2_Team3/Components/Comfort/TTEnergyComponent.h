#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTEnergyComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToExhaustedEvent);

UCLASS(ClassGroup = (Eater), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTEnergyComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, Category = "Energy")
		void RegainEnergy(class UTTEdibleComponent* Edible);
	UFUNCTION(BlueprintCallable, Category = "Energy")
		FORCEINLINE float GetMaxEnergy() const { return MaxEnergy; }
	UFUNCTION(BlueprintCallable, Category = "Energy")
		FORCEINLINE float GetEnergyPercentage() const { return CurrentEnergy / MaxEnergy; }
	UFUNCTION(BlueprintCallable, Category = "Energy")
		void SetCurrentEnergy(float Value);
	UFUNCTION(BlueprintCallable, Category = "Energy")
		void AdjustCurrentEnergy(float Value);

	UPROPERTY(EditAnywhere, Category = "Energy")
		float ExhausionDrain = 1.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Energy")
		float CurrentEnergy = 100;
	UPROPERTY(EditAnywhere, Category = "Energy")
		float MaxEnergy = 100;
	UPROPERTY(BlueprintAssignable, Category = "Energy")
		FToExhaustedEvent OnToExhausted;
};
