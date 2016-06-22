#include "PortfolioApp.h"

#include "ContentManager.h"
#include "FileSort.h"
#include "DirectoryManager.h"


//#include "ImageLoader.h"
//#include "ImagesHolder.h"
//#include "Runtime/Engine/Public/DDSLoader.h"
//#include <string>


ContentManager::ContentManager()
{
	m_pDirectoryManager = new DirectoryManager();
	m_pFileSort = new FileSort();

	if (m_pDirectoryManager->GetSubDirectories().Num() == 0)
	{
		m_pFileSort->sortArray(m_pDirectoryManager->GetCurrentPath() );
	}
}


ContentManager::~ContentManager()
{
	if (m_pFileSort != NULL)
	{
		delete m_pFileSort;
	}
}

TArray<FString> ContentManager::GetSubDirectoriesFromContentManager() 
{ 
	return m_pDirectoryManager->GetSubDirectories(); 
};






