#include "PortfolioApp.h"

#include "Picture.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"


Picture::Picture(FString p_sPath, uint8 p_iExtension)
{
	m_sFullPath = p_sPath;
	m_sType = "Picture";
	m_iExtension = p_iExtension;
	//Déclaration Loader en var membre
	FillData();

}


Picture::~Picture()
{
}

void Picture::FillData()
{
	//FONCTION 1
	TArray<uint8> RawFileData;
	if (FFileHelper::LoadFileToArray(RawFileData, *m_sFullPath)) //put all the data in RawFileData
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		// Note: PNG format.  Other formats are supported
		IImageWrapperPtr ImageWrapper;
		
		switch (m_iExtension)
		{
		case (uint8)EExtension::EPNG:
			ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
			break;
		case (uint8)EExtension::EJPG:
			ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
			break;
		case (uint8)EExtension::EBMP:
			ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);
			break;
		}

		//FONCTION 2
		//if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		//{
		//	const TArray<uint8>* UncompressedBGRA = NULL;
		//	if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		//	{
		//		ImagesPaths.Append(m_sFullPath + TEXT("\n"));
		//		// Create the UTexture for rendering
		//		UTexture2D* MyTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

		//		// Fill in the source data from the file
		//		FTexture2DMipMap& Mip = MyTexture->PlatformData->Mips[0];
		//		void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
		//		FMemory::Memcpy(Data, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
		//		Mip.BulkData.Unlock();
		//		MyTexture->UpdateResource();

		//		p_pHolder->Images.Add(MyTexture);
		//	}
		//}
	}
}
