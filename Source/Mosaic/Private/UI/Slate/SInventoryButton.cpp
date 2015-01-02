//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyUIWidget.cpp

#include "Mosaic.h"
#include "SInventoryButton.h"

#define LOCTEXT_NAMESPACE "Mosaic"

void SInventoryButton::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	Image = InArgs._Image;
	BorderImage = InArgs._BorderImage;
	ColorAndOpacity = InArgs._ColorAndOpacity;
	OnMouseEnterHandler = InArgs._OnMouseEnter;
	OnMouseLeaveHandler = InArgs._OnMouseLeave;
	
	ChildSlot
	[
		SAssignNew(BorderWidget, SBorder)
		.BorderImage(InArgs._BorderImage)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(5)
			.HeightOverride(64)
			.WidthOverride(64)
			[
				SAssignNew(ImageWidget, SImage)
			]
		]
	];
	
	
}

void SInventoryButton::OnMouseEnter(const FGeometry& geometry, const FPointerEvent& mouseEvent)
{
	SWidget::OnMouseEnter(geometry, mouseEvent);

	if (OnMouseEnterHandler.IsBound())
	{
		OnMouseEnterHandler.Execute(geometry, mouseEvent);
	}
}

void SInventoryButton::OnMouseLeave(const FPointerEvent& mouseEvent)
{
	SWidget::OnMouseLeave(mouseEvent);
}

void SInventoryButton::SetImage(TAttribute<const FSlateBrush*> InImage)
{
	Image = InImage;
	ImageWidget->SetImage(Image);
}

void SInventoryButton::SetBorderImage(const TAttribute<const FSlateBrush*>& InBorderImage)
{
	BorderImage = InBorderImage;
	BorderWidget->SetBorderImage(BorderImage);
}

#undef LOCTEXT_NAMESPACE