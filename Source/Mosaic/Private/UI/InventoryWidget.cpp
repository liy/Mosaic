// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "CharacterController.h"
#include "InventoryWidget.h"
#include "InventoryButton.h"
#include "Inventory.h"
#include "Pickup.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// I cannot use "new", have to use CreateDefaultSubobject?!?!?
	// Inventory = new UInventory();
	// Cannot use ConstructObject?!?!? Is it because I'm in the class constructor?! I have to use CreateDefaultSubobject in constructor for all Unreal Object!?!?!
	// If I'm not in the constructor, I can use ConstructObject?!?!??!?!
	// Inventory = ConstructObject<UInventory>(UInventory::StaticClass(), this);
	Inventory = objectInitializer.CreateDefaultSubobject<UInventory>(this, TEXT("Inventory"));

	Activate(false);

	static ConstructorHelpers::FClassFinder<UUserWidget> classObject(TEXT("/Game/UI/InventoryButtonBP"));
	if (classObject.Class != NULL)
	{
		InventoryButtonClass = classObject.Class;
	}
}

TSharedRef<SWidget> UInventoryWidget::RebuildWidget()
{
	TSharedRef<SWidget> root = Super::RebuildWidget();

	if (!bDesignTime){
		ButtonContainer = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel")));

		// Initialize the slots
		int len = Inventory->Num();
		if (len != 0){
			ButtonContainer->ClearChildren();
			for (int i = 0; i < len; ++i)
			{
				CreateButton(Inventory->Get(i), i);
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
			SetPositionInViewport(screenLocation);
		}
	}
}

void UInventoryWidget::Activate(bool flag)
{
	IsActive = flag;
	if (IsActive)
	{
		SetVisibility(ESlateVisibility::Visible);
		FocusIn();
	}
	else{
		SetVisibility(ESlateVisibility::Hidden);
		FocusOff();
	}
}

void UInventoryWidget::Add(const FPickupData& data)
{
	Inventory->Add(data);

	CreateButton(data, Inventory->Num() - 1);
}

void UInventoryWidget::Remove(const FPickupData& data)
{
	int32 index = Inventory->Remove(data);

	ButtonContainer->RemoveChildAt(index);
}

void UInventoryWidget::RemoveAt(int32 index)
{
	Inventory->RemoveAt(index);

	ButtonContainer->RemoveChildAt(index);
}

UUserWidget* UInventoryWidget::GetChildAt(int32 index)
{
	return Cast<UUserWidget>(ButtonContainer->GetChildAt(index));
}

void UInventoryWidget::CreateButton(const FPickupData& data, int index)
{
	UUserWidget* buttonBP = CreateWidget<UUserWidget>(GetOwningPlayer(), InventoryButtonClass);

	UUniformGridSlot* slot = ButtonContainer->AddChildToUniformGrid(buttonBP);
	slot->SetRow(index / 4);
	slot->SetColumn(index % 4);

	Cast<UInventoryButton>(buttonBP->GetWidgetFromName("InventoryButton"))->SetBrushFromTextureForImage(data.Texture);
}