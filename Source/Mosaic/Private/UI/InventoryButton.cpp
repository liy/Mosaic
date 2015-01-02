// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "SInventoryButton.h"
#include "InventoryButton.h"

TSharedRef<SWidget> UInventoryButton::RebuildWidget()
{
	SlateButton = SNew(SInventoryButton);

	//if (GetChildrenCount() > 0)
	//{
	//	GetContentSlot()->BuildSlot(SlateButton.ToSharedRef());
	//}

	return SlateButton.ToSharedRef();
}

//void UInventorySlotWidget::Construct_Implementation()
//{
//	Super::Construct_Implementation();
//
//	UButton* button = Cast<UButton>(GetWidgetFromName(TEXT("Button")));
//
//	button->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnClickDoSometing);
//}

//void UInventorySlotWidget::OnClickDoSometing()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("OnClickDoSometing"));
//}

void UInventoryButton::SetBackgroundColor(FLinearColor InBackgroundColor)
{

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