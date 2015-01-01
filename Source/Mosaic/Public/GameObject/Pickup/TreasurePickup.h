// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "Range.h"
#include "TreasurePickup.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API ATreasurePickup : public APickup
{
	GENERATED_BODY()
	
public:

	ATreasurePickup(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Value)
	int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Value)
	int32 MaxValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Value)
	int32 Value;

	UFUNCTION(BlueprintCallable, Category=value)
	void Evaludate();
};
