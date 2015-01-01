// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickupDataLibrary.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API APickup : public AActor
{
	GENERATED_BODY()

public:
	APickup(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* CollectionSphere;

	// The inventory related information, thumbnail, etc.
	// Note that, this allocate the memory for FInventoryItemInfo type, and not like reference declaration that requires initialization
	// this way we can directly update the data in FInventoryItemInfo without assignment(we only assign class in BeginPlay(), others are assigned in blueprint)
	// We could use pointer, but Unreal Engine seems does not like structure pointer to be used as UPROPERTY.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPickupData Data;

	// In order to make OnCollection polymorphism in both C++ and BP, we need separate implementations.
	// Therefore, I cannot use BlueprintNativeEvent, since it does not allow virtual declaration.
	// You might want to check UE source code's BeginPlay function.
	// Note that, this instance is still active by this time.
	UFUNCTION(BlueprintImplementableEvent, meta=(FriendlyName="OnCollection"))
	virtual void ReceiveOnCollection();
	virtual void OnCollection(class ACharacterController& controller);

	// Setup blueprint related stuff here, e.g., the FInventoryItemInfo's Class property.
	virtual void BeginPlay() override;
};
