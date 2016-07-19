#include "PortfolioApp.h"

#include "LoaderPicture.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "Enums.h"

LoaderPicture::LoaderPicture()
{
}


LoaderPicture::~LoaderPicture()
{
}


void LoaderPicture::WrapImage(FString p_sFullPath, uint8 p_iExtension)
{
	if (FFileHelper::LoadFileToArray(m_RawFileData, *p_sFullPath)) //put all the data in RawFileData
	{
		IImageWrapperModule* ImageWrapperModule = &(FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper")));

		switch (p_iExtension)
		{
		case (uint8)EExtension::EPNG:
			m_ImageWrapperPtr = ImageWrapperModule->CreateImageWrapper(EImageFormat::PNG);
			break;
		case (uint8)EExtension::EJPG:
			m_ImageWrapperPtr = ImageWrapperModule->CreateImageWrapper(EImageFormat::JPEG);
			break;
		case (uint8)EExtension::EBMP:
			m_ImageWrapperPtr = ImageWrapperModule->CreateImageWrapper(EImageFormat::BMP);
			break;
		}
	}
}

						
void LoaderPicture::LoadTexture(FString p_sFullPath, UTexture2D* p_TexturePicture)
{
	if (m_ImageWrapperPtr.IsValid() && m_ImageWrapperPtr->SetCompressed(m_RawFileData.GetData(), m_RawFileData.Num()))
	{
		const TArray<uint8>* UncompressedBGRA = NULL;
		if (m_ImageWrapperPtr->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			//ImagesPaths.Append(p_sFullPath + TEXT("\n"));
			// Fill the UTexture for rendering
			p_TexturePicture = UTexture2D::CreateTransient(m_ImageWrapperPtr->GetWidth(), m_ImageWrapperPtr->GetHeight(), PF_B8G8R8A8);

			// Fill in the source data from the file
			FTexture2DMipMap& Mip = p_TexturePicture->PlatformData->Mips[0];
			void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(Data, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
			Mip.BulkData.Unlock();
			p_TexturePicture->UpdateResource();
		}
	}
}