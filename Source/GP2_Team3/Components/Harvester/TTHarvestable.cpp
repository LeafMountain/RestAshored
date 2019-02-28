#include "TTHarvestable.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void UTTHarvestable::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmount = StartAmount;

}

AActor* UTTHarvestable::Harvest()
{
	if(!IsAvailableForHarvest() || CurrentAmount <= 0) return nullptr;

	progression = 0;

	CurrentAmount--;
	OnBeenHarvested.Broadcast();

	if (CurrentAmount == 0)
	{
		OnResourceDepleted.Broadcast();
	}
	AActor* resource = GetWorld()->SpawnActor(Resource);
	return resource;
}

bool UTTHarvestable::IsAvailableForHarvest()
{
	return progression >= HarvestDuration && CurrentAmount > 0;
}

void UTTHarvestable::UpdateProgression(float deltaTime)
{
	progression += deltaTime;
}
