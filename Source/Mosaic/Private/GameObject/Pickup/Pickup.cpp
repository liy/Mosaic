// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "CharacterController.h"
#include "Pickup.h"


APickup::APickup(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	bIsActive = true;
	
	CollectionSphere = objectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	RootComponent = CollectionSphere;
	
	Mesh = objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	Mesh->AttachTo(RootComponent);
}

void APickup::BeginPlay()
{
	// Cannot put the Class assignment in the constructor, since GetClass() only return the 
	// C++ class in the constructor, not the final blueprint class.
	Data.Class = GetClass();

	Super::BeginPlay();
}

void APickup::OnCollection(ACharacterController& controller)
{
	// Add the Pickable Information to the inventory, I guess InventoryItemInfo should be copied.
	// Since Inventory.Add(InventoryItemInfo item) copy the parameter by default. (It is pass by value, not pass by reference or pointer)
	// And, I assume, that this actor's InventoryItemInfo will be destroyed once this actor is destroyed.
	//character.GetCharacterController()->Inventory->Add(InventoryItemInfo);
	//character.GetCharacterController()->InventoryWidget->Refresh();
	controller.Collect(this);

	// Call blueprint OnCollection native event.
	ReceiveOnCollection();

	bIsActive = false;
	Destroy();
}