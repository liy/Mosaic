// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "HeadPickup.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API AHeadPickup : public APickup
{
	GENERATED_BODY()
	
public:

	AHeadPickup(const FObjectInitializer& objectInitializer);

	virtual void OnCollection(class ACharacterController& controller) override;
};
