//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyUIWidget.h

#pragma once

#include "SlateBasics.h"

DECLARE_DELEGATE_TwoParams(FOnMouseEnter, const FGeometry&, const FPointerEvent&);
DECLARE_DELEGATE_OneParam(FOnMouseLeave, const FPointerEvent&);

class SInventoryButton : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SInventoryButton) :
		// Setup default values
		_OwnerHUD(),
		_Image(FCoreStyle::Get().GetDefaultBrush()),
		_BorderImage(FCoreStyle::Get().GetBrush("Border")),
		_CountText(FText::FromString("99")),
		_HAlign(HAlign_Fill),
		_VAlign(VAlign_Fill),
		_ColorAndOpacity(FLinearColor::White),
		_BorderColor(FLinearColor::White)
		//_OnClicked(),
		//_OnMouseEnterDelegate(),
		//_OnMouseLeaveDelegate()
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_ARGUMENT(const FSlateBrush*, Image);

	/** Horizontal alignment */
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

	/** Vertical alignment */
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)

	SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)

	SLATE_ATTRIBUTE(FSlateColor, BorderColor)

	SLATE_ATTRIBUTE(const FSlateBrush*, BorderImage)

	SLATE_ATTRIBUTE(FText, CountText)

	SLATE_EVENT(FOnClicked, OnClicked)

	SLATE_EVENT(FOnMouseEnter, OnMouseEnterDelegate)

	SLATE_EVENT(FOnMouseLeave, OnMouseLeaveDelegate)

	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

	// Mouse handlers
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseEnter(const FGeometry& geometry, const FPointerEvent& mouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& mouseEvent) override;


	/** See the Image attribute */
	void SetImage(TAttribute<const FSlateBrush*> InImage);

	/** See BorderImage attribute */
	void SetBorderImage(const TAttribute<const FSlateBrush*>& InBorderImage);

	/**
	 * Sets the text string currently being edited
	 *
	 * @param  countText  The new text string
	 */
	void SetText(const TAttribute<FText>& text);

	const FText& GetText() const;

	void SetColorAndOpacity(const TAttribute<FSlateColor>& color);

	void SetBorderColor(const TAttribute<FSlateColor>& color);

protected:
	/** Pointer to our parent HUD */
	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	TAttribute<const FSlateBrush*> Image;

	TAttribute<const FSlateBrush*> BorderImage;

	TSharedPtr<SImage> ImageWidget;

	TSharedPtr<SBorder> BorderWidget;

	// The editable text box.
	TSharedPtr<SEditableTextBox> TextBox;

	/** Color and opacity scale for this image */
	//TAttribute<FSlateColor> ColorAndOpacity;

// User interaction
protected:
	bool bIsMouseButtonDown;

	FOnClicked OnClicked;

	FOnMouseEnter OnMouseEnterDelegate;

	FOnMouseLeave OnMouseLeaveDelegate;

public:
	void SetOnClicked(FOnClicked InOnClicked);
	void SetOnMouseEnter(FOnMouseEnter InOnMouseEnter);
	void SetOnMouseLeave(FOnMouseLeave InOnMouseLeave);
};