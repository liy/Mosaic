// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "GameFramework/PlayerInput.h"
#include "SlateInputMap.h"

SlateInputMap::SlateInputMap() : Map(new TMap<FKey, FName>())
{
	Map->Add(FKey(), FName(""));
}

SlateInputMap::~SlateInputMap()
{
	Map->Reset();
}

bool SlateInputMap::IsValidActionKey(const FKey key, const FName actionName)
{
	const FName* name = Map->Find(key);
	return *name == actionName;
}

bool SlateInputMap::IsValidActionKey(const FKey key)
{
	if (Map->Find(key))
		return true;
	else
		return false;
}