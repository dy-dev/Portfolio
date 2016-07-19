#include "PortfolioApp.h"

#include "Picture.h"

Picture::Picture(FString p_sPath, uint8 p_iExtension)
{
	m_sFullPath = p_sPath;
	m_sType = "Picture";
	m_iExtension = p_iExtension;
	m_TexturePicture = nullptr;
	m_LoaderPicture = new LoaderPicture();
	FillData();

}


Picture::~Picture()
{
}

FString Picture::GetFullPath()
{
	return m_sFullPath;
}


void Picture::FillData()
{
	if (m_LoaderPicture != nullptr)
	{
		m_LoaderPicture->WrapImage(m_sFullPath, m_iExtension);
		m_LoaderPicture->LoadTexture(m_sFullPath, m_TexturePicture);
	}
}
