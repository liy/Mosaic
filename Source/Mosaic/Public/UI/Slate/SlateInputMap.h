// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	bool IsValidActionKey(const FKey key, const FName actionName);
	bool IsValidActionKey(const FKey key);
private:
	SlateInputMap();

	/** Map of Action Name to details about the keys mapped to that action */
	TMap<FKey, FName>* Map;
};
