// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTInteractorComponent.h"
#include "TTInteractableComponent.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EInteractableType : uint8
{
	Prop, Tool, Item, Intangable
};
UENUM(BlueprintType)
enum class EInteractionAnimation : uint8
{
	Idle, Fish, Cut, Harvest, Build
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionEvent, const class UTTInteractorComponent*, interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPickupEvent, const class UTTInteractorComponent*, interactor, const class UTTInventoryComponent*, inventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUseEvent, const class UTTEquiperComponent*, equiper, AActor*, equipment);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUseTickEvent, const class UTTEquiperComponent*, equiper, AActor*, equipment, float, DeltaTime);

UCLASS(ClassGroup = (Interaction), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTInteractableComponent();

	UPROPERTY(EditAnywhere, Category = "Animation")
	EInteractionAnimation UsageAnimation; 

	UFUNCTION(BlueprintCallable)
	bool HasNametag(const FName nametag);

	UFUNCTION(BlueprintCallable)
	FName GetName();

	UFUNCTION(BlueprintCallable)
	void SetName(FName name);

	UPROPERTY(EditAnywhere, Category = "Interaction")
	class UAnimMontage* InteractionAnim = nullptr;

	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "ETTAction"))
	uint8 ActionTags;
public:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AddNameToCommandSystem();
	
	UFUNCTION(BlueprintCallable)
	void StopInteraction();

	UPROPERTY(EditAnywhere)
	bool Waypoint;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FUseEvent OnUse;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FPickupEvent OnPickup;
	
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FInteractionEvent OnDrop;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FInteractionEvent OnEat;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FStopEvent OnStop;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FUseTickEvent OnUseTick;

	//Social stuffs

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetPunched;

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetHuged;

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetSpokenTo;

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetCalled;

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetHighfived;

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetPated;

	UPROPERTY(BlueprintAssignable, Category = "SocialInteraction")
	FInteractionEvent OnGetAnoyed;

	UFUNCTION(BlueprintCallable)
	void TickUpdate(UTTEquiperComponent* equiper, AActor* equipment, float deltaTime);

	UPROPERTY(BlueprintReadOnly)
	bool DontInteractWithMe;

private:

	UPROPERTY(EditAnywhere)
	TArray<FName> speachTags;



public:
	TArray<FName> GetSpeechTags();

	void Use(const class UTTEquiperComponent* equiper, const class UTTEquipableComponent* currentEquipment);


	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Punch(class UTTInteractorComponent* interctor);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Hug(class UTTInteractorComponent* intercto);
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SpeakWith(class UTTInteractorComponent* intercto);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Call(class UTTInteractorComponent* intercto);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Highfive(class UTTInteractorComponent* intercto);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Pat(class UTTInteractorComponent* intercto);
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Anoy(class UTTInteractorComponent* intercto);

	

	
};
