#pragma once

#include "FileSort.h"


class ObjectManager;
class FileSort;

class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	//void ContentManager::beginManageContent();

private :
	FileSort* m_pFileSort;
};

