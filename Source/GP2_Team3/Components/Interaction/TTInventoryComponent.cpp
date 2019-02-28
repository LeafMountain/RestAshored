// Fill out your copyright notice in the Description page of Project Settings.

#include "TTInventoryComponent.h"
#include "../Equipment/TTStoreableComponent.h"
#include "TTInteractableComponent.h"
#include "Components/ActorComponent.h"



bool UTTInventoryComponent::AddToInventory(class UTTStoreableComponent* item)
{
	if(inventory.Num() >= size) return false;

	if (!interactor)
		interactor = CastChecked<UTTInteractorComponent>(GetOwner()->GetComponentByClass(UTTInteractorComponent::StaticClass()));
	if (interactor)
		item->GetInteractable()->OnPickup.Broadcast(interactor, this);

	inventory.Add(item);
	OnAddedItem.Broadcast(item);
	item->GetOwner()->SetActorHiddenInGame(true);
	return true;
}

TArray<UTTStoreableComponent*> UTTInventoryComponent::GetInventoryArray()
{
	for (int32 i = inventory.Num() - 1; i >= 0; i--)
	{
		if(inventory[i] == nullptr)
			inventory.RemoveAt(i);
	}

	return inventory;
}

UTTStoreableComponent* UTTInventoryComponent::GetItem(int32 index)
{
	if(inventory.Num() > 0)
	{
		if(index <=inventory.Num())
		return inventory[index];
	}
	return nullptr;
}

UTTStoreableComponent* UTTInventoryComponent::TakeItemFromInventorybyIndex(int32 index)
{
	return ( inventory.Num() < index ? inventory[index] : nullptr);
}

UTTStoreableComponent* UTTInventoryComponent::GetItemByName(FName name)
{
	for (UTTStoreableComponent* storable : inventory)
	{
		if(storable->GetInteractable()->HasNametag(name))
			return storable;
	}

	return nullptr;
}

UTTStoreableComponent* UTTInventoryComponent::DropItemByName(const FName name, FVector dropPosition)
{
   UTTStoreableComponent* item = GetItemByName(name); 

   if(item == nullptr)
	   return nullptr;

   item->GetOwner()->SetActorHiddenInGame(false);
   item->GetOwner()->SetActorLocation(dropPosition);

   if(!interactor)
	   interactor = CastChecked<UTTInteractorComponent>(GetOwner()->GetComponentByClass(UTTInteractorComponent::StaticClass()));
   if(interactor)
	   item->GetInteractable()->OnDrop.Broadcast(interactor);

   RemoveItemFromInventory(item);

   return item;
}

bool UTTInventoryComponent::RemoveItemFromInventory(class UTTStoreableComponent* item)
{
	int32 size = inventory.Num() - 1;
	for (int i = size; i >= 0; i--)
	{
		if (inventory[i] == item)
		{
			inventory.RemoveAt(i);
			OnRemovedItem.Broadcast(item);
			return true;
		}
	}	
	return false;
}

