#include "PortfolioApp.h"

#include "FileSort.h"
#include "ImageLoader.h"
#include "ImagesHolder.h"
#include "Runtime/Engine/Public/DDSLoader.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

#include "DirectoryVisitor.h"

#include <string>
#include <vector> 
#include <map> 

//using namespace std;

FileSort::FileSort()
{
	sortArray("H:/Documents/S2/Stage/PortfolioApp/Saved/DiapoAssets/Image");
}


FileSort::~FileSort()
{
}


bool FileSort::sortArray(FString p_sPath)
{
	TArray<FString> Files;
	
	GetFiles(p_sPath, Files, false); //We put all the files in Files

	//std::multimap<const string, vector<string>> m_mPathMap;
	//vector<string> m_sPathVector;

	std::multimap<const std::string, FString> m_mExtensionPathMap;

	

	for (FString fileName : Files) //For each file 
	{
		std::string strdir(TCHAR_TO_ANSI(*fileName));
		if (FPaths::GetExtension(fileName).ToLower() == "jpg" ||
			FPaths::GetExtension(fileName).ToLower() == "jpeg" ||
			FPaths::GetExtension(fileName).ToLower() == "png" ||
			FPaths::GetExtension(fileName).ToLower() == "bmp")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string , FString>("picture", fileName));
		}

		else if (FPaths::GetExtension(fileName).ToLower() == "mp4" ||
			FPaths::GetExtension(fileName).ToLower() == "mpeg4" ||
			FPaths::GetExtension(fileName).ToLower() == "avi")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string, FString>("anim", fileName));
		}

		else if (FPaths::GetExtension(fileName).ToLower() == "mp3" ||
			FPaths::GetExtension(fileName).ToLower() == "wav")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string, FString>("sound", fileName));
		}

		else if (FPaths::GetExtension(fileName).ToLower() == "obj")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string, FString>("3D", fileName));
		}
	}

	return true;
}

//void FileSort::ListImagesToDisplay()
//{
//	TArray<FString> Files;
//	GetFiles(RootPath, Files, false);
//	for (auto fileName : Files)
//	{
//		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
//		// Note: PNG format.  Other formats are supported
//		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
//		TArray<uint8> RawFileData;
//
//		if (FFileHelper::LoadFileToArray(RawFileData, *fileName))
//		{
//			if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
//			{
//				const TArray<uint8>* UncompressedBGRA = NULL;
//				if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
//				{
//					m_aTextures.Add(UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8));
//				}
//			}
//		}
//	}
//	DisplayImages.Broadcast();
//}
//
