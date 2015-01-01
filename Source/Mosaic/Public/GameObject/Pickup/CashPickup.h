// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "CashPickup.generated.h"

/**
 * Directly add to player's wealth value.
 */
UCLASS()
class MOSAIC_API ACashPickup : public APickup
{
	GENERATED_BODY()
	
	
public:

	ACashPickup(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
};
