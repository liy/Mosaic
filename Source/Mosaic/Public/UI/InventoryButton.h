// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Blueprint/UserWidget.h"

#include "InventoryButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryButtonClicked);
// Not sure why I cannot use return type defined in InventoryButton::SlateHandleMouseEnter and InventoryButton::SlateHandleMouseLeave?
// Maybe it is because SInventoryButton::OnMouseEnter and SInventoryButton::OnMouseLeave does not have return type?!?!
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryButtonMouseEnter, const FGeometry&, geometry, const FPointerEvent&, mouseEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryButtonMouseLeave, const FPointerEvent&, mouseEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryButtonSelection, const FGeometry&, geometry, const FKeyEvent&, keyEvent);


/**
 * 
 */
UCLASS()
class MOSAIC_API UInventoryButton : public UWidget
{
	GENERATED_BODY()

public:
	UInventoryButton(const FObjectInitializer& objectInitializer);

	/** The color multiplier for the button content */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
	FLinearColor ColorAndOpacity;

	/** The color multiplier for the button background */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Appearance)
	FLinearColor BackgroundColor;

	/** Image to draw */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Content)
	FSlateBrush ImageBrush;

	UPROPERTY()
	FGetSlateBrush ImageBrushDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Content)
	FSlateBrush BorderImageBrush;

	UPROPERTY()
	FGetSlateBrush BorderImageBrushDelegate;

	/** The text content for this editable text box widget */
	UPROPERTY(EditDefaultsOnly, Category = Content)
	FText Text;

	/** 
	 * A bindable delegate to allow logic to drive the text of the widget.
	 * OPTIONAL_BINDING() Macro requires this UPROPERTY.
	 **/
	UPROPERTY()
	FGetText TextDelegate;


	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable)
	FOnInventoryButtonClicked OnClicked;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryButtonMouseEnter OnMouseEnter;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryButtonMouseLeave OnMouseLeave;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryButtonSelection OnSelection;

public:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void SynchronizeProperties() override;

	/** Sets the color multiplier for the button background */
	UFUNCTION(BlueprintCallable, Category=Custom)
	void SetColorAndOpacity(FLinearColor InBackgroundColor);

	/** Sets the color multiplier for the button background */
	UFUNCTION(BlueprintCallable, Category=Custom)
	void SetBackgroundColor(FLinearColor InBackgroundColor);


	UFUNCTION(BlueprintCallable, Category=Custom)
	void SetBrushFromTextureForImage(UTexture2D* Texture);


	UFUNCTION(BlueprintCallable, Category=Custom)
	void SetBrushFromTextureForBorderImage(UTexture2D* Texture);

	UFUNCTION(BlueprintCallable, Category=Custom)
	void SetText(FText inText);

	UFUNCTION(BlueprintCallable, Category = Custom)
	FText GetText() const;

protected:
	/** Handle the actual click event from slate and forward it on */
	FReply SlateHandleClicked();

	void SlateHandleMouseEnter(const FGeometry& geometry, const FPointerEvent& mouseEvent);

	void SlateHandleMouseLeave(const FPointerEvent& mouseEvent);

	void SlateHandleOnSelection(const FGeometry& geometry, const FKeyEvent& keyEvent);

protected:

	/** Translates the bound brush data and assigns it to the cached brush used by this widget. */
	const FSlateBrush* ConvertImage(TAttribute<FSlateBrush> InImageAsset) const;

	/** Translates the bound brush data and assigns it to the cached brush used by this widget. */
	const FSlateBrush* ConvertBorderImage(TAttribute<FSlateBrush> InImageAsset) const;

private:

	/** Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<class SInventoryButton> SlateButton;

#if WITH_EDITOR
public:
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
#endif
};
