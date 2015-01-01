// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "CashPickupSpawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class MOSAIC_API UCashPickupSpawn : public USceneComponent
{
	GENERATED_BODY()

public:

	UCashPickupSpawn(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawn)
	TSubclassOf<class ACashPickup> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxValue;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	virtual ACashPickup* Spawn();
};
