// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Categories_ScrollBox.generated.h"


/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API UCategories_ScrollBox : public UScrollBox
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Category Management" )
        FString RootPath;

    /** Update thickness of Soft Edge Image! Yay! */
    UFUNCTION( BlueprintCallable, Category = "Category Management" )
        void FillButtons();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE( FBindableEvent_DisplayImages );

    /** @brief The event that is broadcasted when the code is set */
    UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Category Management" )
        FBindableEvent_DisplayImages DisplayImages;


    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Category Management" )
        FButtonStyle ButtonStyle;

protected:
    // UWidget interface
    virtual TSharedRef<SWidget> RebuildWidget() override;
    // End of UWidget interface

    void ListImagesToDisplay();
    TMap< UButton*, FString> m_tmButtonToDir;
    TArray<UTexture2D*> m_aTextures;

};
