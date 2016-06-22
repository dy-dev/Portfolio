#include "PortfolioApp.h"

#include "DirectoryManager.h"
#include "DirectoryVisitor.h"
#include "FileSort.h"

#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "Runtime/UMG/Public/Components/Button.h" 

#include <string>


DirectoryManager::DirectoryManager()
	: RootPath(FPaths::Combine(*FPaths::GameSavedDir(), TEXT("DiapoAssets")))
	, m_sCurrentPath(RootPath)
{

}


DirectoryManager::~DirectoryManager()
{
}



TArray<FString> DirectoryManager::GetSubDirectories()
{
	TArray<FString> DirNamesOut;
	if (FPaths::DirectoryExists(RootPath))
	{
		//IFileManager& FileManager = IFileManager::Get();
		
		TArray<FString> Files;
		if (RootPath.Len() > 1)
		{
			FPaths::NormalizeDirectoryName(RootPath);
			FString FinalPath = RootPath;// +"/" + "*.*";
			GetDirectories(FinalPath, DirNamesOut, false);
		}
	}

	return DirNamesOut;
}
