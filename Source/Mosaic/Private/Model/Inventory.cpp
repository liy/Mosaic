// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "Inventory.h"

UInventory::UInventory(int32 maxSize) : Super(), MaxSize(maxSize)
{
}

UInventory::UInventory() : UInventory(10)
{

}

FPickupData& UInventory::Get(int32 index)
{
	return DataEntries[index];
}

void UInventory::Add(const FPickupData data)
{
	DataEntries.Add(data);
}

int32 UInventory::Remove(const FPickupData& data)
{
	return DataEntries.Remove(data);
}

void UInventory::RemoveAt(int32 index)
{
	DataEntries.RemoveAt(index);
}

void UInventory::Clear()
{
	DataEntries.Reset();
}

int32 UInventory::Num()
{
	return DataEntries.Num();
}