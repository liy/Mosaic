// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PanelWidget.h"
#include "TestButton.generated.h"

/**
 * 
 */
UCLASS()
class MOSAIC_API UTestButton : public UPanelWidget
{
	GENERATED_BODY()
	
public:
	virtual TSharedRef<SWidget> RebuildWidget() override;
};
