// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "PickupDataLibrary.h"
#include "CharacterController.h"
#include "CashPickup.h"

ACashPickup::ACashPickup(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	Data.Tags.Add(EPickupType::Cash);
}