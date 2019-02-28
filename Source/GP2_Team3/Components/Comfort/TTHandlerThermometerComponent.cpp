#include "TTHandlerThermometerComponent.h"
#include "TTRadiateTemperatureComponent.h"
#include "TTThermometerComponent.h"


void ATTHandlerThermometerComponent::UpdateComfortComponents()
{
	
	for (UTTThermometerComponent* therometer : TherometerList)
	{
		therometer->ResetHeatSources();
	}

	for (UTTRadiateTemperatureComponent* radiator : RadiateList)
	{
		radiator->RadiateHeat();
	}

}

void ATTHandlerThermometerComponent::UpdateWorldTemperature(float Heat)
{
	WorldTemperature = Heat;
	for (UTTThermometerComponent* therometer : TherometerList)
	{
		therometer->SetTotalTemperature(Heat);
	}
}
void ATTHandlerThermometerComponent::AdjustWorldTemperature(float Heat)
{
	WorldTemperature += Heat;
	for (UTTThermometerComponent* therometer : TherometerList)
	{
		therometer->AdjustWorldTemperature(Heat);
	}
}

void ATTHandlerThermometerComponent::AddToRadiateList(UTTRadiateTemperatureComponent* RadiateObject)
{
	RadiateList.AddUnique(RadiateObject);
}

void ATTHandlerThermometerComponent::AddToTherometerList(UTTThermometerComponent* therometer)
{
	TherometerList.AddUnique(therometer);
}

void ATTHandlerThermometerComponent::RemoveFromRadiateList(UTTRadiateTemperatureComponent* RadiateObject)
{
	for (int i = RadiateList.Num() - 1; i >= 0; i--)
	{
		if (RadiateList[i] == RadiateObject)
		{
			RadiateList.RemoveAt(i);
			break;
		}
	}
}

void ATTHandlerThermometerComponent::RemoveFromTherometerList(UTTThermometerComponent* therometer)
{
	for (int i = TherometerList.Num() - 1; i >= 0; i--)
	{
		if (TherometerList[i] == therometer)
		{
			TherometerList.RemoveAt(i);
			break;
		}
	}
}

void ATTHandlerThermometerComponent::CheckForTemeratureChange()
{
	if (GetWorld()->GetTimeSeconds() - lastTimeOfTempCheck < TemCheckFrequency) return;

	lastTimeOfTempCheck = GetWorld()->GetTimeSeconds();
	UpdateComfortComponents();
}

//void UTTHandlerThermometerComponent::AddToThermometerList(class UTTThermometerComponent* ThermometerObject)
//{
//	ThermometerList.Add(ThermometerObject);
//}

