// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "Pickup.h"
#include "PickupSpawn.h"

UPickupSpawn::UPickupSpawn(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	Class = APickup::StaticClass();
}

APickup* UPickupSpawn::Spawn()
{
	FActorSpawnParameters param;
	param.bNoCollisionFail = true;

	FTransform trans = GetComponentToWorld();
	
	APickup* actor = GetWorld()->SpawnActor<APickup>(Class, trans.GetLocation(), trans.GetRotation().Rotator(), param);

	return actor;
}