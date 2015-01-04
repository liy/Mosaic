// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupDataLibrary.generated.h"

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	Head,
	Food,
	Resource,
	Cash
};

USTRUCT(BlueprintType)
struct FPickupProperty
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Identified;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
};

/**
* For inventory item information
*/
USTRUCT(BlueprintType)
struct FPickupData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPickupType> Tags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor> Class;

	// Thumbnail of the inventory item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attachment)
	FPickupProperty property;

	// Information about the inventory item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Info;

	// Inventory.Remove(item) requires implementation of the comparison operator.
	FORCEINLINE bool operator==(const FPickupData& data) const
	{
		return Class == data.Class && Texture == data.Texture && Info.EqualTo(data.Info);
	}
};