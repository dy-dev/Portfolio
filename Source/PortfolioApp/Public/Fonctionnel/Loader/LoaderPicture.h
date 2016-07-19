#pragma once

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"

class UImagesHolder;
/**
*
*/
class LoaderPicture
{
public:
	LoaderPicture();
	~LoaderPicture();

	void WrapImage(FString p_sFullPath, uint8 p_iExtension);
	void LoadTexture(FString p_sFullPath, UTexture2D* p_TexturePicture);

private :
	IImageWrapperPtr m_ImageWrapperPtr;
	TArray<uint8> m_RawFileData;
};

