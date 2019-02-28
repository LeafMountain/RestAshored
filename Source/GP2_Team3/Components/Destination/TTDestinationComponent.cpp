#include "TTDestinationComponent.h"

float UTTDestinationComponent::GetDistance()
{
	FVector currentPosition = GetOwner()->GetActorLocation();
	return FVector::Distance(currentPosition, destination);
}

void UTTDestinationComponent::SetDestination(FVector position)
{
	destination = position;
}

//void UTTDestinationComponent::SetDestination(FString waypoint)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Waypoint system not implemented."));
//}

//void UTTDestinationComponent::SetDirection(FVector direction)
//{
//	this->direction = direction;
//}

void UTTDestinationComponent::SetDirection(FString direction)
{
	if (direction == "north")
		this->direction = FVector(0, 1, 0);	
	else if (direction == "east")
		this->direction = FVector(1, 0, 0);
	else if (direction == "south")
		this->direction = FVector(0, -1, 0);	
	else if (direction == "west")
		this->direction = FVector(-1, 0, 0);
}
