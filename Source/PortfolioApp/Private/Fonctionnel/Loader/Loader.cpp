#include "PortfolioApp.h"

#include "Loader.h"
#include "ImageLoader.h"
#include "ImagesHolder.h"
#include "Runtime/Engine/Public/DDSLoader.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"

#include "DirectoryVisitor.h"

#include <string>

Loader::Loader()
{
}


Loader::~Loader()
{
}


void Loader::Load(FString p_sPath, UImagesHolder* p_pHolder)
{

	TArray<uint8> RawFileData;

	if (FFileHelper::LoadFileToArray(RawFileData, *p_sPath)) //put all the data in RawFileData
	{
		if (FPaths::GetExtension(p_sPath).ToLower() == "jpg" ||
			FPaths::GetExtension(p_sPath).ToLower() == "jpeg" ||
			FPaths::GetExtension(p_sPath).ToLower() == "png" ||
			FPaths::GetExtension(p_sPath).ToLower() == "bmp")
		{
			ImageLoader(p_sPath, p_pHolder);
		}

		else if (FPaths::GetExtension(p_sPath).ToLower() == "mp4" ||
			FPaths::GetExtension(p_sPath).ToLower() == "mpeg4" ||
			FPaths::GetExtension(p_sPath).ToLower() == "avi")
		{
			//to do : VideoManager
		}

		//else if 3D, sounds objects
	}
}


void Loader::ImageLoader(FString p_sPath, UImagesHolder* p_pHolder)
{

}
						
FString Loader::CreateSearchPaths(FString p_sPath)
{
	ImagesPaths = p_sPath;
	if (FPaths::DirectoryExists(p_sPath))//If the folder exists
	{
		IFileManager& FileManager = IFileManager::Get();
		if (p_sPath.Len() > 1)//Minimum count of letters of the folder must be 2
		{
			FPaths::NormalizeDirectoryName(p_sPath);
			FString FinalPath = p_sPath;// +"/" + "*.*";

			if (FPaths::GetExtension(fileName).ToLower() != "db") //if the extension isn't .db
			{
				FString filePath = FPaths::Combine(*FinalPath, *fileName); //create the full path of the file
				std::string strfileName(TCHAR_TO_ANSI(*filePath));

				return filePath;
			}

		}
	}
}