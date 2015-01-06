// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


struct MOSAIC_API InputActions
{
	static const FName InventorySelection;
};


/**
 * 
 */
class MOSAIC_API SlateInputMap
{
public:
	static SlateInputMap& GetInstance()
	{
		static SlateInputMap Instance;
		return Instance;
	}

	~SlateInputMap();

	bool IsValidActionKey(const FName actionName, const FKey inputKey);
	bool IsValidActionKey(const FKey key);
private:
	SlateInputMap();

	/** Map of Action Name to details about the keys mapped to that action */
	TMap<FName, TArray<FKey>>* Map;
};
