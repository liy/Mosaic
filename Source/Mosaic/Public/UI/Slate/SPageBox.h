#pragma once

#include "SlateBasics.h"

class SPageBox : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SPageBox)
	{}

	SLATE_END_ARGS()

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Needed for every widget
	/////Builds this widget and any of it's children
	void Construct(const FArguments& InArgs);
};