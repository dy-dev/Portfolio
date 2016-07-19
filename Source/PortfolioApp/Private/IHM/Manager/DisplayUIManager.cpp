#include "PortfolioApp.h"

#include "DisplayUIManager.h"

#include "ContentManager.h"
#include "Categories_ScrollBox.h"
#include "PortfolioPlayerController.h"
#include "Category_Button.h"




DisplayUIManager::DisplayUIManager()
	: m_pCategoryScrollBox (nullptr)
{

}


DisplayUIManager::~DisplayUIManager()
{
}

void DisplayUIManager::setCategoriesScrollBox(UCategories_ScrollBox* p_pCatSB)
{
	m_pCategoryScrollBox = p_pCatSB;
}

void DisplayUIManager::ManageExploreUI(ContentManager* p_pContentManager, APortFolioPlayerController* p_pController, UCategory_Button* p_Button)
{
	p_pContentManager->SetCurrentPathFromContentManager(p_Button->GetSubCategoryPath());
	
	auto vSortedAssociateNameToMedia = p_pContentManager->ManageContent();

	if (vSortedAssociateNameToMedia == nullptr && m_pCategoryScrollBox != nullptr)
	{
		//blue print native event -> upadte sb	
		m_pCategoryScrollBox->ClearChildren();
		m_pCategoryScrollBox->FillCatButtons(p_pController);
	}
	else
	{
		//blue print native event -> start display image

		//displayFrame
	}
}