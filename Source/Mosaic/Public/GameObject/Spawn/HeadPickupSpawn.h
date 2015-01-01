// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "HeadPickupSpawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class MOSAIC_API UHeadPickupSpawn : public USceneComponent
{
	GENERATED_BODY()

public:

	UHeadPickupSpawn(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawn)
	TSubclassOf<class AHeadPickup> Class;

	UFUNCTION(BlueprintCallable, Category = Spawn)
	virtual AHeadPickup* Spawn();
};
