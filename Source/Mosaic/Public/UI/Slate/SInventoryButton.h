//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyUIWidget.h

#pragma once

#include "SlateBasics.h"

class SInventoryButton : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SInventoryButton) :
		_OwnerHUD(),
		_Image(FCoreStyle::Get().GetDefaultBrush()),
		_BorderImage(FCoreStyle::Get().GetBrush("Border")),
		_HAlign(HAlign_Fill),
		_VAlign(VAlign_Fill),
		_ColorAndOpacity(FLinearColor::White),
		_OnMouseEnter(),
		_OnMouseLeave()
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_ARGUMENT(const FSlateBrush*, Image);

	/** Horizontal alignment */
	SLATE_ARGUMENT(EHorizontalAlignment, HAlign)

	/** Vertical alignment */
	SLATE_ARGUMENT(EVerticalAlignment, VAlign)

	/** Spacing between button's border and the content. */
	SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)

	SLATE_ATTRIBUTE(const FSlateBrush*, BorderImage)

	SLATE_EVENT(FPointerEventHandler, OnMouseEnter)

	SLATE_EVENT(FPointerEventHandler, OnMouseLeave)

	SLATE_END_ARGS()

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Needed for every widget
	/////Builds this widget and any of it's children
	void Construct(const FArguments& InArgs);

	virtual void OnMouseEnter(const FGeometry& geometry, const FPointerEvent& mouseEvent) override;

	virtual void OnMouseLeave(const FPointerEvent& mouseEvent) override;

	void SetOnMouseEnter(FPointerEventHandler EventHandler);

	void SetOnMouseLeave(FPointerEventHandler EventHandler);

	/** See the Image attribute */
	void SetImage(TAttribute<const FSlateBrush*> InImage);

	/** See BorderImage attribute */
	void SetBorderImage(const TAttribute<const FSlateBrush*>& InBorderImage);

protected:
	/** Pointer to our parent HUD */
	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	TAttribute<const FSlateBrush*> Image;

	TAttribute<const FSlateBrush*> BorderImage;

	TSharedPtr<SImage> ImageWidget;

	TSharedPtr<SBorder> BorderWidget;

	/** Color and opacity scale for this image */
	TAttribute<FSlateColor> ColorAndOpacity;

	FPointerEventHandler OnMouseEnterHandler;

	FPointerEventHandler OnMouseLeaveHandler;
};