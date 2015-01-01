// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "InventorySlotWidget.h"

TSharedRef<SWidget> UInventorySlotWidget::RebuildWidget()
{
	TSharedRef<SWidget> root = Super::RebuildWidget();

	
	if (!bDesignTime){
		UButton* button = Cast<UButton>(GetWidgetFromName(TEXT("Button")));

		button->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnClickDoSometing);
	}

	return root;
}

//void UInventorySlotWidget::Construct_Implementation()
//{
//	Super::Construct_Implementation();
//
//	UButton* button = Cast<UButton>(GetWidgetFromName(TEXT("Button")));
//
//	button->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnClickDoSometing);
//}

void UInventorySlotWidget::OnClickDoSometing()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("OnClickDoSometing"));
}