// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PickupDataLibrary.h" 
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UInventory();
	UInventory(int32 size);
	
	// If you want to expose the integer to blueprint, it has to be 32 bit signed integer?!?!
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Property)
	int32 MaxSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Property)
	TArray<FPickupData> DataEntries;

	UFUNCTION(BlueprintCallable, Category = Manipulation)
	void Add(const FPickupData item);

	UFUNCTION(BlueprintCallable, Category = Manipulation)
	int32 Remove(const FPickupData& item);

	UFUNCTION(BlueprintCallable, Category = Manipulation)
	void RemoveAt(int32 index);

	UFUNCTION(BlueprintCallable, Category=Manipulation)
	void Clear();
};
