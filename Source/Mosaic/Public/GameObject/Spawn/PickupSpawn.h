// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "PickupSpawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class MOSAIC_API UPickupSpawn : public USceneComponent
{
	GENERATED_BODY()

public:

	UPickupSpawn(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawn)
	TSubclassOf<class APickup> Class;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	virtual APickup* Spawn();
};
