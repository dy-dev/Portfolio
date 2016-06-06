// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "PortfolioPlayerState.generated.h"

/**
*  @class APortfolioPlayerState
*
* 	@brief Class representing
*/
UENUM( BlueprintType )		//"BlueprintType" is essential to include
enum class EActiveWidget : uint8
{
    VE_Menus 	    UMETA( DisplayName = "Menu" ),
    VE_Diapo 	    UMETA( DisplayName = "Diapo" ),
    VE_Categories 	UMETA( DisplayName = "Categories" ),
    VE_Flyer 	    UMETA( DisplayName = "Flyer" )
};

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
    
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "PlayerState" )
        EActiveWidget CurrentActiveWidget;


	
};
