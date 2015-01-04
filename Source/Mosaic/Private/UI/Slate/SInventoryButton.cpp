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
	//ColorAndOpacity = InArgs._ColorAndOpacity;
	//OnClicked = InArgs._OnClicked;
	//OnMouseEnterDelegate = InArgs._OnMouseEnterDelegate;
	//OnMouseLeaveDelegate = InArgs._OnMouseLeaveDelegate;
	
	ChildSlot
	[
		SAssignNew(BorderWidget, SBorder)
		.BorderImage(BorderImage)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(1)
			.HeightOverride(64)
			.WidthOverride(64)
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(ImageWidget, SImage).Image(Image)
				]

				+SOverlay::Slot()
				//.Padding(1)
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				[
					SAssignNew(TextBox, SEditableTextBox)
					.IsReadOnly(true)
					.BackgroundColor(FLinearColor(1.0f, 0.0f, 0.0f, 0.0f))
					.ForegroundColor(FLinearColor::Black)
					.Font(FSlateFontInfo("Arial", 12))
					.Text(InArgs._CountText)
				]
			]
		]
	];
}

FReply SInventoryButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bIsMouseButtonDown = true;
	return FReply::Handled();
}


FReply SInventoryButton::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();
	if (bIsMouseButtonDown)
	{
		bIsMouseButtonDown = false;

		if (OnClicked.IsBound())
		{
			Reply = OnClicked.Execute();
		}
		else{
			Reply = FReply::Handled();
		}
	}
	return Reply;
}

void SInventoryButton::OnMouseEnter(const FGeometry& geometry, const FPointerEvent& mouseEvent)
{
	SWidget::OnMouseEnter(geometry, mouseEvent);
	OnMouseEnterDelegate.ExecuteIfBound(geometry, mouseEvent);
}

void SInventoryButton::OnMouseLeave(const FPointerEvent& mouseEvent)
{
	SWidget::OnMouseLeave(mouseEvent);
	OnMouseLeaveDelegate.ExecuteIfBound(mouseEvent);
}

FReply SInventoryButton::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	// we handle this message so that the game doesn't get mouse moves without mouse downs/ups
	if (bIsMouseButtonDown)
	{
		return FReply::Handled();
	}
	return FReply::Unhandled();
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

void SInventoryButton::SetText(const TAttribute<FText>& text)
{
	TextBox->SetText(text);
}

const FText& SInventoryButton::GetText() const
{
	return TextBox->GetText();
}

void SInventoryButton::SetColorAndOpacity(const TAttribute<FSlateColor>& color)
{
	ImageWidget->SetColorAndOpacity(color);
}

void SInventoryButton::SetBorderColor(const TAttribute<FSlateColor>& color)
{
	BorderWidget->SetBorderBackgroundColor(color);
}

void SInventoryButton::SetOnClicked(FOnClicked inOnClicked)
{
	OnClicked = inOnClicked;
}

void SInventoryButton::SetOnMouseEnter(FOnMouseEnter InOnMouseEnter)
{
	OnMouseEnterDelegate = InOnMouseEnter;
}

void SInventoryButton::SetOnMouseLeave(FOnMouseLeave InOnMouseLeave)
{
	OnMouseLeaveDelegate = InOnMouseLeave;
}

bool SInventoryButton::SupportsKeyboardFocus() const
{
	return true;
}

FReply SInventoryButton::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Handled();
}

FReply SInventoryButton::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE