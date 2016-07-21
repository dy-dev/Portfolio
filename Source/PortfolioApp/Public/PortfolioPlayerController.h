// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PortFolioPlayerController.generated.h"

//todo fwd declare filesort
class UImageLoader;
class UAnimLoader;
class UImagesHolder;
class ContentManager;
class DirectoryManager;
class UDisplayUIManager;
class UCategory_Button;
class UCategories_ScrollBox;


/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API APortFolioPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APortFolioPlayerController(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portfolio Images")
		UImagesHolder* ImagesHolder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portfolio Images")
		UAnimLoader* AnimLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portfolio Images")
		UDisplayUIManager* m_pDisplayUIManager;

	UFUNCTION(BlueprintCallable, Category = "Portfolio Images")
		void FillImageArray(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Portfolio")
		void RegisterCategoryScrollBox(UCategories_ScrollBox* p_pCatSB);

	TArray<FString> GetSubDirectoriesFromController();

	void CategoryButtonClicked(UCategory_Button* p_Button);


protected:
	/** @brief   Function call when the game start */
	virtual void BeginPlay() override;


private:
	//UImageLoader* m_pImageLoader;
	ContentManager* m_pContentManager;
};
