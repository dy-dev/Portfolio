// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PortFolioPlayerController.generated.h"

/**
*  @class ADiaporamaState
*
* 	@brief Class representing
*/
UENUM( BlueprintType )		//"BlueprintType" is essential to include
enum class EActiveWidget : uint8
{
    VE_Menus 	UMETA( DisplayName = "Menu" ),
    VE_Diapo 	UMETA( DisplayName = "Diapo" ),
    VE_3D 	    UMETA( DisplayName = "3D" ),
    VE_Anim 	UMETA( DisplayName = "Anim" )
};

class ImageLoader;
class ImagesHolder;
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
        TArray<UTexture2D*> Images;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Diaporama" )
        FString ImagesPaths;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Diaporama" )
        EActiveWidget CurrentActiveWidget;

private:
    ImageLoader* m_pImageLoader;
    ImagesHolder* m_pImagesHolder;

};
