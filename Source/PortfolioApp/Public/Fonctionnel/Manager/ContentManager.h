#pragma once

#include <Runtime/Core/Public/Containers/Map.h>
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
	TArray<TPair < FString, UMedia* >>* ManageContent();


private :
	FileSort* m_pFileSort;
	DirectoryManager* m_pDirectoryManager;

};

