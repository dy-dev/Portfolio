#pragma once


#include <Runtime/Core/Public/Containers/Map.h>
#include <utility>
#include "Object.h"
#include "Media.h"
#include "DisplayUIManager.generated.h"



class APortFolioPlayerController;
class UCategories_ScrollBox;
class ContentManager;
class UCategory_Button;
class UCategory_ScrollBox;
class UMedia;
class UImage;



/**
*
*/
UCLASS(Blueprintable)
class PORTFOLIOAPP_API UDisplayUIManager : public UObject
{
	GENERATED_BODY()

public:
	UDisplayUIManager();
	~UDisplayUIManager();

	void ManageExploreUI(ContentManager* p_pContentManager, APortFolioPlayerController* p_pController, UCategory_Button* p_Button);
	void setCategoriesScrollBox(UCategories_ScrollBox* p_pCatSB);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayUIManager")
	UCategories_ScrollBox* m_pCategoryScrollBox;

	void setDisplayFrame(UImage* p_pDisplayFrame);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayUIManager")
		UImage* m_pDisplayFrame;

	UFUNCTION(BlueprintImplementableEvent)
		void DUIM_UpdateScrollBox(APortFolioPlayerController* p_pController);

	UFUNCTION(BlueprintImplementableEvent)
		void DUIM_DisplayImage(APortFolioPlayerController* p_pController);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisplayUIManager")
		TArray<UMedia*> m_vArrayOfMedia;

	void setArrayOfMedia(TArray<TPair < FString, UMedia* >>* p_vSortedAssociateNameToMedia);

	TArray<TPair < FString, UMedia* >>* m_vSortedAssociateNameToMedia;

};

