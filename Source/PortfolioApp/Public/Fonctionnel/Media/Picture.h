#pragma once

#include "Media.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"


class Picture : public Media
{
public:
	Picture(FString p_sPath, uint8 p_iExtension);
	~Picture();

	void FillData();

private :
	IImageWrapperPtr m_ImageWrapper; // A METTRE DS LE LOADER

};

