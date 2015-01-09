#pragma once

#include "SlateBasics.h"

class MOSAIC_API SPageBox : public SCompoundWidget
{
public:
	class MOSAIC_API FSlot : public TSlotBase<FSlot>, public TSupportsContentPaddingMixin < FSlot >
	{
	public:
		FSlot() : TSlotBase<FSlot>(),
			HAlignment(HAlign_Fill),
			VAlignment(VAlign_Fill)
		{
		}

		EHorizontalAlignment HAlignment;
		EVerticalAlignment VAlignment;

		FSlot& HAlign(EHorizontalAlignment hAlignment)
		{
			HAlignment = hAlignment;
			return *this;
		}

		FSlot& VAlign(EVerticalAlignment vAlignment)
		{
			VAlignment = vAlignment;
			return *this;
		}
	};


	SLATE_BEGIN_ARGS(SPageBox) : _Orientation(Orient_Vertical)
	{}

		SLATE_SUPPORTS_SLOT(FSlot)

		/** The direction that children will be stacked, and also the direction the box will scroll. */
		SLATE_ARGUMENT(EOrientation, Orientation)

	SLATE_END_ARGS()

	// Not sure what this is for
	static FSlot& Slot();

	void Construct(const FArguments& InArgs);

	SPageBox::FSlot& AddSlot();

	void RemoveSlot(const TSharedRef<SWidget>& widget);

	void ClearChildren();

	// Get the current orientation of the scrollbox.
	EOrientation GetOrientation();

public:

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:

	// The panel which stacks the child slots. Contains the scroll content?
	TSharedPtr<class SPagePanel> PagePanel;

	/** The scrolling and stacking orientation. */
	EOrientation Orientation;

	void ConstructVerticalLayout();
};