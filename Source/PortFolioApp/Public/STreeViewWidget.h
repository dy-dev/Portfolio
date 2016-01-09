// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateHUD.h"
#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PORTFOLIOAPP_API STreeViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STreeViewWidget) {}
	/*See private declaration of OwnerHUD below.*/
	SLATE_ARGUMENT(TWeakObjectPtr<class SlateHUD>, OwnerHUD)

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
	TWeakObjectPtr<class SlateHUD> OwnerHUD;
};
