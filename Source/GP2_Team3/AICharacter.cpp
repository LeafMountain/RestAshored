#include "AICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AIController.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	MyController = Cast<AAIController>(GetController());
	MyController->UseBlackboard(Blackboarddata, MyBBComp);
	
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AAICharacter::SetDestination(FVector DestinationPoint)
{
	Destination = DestinationPoint;
}

void AAICharacter::IsDoingInteraction(bool DoInteraction)
{
	DoingInteraction = DoInteraction;
}

void AAICharacter::SetBodyWarmth(float Cold)
{
	BodyWarmth = Cold;
}
void AAICharacter::SetIsBusy(bool busyOrNot)
{
	MyBBComp->SetValueAsBool("IsBusy", busyOrNot);
}



