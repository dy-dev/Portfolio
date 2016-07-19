#pragma once

#include "Media.h"

#include "LoaderPicture.h"


class Picture : public Media
{
public:
	Picture(FString p_sPath, uint8 p_iExtension);
	~Picture();

	void FillData();
	FString GetFullPath();


private :
	LoaderPicture* m_LoaderPicture;
	UTexture2D* m_TexturePicture;
};

