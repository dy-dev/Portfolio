// Fill out your copyright notice in the Description page of Project Settings.

#include "PortFolioApp.h"
#include "SlateHud.h"
#include "SlateGameMode.h"
#include "DiapoPlayerController.h"
#include "DiaporamaState.h"

ASlateGameMode::ASlateGameMode() : Super()
{
	//Set the hud class to use our custom HUD by default.
	this->HUDClass = ASlateHUD::StaticClass();
	this->PlayerControllerClass = ADiapoPlayerController::StaticClass();
	this->PlayerStateClass = ADiaporamaState::StaticClass();
}


