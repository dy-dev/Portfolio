#include "PortfolioApp.h"

#include "../../../Public/Fonctionnel/FileSort/FileSort.h"

#include "PortfolioApp.h"
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

	m_mExtensionPathMap.insert(std::pair<const std::string, FString>("jpeg", "imagePath1"));
	
	//m_mPathMap["picture"] = m_sPicturePathArray;
	//m_mPathMap["anim"] = m_sAnimPathArray;
	//m_mPathMap["sound"] = m_sSoundPathArray;
	//m_mPathMap["3D"] = m_s3DPathArray;

	for (auto fileName : Files) //For each file 
	{
		if (FPaths::GetExtension(p_sPath).ToLower() == "jpg" ||
			FPaths::GetExtension(p_sPath).ToLower() == "jpeg" ||
			FPaths::GetExtension(p_sPath).ToLower() == "png" ||
			FPaths::GetExtension(p_sPath).ToLower() == "bmp")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string , FString>("picture", fileName));
		}

		else if (FPaths::GetExtension(p_sPath).ToLower() == "mp4" ||
			FPaths::GetExtension(p_sPath).ToLower() == "mpeg4" ||
			FPaths::GetExtension(p_sPath).ToLower() == "avi")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string, FString>("anim", fileName));
		}

		else if (FPaths::GetExtension(p_sPath).ToLower() == "mp3" ||
			FPaths::GetExtension(p_sPath).ToLower() == "wav")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string, FString>("sound", fileName));
		}

		else if (FPaths::GetExtension(p_sPath).ToLower() == "obj")
		{
			m_mExtensionPathMap.insert(std::pair<const std::string, FString>("3D", fileName));
		}
	}

	return true;
}

