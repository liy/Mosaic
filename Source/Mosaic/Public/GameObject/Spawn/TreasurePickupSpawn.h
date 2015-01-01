// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "TreasurePickupSpawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class MOSAIC_API UTreasurePickupSpawn : public USceneComponent
{
	GENERATED_BODY()

public:

	UTreasurePickupSpawn(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawn)
	TSubclassOf<class ATreasurePickup> Class;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	virtual ATreasurePickup* Spawn();
};
