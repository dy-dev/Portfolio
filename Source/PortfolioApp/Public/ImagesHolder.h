// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ImagesHolder.generated.h"

class UTexture2D;
/**
 * 
 */   
UCLASS()
class PORTFOLIOAPP_API UImagesHolder  : public UObject
{

    GENERATED_BODY()
public:
    UImagesHolder();
	~UImagesHolder();

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Diaporama" )
        TArray<UTexture2D*> Images;


};
