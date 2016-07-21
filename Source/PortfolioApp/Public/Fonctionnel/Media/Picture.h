#pragma once

#include "Media.h"

#include "LoaderPicture.h"
#include "Picture.generated.h"


/**
*
*/
UCLASS(Blueprintable)
class PORTFOLIOAPP_API UPicture : public UMedia
{
	GENERATED_BODY()
public:
	UPicture();
	//UPicture(FString p_sPath, uint8 p_iExtension);
	~UPicture();

	virtual void Initializer(FString p_sPath, FString p_sFullPath, uint8 p_sExtension);


	void FillData();
	FString GetFullPath();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Picture")
	UTexture2D* m_TexturePicture;

private :
	LoaderPicture* m_LoaderPicture;
};

