// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "HeadPickup.h"
#include "HeadPickupSpawn.h"

UHeadPickupSpawn::UHeadPickupSpawn(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	Class = AHeadPickup::StaticClass();
}

AHeadPickup* UHeadPickupSpawn::Spawn()
{
	FActorSpawnParameters param;
	param.bNoCollisionFail = true;

	FTransform trans = GetComponentToWorld();
	
	AHeadPickup* actor = GetWorld()->SpawnActor<AHeadPickup>(Class, trans.GetLocation(), trans.GetRotation().Rotator(), param);

	return actor;
}