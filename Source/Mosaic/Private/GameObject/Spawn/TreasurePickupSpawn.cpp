// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "TreasurePickup.h"
#include "TreasurePickupSpawn.h"

UTreasurePickupSpawn::UTreasurePickupSpawn(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	Class = ATreasurePickup::StaticClass();
}

ATreasurePickup* UTreasurePickupSpawn::Spawn()
{
	FActorSpawnParameters param;
	param.bNoCollisionFail = true;

	FTransform trans = GetComponentToWorld();
	
	ATreasurePickup* actor = GetWorld()->SpawnActor<ATreasurePickup>(Class, trans.GetLocation(), trans.GetRotation().Rotator(), param);

	return actor;
}