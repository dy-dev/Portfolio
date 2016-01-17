// Fill out your copyright notice in the Description page of Project Settings.

#include "PortfolioApp.h"
#include "SlateHud.h"
#include "SlateGameMode.h"
#include "DiapoPlayerController.h"
#include "PortFolioPlayerController.h"
#include "DiaporamaState.h"
#include "PortfolioPlayerState.h"

ASlateGameMode::ASlateGameMode() : Super()
{
	//Set the hud class to use our custom HUD by default.
	this->HUDClass = ASlateHUD::StaticClass();
	this->PlayerControllerClass = APortFolioPlayerController::StaticClass();
	this->PlayerStateClass = APortfolioPlayerState::StaticClass();
}


