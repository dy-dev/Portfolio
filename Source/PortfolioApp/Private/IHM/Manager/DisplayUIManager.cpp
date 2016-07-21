#include "PortfolioApp.h"

#include "DisplayUIManager.h"
#include <Runtime/Core/Public/Containers/Map.h>

#include "ContentManager.h"
#include "Categories_ScrollBox.h"
#include "PortfolioPlayerController.h"
#include "Category_Button.h"




UDisplayUIManager::UDisplayUIManager()
	: m_pCategoryScrollBox(nullptr)
{

}


UDisplayUIManager::~UDisplayUIManager()
{
}

void UDisplayUIManager::setCategoriesScrollBox(UCategories_ScrollBox* p_pCatSB)
{
	m_pCategoryScrollBox = p_pCatSB;
}

void UDisplayUIManager::setDisplayFrame(UImage* p_pDisplayFrame)
{
	m_pDisplayFrame = p_pDisplayFrame;
}

void UDisplayUIManager::ManageExploreUI(ContentManager* p_pContentManager, APortFolioPlayerController* p_pController, UCategory_Button* p_Button)
{
	p_pContentManager->SetCurrentPathFromContentManager(p_Button->GetSubCategoryPath());

	m_vSortedAssociateNameToMedia = p_pContentManager->ManageContent();


	if (m_vSortedAssociateNameToMedia == nullptr && m_pCategoryScrollBox != nullptr)
	{
		//blue print native event -> upadte sb	
		/*m_pCategoryScrollBox->ClearChildren();
		m_pCategoryScrollBox->FillCatButtons(p_pController);*/
		DUIM_UpdateScrollBox(p_pController);
	}
	else
	{
		//blue print native event -> start display image
		setArrayOfMedia(m_vSortedAssociateNameToMedia);
		DUIM_DisplayImage(p_pController);
		//displayFrame
	}
}

void UDisplayUIManager::setArrayOfMedia(TArray<TPair < FString, UMedia* >>* p_vSortedAssociateNameToMedia)
{
	for (auto media : *p_vSortedAssociateNameToMedia)
	{
		m_vArrayOfMedia.Add(media.Value);
	}
}