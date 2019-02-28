#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTThermometerComponent.generated.h"

UCLASS(ClassGroup = (Temperature), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTThermometerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Temperature")
	void AddHeat(float Heat);

	void ResetHeatSources();
	UFUNCTION(BlueprintCallable, Category = "Temperature")
	void SetTotalTemperature(float Heat);
	UFUNCTION(BlueprintCallable, Category = "Temperature")
	void AdjustWorldTemperature(float Heat);

	UFUNCTION(BlueprintCallable, Category = "Temperature")
	float GetTemperature();// const{return (CurrentHeat / AmountofHeatSources);}

	UPROPERTY(BlueprintReadOnly, Category = "Temperature")
	float AmountofHeatSources = 1;
	UPROPERTY(VisibleAnywhere, Category = "Temperature")
	float TotalHeat = 0;
	

	void BeginPlay() override;

private:
	class ATTHandlerThermometerComponent* TempHandler;
};