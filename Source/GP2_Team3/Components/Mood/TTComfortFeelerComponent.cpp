// Fill out your copyright notice in the Description page of Project Settings.

#include "TTComfortFeelerComponent.h"

// Sets default values for this component's properties
UTTComfortFeelerComponent::UTTComfortFeelerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTTComfortFeelerComponent::SetCurrentMood(EMoods Mood)
{
	CurrentMood = Mood;
}

