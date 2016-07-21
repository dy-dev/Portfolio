#include "PortfolioApp.h"

#include "ContentManager.h"
#include "FileSort.h"
#include "DirectoryManager.h"
#include "DisplayUIManager.h"



//#include "ImageLoader.h"
//#include "ImagesHolder.h"
//#include "Runtime/Engine/Public/DDSLoader.h"
//#include <string>


ContentManager::ContentManager()
{
	m_pDirectoryManager = new DirectoryManager();
	m_pFileSort = new FileSort();
}


ContentManager::~ContentManager()
{
	if (m_pFileSort != NULL)
	{
		delete m_pFileSort;
	}
}

void ContentManager::SetCurrentPathFromContentManager(FString p_sPath)
{
	m_pDirectoryManager->SetCurrentPath(p_sPath);
}

TArray<TPair < FString, UMedia* >>* ContentManager::ManageContent()
{
	if (m_pDirectoryManager->GetSubDirectories().Num() == 0)
	{
		return &(m_pFileSort->PrepareFiles(m_pDirectoryManager->GetCurrentPath()));
	}
	return nullptr;
}

TArray<FString> ContentManager::GetSubDirectoriesFromContentManager()
{
	return m_pDirectoryManager->GetSubDirectories();
};






