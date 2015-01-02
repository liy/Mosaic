//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyHUD.cpp

#include "Mosaic.h"
#include "SInventoryButton.h"
#include "MyHUD.h"


AMyHUD::AMyHUD(const class FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void AMyHUD::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////So far only TSharedPtr<SMyUIWidget> has been created, now create the actual object.
	/////Create a SMyUIWidget on heap, our MyUIWidget shared pointer provides handle to object
	/////Widget will not self-destruct unless the HUD's SharedPtr (and all other SharedPtrs) destruct first.
	SAssignNew(InventoryButton, SInventoryButton).OwnerHUD(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pass our viewport a weak ptr to our widget
	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->
			/*Viewport's weak ptr will not give Viewport ownership of Widget*/
			AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(InventoryButton.ToSharedRef()));
	}

	if (InventoryButton.IsValid())
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/////Set widget's properties as visible (sets child widget's properties recursively)
		InventoryButton->SetVisibility(EVisibility::Visible);
	}
}