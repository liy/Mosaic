// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "CharacterController.h"
#include "InventoryWidget.h"
#include "InventorySlotWidget.h"
#include "Inventory.h"
#include "Pickup.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer), IsActive(false)
{
	// I cannot use "new", have to use CreateDefaultSubobject?!?!?
	// Inventory = new UInventory();
	// Cannot use ConstructObject?!?!? Is it because I'm in the class constructor?! I have to use CreateDefaultSubobject in constructor for all Unreal Object!?!?!
	// If I'm not in the constructor, I can use ConstructObject?!?!??!?!
	// Inventory = ConstructObject<UInventory>(UInventory::StaticClass(), this);
	Inventory = objectInitializer.CreateDefaultSubobject<UInventory>(this, TEXT("Inventory"));

	static ConstructorHelpers::FClassFinder<UInventorySlotWidget> classObject(TEXT("/Game/UI/InventorySlotWidgetBP"));
	if (classObject.Class != NULL)
	{
		SlotWidgetClass = classObject.Class;
	}
}

//TSharedRef<SWidget> UInventoryWidget::RebuildWidget()
//{
//	TSharedRef<SWidget> root = Super::RebuildWidget();
//
//	if (!IsDesignTime()){a
//		/*UWidget* RootWidget = Blueprint->WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
//		RootWidget->SetIsDesignTime(true);
//		Blueprint->WidgetTree->RootWidget = RootWidget;*/
//
//		SlotContainer = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel")));
//		UInventorySlotWidget* slotWidget = WidgetTree->ConstructWidget<UInventorySlotWidget>(SlotWidgetClass);
//		UUniformGridSlot* gridSlot = SlotContainer->AddChildToUniformGrid(slotWidget);
//		gridSlot->SetRow(1);
//		gridSlot->SetColumn(1);
//
//		// Get all widgets
//		TArray<UWidget*> widgets;
//		WidgetTree->GetAllWidgets(widgets);
//
//		Slots.Reset();
//		for (UWidget* widget : widgets)
//		{
//			//if (widget->GetClass()->IsChildOf(UInventorySlotWidget::StaticClass()))
//			if (widget->IsA(UInventorySlotWidget::StaticClass()))
//			{
//				Slots.Add(Cast<UInventorySlotWidget>(widget));
//			}
//		}
//
//		
//	}
//
//	return root;
//}

TSharedRef<SWidget> UInventoryWidget::RebuildWidget()
{
	TSharedRef<SWidget> root = Super::RebuildWidget();

	if (!bDesignTime){
		SlotContainer = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel")));

		// Initialize the slots
		int len = Inventory->Num();
		if (len != 0){
			SlotContainer->ClearChildren();
			for (int i = 0; i < len; ++i)
			{
				AddSlotAt(Inventory->Get(i), i);
			}
		}

		SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	}
	

	return root;
}

void UInventoryWidget::Construct_Implementation()
{
	Super::Construct_Implementation();
}

void UInventoryWidget::Tick_Implementation(FGeometry MyGeometry, float DeltaSeconds)
{
	Super::Tick_Implementation(MyGeometry, DeltaSeconds);

	if (IsActive)
	{
		FVector2D screenLocation;
		ACharacterController* controller = Cast<ACharacterController>(GetOwningPlayer());
		if (controller && controller->ProjectWorldLocationToScreen(controller->GetCharacter()->GetActorLocation(), screenLocation))
		{
			SetVisibility(ESlateVisibility::Visible);
			SetPositionInViewport(screenLocation);
		}
		else
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventoryWidget::Add(const FPickupData& data)
{
	Inventory->Add(data);

	AddSlotAt(data, Inventory->Num() - 1);
}

void UInventoryWidget::Remove(const FPickupData& data)
{
	int32 index = Inventory->Remove(data);

	SlotContainer->RemoveChildAt(index);
}

void UInventoryWidget::RemoveAt(int32 index)
{
	Inventory->RemoveAt(index);

	SlotContainer->RemoveChildAt(index);
}

void UInventoryWidget::AddSlotAt(const FPickupData& data, int index)
{
	UInventorySlotWidget* slotWidget = WidgetTree->ConstructWidget<UInventorySlotWidget>(SlotWidgetClass);
	UUniformGridSlot* gridSlot = SlotContainer->AddChildToUniformGrid(slotWidget);
	gridSlot->SetRow(index / 4);
	gridSlot->SetColumn(index % 4);

	slotWidget->SetTexture(data.Texture);
}