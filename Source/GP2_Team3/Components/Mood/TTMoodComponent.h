// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTMoodComponent.generated.h"

UENUM(BlueprintType)
enum class ESocialisingType : uint8 {
	Punch,
	Hug,
	Speak,
	Help,
	Call, 
	Highfive,
	Give, 
	Pat, 
	Kill,
	Annoy
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMoodEvent, int32, mood);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSocisalialEvent, UTTMoodComponent*, otherSocialicer, ESocialisingType, interactionType);

USTRUCT(BlueprintType)
struct FRandomEvent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RandomEvent")
	FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = "RandomEvent")
	float Mood;
};





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP2_TEAM3_API UTTMoodComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTMoodComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere = Mood)
	float myMood = 80;

	UPROPERTY(EditAnywhere, Category = Mood)
	FVector2D idleTimeRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mood)
	float moodRestorationSpeed = 4.0f;


	TMap<UTTMoodComponent*, int32> characterRelations;

	float currentIdleTime;

	float currentBoredTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FRandomEvent> randomEvents;

	UFUNCTION(BlueprintPure)
	int32 GetWeightedRandomMoodIndex();

private:
	float randomEventRange = 50;

public:	
	UFUNCTION(BlueprintCallable)
	void TickIdleTime(float deltaTime);
	
	UFUNCTION(BlueprintCallable)
	void ResetIdleTime();
	
	UFUNCTION(BlueprintCallable)
	void ChangeMoodTowards(UTTMoodComponent* character, int32 amount);

	UFUNCTION(BlueprintCallable)
	int32 GetMoodTowards(UTTMoodComponent* character);

	UFUNCTION(BlueprintCallable)
	void ChangeMyMood(int32 amount);
	
	UFUNCTION(BlueprintCallable)
	bool DoIWantThis(ESocialisingType socialisingType, UTTMoodComponent* socialize);
	
	//This returns false if they don't want to socialize
	UFUNCTION(BlueprintCallable)
	bool DoILikeThis(ESocialisingType socialisingType, UTTMoodComponent* socialiser, bool applyNegativeConsequenses);

	UPROPERTY(BlueprintAssignable)
	FMoodEvent OnMoodDecreesed;
	
	UPROPERTY(BlueprintAssignable)
	FMoodEvent OnMoodIncreesed;
	
	UPROPERTY(BlueprintAssignable)
	FMoodEvent OnGotBored;

public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 wantToPunchThershold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 hugThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 speakThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 helpThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 listenToCallThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 highfiveThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 acceptGiftThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 patThreshold;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"), Category = MoodThershoalds)
	int32 killThreshold;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 PunchMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 hugMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 spokeMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 helpMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 calledMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 highfiveMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 anoyMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 giftMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 patMoodEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MoodEffector)
	int32 anoyedMoodEffect;


};
