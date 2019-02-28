#include "TTHarvester.h"
#include "TTHarvestable.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/Equipment/TTEquiperComponent.h"
void UTTHarvester::BeginPlay()
{
	Super::BeginPlay();
	CurrentHarvestTime = 0;	
	// En float är 0 automatiskt (om inget annat värde har blivit assignat)
	// Plus att du assignar värdet i headern redan :)
}

// Något missledande namn. Den här triggar complete eventet. I mitt huvud så skulle den ge tillbaka en bool eller något för att
// se om harvesten är färdig
void UTTHarvester::GetHarvestedComplete()
{
	OnHarvesterComplete.Broadcast();
}

void UTTHarvester::ResetHarvest()
{
	CurrentHarvestTime = 0;
}

AActor* UTTHarvester::Harvest(AActor* HarvestTarget, UTTEquiperComponent* CurrentToolEquiped)
{
	return nullptr;
}