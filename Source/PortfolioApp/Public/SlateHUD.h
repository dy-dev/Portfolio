// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "SlateHUD.generated.h"

class SDDFileTree;

/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API ASlateHUD : public AHUD
{
	GENERATED_BODY()
public:

	ASlateHUD();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Reference to an SCompoundWidget, TSharedPtr adds to the refcount of MyUIWidget
	/////MyUIWidget will not self-destruct as long as refcount > 0
	/////MyUIWidget refcount will be (refcout-1) if HUD is destroyed.
	TSharedPtr<SDDFileTree> MyUIWidget;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called as soon as game starts, create SCompoundWidget and give Viewport access
	void BeginPlay();
};
