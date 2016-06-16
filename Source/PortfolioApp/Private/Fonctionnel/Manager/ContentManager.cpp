#include "PortfolioApp.h"

#include "ContentManager.h"
#include "../../../Public/Fonctionnel/FileSort/FileSort.h"


//#include "ImageLoader.h"
//#include "ImagesHolder.h"
//#include "Runtime/Engine/Public/DDSLoader.h"
//#include <string>


ContentManager::ContentManager()
{
	m_pFileSort = new FileSort();

}


ContentManager::~ContentManager()
{
	if (m_pFileSort != NULL)
	{
		delete m_pFileSort;
	}
}





