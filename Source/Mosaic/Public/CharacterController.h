// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PickupDataLibrary.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACharacterController(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPClasses)
	UClass* InventoryWidgetBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Inventory)
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Inventory)
	int32 Wealth;

	virtual void BeginPlay() override;

	// Collect the pickup
	UFUNCTION(BlueprintCallable, Category=Pickup)
	void Collect(class APickup* pickup);
	
	UFUNCTION(BlueprintCallable, Category=Pickup)
	void Drop(FPickupData& data);

	UFUNCTION(BlueprintCallable, Category=Pickup)
	bool CashOut(int32 value);

	// Put non-cash pickup into the inventory
	void StorePickup(class APickup* pickup);

	// Cash in the money! Called by Collect
	void CashIn(int32 value);
};
