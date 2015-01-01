// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "CharacterController.h"

#include "Pickup.h"
#include "CashPickup.h"
#include "InventoryWidget.h"

ACharacterController::ACharacterController(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// Setup the InventoryWidgetBP class, so we can add the widget instance to the viewport in BeginPlay()
	static ConstructorHelpers::FClassFinder<UUserWidget> classObject(TEXT("/Game/UI/InventoryWidgetBP"));
	if (classObject.Class != NULL)
	{
		InventoryWidgetBP = classObject.Class;
	}
}

void ACharacterController::BeginPlay()
{
	InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryWidgetBP);
	InventoryWidget->AddToViewport();

	Super::BeginPlay();
}

void ACharacterController::Collect(APickup* pickup)
{
	ACashPickup* cashPickup = Cast<ACashPickup>(pickup);
	if (cashPickup)
	{
		CashIn(cashPickup->Value);
	}
	else
	{
		StorePickup(pickup);
	}
}

void ACharacterController::Drop(FPickupData& data)
{
	InventoryWidget->Remove(data);

	// TODO: Spawn a new pickup on the ground, or destroy the pickup
}

void ACharacterController::StorePickup(APickup* pickup)
{
	InventoryWidget->Add(pickup->Data);
}

void ACharacterController::CashIn(int32 value)
{
	Wealth += value;

	// TODO: update UI
}

bool ACharacterController::CashOut(int32 value)
{
	if (Wealth >= value){
		Wealth -= value;

		// TODO: update UI
		return true;
	}

	return false;
}