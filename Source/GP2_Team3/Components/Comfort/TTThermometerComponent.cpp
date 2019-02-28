#include "TTThermometerComponent.h"
#include "TTHandlerThermometerComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UTTThermometerComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> tempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATTHandlerThermometerComponent::StaticClass(), tempArray);
	
	if (tempArray.Num() > 0)
	{
		TempHandler = CastChecked<ATTHandlerThermometerComponent>(tempArray[0]);
		TempHandler->AddToTherometerList(this);
	}
		
	else
		UE_LOG(LogTemp, Error, TEXT("There is no temeperture manager in the scene!"));

	TotalHeat = TempHandler->GetWorldTemperature();
}

void UTTThermometerComponent::AddHeat(float Heat)
{
	AmountofHeatSources++;
	TotalHeat += Heat;
}

void UTTThermometerComponent::ResetHeatSources()
{
	AmountofHeatSources = 1;
	TotalHeat = 0;
}


void UTTThermometerComponent::SetTotalTemperature(float Heat)
{
	TotalHeat = Heat;
}

void UTTThermometerComponent::AdjustWorldTemperature(float Heat)
{
	TotalHeat += Heat;
}

float UTTThermometerComponent::GetTemperature()
{
	if(TempHandler == nullptr) return 0;

	TempHandler->CheckForTemeratureChange();
	return TempHandler->GetWorldTemperature() + (AmountofHeatSources > 0 ? (TotalHeat / AmountofHeatSources) : 0);
}

