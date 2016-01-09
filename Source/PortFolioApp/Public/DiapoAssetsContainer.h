// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DiapoAssetsContainer.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API UDiapoAssetsContainer : public UUserWidget
{
	GENERATED_BODY()
public:
		/**
		* @brief	Constructor.
		*
		* @param	ObjectInitializer	The object initializer.
		*/
		UDiapoAssetsContainer(const class FObjectInitializer& ObjectInitializer);
	
	/** @brief	*. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diaporama")
		TArray<UTexture2D*> Images;


};
