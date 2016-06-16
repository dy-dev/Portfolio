#pragma once

#include "../../../Public/Fonctionnel/FileSort/FileSort.h"


class ObjectManager;

class ContentManager
{
public:
	ContentManager();
	~ContentManager();

	//void ContentManager::beginManageContent();

private :
	FileSort* m_pFileSort;
};

