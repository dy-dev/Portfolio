#pragma once

class APortFolioPlayerController;
	class UCategories_ScrollBox;

class DisplayUIManager
{
public:
	DisplayUIManager();
	~DisplayUIManager();

	void ManageUI(UCategories_ScrollBox* p_pScrollBox, APortFolioPlayerController* p_pController);
};

