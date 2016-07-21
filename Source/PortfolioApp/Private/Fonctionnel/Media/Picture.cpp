#include "PortfolioApp.h"

#include "Picture.h"

UPicture::UPicture()
{
	m_sType = "Picture";
	m_TexturePicture = nullptr;
	m_LoaderPicture = nullptr;
}

//UPicture::UPicture(FString p_sPath, uint8 p_iExtension)
//{
//	m_sFullPath = p_sPath;
//	m_sType = "Picture";
//	m_iExtension = p_iExtension;
//	m_TexturePicture = nullptr;
//	m_LoaderPicture = new LoaderPicture();
//	FillData();
//
//}

void UPicture::Initializer(FString p_sPath, FString p_sFullPath, uint8 p_sExtension)
{
	Super::Initializer(p_sPath, p_sFullPath, p_sExtension);
	m_LoaderPicture = new LoaderPicture();
	FillData();
}

UPicture::~UPicture()
{
}

FString UPicture::GetFullPath()
{
	return m_sFullPath;
}


void UPicture::FillData()
{
	if (m_LoaderPicture != nullptr)
	{
		m_LoaderPicture->WrapImage(m_sFullPath, m_iExtension);
		m_LoaderPicture->LoadTexture(m_sFullPath, m_TexturePicture);
	}
}
