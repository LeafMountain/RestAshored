#pragma once

#include "Components/ActorComponent.h"
#include "TTDestinationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewDestination, const FVector, position);

UCLASS(Blueprintable, ClassGroup = (TTComponent), meta = (BlueprintSpawnableComponent))
class GP2_TEAM3_API UTTDestinationComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FVector destination = FVector(0);
	FVector direction = FVector(0);

public:
	UFUNCTION(BlueprintCallable)
	float GetDistance();

	UFUNCTION(BlueprintCallable)
	void SetDestination(FVector position);

	//UFUNCTION(BlueprintCallable)
	//void SetDestination(FString waypoint);

	//UFUNCTION(BlueprintCallable)
	//void SetDirection(FVector direction);

	UFUNCTION(BlueprintCallable)
	void SetDirection(FString direction);

	UPROPERTY(BlueprintAssignable, Category = "TT Command")
	FOnNewDestination OnNewDestination;
};