// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "PickupDataLibrary.h"
#include "TreasurePickup.h"

ATreasurePickup::ATreasurePickup(const FObjectInitializer& objectInitializer) : Super(objectInitializer), MinValue(10), MaxValue(1000)
{
	Data.Tags.Add(EPickupType::Resource);
}

void ATreasurePickup::Evaludate(){
	Value = FMath::FRandRange(MinValue, MaxValue);
}