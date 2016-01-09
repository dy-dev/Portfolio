// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "DiaporamaState.generated.h"


/**
*  @class ADiaporamaState
*
* 	@brief Class representing
*/
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EActiveWidget : uint8
{
	VE_Menus 	UMETA(DisplayName = "Menu"),
	VE_Tour 	UMETA(DisplayName = "Tour"),
	VE_Gallery 	UMETA(DisplayName = "Gallery")
};

/**
 *
 */
UCLASS()
class PORTFOLIOAPP_API ADiaporamaState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ADiaporamaState(const class FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diaporama")
		TArray<UTexture2D*> Images;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diaporama")
		FString ImagesPaths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diaporama")
		EActiveWidget CurrentActiveWidget;


private:
	UTexture2D* LoadTexture(FString TextureFilename);

};
