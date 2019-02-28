#include "TTRadiateTemperatureComponent.h"
#include "Components/SphereComponent.h"
#include "TTThermometerComponent.h"
#include "TTHandlerThermometerComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"



void UTTRadiateTemperatureComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());
	TArray<AActor*> tempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATTHandlerThermometerComponent::StaticClass(), tempArray);

	if (tempArray.Num() > 0)
	{
		TempHandler = CastChecked<ATTHandlerThermometerComponent>(tempArray[0]);
		TempHandler->AddToRadiateList(this);
	}
}


void UTTRadiateTemperatureComponent::SetSphereRadius(float RadiusSize)
{
	RadiusSphere = RadiusSize;
}

void UTTRadiateTemperatureComponent::SetMaxTemperature(float Temperature)
{
	MaxTemperature = Temperature;
}

void UTTRadiateTemperatureComponent::RadiateHeat()
{
	if (ToggleHeat)
	{
		if (!GetOwner())
		{
			TempHandler->RemoveFromRadiateList(this);
			return;
		}
		TArray<FOverlapResult> HitResults;

		FVector StartLocation = GetOwner()->GetActorLocation();

		FVector EndLocatation = GetOwner()->GetActorLocation();
		EndLocatation.Z = RadiusSphere;

		ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(RadiusSphere);
		bool bHit = GetWorld()->OverlapMultiByChannel(HitResults, StartLocation, FQuat::Identity, ECC, CollisionShape);

		if (bHit)
			for (FOverlapResult overlap : HitResults)
			{
				if (overlap.GetActor()->GetComponentByClass(UTTThermometerComponent::StaticClass()) != nullptr)
				{
					//float DistanceToOverlap = FVector::Distance(overlap.GetActor()->GetActorLocation(), StartLocation);
					//Heat = MaxTemperature * (1 - (DistanceToOverlap / RadiusSphere));
					CastChecked<UTTThermometerComponent>(overlap.GetActor()->GetComponentByClass(UTTThermometerComponent::StaticClass()))->AddHeat(MaxTemperature);
				}
			}
	}
}


