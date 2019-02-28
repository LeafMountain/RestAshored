#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTRadiateTemperatureComponent.generated.h"


UCLASS(ClassGroup = (Temperature), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTRadiateTemperatureComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Temperature")
		float RadiusSphere = 20;

	class ATTHandlerThermometerComponent* TempHandler;
	UFUNCTION(BlueprintCallable, Category = "Temperature")
		FORCEINLINE float GetSphereRadius() const { return RadiusSphere; }
	UFUNCTION(BlueprintCallable, Category = "Temperature")
		FORCEINLINE float GetMaxTemperature() const { return MaxTemperature; }

	UFUNCTION(BlueprintCallable, Category = "Temperature")
		void SetSphereRadius(float RadiusSize);
	UFUNCTION(BlueprintCallable, Category = "Temperature")
		void SetMaxTemperature(float Temperature);

	void RadiateHeat();
	UPROPERTY(BlueprintReadWrite, Category = "Temperature")
		bool ToggleHeat = true;
	UPROPERTY(EditAnywhere, Category = "Temperature")
		float MaxTemperature = 1000;

	float Heat = 0;

	void BeginPlay() override;

	//UTTComfortCompoent* TargetWithComfortComponent;
};