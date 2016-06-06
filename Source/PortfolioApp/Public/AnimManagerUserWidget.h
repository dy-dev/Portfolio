// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"

#include "Runtime/MediaAssets/Public/MediaPlayer.h"
#include "Runtime/MediaAssets/Public/MediaTexture.h"
#include "Runtime/MediaAssets/Public/MediaSoundWave.h"

/**
*
*/
//~~~~~~~~~~~~ UMG ~~~~~~~~~~~~~~~~
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "AnimManagerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOAPP_API UAnimManagerUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UAnimManagerUserWidget( const FObjectInitializer& ObjectInitializer );
	
protected:
    // UWidget interface
   // virtual TSharedRef<SWidget> RebuildWidget() override;
    // End of UWidget interface


    //Interface to the material we need to modify
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "3D Loader" )
        UMaterialInterface* InterfaceToAnimMaterial;

    UFUNCTION( BlueprintCallable, Category = "3D Loader" )
        void SetAnimatedMaterial( UImage* image, FString MovieName, UMediaSoundWave * sound );

    UFUNCTION( BlueprintCallable, Category = "Appearance" )
        void LoadAnimTexture( FString url, UMediaSoundWave * sound );
    UMediaTexture * m_mediaTexture;

};
