// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "SInventoryButton.h"
#include "InventoryButton.h"

#define LOCTEXT_NAMESPACE "Mosaic"

UInventoryButton::UInventoryButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SInventoryButton::FArguments ButtonDefaults;
	//WidgetStyle = *ButtonDefaults._ButtonStyle;

	ColorAndOpacity = FLinearColor::White;
	BackgroundColor = FLinearColor::White;
}


TSharedRef<SWidget> UInventoryButton::RebuildWidget()
{
	MyWidget = SAssignNew(SlateButton, SInventoryButton);

	return SlateButton.ToSharedRef();
}

void UInventoryButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute<const FSlateBrush*> borderImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, BorderImageBrush, const FSlateBrush*, ConvertBorderImage);
	TAttribute<const FSlateBrush*> imageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, ImageBrush, const FSlateBrush*, ConvertImage);
	TAttribute<FText> TextBinding = OPTIONAL_BINDING(FText, Text);

	SlateButton->SetImage(imageBinding);
	SlateButton->SetBorderImage(borderImageBinding);
	SlateButton->SetText(TextBinding);

	SlateButton->SetColorAndOpacity(ColorAndOpacity);
	SlateButton->SetBorderColor(BackgroundColor);

	// interaction delegates
	SlateButton->SetOnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked));
	SlateButton->SetOnMouseEnter(BIND_UOBJECT_DELEGATE(FOnMouseEnter, SlateHandleMouseEnter));
	SlateButton->SetOnMouseLeave(BIND_UOBJECT_DELEGATE(FOnMouseLeave, SlateHandleMouseLeave));
}

void UInventoryButton::SetBrushFromTextureForImage(UTexture2D* Texture)
{
	ImageBrush.SetResourceObject(Texture);

	if (SlateButton.IsValid())
	{
		SlateButton->SetImage(&ImageBrush);
	}
}

void UInventoryButton::SetBrushFromTextureForBorderImage(UTexture2D* Texture)
{
	BorderImageBrush.SetResourceObject(Texture);

	if (SlateButton.IsValid())
	{
		SlateButton->SetBorderImage(&BorderImageBrush);
	}
}

const FSlateBrush* UInventoryButton::ConvertImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UInventoryButton* mutableThis = const_cast<UInventoryButton*>(this);
	mutableThis->ImageBrush = InImageAsset.Get();

	return &ImageBrush;
}

const FSlateBrush* UInventoryButton::ConvertBorderImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UInventoryButton* mutableThis = const_cast<UInventoryButton*>(this);
	mutableThis->BorderImageBrush = InImageAsset.Get();

	return &BorderImageBrush;
}

void UInventoryButton::SetColorAndOpacity(FLinearColor color)
{
	ColorAndOpacity = color;
	if (SlateButton.IsValid())
	{
		SlateButton->SetColorAndOpacity(color);
	}
}

void UInventoryButton::SetBackgroundColor(FLinearColor color)
{
	BackgroundColor = color;
	if (SlateButton.IsValid())
	{
		SlateButton->SetBorderColor(color);
	}
}

FText UInventoryButton::GetText() const
{
	return SlateButton->GetText();
}

void UInventoryButton::SetText(FText inText)
{
	SlateButton->SetText(inText);
}

FReply UInventoryButton::SlateHandleClicked()
{
	OnClicked.Broadcast();

	return FReply::Handled();
}

void UInventoryButton::SlateHandleMouseEnter(const FGeometry& geometry, const FPointerEvent& mouseEvent)
{
	OnMouseEnter.Broadcast(geometry, mouseEvent);

	//return FReply::Handled();
}

void UInventoryButton::SlateHandleMouseLeave(const FPointerEvent& mouseEvent)
{
	OnMouseLeave.Broadcast(mouseEvent);
}


#if WITH_EDITOR

const FSlateBrush* UInventoryButton::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Button");
}

const FText UInventoryButton::GetPaletteCategory()
{
	return LOCTEXT("Mosaic", "_Mosaic");
}

#endif

#undef LOCTEXT_NAMESPACE