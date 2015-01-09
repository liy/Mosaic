//Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
//Author: Bleakwise
//File: MyUIWidget.cpp

#include "Mosaic.h"
#include "SPageBox.h"

// For construction use only? When use as: +SPageBox::Slot()?
SPageBox::FSlot& SPageBox::Slot()
{
	return *(new SPageBox::FSlot());
}

class SPagePanel : public SPanel
{
public:
	SLATE_BEGIN_ARGS(SPagePanel)
	{
		/** Visible to the user, but only as art. The cursors hit tests will never see this widget. */
		_Visibility = EVisibility::SelfHitTestInvisible;
	}

		SLATE_ARGUMENT(EOrientation, Orientation)

	SLATE_END_ARGS()

private:

	EOrientation Orientation;

public:

	float PhysicalOffset;

	TPanelChildren<SPageBox::FSlot> Children;

	SPagePanel() : Children()
	{
	}

	void Construct(const FArguments& InArgs, const TArray<SPageBox::FSlot*>& InSlots)
	{
		PhysicalOffset = 0;
		Children.Reserve(InSlots.Num());
		for (int32 SlotIndex = 0; SlotIndex < InSlots.Num(); ++SlotIndex)
		{
			Children.Add(InSlots[SlotIndex]);
		}
		Orientation = InArgs._Orientation;
	}

	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override
	{
		// TODO: need to implement this.
	}

	virtual FVector2D ComputeDesiredSize() const override
	{
		// TODO: needs implementation
		return  FVector2D::ZeroVector;
	}

	virtual FChildren* GetChildren() override
	{
		return &Children;
	}

	EOrientation GeOrientation()
	{
		return Orientation;
	}

	void SetOrientation(EOrientation orientation)
	{
		Orientation = orientation;
	}
};


/**
 * SPageBox
 */
void SPageBox::Construct(const FArguments& InArgs)
{
	Orientation = InArgs._Orientation;
	SAssignNew(PagePanel, SPagePanel, InArgs.Slots);

	ConstructVerticalLayout();
}

void SPageBox::ConstructVerticalLayout()
{
	ChildSlot
	[
		// just in case I need to add extra graphics above the scrolled content
		SNew(SOverlay)
		+ SOverlay::Slot()
		.Padding(FMargin(0))
		[
			// A panel that presents the scrolling content
			PagePanel.ToSharedRef()
		]
	];
}

SPageBox::FSlot& SPageBox::AddSlot()
{
	SPageBox::FSlot& slot = *new SPageBox::FSlot();
	PagePanel->Children.Add(&slot);

	return slot;
}

void SPageBox::RemoveSlot(const TSharedRef<SWidget>& widget)
{
	TPanelChildren<SPageBox::FSlot>& children = PagePanel->Children;
	for (int32 i = 0; i < children.Num(); ++i)
	{
		if (children[i].GetWidget() == widget)
		{
			children.RemoveAt(i);
			return;
		}
	}
}

void SPageBox::ClearChildren()
{
	PagePanel->Children.Empty();
}

void SPageBox::Tick(const FGeometry& geometry, const double currentTime, const float deltaTime)
{
	// Do scrolling here?
	
	TSharedPtr<SWidget> focusedWidget = FSlateApplicationBase::Get().GetKeyboardFocusedWidget();
	FGeometry focusedGeometry = this->FindChildGeometry(geometry, focusedWidget.ToSharedRef());
	FSlateRect focusedRect = TransformRect(focusedGeometry.GetAccumulatedRenderTransform(), FSlateRect(FVector2D(0.0f, 0.0f), focusedGeometry.GetLocalSize()));
	
	FSlateRect pageRect = TransformRect(geometry.GetAccumulatedRenderTransform(), FSlateRect(FVector2D(0.0f, 0.0f), geometry.GetLocalSize()));
	if (!FSlateRect::IsRectangleContained(pageRect, focusedRect)){
		// keep scroll towards focused widget
	}
}

EOrientation SPageBox::GetOrientation()
{
	return Orientation;
}