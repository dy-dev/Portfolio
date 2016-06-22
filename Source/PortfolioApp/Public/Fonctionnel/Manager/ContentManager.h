#pragma once

#include "FileSort.h"


class ObjectManager;
class FileSort;
class DirectoryManager;

class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	//void ContentManager::beginManageContent();
	TArray<FString> GetSubDirectoriesFromContentManager();

private :
	FileSort* m_pFileSort;
	DirectoryManager* m_pDirectoryManager;
};

