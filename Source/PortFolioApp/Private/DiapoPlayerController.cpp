// Fill out your copyright notice in the Description page of Project Settings.

#include "PortFolioApp.h"
#include "DiapoPlayerController.h"
#include "DiaporamaState.h"

#include <string>

ADiapoPlayerController::ADiapoPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ADiaporamaState* DiaporamaState = Cast<ADiaporamaState>(this->PlayerState);
	/*if (DiaporamaState != 0x0 && DiaporamaState->Images.Num() > 0)
	{
		UTexture2D* tex = DiaporamaState->Images[0];
		FString texName = tex->GetName();
		std::string strfileName(TCHAR_TO_ANSI(*texName));
	}*/
}