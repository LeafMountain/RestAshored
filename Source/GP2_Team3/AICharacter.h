// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class GP2_TEAM3_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter(const class FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:


	// Reference to the AI's blackboard data.
	UPROPERTY(EditAnywhere, Category = "AI")
		class UBlackboardData* Blackboarddata;

	class AAIController* MyController;

	class UBlackboardComponent* MyBBComp;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
		FORCEINLINE class UBlackboardComponent* GetBlackboard() const { return MyBBComp; }

	UFUNCTION(BlueprintCallable, Category = Needs)
		FORCEINLINE float GetBodyWarmth()const { return BodyWarmth; }

	UFUNCTION(BlueprintCallable, Category = Needs)
		FORCEINLINE float GetHunger()const { return HungryMeeter; }

	UFUNCTION(BlueprintCallable, Category = Needs)
		FORCEINLINE float GetDistanceToTarget() const { return FVector::Distance(GetActorLocation(), Destination); }

	
	UFUNCTION(BlueprintCallable, Category = "AI")
		void SetDestination(FVector DestinationPoint);

	UFUNCTION(BlueprintCallable, Category = "AI")
		FORCEINLINE FVector GetDestination() const { return Destination; }

	UFUNCTION(BlueprintCallable, Category = "AI")
		void IsDoingInteraction(bool DoInteraction);

	UFUNCTION(BlueprintCallable, Category = "AI")
		FORCEINLINE bool GetIsInteracting() const { return DoingInteraction; }

	UFUNCTION(BlueprintCallable, Category = "AI")
		void SetBodyWarmth(float Cold);


	
	UFUNCTION(BlueprintCallable, Category = "AI")
		void SetIsBusy(bool busyOrNot);

	//UFUNCTION(BlueprintCallable, Category = "AI")
	//	FORCEINLINE bool GetIsBusy() const {return MyBBComp->GetValueAsBool("IsBusy"); }



private:


	FVector Destination = FVector::ZeroVector;
	bool DoingInteraction = false;
	float BodyWarmth = 100;
	float HungryMeeter = 100;

};
