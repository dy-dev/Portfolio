// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PortFolioPlayerController.generated.h"


class UImageLoader;
class UAnimLoader;
class UImagesHolder;
/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API APortFolioPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    APortFolioPlayerController( const class FObjectInitializer& ObjectInitializer );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Portfolio Images" )
        UImagesHolder* ImagesHolder;
    
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Portfolio Images" )
        UAnimLoader* AnimLoader;
  
    UFUNCTION( BlueprintCallable, Category = "Portfolio Images" )
        void FillImageArray( const FString& FilePath );

protected:
    /** @brief   Function call when the game start */
    virtual void BeginPlay() override;


private:
    UImageLoader* m_pImageLoader;

};
