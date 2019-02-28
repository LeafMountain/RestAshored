// Fill out your copyright notice in the Description page of Project Settings.

#include "TTMoodComponent.h"

// Sets default values for this component's properties
UTTMoodComponent::UTTMoodComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTTMoodComponent::BeginPlay()
{
	Super::BeginPlay();

	currentIdleTime = 0;
	currentBoredTime = FMath::RandRange(idleTimeRange.X, idleTimeRange.Y);
}

int32 UTTMoodComponent::GetWeightedRandomMoodIndex()
{
	TArray<TPair<float, int32>> weightedIndex;
	float dist = 0;
	float totalDist = 0;
	for (size_t i = 0; i < randomEvents.Num(); i++)
	{
		dist = FMath::Abs(myMood - randomEvents[i].Mood);
		if (dist <= randomEventRange)
		{
			TPair<float, int32> tempPair;
			totalDist += (randomEventRange - dist);
			tempPair.Key = totalDist;
			tempPair.Value = i;	
			weightedIndex.Add(tempPair);
		}		
	}

	float randomValue = FMath::RandRange(0.0, totalDist);
	for (int i = 0; i < weightedIndex.Num(); i++)
	{
		if(randomValue <= weightedIndex[i].Key)
			return weightedIndex[i].Value;
	}

	return 0;
}

void UTTMoodComponent::TickIdleTime(float deltaTime) 
{
	myMood = FMath::Lerp(myMood, 50.0f, deltaTime * moodRestorationSpeed);

	if (currentIdleTime > currentBoredTime) 
	{
		currentIdleTime = 0;
		OnGotBored.Broadcast(myMood);
		return;
	}

	currentIdleTime += deltaTime;
}

void UTTMoodComponent::ResetIdleTime()
{
	currentIdleTime = 0;
}

void UTTMoodComponent::ChangeMoodTowards(UTTMoodComponent* character, int32 amount)
{
	if(characterRelations.Contains(character))
		characterRelations[character] = FMath::Clamp(amount + characterRelations[character], 0, 100);
	else
		characterRelations.Add(character, FMath::Clamp(50 + amount, 0, 100));
}

int32 UTTMoodComponent::GetMoodTowards(UTTMoodComponent* character)
{
	if(characterRelations.Contains(character))
		return characterRelations[character];

	return characterRelations.Add(character, 50);
}

void UTTMoodComponent::ChangeMyMood(int32 amount)
{
	myMood += amount;

	if(amount > 0)
		OnMoodIncreesed.Broadcast(myMood);
	else
		OnMoodDecreesed.Broadcast(myMood);
}

bool UTTMoodComponent::DoIWantThis(ESocialisingType socialisingType, UTTMoodComponent* socialize) 
{
	bool iWantThis = false;

	switch (socialisingType)
	{
	case ESocialisingType::Punch:
		if(GetMoodTowards(socialize) < wantToPunchThershold)
			iWantThis = true;
		break;
	case ESocialisingType::Hug:
		if (GetMoodTowards(socialize) > hugThreshold)
			iWantThis = true;
		break;
	case ESocialisingType::Speak:
		if (GetMoodTowards(socialize) > speakThreshold)
			iWantThis = true;
			break;
	case ESocialisingType::Help:
		if (GetMoodTowards(socialize) > helpThreshold)
			iWantThis = true;
			break;
	case ESocialisingType::Call:
		if (GetMoodTowards(socialize) > listenToCallThreshold)
			iWantThis = true;
			break;
	case ESocialisingType::Highfive:
		if (GetMoodTowards(socialize) > highfiveThreshold)
			iWantThis = true;
			break;
	case ESocialisingType::Give:
		if (GetMoodTowards(socialize) > acceptGiftThreshold)
			iWantThis = true;
			break;
	case ESocialisingType::Pat:
		if (GetMoodTowards(socialize) > patThreshold)
			iWantThis = true;
			break;
	case ESocialisingType::Kill:
		if(GetMoodTowards(socialize) < killThreshold)
		break;

	}

	return iWantThis;
}

bool UTTMoodComponent::DoILikeThis(ESocialisingType socialisingType, UTTMoodComponent* socialiser, bool applyNegativeConsequenses = false)
{
	bool accepted = false;
	int32 myMoodTowardsSoiclaiser = GetMoodTowards(socialiser);
	switch (socialisingType)
	{
	case ESocialisingType::Punch:
			ChangeMoodTowards(socialiser, PunchMoodEffect);
			ChangeMyMood(PunchMoodEffect);
			accepted = true;
		break;
	case ESocialisingType::Hug:
		accepted = myMoodTowardsSoiclaiser > hugThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, hugMoodEffect);
			ChangeMyMood(hugMoodEffect);
		}
		else if (applyNegativeConsequenses) 
		{
			ChangeMoodTowards(socialiser, -hugMoodEffect);
			ChangeMyMood(-hugMoodEffect);
		}		
		break;
	case ESocialisingType::Speak:
		accepted = myMoodTowardsSoiclaiser  > speakThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, spokeMoodEffect);
			ChangeMyMood(spokeMoodEffect);
		}
		else if (applyNegativeConsequenses)
		{
			ChangeMoodTowards(socialiser, -spokeMoodEffect);
			ChangeMyMood(-spokeMoodEffect);
		}
			
		break;
	case ESocialisingType::Help:
		accepted = myMoodTowardsSoiclaiser > helpThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, helpMoodEffect);
			ChangeMyMood(helpMoodEffect);
		}
		else if (applyNegativeConsequenses)
		{
			ChangeMoodTowards(socialiser, -helpMoodEffect);
			ChangeMyMood(-helpMoodEffect);
		}
		break;
	case ESocialisingType::Call:
		accepted = myMoodTowardsSoiclaiser > listenToCallThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, calledMoodEffect);
			ChangeMyMood(calledMoodEffect);
		}
	
		else if (applyNegativeConsequenses)
		{
			ChangeMoodTowards(socialiser, -calledMoodEffect);
			ChangeMyMood(-calledMoodEffect);
		}
	
		break;
	case ESocialisingType::Highfive:
		accepted = myMoodTowardsSoiclaiser > highfiveThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, highfiveMoodEffect);
			ChangeMyMood(highfiveMoodEffect);
		}	
		else if (applyNegativeConsequenses)
		{
			ChangeMoodTowards(socialiser, -highfiveMoodEffect);
			ChangeMyMood(-highfiveMoodEffect);
		}	
		break;
	case ESocialisingType::Give:
		accepted = myMoodTowardsSoiclaiser > acceptGiftThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, giftMoodEffect);
			ChangeMyMood(giftMoodEffect);
		}

		else if (applyNegativeConsequenses)
		{
			ChangeMoodTowards(socialiser, -giftMoodEffect);
			ChangeMyMood(-giftMoodEffect);
		}
	
		break;
	case ESocialisingType::Pat:
		accepted = myMoodTowardsSoiclaiser > patThreshold;
		if (accepted)
		{
			ChangeMoodTowards(socialiser, patMoodEffect);
			ChangeMyMood(patMoodEffect);
		}
		else if (applyNegativeConsequenses)
		{
			ChangeMoodTowards(socialiser, -patMoodEffect);
			ChangeMyMood(-patMoodEffect);
		}
		break;
	case ESocialisingType::Kill:
		accepted = true;
		ChangeMoodTowards(socialiser, -1000);
		break;
	case ESocialisingType::Annoy:
		accepted = true;
		ChangeMoodTowards(socialiser, anoyedMoodEffect);
		ChangeMyMood(anoyedMoodEffect);
		break;
	default:
		break;

	}

	return accepted;
}
