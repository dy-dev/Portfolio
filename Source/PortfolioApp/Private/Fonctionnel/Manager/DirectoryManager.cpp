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


void DirectoryManager::SetCurrentPath(FString p_sPath)
{
	m_sCurrentPath = p_sPath;
}



TArray<FString> DirectoryManager::GetSubDirectories()
{
	TArray<FString> DirNamesOut;
	if (FPaths::DirectoryExists(m_sCurrentPath))
	{
		TArray<FString> Files;
		if (m_sCurrentPath.Len() > 1)
		{
			FPaths::NormalizeDirectoryName(m_sCurrentPath);
			FString FinalPath = m_sCurrentPath;
			GetDirectories(FinalPath, DirNamesOut, false);
		}
	}

	return DirNamesOut;
}
