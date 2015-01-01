// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	//void Construct_Implementation() override;

	UFUNCTION(BlueprintCallable, Category=Custom)
	void OnClickDoSometing();

	UFUNCTION(BlueprintImplementableEvent, Category=Custom)
	void SetTexture(class UTexture2D* texture);
};
