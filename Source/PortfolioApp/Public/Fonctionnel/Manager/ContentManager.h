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

	TArray<FString> GetSubDirectoriesFromContentManager();
	void SetCurrentPathFromContentManager(FString p_sPath);
	TArray<std::pair < FString, Media* >>* ManageContent();


private :
	FileSort* m_pFileSort;
	DirectoryManager* m_pDirectoryManager;

};

