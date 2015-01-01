// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "CashPickup.h"
#include "CashPickupSpawn.h"

UCashPickupSpawn::UCashPickupSpawn(const FObjectInitializer& objectInitializer) : Super(objectInitializer), MinValue(0), MaxValue(10)
{
	Class = ACashPickup::StaticClass();
}

ACashPickup* UCashPickupSpawn::Spawn()
{
	FActorSpawnParameters param;
	param.bNoCollisionFail = true;

	FTransform trans = GetComponentToWorld();
	
	ACashPickup* actor = GetWorld()->SpawnActor<ACashPickup>(Class, trans.GetLocation(), trans.GetRotation().Rotator(), param);

	return actor;
}