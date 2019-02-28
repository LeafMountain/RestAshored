#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTHandlerThermometerComponent.generated.h"

UCLASS(ClassGroup = (Temperature), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API ATTHandlerThermometerComponent : public AActor
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Temperature")
	void UpdateComfortComponents();

	UFUNCTION(BlueprintCallable, Category = "Temperature")
		void UpdateWorldTemperature(float Heat);	
	UFUNCTION(BlueprintCallable, Category = "Temperature")
		void AdjustWorldTemperature(float Heat);

	void AddToRadiateList(class UTTRadiateTemperatureComponent* RadiateObject);
	void AddToTherometerList(class UTTThermometerComponent* therometer);

	UFUNCTION(BlueprintCallable, Category = "Temperature")
		FORCEINLINE float GetWorldTemperature() const { return WorldTemperature; }
	void RemoveFromRadiateList(class UTTRadiateTemperatureComponent* RadiateObject);
	void RemoveFromTherometerList(class UTTThermometerComponent* therometer);

	TArray<class UTTRadiateTemperatureComponent*> RadiateList;
	TArray<class UTTThermometerComponent*> TherometerList;

	void CheckForTemeratureChange();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Temperature")
		float WorldTemperature = 20;

protected:
	UPROPERTY(EditAnywhere, Category = Temperature)
	float TemCheckFrequency = 0.5f;

private:
	float lastTimeOfTempCheck;
	 
};