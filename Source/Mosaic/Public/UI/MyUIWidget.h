//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyUIWidget.h

#pragma once

#include "MyHUD.h"
#include "SlateBasics.h"

class SMyUIWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SMyUIWidget)
	{}
	/*See private declaration of OwnerHUD below.*/
	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

		SLATE_END_ARGS()

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Needed for every widget
	/////Builds this widget and any of it's children
	void Construct(const FArguments& InArgs);
private:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pointer to our parent HUD
	/////To make sure HUD's lifetime is controlled elsewhere, use "weak" ptr.
	/////HUD has "strong" pointer to Widget,
	/////circular ownership would prevent/break self-destruction of hud/widget (cause memory leak).
	TWeakObjectPtr<class AMyHUD> OwnerHUD;
};