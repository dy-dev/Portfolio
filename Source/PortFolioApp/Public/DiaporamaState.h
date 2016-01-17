// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "DiaporamaState.generated.h"



/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API ADiaporamaState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ADiaporamaState(const class FObjectInitializer& ObjectInitializer);


private:
	UTexture2D* LoadTexture(FString TextureFilename);

};
