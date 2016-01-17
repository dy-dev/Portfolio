// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ImageLoader.generated.h"

class UImagesHolder;
/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API UImageLoader : public UObject
{
    GENERATED_BODY()

public:
    UImageLoader();
    ~UImageLoader();

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Diaporama" )
        FString ImagesPaths;

    void CreateSearchPaths( FString p_sPath, UImagesHolder* p_pHolder );

    UTexture2D* LoadTexture( FString TextureFilename );

private:

};
