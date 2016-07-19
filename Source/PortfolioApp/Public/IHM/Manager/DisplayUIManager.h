#pragma once

class APortFolioPlayerController;
class UCategories_ScrollBox;
class ContentManager;
class UCategory_Button;
class UCategory_ScrollBox;

class DisplayUIManager
{
public:
	DisplayUIManager();
	~DisplayUIManager();

	void ManageExploreUI(ContentManager* p_pContentManager, APortFolioPlayerController* p_pController, UCategory_Button* p_Button);
	void setCategoriesScrollBox(UCategories_ScrollBox* p_pCatSB);

private:
	UCategories_ScrollBox* m_pCategoryScrollBox;
};

