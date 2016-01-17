// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "PortfolioPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOAPP_API APortfolioPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	
public:
    /**
    * @brief	Constructor.
    *
    * @param	ObjectInitializer	The object initializer.
    */
    APortfolioPlayerState( const class FObjectInitializer& ObjectInitializer );

	
};
