// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "InventoryButton.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API UInventoryButton : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** Image to draw */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
	FSlateBrush ImageBrush;

	UPROPERTY()
	FGetSlateBrush ImageBrushDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
	FSlateBrush BorderImageBrush;

	UPROPERTY()
	FGetSlateBrush BorderImageBrushDelegate;

	/** The color multiplier for the button background */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
	FLinearColor BackgroundColor;

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void SynchronizeProperties() override;

	//void Construct_Implementation() override;

	/** Sets the color multiplier for the button background */
	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SetBackgroundColor(FLinearColor InBackgroundColor);


	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SetBrushFromTextureForImage(UTexture2D* Texture);


	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SetBrushFromTextureForBorderImage(UTexture2D* Texture);

protected:
	/** Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<class SInventoryButton> SlateButton;

	/** Translates the bound brush data and assigns it to the cached brush used by this widget. */
	const FSlateBrush* ConvertImage(TAttribute<FSlateBrush> InImageAsset) const;

	/** Translates the bound brush data and assigns it to the cached brush used by this widget. */
	const FSlateBrush* ConvertBorderImage(TAttribute<FSlateBrush> InImageAsset) const;
};
