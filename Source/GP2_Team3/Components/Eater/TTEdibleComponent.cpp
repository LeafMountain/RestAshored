#include "TTEdibleComponent.h"

//void UTTEdibleComponent::BeginPlay()
//{
//
//}

void UTTEdibleComponent::GetBeingEaten()
{
	BeenEaten.Broadcast();
}
