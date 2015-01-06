// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "GameFramework/PlayerInput.h"
#include "SlateInputMap.h"

const FName InputActions::InventorySelection("InventorySelection");


SlateInputMap::SlateInputMap() : Map(new TMap<FName, TArray<FKey>>())
{
	// Inventory selection
	TArray<FKey> selectionKeys = TArray<FKey>();
	selectionKeys.Add(EKeys::Gamepad_LeftShoulder);
	Map->Add(InputActions::InventorySelection, selectionKeys);
}

SlateInputMap::~SlateInputMap()
{
	Map->Reset();
}

bool SlateInputMap::IsValidActionKey(const FName actionName, const FKey inputKey)
{
	const TArray<FKey>* keys = Map->Find(actionName);
	for (int i = 0; i < keys->Num(); ++i)
	{
		if ((*keys)[i] == inputKey)
		{
			return true;
		}
	}
	return false;
}