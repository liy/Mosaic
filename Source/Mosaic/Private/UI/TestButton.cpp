// Fill out your copyright notice in the Description page of Project Settings.

#include "Mosaic.h"
#include "TestButton.h"

TSharedRef<SWidget> UTestButton::RebuildWidget()
{
	//TSharedRef<SWidget> root = Super::RebuildWidget();

	UWidget* widget = ConstructObject<UCanvasPanel>(UCanvasPanel::StaticClass());
	widget->SetIsDesignTime(true);
	AddChild(widget);

	return widget->TakeWidget();
}