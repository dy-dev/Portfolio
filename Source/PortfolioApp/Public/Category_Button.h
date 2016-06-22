// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "Category_Button.generated.h"

class UCategories_ScrollBox;
class APortFolioPlayerController;
/**
 * 
 */
UCLASS( Blueprintable )
class PORTFOLIOAPP_API UCategory_Button : public UButton
{
    GENERATED_UCLASS_BODY()

public : 
    void SetScrollBox( UCategories_ScrollBox* p_pScrollBox );
    void SetSubCategoryPath( FString p_sPath );

	void SetController(APortFolioPlayerController* p_pController) { m_pController = p_pController; };
  
    UFUNCTION( BlueprintCallable, Category = "Category Management" )
        void exploreSubCategory();

protected:
    // UWidget interface
    virtual TSharedRef<SWidget> RebuildWidget() override;
 
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Category Management" )
        FString subCategoryPath;


private:
    UCategories_ScrollBox* m_pScrollBox;
	APortFolioPlayerController* m_pController;
};
