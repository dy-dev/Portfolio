// Fill out your copyright notice in the Description page of Project Settings.

#include "PortFolioApp.h"
#include "SDDFileTree.h"
#include "SlateHUD.h"

ASlateHUD::ASlateHUD()
{

}

void ASlateHUD::BeginPlay()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	///////So far only TSharedPtr<SMyUIWidget> has been created, now create the actual object.
	///////Create a SMyUIWidget on heap, our MyUIWidget shared pointer provides handle to object
	///////Widget will not self-destruct unless the HUD's SharedPtr (and all other SharedPtrs) destruct first.
	MyUIWidget = SNew(SDDFileTree);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	///////Pass our viewport a weak ptr to our widget
	///////Viewport's weak ptr will not give Viewport ownership of Widget
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	///////Set widget's properties as visible (sets child widget's properties recursively)
	MyUIWidget->SetVisibility(EVisibility::Visible);
}