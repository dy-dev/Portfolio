// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PortFolioPlayerController.generated.h"


class UImageLoader;
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

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Diaporama" )
        UImagesHolder* ImagesHolder;

private:
    UImageLoader* m_pImageLoader;
    

};
